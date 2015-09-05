#pragma once
#include "Defines.h"

class Object
{
public:
	Object();
	~Object();
	bool LoadObject(char * path, vector< XMFLOAT3 > *out_vertices, vector< XMFLOAT2 > *out_uvs, vector< XMFLOAT3 > *out_normals);
};

