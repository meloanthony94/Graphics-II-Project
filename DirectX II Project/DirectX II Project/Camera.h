#pragma once
#include "Defines.h"

__declspec(align(16)) class Camera
{
	MatrixTrio Matricies;

public:
	Camera();
	~Camera();
	void InitMatrices(float width, float height);
	MatrixTrio GetMatrix(){ return Matricies; };
	void SetMatrix(MatrixTrio newMatrix, int type);
	void CameraTranslation();
	void CameraRotation();
};

