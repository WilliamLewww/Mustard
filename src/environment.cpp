#include "environment.h"

void random(Track& track, int topIndex, int bottomIndex, int difficulty, int points, int pointSpacing);
void randomPar(Track& track, int topIndex, int bottomIndex, int difficulty, int points, int pointSpacing);
void randomUp(Track& track, int topIndex, int bottomIndex, int difficulty, int points, int pointSpacing);
void randomUpPar(Track& track, int topIndex, int bottomIndex, int difficulty, int points, int pointSpacing);
void randomDown(Track& track, int topIndex, int bottomIndex, int difficulty, int points, int pointSpacing);
void randomDownPar(Track& track, int topIndex, int bottomIndex, int difficulty, int points, int pointSpacing);
void randomLongTrack(Track& track, int topIndex, int bottomIndex, int difficulty, int count, int points, int pointSpacing);
void randomLongTrackPar(Track& track, int topIndex, int bottomIndex, int difficulty, int count, int points, int pointSpacing);

void randomSpeedZone(Track& track, int difficulty, int initialSpeed, int initialNode, int spacing);
void randomGradualSpeedZone(Track& track, int difficulty, int min, int max, int initialSpeed, int initialNode, int spacing);

double f(double x, double a, double b) { return (a * sin(b * x)); }
double fDerivative(double x, double a, double b) { return (a * b * cos(b * x)); }
double g(double x, double a, double b) { return x; }
double gDerivative(double x, double a, double b) { return b; }

void givenInputFunction(Track& track, int period, int buffer, double distance, double a, double b, Vector2 expandVal);
void randomInputFunction(Track& track, int functionCount, int period, int buffer, double distance, Vector2 betweenA, Vector2 betweenB, Vector2 expandVal);

void World::reset() {
	track.resetVisibleRange();
	mountainPolygons.clear();
}

void World::draw(bool drawTrackDetails = true) {
	track.setVisibleRange();
	generateMountainPolygons();

	for (std::vector<Vector2> polygon : mountainPolygons) {
		drawPolygon(polygon, mountainColor, 255);
	}

	track.draw(drawTrackDetails);
}

void World::generateMountainPolygons() {
	for (int x = track.visibleRange.x; x < track.visibleRange.y; x++) {
		std::vector<Vector2> tempPolygon;
		std::vector<Vector2> tempPolygonTop;
		if (x > 0 && (mountainPolygons.size() == 0 || mountainPolygons[mountainPolygons.size() - 1][0].x < track.railList[0][x].x)) {
			tempPolygon.emplace_back(track.railList[1][x]);
			tempPolygon.emplace_back(track.railList[1][x - 1]);
			tempPolygon.emplace_back(track.railList[1][x - 1].x, track.railList[1][x - 1].y + (SCREENHEIGHT * 2));
			tempPolygon.emplace_back(track.railList[1][x].x, track.railList[1][x].y + (SCREENHEIGHT * 2));

			mountainPolygons.push_back(tempPolygon);

			switch (generationStyle) {
				case 0: 
					tempPolygonTop.emplace_back(track.railList[0][x]);
					tempPolygonTop.emplace_back(track.railList[0][x - 1]);
					tempPolygonTop.emplace_back(track.railList[0][x - 1].x, track.railList[0][x - 1].y - 50);
					tempPolygonTop.emplace_back(track.railList[0][x].x, track.railList[0][x].y - 50);
				break;
				case 1:
					tempPolygonTop.emplace_back(track.railList[0][x]);
					tempPolygonTop.emplace_back(track.railList[0][x - 1]);
					tempPolygonTop.emplace_back(track.railList[0][x - 1].x, track.railList[0][x - 1].y - 50 - mountainOffsetValue[x - 1]);
					tempPolygonTop.emplace_back(track.railList[0][x].x, track.railList[0][x].y - 50 - mountainOffsetValue[x]);
				break;

			}
			mountainPolygons.push_back(tempPolygonTop);
		}
	}

	for (int x = 0; x < mountainPolygons.size(); x++) {
		if (mountainPolygons[x][0].x < visibleFrame.sLeft()) {
			mountainPolygons.erase(mountainPolygons.begin());
			x -= 1;
		}
		else { break; }
	}
}

void World::generateSpeedZones() {
	track.addSpeedZone(0, 0);
	randomGradualSpeedZone(track, 5, 0, 50, 5, 2, 15);
}

void World::generateTrack() {
	track.addRail(2);
	track.addVertex(0, 1, Vector2(SCREENWIDTH / 2 - 10, SCREENHEIGHT / 2 - 20), 0);
	track.addVertex(0, 1, Vector2(SCREENWIDTH / 2 - 10, SCREENHEIGHT / 2 - 20), 45);
	track.addVertexRelative(0, 1, -25, 100, 25);
	track.addVertexRelative(0, 1, 0, 150, 0);
	switch (generationStyle) {
		case 0:
			track.addVertexRelative(0, 1, -75, 50, 75);
			track.addVertexRelative(0, 1, -76, 50, 76);
			randomLongTrackPar(track, 0, 1, 50 , 100, 20, 20);
			break;
		case 1:
			randomInputFunction(track, 50, 5, 100, -0.3, Vector2(-10, 10), Vector2(0, 20), Vector2(500, 500));
			for (int x = 0; x < track.railList[0].size(); x++) {
				mountainOffsetValue.push_back(rand() % 25 - 12);
			}
			break;
	}
}

void givenInputFunction(Track& track, int period, int buffer, double distance, double a, double b, Vector2 expandVal) {
	std::vector<Vector2> railA;
	std::vector<Vector2> railB;

	for (double x = 0; x < period; x += 0.1) {
		railA.push_back(Vector2(x, f(x, a, b)));
		railB.push_back(Vector2(
			(distance * fDerivative(x, a, b)) / sqrt(pow(gDerivative(x, a, b), 2) + pow(fDerivative(x, a, b), 2)) + g(x, a, b),
			-(distance * gDerivative(x, a, b)) / sqrt(pow(gDerivative(x, a, b), 2) + pow(fDerivative(x, a, b), 2)) + f(x, a, b)));
	}

	Vector2 initialPoint = track.railList[0][track.railList[0].size() - 1];
	for (Vector2& vector2 : railA) { 
		vector2.expand(expandVal.x, expandVal.y);
		track.addVertexSingle(0, vector2 + initialPoint + Vector2(buffer, 0));
	}
	for (Vector2& vector2 : railB) { 
		vector2.expand(expandVal.x, expandVal.y); 
		track.addVertexSingle(1, vector2 + initialPoint + Vector2(buffer, 0));
	}
}

void randomInputFunction(Track& track, int functionCount, int period, int buffer, double distance, Vector2 betweenA, Vector2 betweenB, Vector2 expandVal) {
	std::vector<Vector2> railA;
	std::vector<Vector2> railB;

	for (int count = 0; count < functionCount; count++) {
		double a = (rand() % (int)(betweenA.y - betweenA.x + 1) + betweenA.x) / 10;
		double b = (rand() % (int)(betweenB.y - betweenB.x + 1) + betweenB.x) / 10;

		for (double x = 0; x < period; x += 0.1) {
			railA.push_back(Vector2(x, f(x, a, b)));
			railB.push_back(Vector2(
				(distance * fDerivative(x, a, b)) / sqrt(pow(gDerivative(x, a, b), 2) + pow(fDerivative(x, a, b), 2)) + g(x, a, b),
				-(distance * gDerivative(x, a, b)) / sqrt(pow(gDerivative(x, a, b), 2) + pow(fDerivative(x, a, b), 2)) + f(x, a, b)));
		}

		Vector2 initialPoint = track.railList[0][track.railList[0].size() - 1];
		for (Vector2& vector2 : railA) { 
			vector2.expand(expandVal.x, expandVal.y);
			track.addVertexSingle(0, vector2 + initialPoint + Vector2(buffer, 0));
		}
		for (Vector2& vector2 : railB) { 
			vector2.expand(expandVal.x, expandVal.y); 
			track.addVertexSingle(1, vector2 + initialPoint + Vector2(buffer, 0));
		}

		railA.clear();
		railB.clear();
	}
}

void randomGradualSpeedZone(Track& track, int difficulty, int min, int max, int initialSpeed, int initialNode, int spacing) {
	bool end = false;
	int currentSpeed = initialSpeed;

	for (int x = initialNode; x < track.railList[0].size(); x += spacing) {
		if (currentSpeed + difficulty > max) {
			currentSpeed += rand() % (max - currentSpeed + difficulty + 1) - difficulty;
			end = true;
		}
		if (currentSpeed - difficulty < min && end == false) {
			currentSpeed += rand() % (difficulty + min - currentSpeed + 1) - (min - currentSpeed);
			end = true;
		}
		if (end == false) {
			currentSpeed += rand() % (difficulty + difficulty + 1) - difficulty;
		}

		track.addSpeedZone(x, currentSpeed);
		end = false;
	}
}

void randomSpeedZone(Track& track, int difficulty, int initialSpeed, int initialNode, int spacing) {
	for (int x = initialNode; x < track.railList[0].size(); x += spacing) {
		track.addSpeedZone(x, (rand() % (difficulty + difficulty + 1) - difficulty) + initialSpeed);
	}
}

void randomLongTrackPar(Track& track, int topIndex, int bottomIndex, int difficulty, int count, int points, int pointSpacing) {
	for (int x = 0; x < count; x++) {
		switch (rand() % 3) {
			case 0:
				randomPar(track, topIndex, bottomIndex, difficulty, points, pointSpacing);
				break;
			case 1:
				randomDownPar(track, topIndex, bottomIndex, difficulty, points, pointSpacing);
				break;
			case 2:
				randomUpPar(track, topIndex, bottomIndex, difficulty, points, pointSpacing);
				break;
		}
	}
}

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

void randomUpPar(Track& track, int topIndex, int bottomIndex, int difficulty, int points, int pointSpacing) {
	for (int x = 0; x < points; x++) { 
		track.addVertexComp(topIndex, bottomIndex, -(rand() % (difficulty + 1)), pointSpacing);
	}
}

void randomDownPar(Track& track, int topIndex, int bottomIndex, int difficulty, int points, int pointSpacing) {
	for (int x = 0; x < points; x++) { 
		track.addVertexComp(topIndex, bottomIndex, rand() % (difficulty + 1), pointSpacing);
	}
}

void randomPar(Track& track, int topIndex, int bottomIndex, int difficulty, int points, int pointSpacing) {
	for (int x = 0; x < points; x++) { 
		track.addVertexComp(topIndex, bottomIndex, (rand() % (difficulty + 1) - (difficulty / 2)), pointSpacing);
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