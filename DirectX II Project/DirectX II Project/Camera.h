#pragma once
#include "Defines.h"

__declspec(align(16)) class Camera
{
	MatrixTrio Matricies;

public:
	Camera();
	~Camera();
	void InitMatrices(float width, float height);
	MatrixTrio GetMatrix(){ /*Matricies.ViewMatrix = XMMatrixInverse(NULL, Matricies.ViewMatrix);*/ return Matricies; };
	void SetMatrix(MatrixTrio newMatrix, int type);
	void SetWorldMatrix(XMMATRIX newWorld){ Matricies.WorldMatrix = newWorld; }
	void CameraTranslation();
	void CameraRotation();
};

