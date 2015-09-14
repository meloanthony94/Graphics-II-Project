#pragma once
#include "Defines.h"

class Object
{
public:
	Object();
	~Object();
	Vertex* CreateStar();
	bool LoadObject(char * path, vector< Send_To_VRAM > *out_vertices, vector< XMFLOAT2 > *out_uvs, vector< XMFLOAT3 > *out_normals, vector< unsigned int > *indicies);
};

