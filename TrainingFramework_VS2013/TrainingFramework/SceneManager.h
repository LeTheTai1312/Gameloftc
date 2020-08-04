#pragma once
#include "Object.h"
#include "ResourceManager.h"
#include "Camera.h"
#include <vector>

class SceneManager
{
public:
	int objectNum, textureNum, cubeTextureNum;
	Objects* objects;
	Camera camera;
	void loadObjects(char *l, ResourceManager RsMnger);
	void draw(ResourceManager RsMnger);
	void free();
	SceneManager();
	~SceneManager();
private:

};

