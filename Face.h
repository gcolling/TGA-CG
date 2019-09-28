#ifndef FACE_H
#define FACE_H

#include <vector>

using namespace std;

class Face {
private:
	vector<int> verts;
	vector<int> texts;
	vector<int> norms;

public:
	void addVertexInfo(int vertexIndex, int textureIndex, int normalIndex);
	void setInfo(vector<int> verts, vector<int> texts, vector<int> norms);
	void setVerts(vector<int> verts);
	void setTexts(vector<int> texts);
	void setNorms(vector<int> norms);
	vector<int> getVerts();
	vector<int> getTexts();
	vector<int> getNorms();
};

#endif