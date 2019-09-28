#include "Face.h"

#include <iostream>
using namespace std;

void Face::addVertexInfo(int vertexIndex, int textureIndex, int normalIndex) {
	this->verts.push_back(vertexIndex);
	this->texts.push_back(textureIndex);
	this->norms.push_back(normalIndex);
}

void Face::setInfo(vector<int> verts, vector<int> texts, vector<int> norms) {
	this->setNorms(norms);
	this->setTexts(texts);
	this->setVerts(verts);
}

void Face::setNorms(vector<int> norms) {
	this->norms = norms;
}

void Face::setVerts(vector<int> verts) {
	this->verts = verts;
}

void Face::setTexts(vector<int> texts) {
	this->texts = texts;
}

vector<int> Face::getVerts() {
	return this->verts;
}

vector<int> Face::getNorms() {
	return this->norms;
}

vector<int> Face::getTexts() {
	return this->texts;
}