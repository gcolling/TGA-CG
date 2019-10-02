#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector> 
#include <iostream>
#include <glm/glm.hpp>
#include "mesh.h"

using namespace std;

class Object {
private:
	string filePath;
	Mesh* mesh;
	bool selected;
	glm::mat4 model;
	glm::mat4 translation;
	glm::mat4 rotation;
	glm::mat4 scaling;
	float centerX;
	float centerY;
public:
	Object(string filePath);
	bool isSelected();
	void toggleSelected();
	void setMesh(Mesh* mesh);
	Mesh* getMesh();
	string getFilePath();
	void disable();
	void setModel(glm::mat4 model);
	glm::mat4 getModel();
	void setTranslation(glm::mat4 translation);
	glm::mat4 getTranslation();
	void setRotation(glm::mat4 rotation);
	glm::mat4 getRotation();
	void setScaling(glm::mat4 scaling);
	glm::mat4 getScaling();
	void setCenter(float centerX, float centerY);
	vector<float> getCenter();
};

#endif