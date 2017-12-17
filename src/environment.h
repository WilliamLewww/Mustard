#pragma once
#include "..\constants.h"
#include "vector2.h"
#include "track.h"

class World {
	int mountainColor[3] = { 118, 92, 67 };

	std::vector<std::vector<Vector2>> mountainPolygons;
public:
	Track track;
	void generateSpeedZones();
	void generateTrack();
	void draw(bool drawTrackDetails);

	void reset();

	void generateMountainPolygons();
};