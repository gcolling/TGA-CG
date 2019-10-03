#ifndef GROUP_H
#define GROUP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <iostream>
#include "Face.h"

using namespace std;

class Group {
private:
	string name;
	string material;
	vector<Face*> faces;
	GLuint VAO, textureIndex = 0;

public:
	int vertexLength = 0;
	Group(string name, string material);
	void setName(string name);
	void addFace(Face* face);
	void addFace(vector<int> verts, vector<int> texts, vector<int> norms);
	vector<Face*> getFaces();
	void setMaterial(string material);
	string getMaterial();
	void setTextureIndex(GLuint index);
	GLuint getTextureIndex();
	void setVAOIndex(GLuint vaoIndex);
	GLuint getVAOIndex();

};

#endif