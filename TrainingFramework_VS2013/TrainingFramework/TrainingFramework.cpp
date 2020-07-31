// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "model.h"
#include "Texture.h"
#include "Object.h"
#include "Matran.h"
#include "Camera.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include <conio.h>
#include <iostream>


using namespace std;
GLuint vboId, iboId, textureID, matrixID;
Shaders myShaders;
//model models;
//model models2;
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


	//cout << scm.objects[0].shaders.fs;

	
	//models.init("../Resources/Models/Woman1.nfg");
	//buffer object
	
	/*glGenBuffers(1, &scm.objects[0].models.vboId);
	glBindBuffer(GL_ARRAY_BUFFER, scm.objects[0].models.vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*(scm.objects[0].models.num_vertice), scm.objects[0].models.vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/
	
	//glGenBuffers(1, &vboId);
	//glBindBuffer(GL_ARRAY_BUFFER, vboId);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*(models.num_vertice), models.vertices, GL_STATIC_DRAW);

	/*glGenBuffers(1, &scm.objects[0].models.iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, scm.objects[0].models.iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*scm.objects[0].models.num_indice, scm.objects[0].models.indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/

	//glGenBuffers(1, &iboId);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*models.num_indice, models.indices, GL_STATIC_DRAW);

	//texture.loadTexture("..\\Resources\\Textures\\Woman1.tga");
	//glEnable(GL_DEPTH_TEST);
	//creation of shaders and program
	//myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	//scm.objects[0].shaders.Init(scm.objects[0].shaders.vs, scm.objects[0].shaders.fs);
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
	if (key == 0x68 && bIsPressed && !MoveF) MoveF = true;
	if (key == 0x62 && bIsPressed && !MoveB) MoveB = true;
	if (key == 0x4A && bIsPressed && !RotateL) RotateL = true;
	if (key == 0x4C && bIsPressed && !RotateR) RotateR = true;
	if (key == 0x4B && bIsPressed && !RotateD) RotateD = true;
	if (key == 0x49 && bIsPressed && !RotateU) RotateU = true;
	if (key == 0x25 && bIsPressed && !MoveL) MoveL = true;
	if (key == VK_RIGHT && bIsPressed && !MoveR) MoveR = true;
	if (key == VK_UP && bIsPressed && !MoveU) MoveU = true;
	if (key == VK_DOWN && bIsPressed && !MoveD) MoveD = true;

}

void CleanUp()
{
	glDeleteBuffers(1, &scm.objects[0].models.vboId);
	glDeleteBuffers(1, &scm.objects[0].models.iboId);
	//glDeleteBuffers(1, &vboId);
	//glDeleteBuffers(1, &models.iboId);
	//glDeleteBuffers(1, &models2.vboId); glDeleteBuffers(1, &models2.iboId);
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

