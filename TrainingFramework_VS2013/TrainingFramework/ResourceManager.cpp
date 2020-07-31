#include "stdafx.h"
#include "ResourceManager.h"

using namespace std;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::loadResource(char* l) {
	int modelNum, modelID; char modelLink[100];
	int TDTextureNum, TDTextureID; char TDTextureLink[100];
	int cubeTextureNum, cubeTextureID; char cubeTextureLink[100], tiling[100];
	int shaderNum, shaderID; char shaderVSLink[260], shaderFSLink[260];
	FILE* file;
	file = fopen(l, "r");
	fscanf(file, "#Models: %d\n", &modelNum);
	models = new model[modelNum];
	for (int i = 0; i < modelNum; i++) {
		fscanf(file, "ID %d\n", &modelID);
		fscanf(file, "FILE %s\n", modelLink);
		models[modelID].init(modelLink);
	}
	fscanf(file, "#2D Textures: %d\n", &TDTextureNum);
	TD_Textures = new Texture[TDTextureNum];
	for (int i = 0; i < TDTextureNum; i++) {
		fscanf(file, "ID %d\n", &TDTextureID);
		fscanf(file, "FILE %s\n", TDTextureLink);
		fscanf(file, "TILING %s\n", tiling);
		TD_Textures[TDTextureID].loadTexture(TDTextureLink);
		tilingTD[TDTextureID] = tiling;
	}
	fscanf(file, "#Cube Textures: %d\n", &cubeTextureNum);
	cube_Textures = new Texture[cubeTextureNum];
	for (int i = 0; i < cubeTextureNum; i++) {
		fscanf(file, "ID %d\n", &cubeTextureID);
		fscanf(file, "FILE %s\n", cubeTextureLink);
		fscanf(file, "TILING %s\n", tiling);
		cube_Textures[cubeTextureID].loadTexture(cubeTextureLink);
		tilingCube[cubeTextureID] = tiling;
	}

	fscanf(file, "#Shaders: %d\n", &shaderNum);
	shader = new Shaders[shaderNum];
	for (int i = 0; i < shaderNum; i++) {
		fscanf(file, "ID %d\n", &shaderID);
		fscanf(file, "VS %s\n", shaderVSLink);
		fscanf(file, "FS %s\n", shaderFSLink);
		memcpy(shader[shaderID].fs, shaderFSLink, 100);
		memcpy(shader[shaderID].vs, shaderVSLink, 100);
		shader[shaderID].Init(shaderVSLink, shaderFSLink);
		//cout << shader[shaderID].fs;
	}
	fclose(file);
}