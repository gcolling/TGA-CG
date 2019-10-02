#include "Object.h"

Object::Object(string filePath) {
	centerX = 0.0f;
	centerY = 0.0f;
	translation = glm::mat4(1);
	rotation = glm::mat4(1);
	scaling = glm::mat4(1);
	this->model = translation * rotation * scaling;

	this->selected = false;
	this->filePath = filePath;
}

bool Object::isSelected() {
	return this->selected;
}

void Object::toggleSelected() {
	this->selected = !this->selected;
}

void Object::setMesh(Mesh* mesh) {
	this->mesh = mesh;
}

Mesh* Object::getMesh() {
	return this->mesh;
}

string Object::getFilePath() {
	return this->filePath;
}

void Object::disable() {
	this->selected = false;
}

void Object::setModel(glm::mat4 model) {
	this->model = model;
}

glm::mat4 Object::getModel() {
	return this->model;
}

void Object::setTranslation(glm::mat4 translation) {
	this->translation = translation;
}

glm::mat4 Object::getTranslation() {
	return this->translation;
}

void Object::setRotation(glm::mat4 rotation) {
	this->rotation = rotation;
}

glm::mat4 Object::getRotation() {
	return this->rotation;
}

void Object::setScaling(glm::mat4 scaling) {
	this->scaling = scaling;
}

glm::mat4 Object::getScaling() {
	return this->scaling;
}

void Object::setCenter(float centerX, float centerY) {
	this->centerX = centerX;
	this->centerY = centerY;
}

vector<float> Object::getCenter() {
	vector<float> center;

	center.push_back(this->centerX);
	center.push_back(this->centerY);

	return center;
}