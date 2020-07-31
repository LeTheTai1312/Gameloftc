#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include <vector>
#include<iostream>
#include<stdio.h>
#include<string.h>

class Texture
{
public:
	
	GLint width, height, bpp;
	GLuint textureID;
	void loadTexture(char* l);
	Texture();
	~Texture();

private:

};
