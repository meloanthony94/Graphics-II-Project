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
	float3 glightDir = {1, 1, 1};

	//float3 ldir = -normalize(glightDir);
	float3 ldir = -normalize(glightDir);
	float3 wnrm = normalize(modulate.norm);

	float LightRatio = clamp(dot(-ldir, wnrm), 0, 1);
	LightRatio *= 0.99f;

		//MultiTexturing
	float4 baseColor = baseTexture.Sample(filter, modulate.UV.xy);
	float4 newColor = SecondTexture.Sample(filter, modulate.UV.xy);
	
	float4 Final = baseColor * newColor;
	
	//Directional Light
	float4 ambientColor = { 1, 1, 1, 1 };
	
	return (LightRatio * ambientColor * Final) + 0.01f;

	//return Final;
}