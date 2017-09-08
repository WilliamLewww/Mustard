#include "environment.h"

void World::draw() {
	track.draw();
}

void genPresetA(Track& track);
void genPresetB(Track& track);
void genPresetC(Track& track);
void genPresetD(Track& track);
void randomLongTrack(Track& track, int topIndex, int bottomIndex, int difficulty, int count, int points, int pointSpacing);
void World::generateTrack() {
	track.addRail(2);
	track.addVertex(0, 1, Vector2(SCREENWIDTH / 2 - 10, SCREENHEIGHT / 2 - 20), 0);
	track.addVertex(0, 1, Vector2(SCREENWIDTH / 2 - 10, SCREENHEIGHT / 2 - 20), 45);
	track.addVertexRelative(0, 1, -25, 100, 25);
	track.addVertexRelative(0, 1, 0, 150, 0);
	track.addVertexRelative(0, 1, -25, 50, 25);
	randomLongTrack(track, 0, 1, 50, 100, 20, 20);
}

void random(Track& track, int topIndex, int bottomIndex, int difficulty, int points, int pointSpacing);
void randomUp(Track& track, int topIndex, int bottomIndex, int difficulty, int points, int pointSpacing);
void randomDown(Track& track, int topIndex, int bottomIndex, int difficulty, int points, int pointSpacing);
void randomLongTrack(Track& track, int topIndex, int bottomIndex, int difficulty, int count, int points, int pointSpacing) {
	for (int x = 0; x < count; x++) {
		switch (rand() % 3) {
			case 0:
				random(track, topIndex, bottomIndex, difficulty, points, pointSpacing);
				break;
			case 1:
				randomDown(track, topIndex, bottomIndex, difficulty, points, pointSpacing);
				break;
			case 2:
				randomUp(track, topIndex, bottomIndex, difficulty, points, pointSpacing);
				break;
		}
	}
}

void randomUp(Track& track, int topIndex, int bottomIndex, int difficulty, int points, int pointSpacing) {
	for (int x = 0; x < points; x++) { 
		track.addVertexComp(topIndex, bottomIndex, -(rand() % (difficulty + 1)), pointSpacing, 200, -20, 20);
	}
}

void randomDown(Track& track, int topIndex, int bottomIndex, int difficulty, int points, int pointSpacing) {
	for (int x = 0; x < points; x++) { 
		track.addVertexComp(topIndex, bottomIndex, rand() % (difficulty + 1), pointSpacing, 200, -20, 20);
	}
}

void random(Track& track, int topIndex, int bottomIndex, int difficulty, int points, int pointSpacing) {
	for (int x = 0; x < points; x++) { 
		track.addVertexComp(topIndex, bottomIndex, (rand() % (difficulty + 1) - (difficulty / 2)), pointSpacing, 200, -20, 20);
	}
}

void smoothCarveUp(Track& track, int topIndex, int bottomIndex, int interval, int spacing, int count) {
	int intensity = 0;
	for (int x = 0; x < count; x++) {
		track.addVertexRelative(topIndex, bottomIndex, -intensity, spacing * spacing, -intensity);
		if (x < count / 2) { intensity += interval; }
		else {intensity -= interval; }
	} 
}

void smoothCarveDown(Track& track, int topIndex, int bottomIndex, int interval, int spacing, int count) {
	int intensity = 0;
	for (int x = 0; x < count; x++) {
		track.addVertexRelative(topIndex, bottomIndex, intensity, spacing * spacing, intensity);
		if (x < count / 2) { intensity += interval; }
		else {intensity -= interval; }
	} 
}