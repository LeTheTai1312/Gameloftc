#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Texture.h"
#include "Shaders.h"
#include <vector>
#include<iostream>

using namespace std;

class model
{
public:
	float pos, normal, binormal, tangent, uv;
	int n, nr, num_vertice, num_indice;
	void init(char* l);
	Vertex *vertices;
	int *indices;

	GLuint vboId, iboId;




	model();
	~model();

private:

};

