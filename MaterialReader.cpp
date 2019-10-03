#include "MaterialReader.h"

MaterialReader::MaterialReader(string filename) {
	this->filename = filename;
	this->file.open(filename);

	if (this->file.fail()) {
		printf("Problem while opening material file\n");
		this->success = false;
	}
	else {
		this->success = true;
	}
};

vector<Material*> MaterialReader::readFile() {
	vector<Material*> materials;

	if (!success) {
		return materials;
	}

	int index = 0;

	while (!this->file.eof()) {
		string line;
		getline(this->file, line);

		stringstream sline;
		sline << line;
		string temp;
		sline >> temp;

		if (temp == "newmtl") {
			string materialName;
			sline >> materialName;
			Material* material = new Material(materialName);
			materials.push_back(material);
			index = materials.size() - 1;
		}
		else if (temp == "map_Kd") {
			string textureFile;
			sline >> textureFile;

			materials[index]->setTextureFile(textureFile);
		}
		else if (temp == "Ka" || temp == "Ks" || temp == "Kd") {
			float r, g, b;
			sline >> r >> g >> b;

			if (temp == "Ka") materials[index]->setKa(r, g, b);
			else if (temp == "Ks") materials[index]->setKs(r, g, b);
			else if (temp == "Kd") materials[index]->setKd(r, g, b);
		}
		else if (temp == "Ns") {
			float ns;
			sline >> ns;
			if (ns < 0) {
				ns = ns * -1;
			}
			materials[index]->setNs(ns);
		}
	}

	return materials;
}