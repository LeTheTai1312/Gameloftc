// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include"../Include/Box2D/Box2D.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "model.h"
#include "Texture.h"
#include "Object.h"
#include "Matran.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include <conio.h>
#include <iostream>


using namespace std;
GLuint vboId, iboId, textureID, matrixID;
Shaders myShaders;
Matran matrix;
Texture texture;
Objects objects;
Camera cam;
ResourceManager rsm;
SceneManager scm;



int Init ( ESContext *esContext )
{
	glClearColor (1.0f, 1.0f, 1.0f, 1.0f );
	
	rsm.loadResource("../Resources/Resource.txt");
	scm.loadObjects("../Resources/Scene.txt", rsm);
	//cout << scm.objectNum << endl;
	//cout << scm.objects[4].textureNum << endl;
	//cout << scm.objects[4].cubeTexture[0] << endl;
	cout << scm.objects[2].texture[0];
	return 0;

}

void Draw ( ESContext *esContext )
{
	scm.draw(rsm);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

bool MoveR, MoveL, MoveU, MoveD, MoveF, MoveB;
bool RotateL, RotateR, RotateU, RotateD;

void Update ( ESContext *esContext, float deltaTime )
{
	if (MoveF) {
		cout << "forward" << endl;
		scm.camera.movementF(deltaTime);
		MoveF = false;
	}
	if (MoveB) {
		cout << "Back" << endl;
		scm.camera.movementB(deltaTime);
		MoveB = false;
	}
	if (MoveL) {
		cout << "Left" << endl;
		scm.camera.movementL(deltaTime);
		MoveL = false;
	}
	if (MoveR) {
		cout << "Right" << endl;
		scm.camera.movementR(deltaTime);
		MoveR = false;
	}
	if (MoveU) {
		cout << "Up" << endl;
		scm.camera.movementU(deltaTime);
		MoveU = false;
	}
	if (MoveD) {
		cout << "Down" << endl;
		scm.camera.movementD(deltaTime);
		MoveD = false;
	}
	if (RotateL) {
		cout << "RLeft" << endl;
		scm.camera.rotationsL(deltaTime);
		RotateL = false;
	}
	if (RotateR) {
		cout << "RRight" << endl;
		scm.camera.rotationsR(deltaTime);
		RotateR = false;
	}
	if (RotateD) {
		cout << "RDown" << endl;
		scm.camera.rotationsD(deltaTime);
		RotateD = false;
	}
	if (RotateU) {
		cout << "RUp" << endl;
		scm.camera.rotationsU(deltaTime);
		RotateU = false;
	}

	//cam.rotationsR(deltaTime);

}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (key == 0x51 && bIsPressed && !MoveF) MoveF = true;
	if (key == 0x45 && bIsPressed && !MoveB) MoveB = true;
	if (key == 0x41 && bIsPressed && !RotateL) RotateL = true;
	if (key == 0x44 && bIsPressed && !RotateR) RotateR = true;
	if (key == 0x53 && bIsPressed && !RotateD) RotateD = true;
	if (key == 0x57 && bIsPressed && !RotateU) RotateU = true;
	if (key == VK_LEFT && bIsPressed && !MoveL) MoveL = true;
	if (key == VK_RIGHT && bIsPressed && !MoveR) MoveR = true;
	if (key == VK_UP && bIsPressed && !MoveU) MoveU = true;
	if (key == VK_DOWN && bIsPressed && !MoveD) MoveD = true;

}

void CleanUp()
{
	glDeleteBuffers(1, &scm.objects[0].models.vboId);
	glDeleteBuffers(1, &scm.objects[0].models.iboId);
	for (int i = 0; i < scm.objectNum; i++) {
		scm.objects[i].models.free();
		rsm.free();
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

