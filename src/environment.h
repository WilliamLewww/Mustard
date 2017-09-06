#pragma once
#include "..\constants.h"
#include "track.h"

class World {
	Track track;
public:
	void generateTrack();
	void draw();
};