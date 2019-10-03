#include "Face.h"

#include <iostream>
using namespace std;

void Face::addVertexInfo(int vertexIndex, int textureIndex, int normalIndex) {
	this->vertices.push_back(vertexIndex);
	this->textures.push_back(textureIndex);
	this->normals.push_back(normalIndex);
}

void Face::setInfo(vector<int> verts, vector<int> texts, vector<int> norms) {
	this->setVertices(verts);
	this->setTextures(texts);
	this->setNormals(norms);
}

void Face::setVertices(vector<int> verts) {
	this->vertices = verts;
}

vector<int> Face::getVertices() {
	return this->vertices;
}

void Face::setTextures(vector<int> texts) {
	this->textures = texts;
}

vector<int> Face::getTextures() {
	return this->textures;
}

void Face::setNormals(vector<int> norms) {
	this->normals = norms;
}

vector<int> Face::getNormals() {
	return this->normals;
}