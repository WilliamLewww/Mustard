#include "environment.h"

void World::draw() {
	track.draw();
}

void genPresetA(Track& track);
void genPresetB(Track& track);
void genPresetC(Track& track);
void genPresetD(Track& track);
void randomLongTrack(Track& track, int difficulty, int count, int points, int pointSpacing);
void World::generateTrack() {
	track.addVertex(Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2 - 20), 45);
	track.addVertexRelative(-25, 100, 25);
	track.addVertexRelative(0, 150, 0);
	track.addVertexRelative(-25, 50, 25);
	randomLongTrack(track, 50, 100, 20, 20);
}

void smoothCarveUp(Track& track, int interval, int spacing, int count);
void smoothCarveDown(Track& track, int interval, int spacing, int count);
void genPresetA(Track& track) {
	smoothCarveUp(track, 5, 7, 25);
	smoothCarveDown(track, 5, 7, 25);
}

void genPresetB(Track& track) {
	smoothCarveUp(track, 5, 7, 25);
	smoothCarveDown(track, 5, 7, 25);
}

void genPresetC(Track& track) {
	smoothCarveUp(track, 12, 7, 10);
}

void genPresetD(Track& track) {
	smoothCarveDown(track, 12, 7, 10);
}

void random(Track& track, int difficulty, int points, int pointSpacing);
void randomUp(Track& track, int difficulty, int points, int pointSpacing);
void randomDown(Track& track, int difficulty, int points, int pointSpacing);
void randomLongTrack(Track& track, int difficulty, int count, int points, int pointSpacing) {
	for (int x = 0; x < count; x++) {
		switch (rand() % 3) {
			case 0:
				random(track,difficulty, points, pointSpacing);
				break;
			case 1:
				randomDown(track, difficulty, points, pointSpacing);
				break;
			case 2:
				randomUp(track, difficulty, points, pointSpacing);
				break;
		}
	}
}

void randomUp(Track& track, int difficulty, int points, int pointSpacing) {
	for (int x = 0; x < points; x++) { 
		track.addVertexComp(-(rand() % (difficulty + 1)), pointSpacing);
	}
}

void randomDown(Track& track, int difficulty, int points, int pointSpacing) {
	for (int x = 0; x < points; x++) { 
		track.addVertexComp(rand() % (difficulty + 1), pointSpacing);
	}
}

void random(Track& track, int difficulty, int points, int pointSpacing) {
	for (int x = 0; x < points; x++) { 
		track.addVertexComp((rand() % (difficulty + 1) - (difficulty / 2)), pointSpacing);
	}
}

void smoothCarveUp(Track& track, int interval, int spacing, int count) {
	int intensity = 0;
	for (int x = 0; x < count; x++) {
		track.addVertexRelative(-intensity, spacing * spacing, -intensity);
		if (x < count / 2) { intensity += interval; }
		else {intensity -= interval; }
	} 
}

void smoothCarveDown(Track& track, int interval, int spacing, int count) {
	int intensity = 0;
	for (int x = 0; x < count; x++) {
		track.addVertexRelative(intensity, spacing * spacing, intensity);
		if (x < count / 2) { intensity += interval; }
		else {intensity -= interval; }
	} 
}