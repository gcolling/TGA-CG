#include "ObjectReader.h"

ObjectReader::ObjectReader(string filename) {
	this->filename = filename;
	this->file.open(filename);

	if (this->file.fail()) {
		printf("Problem while reading the object file\n");
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
		string subString;
		sline >> subString;

		if (subString == "v") {
			float x, y, z;
			sline >> x >> y >> z;
			mesh->addVertex(x, y, z);

		}
		else if (subString == "vt") {
			float x, y;
			sline >> x >> y;

			mesh->addTexture(x, y);
		}
		else if (subString == "vn") {
			float x, y, z;
			sline >> x >> y >> z;

			mesh->addNormal(x, y, z);
		}
		else if (subString == "g") {
			string groupName;
			sline >> groupName;
			if (mesh->getGroups().size() == 1) {
				mesh->getGroups()[0]->setName(groupName);
			}
			else {
				mesh->newGroup(groupName);
			}
		}
		else if (subString == "f") {
			vector<int> vert;
			vector<int> text;
			vector<int> norm;
			string token, v, t, n;

			while (sline.rdbuf()->in_avail()) {
				token = "";
				sline >> token;
				if (token == "") {
					break;
				}
				stringstream stoken(token);

				getline(stoken, v, '/');
				getline(stoken, t, '/');
				getline(stoken, n, ' ');

				if (vert.size() == 3) {
					mesh->addFace(vert, text, norm);
					vert[1] = stoi(v) - 1;
					if (t != "") text[1] = stoi(t) - 1;
					if (n != "") norm[1] = stoi(n) - 1;
				}
				else {
					vert.push_back(stoi(v) - 1);
					if(t != "")	text.push_back(stoi(t) - 1);
					if(n != "")	norm.push_back(stoi(n) - 1);
				}
			}

			mesh->addFace(vert, text, norm);
		}
		else if (subString == "mtllib") {
			string materialFile;
			sline >> materialFile;
			mesh->setMaterialFile(materialFile);
		}
		else if (subString == "usemtl") {
			string materialId;
			sline >> materialId;
			mesh->setGroupMaterialId(materialId);
		}
	}

	return mesh;
}