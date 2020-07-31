#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::loadObjects(char *l, ResourceManager RsMnger) {
	int ob, objectID, modelID, textureNum, textureID, cubeTextureNum, cubeTextureID, shaderID;
	FILE *file;
	file = fopen(l, "r");
	fscanf(file, "#Objects: %d\n", &objectNum);
	//cout << objectNum;
	objects = new Objects[objectNum];
	for(int i = 0; i < objectNum; i++){
		//Objects *o;
		//objects.push_back(o);
		fscanf(file, "ID %d\n", &objectID);
		fscanf(file, "MODEL %d\n", &modelID);
		objects[objectID].models = RsMnger.models[modelID];
		fscanf(file, "TEXTURES %d\n", &textureNum);
		objects[objectID].texture = new int[textureNum];
		objects[objectID].textureNum = textureNum;
		for (int j = 0; j < textureNum; j++) {
			fscanf(file, "TEXTURE %d\n", &textureID);
			objects[objectID].texture[j] = textureID;
			//objects[objectID].texture[textureID] = RsMnger.TD_Textures[textureID];
		}
		fscanf(file, "CUBETEXTURES %d\n", &cubeTextureNum);
		objects[objectID].cubeTexture = new int[cubeTextureNum];
		for (int j = 0; j < cubeTextureNum; j++) {
			fscanf(file, "CUBETEX %d\n", &cubeTextureID);
			objects[objectID].cubeTexture[j] = cubeTextureID;
			//objects[objectID].cubeTexture[cubeTextureID] = RsMnger.cube_Textures[cubeTextureID];
		}
		fscanf(file, "SHADER %d\n", &shaderID);
		objects[objectID].shaders = RsMnger.shader[shaderID];
		//cout << objects[objectID].shaders.vs << endl;
		//cout << shaderID << endl;
		//cout << objects[objectID].shaders.fs << endl;
		fscanf(file, "POSITION %f, %f, %f\n", &objects[objectID].txw, &objects[objectID].tyw, &objects[objectID].tzw);
		fscanf(file, "ROTATION %f, %f, %f\n", &objects[objectID].rxw, &objects[objectID].ryw, &objects[objectID].rzw);
		fscanf(file, "SCALE %f, %f, %f\n", &objects[objectID].sxw, &objects[objectID].syw, &objects[objectID].szw);

		//cout << objects[objectID].tyw;
	}

	fscanf(file, "#CAMERA\nNEAR %f\nFAR %f\nFOV %f\nSPEED %f", &camera.nearPlane, &camera.farPlane, &camera.fov, &camera.speed);
	fclose(file);

}

void SceneManager::draw(ResourceManager RsMnger) {
	camera.set_CamVP();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < objectNum; i++) {
		
		objects[i].set_matrix(camera.camera_VP);
		glUseProgram(objects[i].shaders.program);
		glUniformMatrix4fv(objects[i].shaders.WVP, 1, GL_FALSE, &objects[i].wvpMatrix.m[0][0]);

		glBindBuffer(GL_ARRAY_BUFFER, objects[i].models.vboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objects[i].models.iboId);

		if (objects[i].shaders.positionAttribute != -1)
		{
			glEnableVertexAttribArray(objects[i].shaders.positionAttribute);
			glVertexAttribPointer(objects[i].shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		}
		if (objects[i].shaders.uvAttribute != -1)
		{
			glEnableVertexAttribArray(objects[i].shaders.uvAttribute);
			glVertexAttribPointer(objects[i].shaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)0 + sizeof(Vector3)
				+ sizeof(Vector3) + sizeof(Vector3) + sizeof(Vector3));
		}

		for (int j = 0; j < objects[i].textureNum; j++) {
			glBindTexture(GL_TEXTURE_2D, RsMnger.TD_Textures[objects[i].texture[0]].textureID);
			int iTextureLoc = glGetUniformLocation(objects[i].shaders.program, "u_texture");
			glUniform1i(iTextureLoc, 0);
		}
	
		glDrawElements(GL_TRIANGLES, objects[i].models.num_indice, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//glBindTexture(GL_TEXTURE_2D, 0);
	}
	

}
