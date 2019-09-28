#include "Material.h"

Material::Material(string materialId) {
	this->materialId = materialId;
}

void Material::setMaterialId(string materialId) {
	this->materialId = materialId;
}

void Material::setTextureFile(string textureFile) {
	this->textureFile = textureFile;
}

void Material::setKa(float r, float g, float b) {
	this->ka = glm::vec3(r, g, b);
}

void Material::setKd(float r, float g, float b) {
	this->kd = glm::vec3(r, g, b);
}

void Material::setKs(float r, float g, float b) {
	this->ks = glm::vec3(r, g, b);
}

void Material::setNs(float ns) {
	this->ns = ns;
}

string Material::getTextureFile() {
	return this->textureFile;
}

string Material::getMaterialid() {
	return this->materialId;
}

glm::vec3 Material::getKs() {
	return this->ks;
}

glm::vec3 Material::getKa() {
	return this->ka;
}

glm::vec3 Material::getKd() {
	return this->kd;
}

float Material::getNs() {
	return this->ns;
}