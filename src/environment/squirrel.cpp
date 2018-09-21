#include "squirrel.h"

Squirrel::Squirrel(Vector2 position, Vector2 bottomRail, Vector2 topRail, int width, int height) {
	polygon.setPosition(position);
	polygon.setSize(width, height);

	this->bottomRail = bottomRail;
	this->topRail = topRail;

	randomInterval = rand() % (5) + 3;
}

void Squirrel::kill() {
	if (dead == false) {
		for (int x = 0; x < 25; x++) {
			particleManager.generateSquirrelGibParticles(4, polygon.getCenter(), 225);
		}
	}
	else {
		particleManager.generateSquirrelGibParticles(4, polygon.getCenter(), 225);
	}

	dead = true;
}

void Squirrel::update(float elapsedTimeSeconds) {
	if (dead == false) {
		if (crossRoad == true) {
			if (currentRail == 1) {
				if (polygon.getX() < topRail.x) polygon.addX(randomX * elapsedTimeSeconds);
				if (polygon.getX() > topRail.x) polygon.addX(-randomX * elapsedTimeSeconds);
				if (polygon.getY() < topRail.y) polygon.addY(randomX * elapsedTimeSeconds);
				if (polygon.getY() > topRail.y) polygon.addY(-randomX * elapsedTimeSeconds);
			}

			if (currentRail == 0) {
				if (polygon.getX() < bottomRail.x) polygon.addX(randomX * elapsedTimeSeconds);
				if (polygon.getX() > bottomRail.x) polygon.addX(-randomX * elapsedTimeSeconds);
				if (polygon.getY() < bottomRail.y) polygon.addY(randomX * elapsedTimeSeconds);
				if (polygon.getY() > bottomRail.y) polygon.addY(-randomX * elapsedTimeSeconds);
			}

			if (currentRail == 0 && polygon.getX() < bottomRail.x + 5 && polygon.getX() > bottomRail.x - 5 && polygon.getY() + (polygon.getHeight() / 2) < bottomRail.y + 5 && polygon.getY() + (polygon.getHeight() / 2) > bottomRail.y - 5) {
				currentRail = 1;
				crossRoad = false;
			}

			if (currentRail == 1 && polygon.getX() < topRail.x + 5 && polygon.getX() > topRail.x - 5 && polygon.getY() + (polygon.getHeight() / 2) < topRail.y + 5 && polygon.getY() + (polygon.getHeight() / 2) > topRail.y - 5) {
				currentRail = 0;
				crossRoad = false;
			}
		}
		else {
			if (polygon.getY() + polygon.getHeight() < topRail.y) {
				if (randomY < 0) { randomY = -randomY; }
			}

			if (polygon.getY() + polygon.getHeight() > bottomRail.y + 75) {
				if (randomY > 0) { randomY = -randomY; }
			}

			polygon.addX(randomX * elapsedTimeSeconds);
			polygon.addY(randomY * elapsedTimeSeconds);
		}

		if (decisionTimer > randomInterval) {
			if (crossRoad == false) {
				if (rand() % 5 == 0) {

					randomX = rand() % (500 + 1 - 200) + 200;

					crossRoad = true;
				}
				else {
					if (rand() % 5 == 0) {
						randomX = 0;
						randomY = 0;
					}
					else {
						randomX = (rand() % (7) - 3) * 3;
						randomY = (rand() % (7) - 3) * 3;
					}

					randomInterval = rand() % (3) + 1;
					decisionTimer = 0;
				}
			}
		}	
		else {
			decisionTimer += elapsedTimeSeconds;
		}
	}
}

void Squirrel::draw() {
	if (dead) {
		drawing.drawRect(polygon.getPosition(), polygon.getWidth(), polygon.getHeight(), deadColor);
	}
	else {
		drawing.drawRect(polygon.getPosition(), polygon.getWidth(), polygon.getHeight(), color);
	}
}