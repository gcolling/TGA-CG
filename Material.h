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
	string getMaterialid();
	void setTextureFile(string textureFile);
	string getTextureFile();
	void setKa(float r, float g, float b);
	glm::vec3 getKa();
	void setKs(float r, float g, float b);
	glm::vec3 getKs();
	void setKd(float r, float g, float b);
	glm::vec3 getKd();
	void setNs(float ns);
	float getNs();
};
#endif