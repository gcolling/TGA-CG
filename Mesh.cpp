#include "Mesh.h"

Mesh::Mesh() {
	Group* defaultGroup = new Group("group", "");
	this->groups.push_back(defaultGroup);
	this->mainShader = new Shader("vs.glsl", "fs.glsl");
	this->activeGroup = 0;
}

void Mesh::setObjectFile(string objectFile) {
	this->objectFile = objectFile;
}

Shader* Mesh::getShader() {
	return this->mainShader;
}

void Mesh::addTexture(float x, float y) {
	glm::vec2 mapping = glm::vec2(x, y);
	this->texture.push_back(mapping);
}

void Mesh::addNormal(float x, float y, float z) {
	glm::vec3 normal = glm::vec3(x, y, z);
	this->normals.push_back(normal);
}

void Mesh::addVertex(float x, float y, float z) {
	glm::vec3 vertex = glm::vec3(x, y, z);
	this->vertex.push_back(vertex);
}

int Mesh::newGroup(string name) {
	Group* group = new Group(name, "");
	this->groups.push_back(group);

	int groupIndex = this->groups.size() - 1;

	this->setActiveGroup(groupIndex);

	return groupIndex;
}

void Mesh::setGroupMaterialId(string material) {
	this->groups[this->activeGroup]->setMaterial(material);
}

void Mesh::setMaterialFile(string materialFile) {
	this->materialFile = materialFile;
}

string Mesh::getMaterialFile() {
	string materialFile;
	if (this->materialFile.length() > 0) {
		materialFile = this->materialFile;
	}
	else {
		materialFile = this->objectFile.substr(0, this->objectFile.find(".")) + ".mtl";
	}

	return this->materialFile;
}

void Mesh::setActiveGroup(int index) {
	this->activeGroup = index;
}

void Mesh::addFace(vector<int> verts, vector<int> texts, vector<int> norms) {
	Group* group = this->groups[this->activeGroup];
	group->addFace(verts, texts, norms);
}

void Mesh::addFace(Face* face) {
	Group* group = this->groups[this->activeGroup];
	group->addFace(face);
}

vector<Group*> Mesh::getGroups() {
	return this->groups;
}

vector<glm::vec3> Mesh::getVertex() {
	return this->vertex;
}

vector<glm::vec2> Mesh::getTexture() {
	return this->texture;
}

vector<glm::vec3> Mesh::getNormals() {
	return this->normals;
}