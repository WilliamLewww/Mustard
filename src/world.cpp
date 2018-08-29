#include "world.h"

double f(double x, double a, double b) { return (a * sin(b * x)); }
double fDerivative(double x, double a, double b) { return (a * b * cos(b * x)); }
double g(double x, double a, double b) { return x; }
double gDerivative(double x, double a, double b) { return b; }

void World::reset() {
	track.resetVisibleRange();
	mountainPolygons.clear();
	environment.resetVisibleRange();
}

void World::draw() {
	track.updateVisibleRange();
	generateMountainPolygons();

	for (std::vector<Vector2> polygon : mountainPolygons) {
		drawing.drawPolygon(polygon, mountainColor, 255);
	}

	track.draw(configuration.getConfigurations()["TrackGenerationStyle"], configuration.getConfigurations()["DrawTrackDetails"]);

	environment.draw();
}

void World::generateMountainPolygons() {
	for (int x = track.visibleRange.x; x < track.visibleRange.y; x++) {
		std::vector<Vector2> tempPolygon;
		std::vector<Vector2> tempPolygonTop;
		if (x > 0 && (mountainPolygons.size() == 0 || mountainPolygons[mountainPolygons.size() - 1][0].x < track.railList[0][x].x)) {
			tempPolygon.emplace_back(track.railList[1][x]);
			tempPolygon.emplace_back(track.railList[1][x - 1]);
			tempPolygon.emplace_back(track.railList[1][x - 1].x, track.railList[1][x - 1].y + (configuration.getScreenHeight() * 2));
			tempPolygon.emplace_back(track.railList[1][x].x, track.railList[1][x].y + (configuration.getScreenHeight() * 2));

			mountainPolygons.push_back(tempPolygon);

			switch (configuration.getConfigurations()["TrackGenerationStyle"]) {
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
		if (mountainPolygons[x][0].x < camera.getBoundaryLeft()) {
			mountainPolygons.erase(mountainPolygons.begin());
			x -= 1;
		}
		else { break; }
	}
}

void World::generateWorld() {
	track.initialize();
	generateTrack();
	track.generateTrackDirection();
	generateSpeedZones();
	environment.generateTrees(track.railList[1], 5, 10, 5, 15);
	// environment.generateTrees(track.railList[1], 8, 40, 5, 15);
	environment.generateTrees(track.railList[0], 5, 0, 3, 7);
}

void World::generateSpeedZones() {
	randomGradualSpeedZone(5, 0, 50, 5, 0, configuration.getConfigurations()["TrackSpeedSpacing"]);
}

void World::generateTrack() {
	track.addVertex(Vector2(-1000, -25), 0);
	track.addVertex(Vector2(-1000, -25), 125);
	track.addVertexRelative(0, 1150, 0);
	switch (configuration.getConfigurations()["TrackGenerationStyle"]) {
		case 0:
			if (configuration.getConfigurations()["HardTrack"]) {
				track.addVertexRelative(-25, 50, 25);
				track.addVertexRelative(-25, 50, 25);
			}
			else {
				track.addVertexRelative(-75, 50, 75);
				track.addVertexRelative(-76, 50, 76);
			}

			randomLongTrackPar(50, 100, 20, 20);
			break;
		case 1:
			randomInputFunction(50, 5, 500, -0.3, Vector2(-10, 10), Vector2(0, 20), Vector2(1000, 1000));
			for (int x = 0; x < track.railList[0].size(); x++) {
				mountainOffsetValue.push_back(rand() % 25 - 12);
			}
			break;
	}
}

void World::givenInputFunction(int period, int buffer, double distance, double a, double b, Vector2 expandVal) {
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

void World::randomInputFunction(int functionCount, int period, int buffer, double distance, Vector2 betweenA, Vector2 betweenB, Vector2 expandVal) {
	std::vector<Vector2> railA;
	std::vector<Vector2> railB;

	for (int count = 0; count < functionCount; count++) {
		double a = (rand() % (int)(betweenA.y - betweenA.x + 1) + betweenA.x) / 10;
		double b = (rand() % (int)(betweenB.y - betweenB.x + 1) + betweenB.x) / 10;

		while (a == 0) { a = (rand() % (int)(betweenA.y - betweenA.x + 1) + betweenA.x) / 10; }
		while (b == 0) { b = (rand() % (int)(betweenB.y - betweenB.x + 1) + betweenB.x) / 10; }

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

void World::randomLongTrackPar(int difficulty, int count, int points, int pointSpacing) {
	for (int x = 0; x < count; x++) {
		switch (rand() % 3) {
			case 0:
				randomUpPar(difficulty, points, pointSpacing);
				break;
			case 1:
				randomDownPar(difficulty, points, pointSpacing);
				break;
			case 2:
				randomPar(difficulty - 25, points, pointSpacing - 5);
				break;
		}
	}
}

void World::randomUpPar(int difficulty, int points, int pointSpacing) {
	for (int x = 0; x < points; x++) { 
		track.addVertexComp(-(rand() % (difficulty + 1)), pointSpacing);
	}
}

void World::randomDownPar(int difficulty, int points, int pointSpacing) {
	for (int x = 0; x < points; x++) { 
		track.addVertexComp(rand() % (difficulty + 1), pointSpacing);
	}
}

void World::randomPar(int difficulty, int points, int pointSpacing) {
	for (int x = 0; x < points; x++) { 
		track.addVertexComp((rand() % (difficulty + 1) - (difficulty / 2)), pointSpacing);
	}
}

void World::randomGradualSpeedZone(int difficulty, int min, int max, int initialSpeed, int initialNode, int spacing) {
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

void World::randomSpeedZone(int difficulty, int initialSpeed, int initialNode, int spacing) {
	for (int x = initialNode; x < track.railList[0].size(); x += spacing) {
		track.addSpeedZone(x, (rand() % (difficulty + difficulty + 1) - difficulty) + initialSpeed);
	}
}