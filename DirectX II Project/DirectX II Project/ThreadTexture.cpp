#include "ThreadTexture.h"

void LoadME(TexutreThread * picture)
{
	CreateDDSTextureFromFile(*picture->ThreadDevice, L"bleachedWood_seamless.dds", NULL, *&picture->ThreadSRV);
}