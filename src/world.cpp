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

void World::update() {
	environment.update(track.railList);
}

void World::draw(int tutorialState) {
	track.updateVisibleRange();
	generateMountainPolygons();

	track.draw(configuration.getConfigurations()["TrackGenerationStyle"], configuration.getConfigurations()["DrawTrackDetails"]);
	
	environment.drawUnderMountain();
	drawing.drawPolygon(mountainPolygonsStart, mountainColor, 255);
	for (std::vector<Vector2> polygon : mountainPolygons) {
		drawing.drawPolygon(polygon, mountainColor, 255);
	}

	drawMountainOutline();

	environment.draw();

	if (tutorialState != -1) {
		drawTutorial(tutorialState);
		drawing.drawLine(track.railList[0][endNode], track.railList[1][endNode]);
	}
}

void World::drawStatic() {
	environment.drawStatic();
}

void World::drawStaticBackground() {
	environment.drawStaticBackground();
}

void World::drawMountainOutline() {
	drawing.drawLineStrip(track.getVisibleRail(0), -50, mountainOutlineColor, 255);
	drawing.drawLineStrip(track.getVisibleRail(0), -48, mountainOutlineColor, 255);
}

void World::generateMountainPolygons() {
	mountainPolygonsStart.emplace_back(track.railList[0][0] + Vector2(0, -30));
	mountainPolygonsStart.emplace_back(track.railList[0][0] + Vector2(-25, -10));
	mountainPolygonsStart.emplace_back(track.railList[0][0] + Vector2(-25, 50));
	mountainPolygonsStart.emplace_back(track.railList[0][0] + Vector2(0, 80));

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
				case 3:
				case 2:
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

int World::generateWorld(int tutorialState) {
	track.initialize();
	generateTrack(tutorialState);
	track.generateTrackDirection();
	generateSpeedZones();
	environment.generateGuardRails(track.railList[0], 2, 5, 15, 25);
	environment.generateTrees(track.railList[1], 5, 10, 5, 15);
	environment.generatePinecones(track.railList[1], 12, 6, 10);
	environment.generateSquirrels(track.railList, 20, 5, 7);
	environment.generateGravel(track.railList, 35);
	environment.generateCars(track.railList[1], 8);
	environment.generateBikes(track.railList[0], 6, false);
	environment.generateBikes(track.railList[1], 6, true);
	if (configuration.getConfigurations()["IsRaining"]) { environment.generateRain(track.railList[1], 25); }
	environment.generateBoulders(track.railList[1], 10);
	environment.generateWaves();

	return tutorialEnd;
}

void World::generateSpeedZones() {
	randomGradualSpeedZone(5, 0, 50, 5, 0, configuration.getConfigurations()["TrackSpeedSpacing"]);
}

void World::generateTrack(int tutorialState) {
	if (tutorialState == -1) {
		track.addVertex(Vector2(-10, -20), 0);
		track.addVertex(Vector2(-10, -20), 45);
		track.addVertexRelative(-25, 100, 25);
		track.addVertexRelative(0, 150, 0);
		switch (configuration.getConfigurations()["TrackGenerationStyle"]) {
			case 0:
				track.addVertexRelative(-75, 50, 75);
				track.addVertexRelative(-76, 50, 76);
				randomLongTrackPar(50, 100, 20, 20);
				break;
			case 1:
				randomInputFunction(50, 5, 500, -0.3, Vector2(-10, 10), Vector2(0, 20), Vector2(1000, 1000));
				for (int x = 0; x < track.railList[0].size(); x++) {
					mountainOffsetValue.push_back(rand() % 25 - 12);
				}
				break;
			case 2:
				track.addVertexRelative(-25, 50, 25);
				track.addVertexRelative(-25, 50, 25);
				randomLongTrackPar(50, 100, 20, 20);
				break;
			case 3:
				track.addVertexRelative(-75, 50, 75);
				track.addVertexRelative(-175, 50, 175);
				randomLongTrackPar(45, 100, 20, 20);
				break;
		}

		tutorialEnd = 0;
	}
	else {
		generateTutorial(tutorialState);
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

void World::generateTutorial(int state) {
	if (state == 0) {
		track.addVertex(Vector2(-10, -20), 0);
		track.addVertex(Vector2(-10, -20), 45);
		track.addVertexRelative(-25, 100, 25);
		track.addVertexRelative(0, 150, 0);
		track.addVertexRelative(0, 250, 0);
		track.addVertexRelative(0, 250, 0);
		track.addVertexRelative(0, 250, 0);
		track.addVertexRelative(0, 250, 0);
		track.addVertexRelative(0, 250, 0);

		endNode = track.railList[0].size() - 1;
		tutorialEnd = track.railList[0][endNode].x;

		track.addVertexRelative(0, 150, 0);
		randomLongTrackPar(50, 100, 20, 20);
	}

	if (state == 1) {
		track.addVertex(Vector2(-10, -20), 0);
		track.addVertex(Vector2(-10, -20), 45);
		track.addVertexRelative(-25, 100, 25);
		track.addVertexRelative(0, 150, 0);
		track.addVertexRelative(0, 300, 0);
		track.addVertexRelative(-50, 150, 50);
		randomUpPar(50, 10, 50);
		randomDownPar(50, 10, 50);

		endNode = track.railList[0].size() - 1;
		tutorialEnd = track.railList[0][endNode].x;

		track.addVertexRelative(0, 250, 0);
		randomLongTrackPar(50, 100, 20, 20);
	}

	if (state == 2) {
		track.addVertex(Vector2(-10, -20), 0);
		track.addVertex(Vector2(-10, -20), 45);
		track.addVertexRelative(-25, 100, 25);
		track.addVertexRelative(0, 150, 0);
		track.addVertexRelative(0, 300, 0);
		track.addVertexRelative(-35, 150, 35);
		randomUpPar(60, 15, 50);
		randomDownPar(60, 15, 50);
		randomUpPar(60, 15, 50);
		randomDownPar(60, 15, 50);

		endNode = track.railList[0].size() - 1;
		tutorialEnd = track.railList[0][endNode].x;

		track.addVertexRelative(0, 250, 0);
		randomLongTrackPar(50, 100, 20, 20);
	}

	if (state == 3) {
		track.addVertex(Vector2(-10, -20), 0);
		track.addVertex(Vector2(-10, -20), 45);
		track.addVertexRelative(-25, 100, 25);
		track.addVertexRelative(0, 150, 0);
		track.addVertexRelative(0, 250, 0);
		track.addVertexRelative(0, 250, 0);
		track.addVertexRelative(0, 250, 0);
		track.addVertexRelative(0, 250, 0);
		track.addVertexRelative(0, 250, 0);
		track.addVertexRelative(0, 250, 0);
		track.addVertexRelative(0, 250, 0);
		track.addVertexRelative(0, 250, 0);

		endNode = track.railList[0].size() - 1;
		tutorialEnd = track.railList[0][endNode].x;

		track.addVertexRelative(0, 150, 0);
		randomLongTrackPar(50, 100, 20, 20);
	}

	if (state == 4) {
		track.addVertex(Vector2(-10, -20), 0);
		track.addVertex(Vector2(-10, -20), 45);
		track.addVertexRelative(-25, 100, 25);
		track.addVertexRelative(0, 150, 0);
		track.addVertexRelative(0, 300, 0);
		track.addVertexRelative(-50, 150, 50);
		randomUpPar(50, 10, 50);
		randomDownPar(50, 10, 50);
		randomUpPar(50, 10, 50);
		randomDownPar(50, 10, 50);
		randomUpPar(50, 10, 50);
		randomDownPar(50, 10, 50);

		endNode = track.railList[0].size() - 1;
		tutorialEnd = track.railList[0][endNode].x;

		track.addVertexRelative(0, 250, 0);
		randomLongTrackPar(50, 100, 20, 20);
	}

	if (state == 5) {
		track.addVertex(Vector2(-10, -20), 0);
		track.addVertex(Vector2(-10, -20), 45);
		track.addVertexRelative(-25, 100, 25);
		track.addVertexRelative(0, 150, 0);
		track.addVertexRelative(0, 250, 0);
		track.addVertexRelative(0, 250, 0);
		track.addVertexRelative(0, 250, 0);
		track.addVertexRelative(-75, 150, 75);
		randomUpPar(50, 25, 50);
		randomDownPar(50, 25, 50);
		randomUpPar(50, 25, 50);
		randomDownPar(50, 25, 50);

		endNode = track.railList[0].size() - 1;
		tutorialEnd = track.railList[0][endNode].x;

		track.addVertexRelative(0, 250, 0);
		randomLongTrackPar(50, 100, 20, 20);
	}

	if (state == 6) {
		track.addVertex(Vector2(-10, -20), 0);
		track.addVertex(Vector2(-10, -20), 45);
		track.addVertexRelative(-25, 100, 25);
		track.addVertexRelative(0, 150, 0);
		track.addVertexRelative(0, 250, 0);
		track.addVertexRelative(0, 250, 0);

		endNode = track.railList[0].size() - 1;
		tutorialEnd = track.railList[0][endNode].x;

		track.addVertexRelative(0, 150, 0);
		randomLongTrackPar(50, 100, 20, 20);
	}
}

void World::drawTutorial(int state) {
	if (state == 0) {
		drawing.drawText("Welcome to Thane!!!", track.railList[0][0] - Vector2(100, 150), 24, tutorialColor1);
		drawing.drawText("(Press any key to start)", track.railList[0][0] - Vector2(100, 120), 24, tutorialColor2);
		drawing.drawText("You are at the peak of a very very very very very very very very very large hill", track.railList[0][4] - Vector2(100, 120), 24, tutorialColor2);
	}

	if (state == 1) {
		drawing.drawText("Use the left and right arrow keys to navigate through the hills", track.railList[0][0] - Vector2(100, 150), 24, tutorialColor3);
	}

	if (state == 2) {
		drawing.drawText("Uh oh, the corners just got tighter", track.railList[0][0] - Vector2(100, 150), 24, tutorialColor1);
		drawing.drawText("Hold \"A\" when turning to preform a slide/drift", track.railList[0][0] - Vector2(125, 120), 24, tutorialColor2);
	}

	if (state == 3) {
		drawing.drawText("As your speed increases, you might get speedwobbles if your form is stinky", track.railList[0][0] - Vector2(200, 150), 24, tutorialColor1);
		drawing.drawText("Hold \"SPACEBAR\" to preform a tuck", track.railList[0][0] - Vector2(125, 120), 24, tutorialColor2);
		drawing.drawText("You will gain speed and increase your stability in a tuck", track.railList[0][5] - Vector2(50, 120), 24, tutorialColor2);
	}

	if (state == 4) {
		drawing.drawText("Technical slides are fast, flashy, and stylish", track.railList[0][0] - Vector2(200, 150), 24, tutorialColor1);
		drawing.drawText("Hold \"S\" when turning to preform a technical slide", track.railList[0][0] - Vector2(125, 120), 24, tutorialColor2);
	}

	if (state == 5) {
		drawing.drawText("Going too fast?", track.railList[0][0] - Vector2(200, 150), 24, tutorialColor1);
		drawing.drawText("Hold \"D\" when turning to preform a shutdown slide", track.railList[0][0] - Vector2(125, 120), 24, tutorialColor2);
	}

	if (state == 6) {
		drawing.drawText("Beware of cars, cyclists, gravel pits, road squirrels, steep hills, speedwobbles, potholes, pinecones, trees, rain, puddles, oh god please help me, I think I just failed my stats final", track.railList[0][0] - Vector2(200, 200), 24, tutorialColor1);
		drawing.drawText("Smash pinecones to gain money", track.railList[0][0] - Vector2(125, 150), 24, tutorialColor2);
		drawing.drawText("You can show the main menu by pressing \"1\"", track.railList[0][0] - Vector2(125, 120), 24, tutorialColor2);
	}
}