#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <glm/glm.hpp>

using namespace std;

class Material {
private:
	string materialId;
	string textureFile;
	glm::vec3 ka;
	glm::vec3 ks;
	glm::vec3 kd;
	float ns;

public:
	Material(string materialId);
	void setMaterialId(string materialId);
	void setTextureFile(string textureFile);
	void setKa(float r, float g, float b);
	void setKs(float r, float g, float b);
	void setKd(float r, float g, float b);
	void setNs(float ns);
	string getTextureFile();
	string getMaterialid();
	glm::vec3 getKa();
	glm::vec3 getKd();
	glm::vec3 getKs();
	float getNs();
};
#endif