#ifndef FACE_H
#define FACE_H

#include <vector>

using namespace std;

class Face {
private:
	vector<int> vertices;
	vector<int> textures;
	vector<int> normals;

public:
	void addVertexInfo(int vertexIndex, int textureIndex, int normalIndex);
	void setInfo(vector<int> verts, vector<int> texts, vector<int> norms);
	void setVertices(vector<int> verts);
	vector<int> getVertices();
	void setTextures(vector<int> texts);
	vector<int> getTextures();
	void setNormals(vector<int> norms);
	vector<int> getNormals();
};

#endif