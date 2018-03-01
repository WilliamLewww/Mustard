#pragma once
#include "track.h"
#include "drawing.h"

class World {
private:
	Track track;

	int mountainColor[3] = { 118, 92, 67 };

	std::vector<std::vector<Vector2>> mountainPolygons;
	std::vector<int> mountainOffsetValue;
public:
	void generateSpeedZones();
	void generateTrack();
	void draw(bool drawTrackDetails);

	void reset();

	void generateMountainPolygons();
};