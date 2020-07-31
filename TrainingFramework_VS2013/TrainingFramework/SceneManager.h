#pragma once
#include "Object.h"
#include "ResourceManager.h"
#include "Camera.h"
#include <vector>

class SceneManager
{
public:
	int objectNum;
	Objects* objects;
	Camera camera;
	//ResourceManager RsMnger;
	void loadObjects(char *l, ResourceManager RsMnger);
	SceneManager();
	~SceneManager();
	void draw(ResourceManager RsMnger);
private:

};

