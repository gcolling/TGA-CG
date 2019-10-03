#include "Material.h"

Material::Material(string materialId) {
	this->materialId = materialId;
}

void Material::setMaterialId(string materialId) {
	this->materialId = materialId;
}

string Material::getMaterialid() {
	return this->materialId;
}

void Material::setTextureFile(string textureFile) {
	this->textureFile = textureFile;
}

string Material::getTextureFile() {
	return this->textureFile;
}

void Material::setKa(float r, float g, float b) {
	this->ka = glm::vec3(r, g, b);
}

glm::vec3 Material::getKa() {
	return this->ka;
}

void Material::setKs(float r, float g, float b) {
	this->ks = glm::vec3(r, g, b);
}

glm::vec3 Material::getKs() {
	return this->ks;
}

void Material::setKd(float r, float g, float b) {
	this->kd = glm::vec3(r, g, b);
}

glm::vec3 Material::getKd() {
	return this->kd;
}

void Material::setNs(float ns) {
	this->ns = ns;
}

float Material::getNs() {
	return this->ns;
}