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
};

texture2D baseTexture : register(t0);
texture2D SecondTexture : register(t1);

SamplerState filter : register(s0);

float4 main(P_IN modulate) : SV_TARGET
{
	//direction lighting
	float3 Point_glightpos = { 0, 0, 0 };
	float3 Direction_glightDir = { 1, 1, 1 };

	float3 Direction_ldir = -normalize(Direction_glightDir);
	float3 Point_ldir = -normalize(Point_glightpos - modulate.projectedCoordinate);
	float3 wnrm = normalize(modulate.norm);

	float Direction_LightRatio = clamp(dot(-Direction_ldir, wnrm), 0, 1);
	Direction_LightRatio *= 0.99f;

	float Point_LightRatio = clamp(dot(Point_ldir, modulate.norm), 0, 1);

		//MultiTexturing
		float4 baseColor = baseTexture.Sample(filter, modulate.UV.xy);
		float4 newColor = SecondTexture.Sample(filter, modulate.UV.xy);

		float4 Final = baseColor * newColor;

		//Directional Light
		float4 Direction_ambientColor = { 1, 1, 1, 1 };
		float4 Point_ambientColor = { 1, 1, 1, 1 };

		//return (LightRatio * ambientColor * Final) + 0.01f;
		return (Point_LightRatio * Point_ambientColor * Final) + ((Direction_LightRatio * Direction_ambientColor * Final) + 0.01f);

	//return Final;
}