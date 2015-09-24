#pragma once
#include "Defines.h"

class Lights
{
	LIGHTS changeLights;
	XTime MrTimer;
	short GO;

public:
	Lights();
	~Lights();

	XMFLOAT3 DirectionalLight();
	XMFLOAT3 PointLight();
	//Lights getLights() { return changeLights; }
};

