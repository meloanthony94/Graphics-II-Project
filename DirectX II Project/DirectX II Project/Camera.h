#pragma once
#include "Defines.h"

__declspec(align(16)) class Camera
{
	struct MatrixTrio
	{
		XMMATRIX WorldMatrix;
		XMMATRIX ViewMatrix;
		XMMATRIX ProjectionMatrix;
	};

	MatrixTrio Matricies;

public:
	Camera();
	~Camera();
	void InitMatrices(float width, float height);
};

