#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::InitMatrices(float width, float height)
{
	int fieldOfview = 65;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;
	float Yscale = 1 / tan(XMConvertToDegrees(fieldOfview * 0.5f));
	float AspectRatio = height / width;
	//float Xscale = Yscale * AspectRatio;

	Matricies.WorldMatrix = XMMatrixIdentity();
	Matricies.WorldMatrix = XMMatrixTranslation(0, 0, 2);

	Matricies.ViewMatrix = XMMatrixIdentity();

	Matricies.ProjectionMatrix = XMMatrixPerspectiveFovLH(Yscale, AspectRatio, nearPlane, farPlane);
}