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
	float farPlane = 1000.0f;
	float Yscale = 1 / tan(XMConvertToDegrees(fieldOfview * 0.5f));
	float AspectRatio = width / height;
	//float Xscale = Yscale * AspectRatio;

	Matricies.WorldMatrix = XMMatrixIdentity();
	Matricies.WorldMatrix = XMMatrixTranslation(0, 0, 5);

	Matricies.ViewMatrix = XMMatrixIdentity();
	Matricies.ViewMatrix = XMMatrixInverse(NULL, Matricies.ViewMatrix);

	Matricies.ProjectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(fieldOfview), AspectRatio, nearPlane, farPlane);
}

void Camera::SetMatrix(MatrixTrio newMatrix, int type)
{
	if (type == 1)
		Matricies.WorldMatrix = newMatrix.WorldMatrix;
	else if (type == 2)
		Matricies.ViewMatrix = newMatrix.ViewMatrix;
	else if (type == 3)
		Matricies.ProjectionMatrix = newMatrix.ProjectionMatrix;
}

void Camera::CameraTranslation()
{
	//Lab 9
	if (GetAsyncKeyState(VK_DOWN) & 1)
		Matricies.ViewMatrix = XMMatrixMultiply(XMMatrixTranslation(0, 0, 0.05f), Matricies.ViewMatrix);
	else if (GetAsyncKeyState(VK_UP) & 1)
		Matricies.ViewMatrix = XMMatrixMultiply(XMMatrixTranslation(0, 0, -0.05f), Matricies.ViewMatrix);
	else if (GetAsyncKeyState(VK_LEFT) & 1)
		Matricies.ViewMatrix = XMMatrixMultiply(XMMatrixTranslation(0.05f, 0, 0), Matricies.ViewMatrix);
	else if (GetAsyncKeyState(VK_RIGHT) & 1)
		Matricies.ViewMatrix = XMMatrixMultiply(XMMatrixTranslation(-0.05f, 0, 0), Matricies.ViewMatrix);
	else if (GetAsyncKeyState(VK_SPACE) & 1)
		Matricies.ViewMatrix = XMMatrixMultiply(XMMatrixTranslation(0, -0.1f, 0), Matricies.ViewMatrix);
	else if (GetAsyncKeyState(VK_SHIFT) & 1)
		Matricies.ViewMatrix = XMMatrixMultiply(XMMatrixTranslation(0, 0.1f, 0), Matricies.ViewMatrix);
}

void Camera::CameraRotation()
{

	if (GetAsyncKeyState(VK_NUMPAD8) & 1)
		Matricies.ViewMatrix = XMMatrixMultiply(Matricies.ViewMatrix, XMMatrixRotationX(0.1f));
	else if (GetAsyncKeyState(VK_NUMPAD5) & 1)
		Matricies.ViewMatrix = XMMatrixMultiply(Matricies.ViewMatrix, XMMatrixRotationX(-0.1f));
	else if (GetAsyncKeyState(VK_NUMPAD4) & 1)
		Matricies.ViewMatrix = XMMatrixMultiply(Matricies.ViewMatrix, XMMatrixRotationY(0.1f));
	else if (GetAsyncKeyState(VK_NUMPAD6) & 1)
		Matricies.ViewMatrix = XMMatrixMultiply(Matricies.ViewMatrix, XMMatrixRotationY(-0.1f));
	else if (GetAsyncKeyState(VK_NUMPAD7) & 1)
		Matricies.ViewMatrix = XMMatrixMultiply(Matricies.ViewMatrix, XMMatrixRotationZ(0.1f));
	else if (GetAsyncKeyState(VK_NUMPAD9) & 1)
		Matricies.ViewMatrix = XMMatrixMultiply(Matricies.ViewMatrix, XMMatrixRotationZ(-0.1f));
}