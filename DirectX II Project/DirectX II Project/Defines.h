#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")

#include "Trivial_PS.csh"
#include "Trivial_VS.csh"

#include <iostream>
#include <ctime>
#include "XTime.h"
#include <vector>

using namespace std;
using namespace DirectX;

#define BACKBUFFER_WIDTH	500
#define BACKBUFFER_HEIGHT	500

const bool Is_FullScreen = true;
const bool Is_VSync = false;

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

struct Vertex
{
	float Mrarray[4];
	unsigned int MrColor;
	float U;
	float V;
};