#ifndef OBJECTREADER_H
#define OBJECTREADER_H

#include <string>
#include <fstream> 
#include <iostream>
#include <sstream>
#include "Mesh.h"

using namespace std;

class ObjectReader {
private:
	Mesh* mesh;
	ifstream file;
	string filename;

public:
	ObjectReader(string filename);
	Mesh* readFile();
};

#endif