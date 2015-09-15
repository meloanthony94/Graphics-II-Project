#pragma once
#include "Defines.h"

class Object
{


public:
	Object();
	~Object();
	void CreateStar(vector<Send_To_VRAM> & me, vector<unsigned int> * indicies);
	bool LoadObject(char * path, vector< Send_To_VRAM > *out_vertices, vector< XMFLOAT2 > *out_uvs, vector< XMFLOAT3 > *out_normals, vector< unsigned int > *indicies);
};

