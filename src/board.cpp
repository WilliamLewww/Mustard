#include "board.h"

void Board::initialize() {
	linkPolygonWithConfigurations();
	
	bitmapPolygon.setColor(boardColor[0], boardColor[1], boardColor[2], 255);
	bitmapPolygon.setPosition(Vector2(0, 0));
}

void Board::linkPolygonWithConfigurations() {
	bitmapPolygon.setSize(configuration.getConfigurations()["BoardWidth"], configuration.getConfigurations()["BoardHeight"]);
	std::string boardFileName = "board_" + std::to_string(configuration.getConfigurations()["BoardID"]) + ".txt";
	bitmapPolygon.setVerticesFromFile(boardFileName.c_str());
}

void Board::update(int elapsedTime, int speedZone) {
	elapsedTimeSeconds = (float)(elapsedTime) / 1000;

	addSpeedFromHill(speedZone);
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
	drawThaneLines();
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

void Board::addSpeedFromHill(int speedZone) {
	velocity += (rollSpeed + speedZone) * elapsedTimeSeconds;
}

void Board::handlePushTuck() {
	if (input.checkKeyDown(SDLK_SPACE) && slide == false) {
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

void Board::handleLeftTurn() {
	if (input.checkKeyDown(SDLK_LEFT) && !input.checkKeyDown(SDLK_RIGHT)) {
		turnLeft = true;

		if (input.checkKeyDown(SDLK_d)) {
			shutdownSlide = true;
			slide = true;

			bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (turnSpeed * elapsedTimeSeconds * 3));
			movementAngle += turnSpeed * elapsedTimeSeconds;
		}
		else {
			if (input.checkKeyDown(SDLK_s)) {
				slide = true;

				if (shutdownSlide == true) {
					bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (turnSpeed * elapsedTimeSeconds * 5));
					movementAngle += turnSpeed * elapsedTimeSeconds / 3;
				}
				else {
					bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (turnSpeed * elapsedTimeSeconds * 6));
					movementAngle += turnSpeed * elapsedTimeSeconds / 3;
				}
			}
			else {
				if (input.checkKeyDown(SDLK_a)) {
					slide = true;

					bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (turnSpeed * elapsedTimeSeconds * 3));
					movementAngle += turnSpeed * elapsedTimeSeconds * 1.25;
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
	if (input.checkKeyDown(SDLK_RIGHT) && !input.checkKeyDown(SDLK_LEFT)) {
		turnRight = true;

		if (input.checkKeyDown(SDLK_d)) {
			shutdownSlide = true;
			slide = true;

			bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (turnSpeed * elapsedTimeSeconds * 3));
			movementAngle -= turnSpeed * elapsedTimeSeconds;
		}
		else {
			if (input.checkKeyDown(SDLK_s)) {
				slide = true;

				if (shutdownSlide == true) {
					bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (turnSpeed * elapsedTimeSeconds * 5));
					movementAngle -= turnSpeed * elapsedTimeSeconds / 3;
				}
				else {
					bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (turnSpeed * elapsedTimeSeconds * 6));
					movementAngle -= turnSpeed * elapsedTimeSeconds / 3;
				}
			}
			else {
				if (input.checkKeyDown(SDLK_a)) {
					slide = true;

					bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (turnSpeed * elapsedTimeSeconds * 3));
					movementAngle -= turnSpeed * elapsedTimeSeconds * 1.25;
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

		bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (20 * elapsedTimeSeconds));  

		if (movementAngle - bitmapPolygon.getAngle() > 90) {
			movementAngle -= 180;
			flipped = !flipped;
		}
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

		bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (20 * elapsedTimeSeconds));  

		if (bitmapPolygon.getAngle() - movementAngle > 90) {
			movementAngle += 180;
			flipped = !flipped;
		}
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
}

void Board::clearLines() {
	if (input.checkKeyDown(SDLK_i)) {
		thaneLines.clear();
		brakeLines.clear();
	}
}