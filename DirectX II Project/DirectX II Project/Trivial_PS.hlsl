//float4 main( float3 colorFromRasterizer : COLOR ) : SV_TARGET
//{
//	return float4(colorFromRasterizer,1);
//}
struct P_IN
{
	float4 projectedCoordinate : SV_POSITION;
	float4 color : COLOR;
	float2 UV : UVCOORD;
	float3 norm : NORMAL;
	float3 Wpos : WORLDPOS;
	float3 Lpos : LOCALPOS;
	float3 DirLight : DIRECTION;
	float3 PointLight : PDIRECTION;
	float3 SpotDir : SDIRECTION;
	float3 Spotpos : SPOTPOS;
};

texture2D baseTexture : register(t0);
texture2D SecondTexture : register(t1);

SamplerState filter : register(s0);

float4 main(P_IN modulate) : SV_TARGET
{
	//spot light cone
	float3 Spot_Conedir = normalize(modulate.SpotDir);

	//light position
	float3 Spot_glightpos = { 0, 0, -0.3 };
	float3 Point_glightpos = { 0, 2, 0 };
	float3 Direction_glightDir = { 0, -1, -1 };

	//light directions 
	float3 Spot_ldir = normalize(modulate.Spotpos - modulate.Wpos);
	float3 Direction_ldir = -normalize(modulate.DirLight);
	float3 Point_ldir = normalize(modulate.PointLight - modulate.Wpos);
	float3 wnrm = normalize(modulate.norm);

	//Surface ratio
	float Spot_LightSurfaceRatio = clamp(dot(-Spot_ldir, Spot_Conedir), 0, 1);

	int Spot_Factor = (Spot_LightSurfaceRatio > 0.95F) ? 1 : 0;

	//light ratio's
	float Direction_LightRatio = clamp(dot(-Direction_ldir, wnrm), 0, 1);
	Direction_LightRatio *= 0.99f;

	float Point_LightRatio = clamp(dot(Point_ldir, wnrm), 0, 1);
	Point_LightRatio *= 0.99f;

	float Spot_LightRatio = clamp(dot(Spot_ldir, wnrm), 0, 1);

	//MultiTexturing
	float4 baseColor = baseTexture.Sample(filter, modulate.UV.xy);
		float4 newColor = SecondTexture.Sample(filter, modulate.UV.xy);

		float4 Final = baseColor * newColor;

		//Light Color
		float4 Direction_ambientColor = { 3, 3, 3, 3 };
		float4 Point_ambientColor = { 0.5f, 1, 0.5f, 1 };
		float4 Spot_ambientColor = { 1, 0.5f, 0.5f, 1 };

		if (modulate.Spotpos.x == 0 &&
			modulate.Spotpos.y == 0 &&
			modulate.Spotpos.z == 0)
			Spot_Factor = 0;
	//return (Direction_LightRatio *  Direction_ambientColor * Final) + 0.01f;
	//return (Point_LightRatio * Point_ambientColor * Final);
	//return ((Spot_Factor * Spot_LightSurfaceRatio) * Spot_ambientColor * Final);
	return saturate(((Point_LightRatio * Point_ambientColor * Final) * 0.33f) + (((Direction_LightRatio * Direction_ambientColor * Final) + 0.01f) * 0.33f) + (((Spot_Factor * Spot_LightSurfaceRatio) * Spot_ambientColor * Final) * 0.33f));

	//return Final;
}