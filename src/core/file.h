#pragma once
#include <vector>
#include <map>
#include <fstream>
#include "vector2.h"

class File {
public:
	void exportSplits(int index, std::vector<float> splits, float finalTime);

	std::vector<Vector2> getVerticesFromFile(const char* filename);
	std::map<std::string, int> getConfigurationFromFile(const char* filename);
};

extern File file;