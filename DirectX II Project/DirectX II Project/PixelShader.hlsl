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

TextureCube baseTexture : register(t2);
//texture2D baseTexture : register(t0);

SamplerState filter : register(s0);

float4 main(P_IN modulate) : SV_TARGET
{
	modulate.UV.y = 1 - modulate.UV.y;

	float4 baseColor = baseTexture.Sample(filter, modulate.Lpos);
	//float4 baseColor = baseTexture.Sample(filter, modulate.UV.xy);

	return baseColor;
}