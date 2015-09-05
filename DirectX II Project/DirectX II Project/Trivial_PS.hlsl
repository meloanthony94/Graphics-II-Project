//float4 main( float3 colorFromRasterizer : COLOR ) : SV_TARGET
//{
//	return float4(colorFromRasterizer,1);
//}
struct P_IN
{
	float4 projectedCoordinate : SV_POSITION;
	float3 UV : UVCOORD;
	float3 norm : NORMAL;
};

texture2D baseTexture : register(t0);
texture2D SecondTexture : register(t1);

SamplerState filter : register(s0);

float4 main(P_IN modulate) : SV_TARGET
{
	float4 baseColor = baseTexture.Sample(filter, modulate.UV.xy);

	//float4 col;
	//col.a = baseColor.b;
	//col.r = baseColor.g;
	//col.g = baseColor.r;
	//col.b = baseColor.a;

	return baseColor;
}