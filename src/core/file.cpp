#include "file.h"

void File::exportSplits(int seed, std::vector<float> splits, float finalTime) {
	std::ofstream out(std::to_string(seed) + ".splits");

	out << "Final Time: " << finalTime << "\n\n";
	out << "Splits:\n";
	for (int x = 0; x < splits.size(); x++) {
		if (x == splits.size() - 1) { out << splits[x]; }
		else { out << splits[x] << "\n"; }
	}

	out.close();
}

std::vector<Vector2> File::getVerticesFromFile(const char* filename) {
	std::ifstream fin(filename);
	std::vector<Vector2> vertices;
	Vector2 temp_vertex = Vector2(-1, -1);

	int x;
	while (fin >> x) {
		if (temp_vertex.y != -1) { vertices.push_back(temp_vertex); temp_vertex = Vector2(-1, -1); }
		if (temp_vertex.x == -1) { temp_vertex.x = x; }
		else { temp_vertex.y = x; }
	}

	vertices.push_back(temp_vertex);
	fin.close();

	return vertices;
}

std::map<std::string, int> File::getConfigurationFromFile(const char* filename) {
	std::map<std::string, int> configurations;

	std::ifstream configFile(filename);
	std::string lineFromFile;
	while (std::getline(configFile, lineFromFile)) {
		if (lineFromFile[0] != '#') {
			configurations[lineFromFile.substr(0, lineFromFile.find(" "))] 
				= atoi(lineFromFile.substr(lineFromFile.find(" ") + 1, lineFromFile.length()).c_str());
		}
	}

	return configurations;
}

File file;