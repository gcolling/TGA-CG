#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector> 
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Group.h"
#include "Shader.h"

using namespace std;

class Mesh {
private:
	vector<glm::vec2> mappings;
	vector<glm::vec3> vertex;
	vector<glm::vec3> normals;
	vector<Group*> groups;
	int activeGroup;
	Shader* mainShader;
	string materialFile;
	string objectFile;

public:
	Mesh();
	void addMapping(float x, float y);
	void addVertex(float x, float y, float z);
	void addNormal(float x, float y, float z);
	int newGroup(string name);
	void setObjectFile(string objectFile);
	void setActiveGroup(int groupPointer);
	void setGroupMaterialId(string material);
	void setMaterialFile(string materialFile);
	void addFace(vector<int> verts, vector<int> texts, vector<int> norms);
	void addFace(Face* face);
	vector<Group*> getGroups();
	vector<glm::vec3> getVertex();
	vector<glm::vec3> getNormals();
	vector<glm::vec2> getMappings();
	Shader* getShader();
	string getMaterialFile();

	bool isInitialGroup = true;
};

#endif