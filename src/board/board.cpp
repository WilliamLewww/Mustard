#include "board.h"

void Board::initialize() {
	initializeWheel();
	linkPolygonWithConfigurations();
	bitmapPolygon.setPosition(Vector2(0, 0));
}

void Board::initializeWheel() {
	wheel = getWheel(configuration.getConfigurations()["WheelID"]);
	wheel.setID(configuration.getConfigurations()["WheelID"]);

	configuration.setConfiguration("ThaneColorR", wheel.getColor()[0]);
	configuration.setConfiguration("ThaneColorG", wheel.getColor()[1]);
	configuration.setConfiguration("ThaneColorB", wheel.getColor()[2]);

	particleManager.initialize();
}

void Board::linkPolygonWithConfigurations() {
	thaneColor[0] = wheel.getColor()[0];
	thaneColor[1] = wheel.getColor()[1];
	thaneColor[2] = wheel.getColor()[2];
	
	bitmapPolygon.setColor(configuration.getConfigurations()[("Board" + std::to_string(configuration.getConfigurations()["BoardID"]) + ("ColorR")).c_str()], 
		configuration.getConfigurations()[("Board" + std::to_string(configuration.getConfigurations()["BoardID"]) + ("ColorG")).c_str()], 
		configuration.getConfigurations()[("Board" + std::to_string(configuration.getConfigurations()["BoardID"]) + ("ColorB")).c_str()], 
		configuration.getConfigurations()["BoardColorA"]);

	bitmapPolygon.setSize(configuration.getConfigurations()["BoardLength"], configuration.getConfigurations()["BoardWidth"]);
	std::string boardFileName = "board_" + std::to_string(configuration.getConfigurations()["BoardID"]) + ".txt";
	bitmapPolygon.setVertices(boardFileName.c_str());
}

void Board::update(int speedZone, int trackDirection) {
	elapsedTimeSeconds = timer.getTimeSeconds();

	addSpeedFromHill(speedZone, trackDirection);
	handlePushTuck();
	handleLeftTurn();
	handleRightTurn();

	double difference = getAngleDifference();
	handleSlideRight(difference);
	handleSlideLeft(difference);

	Vector2 direction = getDirection();
	moveInDirection(direction);
	refreshSlide();
}

void Board::draw() {
	bitmapPolygon.drawOutline();
}

void Board::drawThaneLines() {
	for (Vector3 line : thaneLines) { 
		if (camera.checkEntityInVisibleRange(Vector2(line.x, line.y), 0, 0)) {
			drawing.drawPoint(Vector2(line.x, line.y), thaneColor, line.z); 
		}
	}
}

void Board::drawBrakeLines() {
	//for (Vector2 line : brakeLines) { if (line.x < visibleFrame.sRight() && line.x > visibleFrame.sLeft()) { drawing.drawPoint(line, board.shoe.breakColor); }}
}

float Board::getRollSpeed() {
	return rollSpeed * wheel.getRollSpeed();
}

void Board::addSpeedFromHill(int speedZone, int trackDirection) {
	if (bitmapPolygon.getAngle() > trackDirection - 30 && bitmapPolygon.getAngle() < trackDirection + 30) {
		if (bitmapPolygon.getAngle() > trackDirection - 15 && bitmapPolygon.getAngle() < trackDirection + 15) {
			if (bitmapPolygon.getAngle() > trackDirection - 10 && bitmapPolygon.getAngle() < trackDirection + 10) {
				velocity += (getRollSpeed() + speedZone) * 1.2 * elapsedTimeSeconds;
			}
			else {
				velocity += (getRollSpeed() + speedZone) * 1.0 * elapsedTimeSeconds;
			}
		}
		else {
			velocity += (getRollSpeed() + speedZone) * 0.8 * elapsedTimeSeconds;
		}
	}
	else {
		velocity += (getRollSpeed() + speedZone) * 0.5 * elapsedTimeSeconds;
	}
}

void Board::handlePushTuck() {
	if ((input.checkKeyDown(SDLK_SPACE) || input.checkButtonDown(5) || input.checkButtonDown(4)) && slide == false) {
		if (velocity > pushMax) {
			velocity += tuckSpeed * elapsedTimeSeconds;
		}
		else {
			if (pushTimer >= pushInterval) {
				velocity += pushSpeed;
				pushTimer = 0;
			}
		}
	}

	if (pushTimer < pushInterval) {
		pushTimer += elapsedTimeSeconds;
	}
}

void Board::handleFootBrake() {
	// if (std::find(keyList.begin(), keyList.end(), SDLK_LCTRL) != keyList.end() && slide == false) {
	// 	if (board.shoe.left - (board.velocity * deltaTimeS) / board.shoe.strength < 0) { board.shoe.left = 0; }
	// 	else { board.shoe.left -= (board.velocity * deltaTimeS) / board.shoe.strength; }

	// 	if (board.shoe.left > 0) {
	// 		if (board.velocity - (board.shoe.strength * 15) * deltaTimeS <= 0) { board.velocity = 0; }
	// 		else { board.velocity -= (board.shoe.strength * 15) * deltaTimeS; }

	// 		brakeLines.push_back(board.rectangle.bottomLeft());
	// 	}
	// }
}

float Board::getTurnSpeed() {
	return turnSpeed * wheel.getTraction();
}

void Board::handleLeftTurn() {
	if ((input.checkKeyDown(SDLK_LEFT) && !input.checkKeyDown(SDLK_RIGHT)) || input.getControllerPadInput() == 7) {
		turnLeft = true;

		if (input.checkKeyDown(SDLK_d) || input.checkButtonDown(1)) {
			shutdownSlide = true;
			slide = true;

			bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (getTurnSpeed() * elapsedTimeSeconds * 3));
			movementAngle += getTurnSpeed() * elapsedTimeSeconds;
		}
		else {
			if (input.checkKeyDown(SDLK_s) || input.checkButtonDown(0)) {
				slide = true;

				if (shutdownSlide == true) {
					bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (getTurnSpeed() * elapsedTimeSeconds * 5));
					movementAngle += getTurnSpeed() * elapsedTimeSeconds / 3;
				}
				else {
					bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (getTurnSpeed() * elapsedTimeSeconds * 6));
					movementAngle += getTurnSpeed() * elapsedTimeSeconds / 3;
				}
			}
			else {
				if (input.checkKeyDown(SDLK_a) || input.checkButtonDown(2)) {
					slide = true;

					bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (getTurnSpeed() * elapsedTimeSeconds * 3));
					movementAngle += getTurnSpeed() * elapsedTimeSeconds * 1.25;
				}
				else {
					bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (turnSpeed * elapsedTimeSeconds));
					movementAngle += turnSpeed * elapsedTimeSeconds;
				}	
			}
		}
	}
	else {
		turnLeft = false;
	}
}

void Board::handleRightTurn() {
	if ((input.checkKeyDown(SDLK_RIGHT) && !input.checkKeyDown(SDLK_LEFT)) || input.getControllerPadInput() == 3) {
		turnRight = true;

		if (input.checkKeyDown(SDLK_d) || input.checkButtonDown(1)) {
			shutdownSlide = true;
			slide = true;

			bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (getTurnSpeed() * elapsedTimeSeconds * 3));
			movementAngle -= getTurnSpeed() * elapsedTimeSeconds;
		}
		else {
			if (input.checkKeyDown(SDLK_s) || input.checkButtonDown(0)) {
				slide = true;

				if (shutdownSlide == true) {
					bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (getTurnSpeed() * elapsedTimeSeconds * 5));
					movementAngle -= getTurnSpeed() * elapsedTimeSeconds / 3;
				}
				else {
					bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (getTurnSpeed() * elapsedTimeSeconds * 6));
					movementAngle -= getTurnSpeed() * elapsedTimeSeconds / 3;
				}
			}
			else {
				if (input.checkKeyDown(SDLK_a) || input.checkButtonDown(2)) {
					slide = true;

					bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (getTurnSpeed() * elapsedTimeSeconds * 3));
					movementAngle -= getTurnSpeed() * elapsedTimeSeconds * 1.25;
				}
				else {
					bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (turnSpeed * elapsedTimeSeconds));
					movementAngle -= turnSpeed * elapsedTimeSeconds;
				}
			}
		}
	}
	else {
		turnRight = false;
	}
}

double Board::getAngleDifference() {
	if (shutdownSlide) { return abs(bitmapPolygon.getAngle() - movementAngle) * 3 * elapsedTimeSeconds; }
	else { return abs(bitmapPolygon.getAngle() - movementAngle) * 1.5 * elapsedTimeSeconds; }

}

void Board::handleSlideRight(double difference) {
	if (movementAngle > bitmapPolygon.getAngle()) { 
		if ((slide == false && turnRight == false) || turnLeft == true) {
			if (turnLeft == true) {
				bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (120 * elapsedTimeSeconds)); 
			}
			bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (150 * elapsedTimeSeconds)); 
		}

		if (movementAngle - bitmapPolygon.getAngle() > 5) {
			if (velocity - difference < 0) {
				velocity = 0;
			}
			else {
				velocity -= difference;
			}

			if (shutdownSlide) { generateThane(255); }
			else { generateThane(100); }
		}
		else {
			shutdownSlide = false;
		}

		if (slide == true) {
			bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (20 * elapsedTimeSeconds));  
		}

		if (shutdownSlide) {
			if (movementAngle - bitmapPolygon.getAngle() > 75) {
				movementAngle -= 180;
				flipped = !flipped;
			}
		}
		else {
			if (movementAngle - bitmapPolygon.getAngle() > 60) {
				movementAngle -= 180;
				flipped = !flipped;
			}
		}

		wheel.decayWheel(elapsedTimeSeconds, difference, velocity);
	}
}

void Board::handleSlideLeft(double difference) {
	if (movementAngle < bitmapPolygon.getAngle()) { 
		if ((slide == false && turnLeft == false) || turnRight == true) {
			if (turnRight == true) {
				bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (120 * elapsedTimeSeconds)); 
			}
			bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (150 * elapsedTimeSeconds));  
		}
		if (bitmapPolygon.getAngle() - movementAngle > 5) {
			if (velocity - difference < 0) {
				velocity = 0;
			}
			else {
				velocity -= difference;
			}

			if (shutdownSlide) { generateThane(255); }
			else { generateThane(100); }
		}
		else {
			shutdownSlide = false;
		}

		if (slide == true) {
			bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (20 * elapsedTimeSeconds));  
		}

		if (shutdownSlide) {
			if (bitmapPolygon.getAngle() - movementAngle > 75) {
				movementAngle += 180;
				flipped = !flipped;
			}
		}
		else {
			if (bitmapPolygon.getAngle() - movementAngle > 60) {
				movementAngle += 180;
				flipped = !flipped;
			}
		}
		
		wheel.decayWheel(elapsedTimeSeconds, difference, velocity);
	}
}

Vector2 Board::getDirection() {
	Vector2 direction = Vector2((float)cos((-movementAngle * M_PI) / 180), sin((-movementAngle * M_PI) / 180));
	direction.normalize();
	return direction;
}

void Board::moveInDirection(Vector2 direction) {
	if (flipped) { bitmapPolygon.setPosition(bitmapPolygon.getPosition() - ((direction * elapsedTimeSeconds) * velocity)); }
	else { bitmapPolygon.setPosition(bitmapPolygon.getPosition() + ((direction * elapsedTimeSeconds) * velocity)); }
}

void Board::refreshSlide() {
	slide = false;
}

void Board::generateThane(int multiplier) {
	double thaneAlpha = pow(velocity / 600, 2) * multiplier;
	thaneLines.push_back(Vector3(bitmapPolygon.getTopLeft(), thaneAlpha));
	thaneLines.push_back(Vector3(bitmapPolygon.getTopRight(), thaneAlpha));
	thaneLines.push_back(Vector3(bitmapPolygon.getBottomLeft(), thaneAlpha));
	thaneLines.push_back(Vector3(bitmapPolygon.getBottomRight(), thaneAlpha));

	if (elapsedTimeSeconds > 0.01) {
		if (rand() % 2 == 0) {
			particleManager.generateThaneParticles(1, bitmapPolygon.getTopLeft(), thaneAlpha + 25);
			particleManager.generateThaneParticles(1, bitmapPolygon.getTopRight(), thaneAlpha + 25);
			particleManager.generateThaneParticles(1, bitmapPolygon.getBottomLeft(), thaneAlpha + 25);
			particleManager.generateThaneParticles(1, bitmapPolygon.getBottomRight(), thaneAlpha + 25);
		}
	}
	else {
		if (rand() % 7 == 0) {
			particleManager.generateThaneParticles(1, bitmapPolygon.getTopLeft(), thaneAlpha + 50);
			particleManager.generateThaneParticles(1, bitmapPolygon.getTopRight(), thaneAlpha + 50);
			particleManager.generateThaneParticles(1, bitmapPolygon.getBottomLeft(), thaneAlpha + 50);
			particleManager.generateThaneParticles(1, bitmapPolygon.getBottomRight(), thaneAlpha + 50);
		}
	}
}

void Board::clearLines() {
	thaneLines.clear();
	brakeLines.clear();
}

void Board::reset() {
	bitmapPolygon.setPosition(Vector2(0, 0));
	bitmapPolygon.setAngle(0);
	movementAngle = 0;
	velocity = 0;
	flipped = false;
}

bool Board::handleCollision(BitmapPolygon polygon) {
	if (bitmapPolygon.checkCollision(polygon) == true) {
		return true;
	}

	return false;
}

bool Board::handleCollision(Vector2* wall) {
	if (bitmapPolygon.checkCollision(wall) == true) {
		return true;
	}

	return false;
}

bool Board::handleCollision(Vector2 pointA, Vector2 pointB) {
	Vector2 tempVector[] = { pointA, pointB };
	if (bitmapPolygon.checkCollision(tempVector) == true) {
		return true;
	}

	return false;
}