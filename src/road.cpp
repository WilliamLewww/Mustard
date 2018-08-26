#include "road.h"

void Road::generate(std::vector<std::vector<Vector2>> railList, std::vector<Vector2> speedZones, int visibleRangeX, int visibleRangeY) {
	if (roadColorList.size() == 0) {
		for (int x = 0; x < railList[0].size(); x++) {
			roadColorList.emplace_back(((speedZones[x / configuration.getConfigurations()["TrackSpeedSpacing"]].y / 50.0f) - 0.5f) * 25.0f);
		}
	}

	for (int x = visibleRangeX; x < visibleRangeY; x++) {
		std::vector<Vector2> tempPolygon;
		if (x > 0 && (roadPolygonList.size() == 0 || roadPolygonList[roadPolygonList.size() - 1][0].x < railList[0][x].x)) {
			tempPolygon.emplace_back(railList[0][x]);
			tempPolygon.emplace_back(railList[0][x - 1]);
			tempPolygon.emplace_back(railList[1][x - 1]);
			tempPolygon.emplace_back(railList[1][x]);

			roadPolygonList.push_back(tempPolygon);
		}
	}

	for (int x = 0; x < roadPolygonList.size(); x++) {
		if (roadPolygonList[x][0].x < camera.getBoundaryLeft()) {
			roadPolygonList.erase(roadPolygonList.begin());
			x -= 1;
		}
		else { break; }
	}
}

void Road::clear() {
	roadPolygonList.clear();
}

void Road::draw(int visibleRangeX) {
	for (int x = 0; x < roadPolygonList.size(); x++) {
		drawing.drawPolygon(roadPolygonList[x], roadColor - roadColorList[visibleRangeX + x - 1], 255);
	}
}