#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}

void Object::CreateStar(vector<Send_To_VRAM> & me, vector<unsigned int> * indicies)
{
	//Vertex me[8];
	//me[0].Mrarray[0] = -0.25f;
	//me[0].Mrarray[1] = -0.25f;
	//me[0].Mrarray[2] = -0.25f;
	//me[0].Mrarray[3] = 1.0f;
	//me[0].U = 0;
	//me[0].V = 0;
	//
	//verts->push_back(me[0]);
	////3
	//me[1].Mrarray[0] = 0.25f;
	//me[1].Mrarray[1] = 0.25f;
	//me[1].Mrarray[2] = -0.25f;
	//me[1].Mrarray[3] = 1.0f;
	//me[1].U = 1;
	//me[1].V = 1;
	//verts->push_back(me[1]);
	//
	////2
	//me[2].Mrarray[0] = -0.25f;
	//me[2].Mrarray[1] = 0.25f;
	//me[2].Mrarray[2] = -0.25f;
	//me[2].Mrarray[3] = 1.0f;
	//me[2].U = 0;
	//me[2].V = 1;
	//verts->push_back(me[2]);
	//
	////Make Tirangle 2
	////0
	//me[3].Mrarray[0] = -0.25f;
	//me[3].Mrarray[1] = -0.25f;
	//me[3].Mrarray[2] = -0.25f;
	//me[3].Mrarray[3] = 1.0f;
	//me[3].U = 0;
	//me[3].V = 0;
	//
	////1
	//me[4].Mrarray[0] = 0.25f;
	//me[4].Mrarray[1] = -0.25f;
	//me[4].Mrarray[2] = -0.25f;
	//me[4].Mrarray[3] = 1.0f;
	//me[4].U = 1;
	//me[4].V = 0;
	//verts->push_back(me[1]);
	//
	////3
	//me[5].Mrarray[0] = 0.25f;
	//me[5].Mrarray[1] = 0.25f;
	//me[5].Mrarray[2] = -0.25f;
	//me[5].Mrarray[3] = 1.0f;
	//me[5].U = 1;
	//me[5].V = 1;
	//
	//
	////Make me 3
	////7
	//me[6].Mrarray[0] = 0.25f;
	//me[6].Mrarray[1] = 0.25f;
	//me[6].Mrarray[2] = 0.25f;
	//me[6].Mrarray[3] = 1.0f;
	//me[6].U = 1;
	//me[6].V = 1;
	//verts->push_back(me[6]);
	//
	////1
	//me[7].Mrarray[0] = 0.25f;
	//me[7].Mrarray[1] = -0.25f;
	//me[7].Mrarray[2] = -0.25f;
	//me[7].Mrarray[3] = 1.0f;
	//me[7].U = 0;
	//me[7].V = 0;
	//
	////3
	//me[8].Mrarray[0] = 0.25f;
	//me[8].Mrarray[1] = 0.25f;
	//me[8].Mrarray[2] = -0.25f;
	//me[8].Mrarray[3] = 1.0f;
	//me[8].U = 0;
	//me[8].V = 1;
	//
	////Make me 4
	////7,1,5
	////7
	//me[9].Mrarray[0] = 0.25f;
	//me[9].Mrarray[1] = 0.25f;
	//me[9].Mrarray[2] = 0.25f;
	//me[9].Mrarray[3] = 1.0f;
	//me[9].U = 1;
	//me[9].V = 1;
	//
	////1
	//me[10].Mrarray[0] = 0.25f;
	//me[10].Mrarray[1] = -0.25f;
	//me[10].Mrarray[2] = -0.25f;
	//me[10].Mrarray[3] = 1.0f;
	//me[10].U = 0;
	//me[10].V = 0;
	//
	////5
	//me[11].Mrarray[0] = 0.25f;
	//me[11].Mrarray[1] = -0.25f;
	//me[11].Mrarray[2] = 0.25f;
	//me[11].Mrarray[3] = 1.0f;
	//me[11].U = 1;
	//me[11].V = 0;
	//verts->push_back(me[11]);
	//
	////Make me 5
	////0,4,6
	////0
	//me[12].Mrarray[0] = -0.25f;
	//me[12].Mrarray[1] = -0.25f;
	//me[12].Mrarray[2] = -0.25f;
	//me[12].Mrarray[3] = 1.0f;
	//me[12].U = 1;
	//me[12].V = 0;
	//
	////4
	//me[13].Mrarray[0] = -0.25f;
	//me[13].Mrarray[1] = -0.25f;
	//me[13].Mrarray[2] = 0.25f;
	//me[13].Mrarray[3] = 1.0f;
	//me[13].U = 0;
	//me[13].V = 0;
	//verts->push_back(me[13]);
	//
	////6
	//me[14].Mrarray[0] = -0.25f;
	//me[14].Mrarray[1] = 0.25f;
	//me[14].Mrarray[2] = 0.25f;
	//me[14].Mrarray[3] = 1.0f;
	//me[14].U = 0;
	//me[14].V = 1;
	//verts->push_back(me[14]);
	//
	////Make me 6
	////0,6,2
	////0
	//me[15].Mrarray[0] = -0.25f;
	//me[15].Mrarray[1] = -0.25f;
	//me[15].Mrarray[2] = -0.25f;
	//me[15].Mrarray[3] = 1.0f;
	//me[15].U = 1;
	//me[15].V = 0;
	//
	////6
	//me[16].Mrarray[0] = -0.25f;
	//me[16].Mrarray[1] = 0.25f;
	//me[16].Mrarray[2] = 0.25f;
	//me[16].Mrarray[3] = 1.0f;
	//me[16].U = 0;
	//me[16].V = 1;
	//
	////2
	//me[17].Mrarray[0] = -0.25f;
	//me[17].Mrarray[1] = 0.25f;
	//me[17].Mrarray[2] = -0.25f;
	//me[17].Mrarray[3] = 1.0f;
	//me[17].U = 1;
	//me[17].V = 1;
	//
	////Make me 7
	////4,5,7
	////4 
	//me[18].Mrarray[0] = -0.25f;
	//me[18].Mrarray[1] = -0.25f;
	//me[18].Mrarray[2] = 0.25f;
	//me[18].Mrarray[3] = 1.0f;
	//me[18].U = 1;
	//me[18].V = 0;
	//
	////5
	//me[19].Mrarray[0] = 0.25f;
	//me[19].Mrarray[1] = -0.25f;
	//me[19].Mrarray[2] = 0.25f;
	//me[19].Mrarray[3] = 1.0f;
	//me[19].U = 0;
	//me[19].V = 0;
	//
	////7
	//me[20].Mrarray[0] = 0.25f;
	//me[20].Mrarray[1] = 0.25f;
	//me[20].Mrarray[2] = 0.25f;
	//me[20].Mrarray[3] = 1.0f;
	//me[20].U = 0;
	//me[20].V = 1;
	//
	////Make me 8
	////4,6,7
	////4
	//me[21].Mrarray[0] = -0.25f;
	//me[21].Mrarray[1] = -0.25f;
	//me[21].Mrarray[2] = 0.25f;
	//me[21].Mrarray[3] = 1.0f;
	//me[21].U = 1;
	//me[21].V = 0;
	//
	////7
	//me[22].Mrarray[0] = 0.25f;
	//me[22].Mrarray[1] = 0.25f;
	//me[22].Mrarray[2] = 0.25f;
	//me[22].Mrarray[3] = 1.0f;
	//me[22].U = 0;
	//me[22].V = 1;
	//
	////6
	//me[23].Mrarray[0] = -0.25f;
	//me[23].Mrarray[1] = 0.25f;
	//me[23].Mrarray[2] = 0.25f;
	//me[23].Mrarray[3] = 1.0f;
	//me[23].U = 1;
	//me[23].V = 1;
	//
	////Make me 9
	////0,1,4
	////0
	//me[24].Mrarray[0] = -0.25f;
	//me[24].Mrarray[1] = -0.25f;
	//me[24].Mrarray[2] = -0.25f;
	//me[24].Mrarray[3] = 1.0f;
	//me[24].U = 0;
	//me[24].V = 1;
	//
	////1
	//me[25].Mrarray[0] = 0.25f;
	//me[25].Mrarray[1] = -0.25f;
	//me[25].Mrarray[2] = -0.25f;
	//me[25].Mrarray[3] = 1.0f;
	//me[25].U = 1;
	//me[25].V = 1;
	//
	////4
	//me[26].Mrarray[0] = -0.25f;
	//me[26].Mrarray[1] = -0.25f;
	//me[26].Mrarray[2] = 0.25f;
	//me[26].Mrarray[3] = 1.0f;
	//me[26].U = 0;
	//me[26].V = 0;
	//
	////Make me 10
	////1,5,4
	////1
	//me[27].Mrarray[0] = 0.25f;
	//me[27].Mrarray[1] = -0.25f;
	//me[27].Mrarray[2] = -0.25f;
	//me[27].Mrarray[3] = 1.0f;
	//me[27].U = 1;
	//me[27].V = 1;
	//
	////5
	//me[28].Mrarray[0] = 0.25f;
	//me[28].Mrarray[1] = -0.25f;
	//me[28].Mrarray[2] = 0.25f;
	//me[28].Mrarray[3] = 1.0f;
	//me[28].U = 1;
	//me[28].V = 0;
	//
	////4
	//me[29].Mrarray[0] = -0.25f;
	//me[29].Mrarray[1] = -0.25f;
	//me[29].Mrarray[2] = 0.25f;
	//me[29].Mrarray[3] = 1.0f;
	//me[29].U = 0;
	//me[29].V = 0;
	//
	////me 11
	////3,2,6
	////2
	//me[30].Mrarray[0] = -0.25f;
	//me[30].Mrarray[1] = 0.25f;
	//me[30].Mrarray[2] = -0.25f;
	//me[30].Mrarray[3] = 1.0f;
	//me[30].U = 0;
	//me[30].V = 1;
	//
	////3
	//me[31].Mrarray[0] = 0.25f;
	//me[31].Mrarray[1] = 0.25f;
	//me[31].Mrarray[2] = -0.25f;
	//me[31].Mrarray[3] = 1.0f;
	//me[31].U = 1;
	//me[31].V = 1;
	//
	////6
	//me[32].Mrarray[0] = -0.25f;
	//me[32].Mrarray[1] = 0.25f;
	//me[32].Mrarray[2] = 0.25f;
	//me[32].Mrarray[3] = 1.0f;
	//me[32].U = 0;
	//me[32].V = 0;
	//
	////me 12
	////3,7,6
	////3
	//me[33].Mrarray[0] = 0.25f;
	//me[33].Mrarray[1] = 0.25f;
	//me[33].Mrarray[2] = -0.25f;
	//me[33].Mrarray[3] = 1.0f;
	//me[33].U = 1;
	//me[33].V = 1;
	//
	////7
	//me[34].Mrarray[0] = 0.25f;
	//me[34].Mrarray[1] = 0.25f;
	//me[34].Mrarray[2] = 0.25f;
	//me[34].Mrarray[3] = 1.0f;
	//me[34].U = 1;
	//me[34].V = 0;
	//
	////6
	//me[35].Mrarray[0] = -0.25f;
	//me[35].Mrarray[1] = 0.25f;
	//me[35].Mrarray[2] = 0.25f;
	//me[35].Mrarray[3] = 1.0f;
	//me[35].U = 0;
	//me[35].V = 0;

Send_To_VRAM insert;

//0
insert.Position.x = -0.25f;
insert.Position.y = -0.25f;
insert.Position.z = -0.25f;
insert.UV.x = 0;
insert.UV.y = 1;
me.push_back(insert);

//1
insert.Position.x = 0.25f;
insert.Position.y = -0.25f;
insert.Position.z = -0.25f;
insert.UV.x = 1;
insert.UV.y = 1;
me.push_back(insert);

//2
insert.Position.x = -0.25f;
insert.Position.y = 0.25f;
insert.Position.z = -0.25f;
insert.UV.x = 0;
insert.UV.y = 0;
me.push_back(insert);

//3
insert.Position.x = 0.25f;
insert.Position.y = 0.25f;
insert.Position.z = -0.25f;
insert.UV.x = 1;
insert.UV.y = 0;
me.push_back(insert);

//4
insert.Position.x = 0.25f;
insert.Position.y = 0.25f;
insert.Position.z = 0.25f;
insert.UV.x = 1;
insert.UV.y = 1;
me.push_back(insert);

//5
insert.Position.x = 0.25f;
insert.Position.y = -0.25f;
insert.Position.z = -0.25f;
insert.UV.x = 0;
insert.UV.y = 0;
me.push_back(insert);

//6
insert.Position.x = 0.25f;
insert.Position.y = 0.25f;
insert.Position.z = -0.25f;
insert.UV.x = 0;
insert.UV.y = 1;
me.push_back(insert);

//7
insert.Position.x = 0.25f;
insert.Position.y = -0.25f;
insert.Position.z = 0.25f;
insert.UV.x = 1;
insert.UV.y = 0;
me.push_back(insert);

//8
insert.Position.x = -0.25f;
insert.Position.y = -0.25f;
insert.Position.z = -0.25f;
insert.UV.x = 1;
insert.UV.y = 1;
me.push_back(insert);

//9
insert.Position.x = -0.25f;
insert.Position.y = -0.25f;
insert.Position.z = 0.25f;
insert.UV.x = 0;
insert.UV.y = 1;
me.push_back(insert);

//10
insert.Position.x = -0.25f;
insert.Position.y = 0.25f;
insert.Position.z = 0.25f;
insert.UV.x = 0;
insert.UV.y = 0;
me.push_back(insert);

//11
insert.Position.x = -0.25f;
insert.Position.y = 0.25f;
insert.Position.z = -0.25f;
insert.UV.x = 1;
insert.UV.y = 0;
me.push_back(insert);

//12
insert.Position.x = -0.25f;
insert.Position.y = 0.25f;
insert.Position.z = 0.25f;
insert.UV.x = 1;
insert.UV.y = 0;
me.push_back(insert);

//13
insert.Position.x = -0.25f;
insert.Position.y = -0.25f;
insert.Position.z = 0.25f;
insert.UV.x = 1;
insert.UV.y = 1;
me.push_back(insert);

//14
insert.Position.x = 0.25f;
insert.Position.y = 0.25f;
insert.Position.z = 0.25f;
insert.UV.x = 0;
insert.UV.y = 0;
me.push_back(insert);

//15
insert.Position.x = 0.25f;
insert.Position.y = -0.25f;
insert.Position.z = 0.25f;
insert.UV.x = 0;
insert.UV.y = 1;
me.push_back(insert);

//16
insert.Position.x = -0.25f;
insert.Position.y = 0.25f;
insert.Position.z = 0.25f;
insert.UV.x = 0;
insert.UV.y = 0;
me.push_back(insert);

//17
insert.Position.x = 0.25f;
insert.Position.y = 0.25f;
insert.Position.z = 0.25f;
insert.UV.x = 1;
insert.UV.y = 0;
me.push_back(insert);

//18
insert.Position.x = -0.25f;
insert.Position.y = 0.25f;
insert.Position.z = -0.25f;
insert.UV.x = 0;
insert.UV.y = 1;
me.push_back(insert);

//19
insert.Position.x = 0.25f;
insert.Position.y = 0.25f;
insert.Position.z = -0.25f;
insert.UV.x = 1;
insert.UV.y = 1;
me.push_back(insert);

//20
insert.Position.x = -0.25f;
insert.Position.y = -0.25f;
insert.Position.z = 0.25f;
insert.UV.x = 0;
insert.UV.y = 1;
me.push_back(insert);

//21
insert.Position.x = -0.25f;
insert.Position.y = -0.25f;
insert.Position.z = -0.25f;
insert.UV.x = 0;
insert.UV.y = 0;
me.push_back(insert);

//22
insert.Position.x = 0.25f;
insert.Position.y = -0.25f;
insert.Position.z = 0.25f;
insert.UV.x = 1;
insert.UV.y = 1;
me.push_back(insert);

//23
insert.Position.x = 0.25f;
insert.Position.y = -0.25f;
insert.Position.z = -0.25f;
insert.UV.x = 1;
insert.UV.y = 0;
me.push_back(insert);

//indacies
	indicies->push_back(2);
	indicies->push_back(3);
	indicies->push_back(1);

	indicies->push_back(2);
	indicies->push_back(1);
	indicies->push_back(0);

	indicies->push_back(4);
	indicies->push_back(5);
	indicies->push_back(6);

	indicies->push_back(7);
	indicies->push_back(5);
	indicies->push_back(4);

	indicies->push_back(10);
	indicies->push_back(11);
	indicies->push_back(8);

	indicies->push_back(10);
	indicies->push_back(8);
	indicies->push_back(9);

	indicies->push_back(14);
	indicies->push_back(12);
	indicies->push_back(13);
	
	indicies->push_back(14);
	indicies->push_back(13);
	indicies->push_back(15);
	
	indicies->push_back(16);
	indicies->push_back(17);
	indicies->push_back(19);
	
	indicies->push_back(16);
	indicies->push_back(19);
	indicies->push_back(18);
	
	indicies->push_back(21);
	indicies->push_back(23);
	indicies->push_back(22);
	
	indicies->push_back(21);
	indicies->push_back(22);
	indicies->push_back(20);
}

bool Object::LoadObject(char * path, vector< Send_To_VRAM > *out_vertices, vector< XMFLOAT2 > *out_uvs, vector< XMFLOAT3 > *out_normals, vector< unsigned int > *indicies)
{
	vector<unsigned int> vertexIndices, uvIndices, normalIndices;

	vector< XMFLOAT3 > temp_vertices;
	vector< XMFLOAT2 > temp_uvs;
	vector< XMFLOAT3 > temp_normals;

	FILE * file;
	
	fopen_s(&file, path, "r");

	if (file == NULL)
	{
		printf("Impossible to open the file !\n");
		return false;
	}

	while (true)
	{
		// read the first word of the line
		char lineHeader[128];
		int result = fscanf(file, "%s", lineHeader);

		if (result == EOF)
			break; // EOF = End Of File. Quit the loop.

		if (strcmp(lineHeader, "v") == 0)
		{
			XMFLOAT3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			XMFLOAT2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			XMFLOAT3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	//CheckVerts = NULL;

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		bool equal = false;

		XMFLOAT3 vertex = temp_vertices[vertexIndex - 1];
		XMFLOAT2 uv = temp_uvs[uvIndex - 1];
		XMFLOAT3 normal = temp_normals[normalIndex - 1];

		Send_To_VRAM out;
		out.UV = uv;
		out.norms = normal;
		out.Position = vertex;

		out_vertices->push_back(out);

		//nested if's
	//for (size_t j = 0; j < out_vertices->size(); j++)
	//{
	//	if ((*out_vertices)[j].Position.x == out.Position.x)
	//	{
	//		if ((*out_vertices)[j].Position.y == out.Position.y)
	//			if ((*out_vertices)[j].Position.z == out.Position.z)
	//			{
	//				equal = true;
	//				break;
	//			}
	//	}
	//
	//	//if ((*out_vertices)[j].UV.x == out.UV.x)
	//	//	if ((*out_vertices)[j].UV.y == out.UV.y)
	//	// if ((*out_vertices)[j].norms.x == out.norms.x)
	//	//{
	//	//	if ((*out_vertices)[j].norms.y == out.norms.y)
	//	//		if ((*out_vertices)[j].norms.z == out.norms.z)
	//	//			count++;
	//	//
	//}

		//if (!equal)
		//out_vertices->push_back(out);

		//indicies->push_back(vertexIndex);
		//out_uvs->push_back(uv);
		//out_normals->push_back(normal);
	}
	
	*indicies = vertexIndices;
	return true;
}