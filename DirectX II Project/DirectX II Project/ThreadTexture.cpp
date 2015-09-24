#include "ThreadTexture.h"

void LoadME(TexutreThread * picture)
{
	CreateDDSTextureFromFile(*picture->ThreadDevice, L"Gotham_Skyline_BuildingBLock01_D.dds", NULL, *&picture->ThreadSRV);
}

void ThreadDrawSpidey(TexutreThread * model)
{
	(*model->ThreadContext)->Draw(26940, 0);
}