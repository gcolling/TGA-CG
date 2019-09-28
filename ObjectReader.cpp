#include "ObjectReader.h"

ObjectReader::ObjectReader(string filename) {
	this->filename = filename;
	this->file.open(filename);

	if (this->file.fail()) {
		printf("It was not possible to open the file\n");
	}

	this->mesh = new Mesh();
	mesh->setObjectFile(filename);
};

Mesh* ObjectReader::readFile() {
	while (!this->file.eof()) {
		string line;
		getline(this->file, line);

		stringstream sline;
		sline << line;
		string temp;
		sline >> temp;

		if (temp == "v") {
			float x, y, z;
			sline >> x >> y >> z;
			mesh->addVertex(x, y, z);

		}
		else if (temp == "vn") {
			float x, y, z;
			sline >> x >> y >> z;

			mesh->addNormal(x, y, z);
		}
		else if (temp == "vt") {
			float x, y;
			sline >> x >> y;

			mesh->addMapping(x, y);
		}
		else if (temp == "f") {
			vector<int> vert;
			vector<int> text;
			vector<int> norm;
			string token, v, t, n;

			while (sline.rdbuf()->in_avail()) { //trocar por file end of line
				token = "";
				sline >> token;
				if (token == "") {
					break;
				}
				stringstream stoken(token);

				getline(stoken, v, '/');
				getline(stoken, t, '/');
				getline(stoken, n, ' ');

				//@TODO verificar  se tem normal e textura, senao nem preenche

				if (vert.size() == 3) {
					mesh->addFace(vert, text, norm);
					vert[1] = stoi(v) - 1;
					text[1] = stoi(t) - 1;
					norm[1] = stoi(n) - 1;
				}
				else {
					vert.push_back(stoi(v) - 1);
					text.push_back(stoi(t) - 1);
					norm.push_back(stoi(n) - 1);
				}
			}

			mesh->addFace(vert, text, norm);
		}
		else if (temp == "g") {
			string groupName;
			sline >> groupName;
			if (mesh->getGroups().size() == 1) {
				mesh->getGroups()[0]->setName(groupName);
			}
			else {
				mesh->newGroup(groupName);
			}
		}
		else if (temp == "mtllib") {
			string materialFile;
			sline >> materialFile;
			mesh->setMaterialFile(materialFile);
		}
		else if (temp == "usemtl") {
			string materialId;
			sline >> materialId;
			mesh->setGroupMaterialId(materialId);
		}
	}

	return mesh;
}