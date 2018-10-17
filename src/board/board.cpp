#include "board.h"

void Board::initialize() {
	initializeDeck();
	initializeWheel();
	linkPolygonWithConfigurations();
	bitmapPolygon.setPosition(Vector2(0, 0));

	particleManager.initialize();
}

void Board::initializeDeck() {
	deck = profile.getDeckFromList(configuration.getConfigurations()["SelectedDeck"]);

	configuration.setConfiguration("BoardColorR", deck->getColor()[0]);
	configuration.setConfiguration("BoardColorG", deck->getColor()[1]);
	configuration.setConfiguration("BoardColorB", deck->getColor()[2]);
}

void Board::initializeWheel() {
	wheel = profile.getWheelFromList(configuration.getConfigurations()["SelectedWheel"]);

	configuration.setConfiguration("ThaneColorR", wheel->getColor()[0]);
	configuration.setConfiguration("ThaneColorG", wheel->getColor()[1]);
	configuration.setConfiguration("ThaneColorB", wheel->getColor()[2]);
}

void Board::linkPolygonWithConfigurations() {
	thaneColor[0] = wheel->getColor()[0];
	thaneColor[1] = wheel->getColor()[1];
	thaneColor[2] = wheel->getColor()[2];
	
	bitmapPolygon.setColor(deck->getColor()[0], deck->getColor()[1], deck->getColor()[2], 255);
	bitmapPolygon.setSize(deck->getLength(), deck->getWidth());
	bitmapPolygon.setVertices(profile.getDeckModel(deck->getID()));
}

void Board::update(int speedZone, int trackDirection) {
	elapsedTimeSeconds = timer.getTimeSeconds();

	addSpeedFromHill(speedZone, trackDirection);
	handleLeftTurn();
	handleRightTurn();
	handlePushTuck();
	handleWobble();

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

void Board::subtractSpeedExternal(float speed) {
	if (velocity - speed < 0) { velocity = 0; }
	else { velocity -= speed; }
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

void Board::handleWobble() {
	if (velocity > 250 && !slide) {
		if (input.checkKeyDown(SDLK_SPACE)) { wobbleCancel += 3; }
		if (turnLeft || turnRight) { wobbleCancel += 2; }

		if (wobbleCycle >= 0) {
			if (wobbleCancel > 0) {
				bitmapPolygon.setAngle(bitmapPolygon.getAngle() + ((wobbleMagnitude / wobbleCancel) * elapsedTimeSeconds));
				movementAngle += (wobbleMagnitude / wobbleCancel) * elapsedTimeSeconds;
			}
			else {
				bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (wobbleMagnitude * elapsedTimeSeconds));
				movementAngle += wobbleMagnitude * elapsedTimeSeconds;
			}
		}
		else {
			if (wobbleCancel > 0) {
				bitmapPolygon.setAngle(bitmapPolygon.getAngle() - ((wobbleMagnitude / wobbleCancel) * elapsedTimeSeconds));
				movementAngle -= (wobbleMagnitude / wobbleCancel) * elapsedTimeSeconds;
			}
			else {
				bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (wobbleMagnitude * elapsedTimeSeconds));
				movementAngle -= wobbleMagnitude * elapsedTimeSeconds;
			}
		}

		if (wobbleCycle >= 10) {
			wobbleCycle = -10;
		}

		wobbleCycle += (25 + (wobbleMagnitude * 0.85)) * elapsedTimeSeconds;
		wobbleMagnitude += (velocity / 1500.0);
		wobbleCancel = 0;
	}
	else {
		wobbleMagnitude = velocity - 225;
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

void Board::handleLeftTurn() {
	if ((input.checkKeyDown(SDLK_LEFT) && !input.checkKeyDown(SDLK_RIGHT)) || input.getControllerPadInput() == 7) {
		turnLeft = true;

		if (input.checkKeyDown(SDLK_d) || input.checkButtonDown(1)) {
			slide = true;

			if (forcedSlide) {
				bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (getTurnSpeed() * elapsedTimeSeconds * 4));
				movementAngle += getTurnSpeed() * elapsedTimeSeconds / 2;
			}
			else {
				shutdownSlide = true;

				bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (getTurnSpeed() * elapsedTimeSeconds * 3));
				movementAngle += getTurnSpeed() * elapsedTimeSeconds;
			}
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
				if (input.checkKeyDown(SDLK_a) || input.checkButtonDown(2) || forcedSlide) {
					slide = true;

					if (forcedSlide && (input.checkKeyDown(SDLK_a) || input.checkButtonDown(2))) {
						bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (getTurnSpeed() * elapsedTimeSeconds * 4));
						movementAngle += getTurnSpeed() * elapsedTimeSeconds / 2;
					}
					else {
						bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (getTurnSpeed() * elapsedTimeSeconds * 3));
						movementAngle += getTurnSpeed() * elapsedTimeSeconds * 1.25;
					}
				}
				else {
					bitmapPolygon.setAngle(bitmapPolygon.getAngle() + (getTurnRadius() * elapsedTimeSeconds));
					movementAngle += getTurnRadius() * elapsedTimeSeconds;
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
			slide = true;

			if (forcedSlide) {
				bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (getTurnSpeed() * elapsedTimeSeconds * 4));
				movementAngle -= getTurnSpeed() * elapsedTimeSeconds / 2;
			}
			else {
				shutdownSlide = true;
				
				bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (getTurnSpeed() * elapsedTimeSeconds * 3));
				movementAngle -= getTurnSpeed() * elapsedTimeSeconds;
			}
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
				if (input.checkKeyDown(SDLK_a) || input.checkButtonDown(2) || forcedSlide) {
					slide = true;

					if (forcedSlide && (input.checkKeyDown(SDLK_a) || input.checkButtonDown(2))) {
						bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (getTurnSpeed() * elapsedTimeSeconds * 4));
						movementAngle -= getTurnSpeed() * elapsedTimeSeconds / 2;
					}
					else {
						bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (getTurnSpeed() * elapsedTimeSeconds * 3));
						movementAngle -= getTurnSpeed() * elapsedTimeSeconds * 1.25;
					}
				}
				else {
					bitmapPolygon.setAngle(bitmapPolygon.getAngle() - (getTurnRadius() * elapsedTimeSeconds));
					movementAngle -= getTurnRadius() * elapsedTimeSeconds;
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

		wheel->decayWheel(elapsedTimeSeconds, difference, velocity, shutdownSlide);
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
		
		wheel->decayWheel(elapsedTimeSeconds, difference, velocity, shutdownSlide);
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
	forcedSlide = false;
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

bool Board::checkProximity(Vector2 position) {
	if (bitmapPolygon.getPosition().x + 50 > position.x && bitmapPolygon.getPosition().x < position.x + 50) {
		return true;
	}

	return false;
}

bool Board::checkCollision(Vector2 position, int width, int height) {
	if (bitmapPolygon.getCenter().x > position.x && bitmapPolygon.getCenter().x < position.x + width &&
		bitmapPolygon.getCenter().y > position.y && bitmapPolygon.getCenter().y < position.y + height) {

		return true;
	}

	return false;
}

bool Board::checkCollision(BitmapPolygon polygon) {
	if (bitmapPolygon.checkCollision(polygon) == true) {
		return true;
	}

	return false;
}

bool Board::checkCollision(Vector2* wall) {
	if (bitmapPolygon.checkCollision(wall) == true) {
		return true;
	}

	return false;
}

bool Board::checkCollision(Vector2 pointA, Vector2 pointB) {
	Vector2 tempVector[] = { pointA, pointB };
	if (bitmapPolygon.checkCollision(tempVector) == true) {
		return true;
	}

	return false;
}