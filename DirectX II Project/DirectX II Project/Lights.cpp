#include "Lights.h"


Lights::Lights()
{
	MrTimer.Signal();
	GO = -1;
}


Lights::~Lights()
{

}

XMFLOAT3 Lights::DirectionalLight()
{
	if (changeLights.dir.x < 10.0f && changeLights.dir.y == 10.0f)
	{
		changeLights.dir.x += MrTimer.SmoothDelta() * 4000;
		//changeLights.dir.y += MrTimer.SmoothDelta() * 1000;

		if (changeLights.dir.x > 10.0f)
			changeLights.dir.x = 10.0f;
	}
	else if (changeLights.dir.x == 10.0f && changeLights.dir.y > -10.0f)
	{
		changeLights.dir.y -= MrTimer.SmoothDelta() * 4000;
		//changeLights.dir.y -= MrTimer.SmoothDelta() * 1000;

		if (changeLights.dir.y < -10.0f)
 			changeLights.dir.y = -10.0f;
	}
	else if (changeLights.dir.x > -10.0f && changeLights.dir.y == -10.0f)
	{
		changeLights.dir.x -= MrTimer.SmoothDelta() * 4000;
		//changeLights.dir.y += MrTimer.SmoothDelta() * 1000;

		if (changeLights.dir.x < -10.0f)
			changeLights.dir.x = -10.0f;
	}
	else if (changeLights.dir.x == -10.0f && changeLights.dir.y <= 10.0f)
	{
		changeLights.dir.y += MrTimer.SmoothDelta() * 4000;
		//changeLights.dir.y -= MrTimer.SmoothDelta() * 1000;

		if (changeLights.dir.y > 10.0f)
			changeLights.dir.y = 10.0f;
	}

	return changeLights.dir;
}

XMFLOAT3 Lights::PointLight()
{
	if (changeLights.point.x > -3.0f && changeLights.point.z == 0.0f)
	{
		changeLights.point.x -= MrTimer.SmoothDelta() * 3000;

		if (changeLights.point.x < -3.0f)
			changeLights.point.x = -3.0f;

		//changeLights.point.y += MrTimer.SmoothDelta() * 1000;
	}
	else if (changeLights.point.x == -3.0f && changeLights.point.z > -5.0f)
	{
		changeLights.point.z -= MrTimer.SmoothDelta() * 3000;
 
		if (changeLights.point.z < -5.0f)
			changeLights.point.z = -5.0f;
	}
	else if (changeLights.point.x == -3.0f && changeLights.point.z < 0.0f)
	{
		changeLights.point.z += MrTimer.SmoothDelta() * 3000;

		if (changeLights.point.z > 0.0f)
			changeLights.point.z = 0.0f;
	}
	else if (changeLights.point.z == 0.0f && changeLights.point.x < 3.0f)
	{
		changeLights.point.x += MrTimer.SmoothDelta() * 3000;

		if (changeLights.point.x > 3.0f)
			changeLights.point.x = 3.0f;
	}

	return changeLights.point;
}