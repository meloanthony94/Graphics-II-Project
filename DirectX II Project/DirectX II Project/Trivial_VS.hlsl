#pragma pack_matrix(row_major)

struct INPUT_VERTEX
{
	float3 coordinate : POSITION;
	float4 color : COLOR;
	float2 UV : UVCOORD;
	float3 norm : NORMAL;
};

struct OUTPUT_VERTEX
{
	float4 projectedCoordinate : SV_POSITION;
	float4 color : COLOR;
	float2 UV : UVCOORD;
	float3 norm : NORMAL;
	float3 Wpos : WORLDPOS;
};

// TODO: PART 3 STEP 2a
cbuffer THIS_IS_VRAM : register(b0)
{
	float3 constantOffset;
	float1 padding;
	float4 constantColor;
	float2 UV;
	float3 norms;
	//float3 instance;
};

cbuffer MatrixTrio : register(b1)
{
	float4x4 WorldMatrix;
	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;
};

OUTPUT_VERTEX main(INPUT_VERTEX fromVertexBuffer)
{
	OUTPUT_VERTEX output = (OUTPUT_VERTEX)0;

	float4 newVertex = float4(fromVertexBuffer.coordinate, 1);

	newVertex = mul(newVertex, WorldMatrix);
	output.Wpos = newVertex.xyz;
	newVertex = mul(newVertex, ViewMatrix);
	newVertex = mul(newVertex, ProjectionMatrix);
   
	//output.colorOut = fromVertexBuffer.colorOut;
	output.projectedCoordinate = newVertex;
	output.UV = fromVertexBuffer.UV;
	output.UV.y = 1 - fromVertexBuffer.UV.y;

	output.norm = mul(float4(fromVertexBuffer.norm,0), WorldMatrix).xyz;
	//output.norm.y = 1 - output.norm.y;
	return output;
}