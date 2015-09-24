#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "DDSTextureLoader.h"

#pragma comment(lib, "d3d11.lib")

#include "Trivial_PS.csh"
#include "Trivial_VS.csh"
#include "PixelShader.csh"
#include "VertexShaderInstance.csh"

#include <iostream>
#include <ctime>
#include "XTime.h"
#include <thread>
#include <vector>

using namespace std;
using namespace DirectX;

#define BACKBUFFER_WIDTH	500
#define BACKBUFFER_HEIGHT	500

struct MatrixTrio
{
	XMMATRIX WorldMatrix;
	XMMATRIX ViewMatrix;
	XMMATRIX ProjectionMatrix;
};

struct Send_To_VRAM
{
	XMFLOAT3 Position;
	XMFLOAT4 Color;
	XMFLOAT2 UV;
	XMFLOAT3 norms;
};

struct LIGHTS
{
	XMFLOAT3 dir = { -10, 10, 0 };
	float padding1;
	XMFLOAT3 point = { 3, 0, 0 };
	float padding2;
	XMFLOAT3 SpotPos;
	float padding3;
	XMFLOAT3 SpotDir;
	float padding4;
};

struct Vertex
{
	float Mrarray[4];
	unsigned int MrColor;
	float U;
	float V;
};

struct TexutreThread
{
	ID3D11Device ** ThreadDevice;
	ID3D11ShaderResourceView ** ThreadSRV;
	ID3D11DeviceContext ** ThreadContext;
};

struct Thingys
{
	XMMATRIX WorldMatrix;
	XMFLOAT3 Pos;
	XMFLOAT3 Rotation;
};

struct NewGuys
{
	XMFLOAT4X4 NewOne[2];
};