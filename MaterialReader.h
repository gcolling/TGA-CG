#ifndef MaterialReader_hpp
#define MaterialReader_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Material.h"
#include <vector>

class MaterialReader {
private:
	ifstream file;
	string filename;
	bool success;

public:
	MaterialReader(string filename);
	vector<Material*> readFile();
};
#endif