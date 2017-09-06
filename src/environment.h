#pragma once
#include "..\constants.h"
#include "track.h"

class World {
public:
	Track track;
	void generateTrack();
	void draw();
};