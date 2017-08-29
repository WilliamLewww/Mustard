#include "environment.h"

std::vector<Vector2> generateLongTrackRand(int difficulty, int count, int points, int pointSpacing, Vector2 startPoint) {
	std::vector<Vector2> tempTrack;
	std::vector<Vector2> tempTrack2;
	tempTrack.push_back(startPoint);

	for (int x = 0; x < count; x++) {
		switch (rand() % 3) {
			case 0:
				tempTrack2 = generateTrackRand(difficulty, points, pointSpacing, Vector2(tempTrack[tempTrack.size() - 1].x, tempTrack[tempTrack.size() - 1].y));
				break;
			case 1:
				tempTrack2 = generateTrackDown(difficulty, points, pointSpacing, Vector2(tempTrack[tempTrack.size() - 1].x, tempTrack[tempTrack.size() - 1].y));
				break;
			case 2:
				tempTrack2 = generateTrackUp(difficulty, points, pointSpacing, Vector2(tempTrack[tempTrack.size() - 1].x, tempTrack[tempTrack.size() - 1].y));
				break;
		}

		tempTrack.insert(tempTrack.end(), tempTrack2.begin(), tempTrack2.end());
	}

	return tempTrack;
}

std::vector<Vector2> generateTrackDown(int difficulty, int points, int pointSpacing, Vector2 startPoint) {
	std::vector<Vector2> tempTrack;
	tempTrack.push_back(startPoint);
	for (int x = 0; x < points; x++) { tempTrack.push_back(Vector2(tempTrack[tempTrack.size() - 1].x + pointSpacing, tempTrack[tempTrack.size() - 1].y + (rand() % (difficulty + 1)))); }

	return tempTrack;
}

std::vector<Vector2> generateTrackUp(int difficulty, int points, int pointSpacing, Vector2 startPoint) {
	std::vector<Vector2> tempTrack;
	tempTrack.push_back(startPoint);
	for (int x = 0; x < points; x++) { tempTrack.push_back(Vector2(tempTrack[tempTrack.size() - 1].x + pointSpacing, tempTrack[tempTrack.size() - 1].y - (rand() % (difficulty + 1)))); }

	return tempTrack;
}

std::vector<Vector2> generateTrackRand(int difficulty, int points, int pointSpacing, Vector2 startPoint) {
	std::vector<Vector2> tempTrack;
	tempTrack.push_back(startPoint);
	for (int x = 0; x < points; x++) { tempTrack.push_back(Vector2(tempTrack[tempTrack.size() - 1].x + pointSpacing, tempTrack[tempTrack.size() - 1].y + (rand() % (difficulty + 1) - (difficulty / 2)))); }

	return tempTrack;
}

std::vector<Vector2> generateTrackComp(std::vector<Vector2> track, Vector2 startPoint, int offsetY, int limitTop, int limitBottom) {
	std::vector<Vector2> tempTrack;
	tempTrack.push_back(startPoint);
	track.erase(track.begin());
	for (Vector2 point : track) { 
		tempTrack.push_back(Vector2(point.x, point.y + offsetY + (rand() % (limitBottom - limitTop + 1) - limitTop))); 
	}

	return tempTrack;
}

std::vector<Vector2> duplicateTrack(std::vector<Vector2> track, int offsetY) {
	std::vector<Vector2> tempTrack;
	for (int x = 0; x < track.size(); x++) { tempTrack.push_back(Vector2(track[x].x, track[x].y + offsetY)); }

	return tempTrack;
}

std::vector<Vector2> duplicateTrackPosition(std::vector<Vector2> track, Vector2 position) {
	std::vector<Vector2> tempTrack;
	for (int x = 0; x < track.size(); x++) { 
		tempTrack.push_back(Vector2(track[x].x - track[0].x + position.x, track[x].y - track[0].y + position.y));
	}

	return tempTrack;
}