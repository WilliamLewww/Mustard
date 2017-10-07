#include "board.h"

Board board;
std::vector<Vector3> thaneLines;
std::vector<Vector2> breakLines;

bool turnRight = false, turnLeft = false;
bool slideLeft = false, slideRight = false, recover = false, releaseSlide = false;
double startSlideAngle = 0, slideDistance = 1;
double pushTimer = board.pushInterval, slideTimer = 0;
void updateBoard(int elapsedTime, int speedZone) {
	float deltaTimeS = (float)(elapsedTime) / 1000;

	if ((std::find(keyList.begin(), keyList.end(), SDLK_LEFT) != keyList.end() && 
		std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) == keyList.end()) ||
		controllerPad == 6 || controllerPad == 7 || controllerPad == 8) {
		turnLeft = true;
		if (board.velocity > board.turnSpeed) { 
			board.velocity -= (board.breakSpeed / 6) * deltaTimeS;
			board.rectangle.angle += (board.velocity * deltaTimeS) / 4;
			board.rectangle.angle += (board.turnSpeed * deltaTimeS) + ((slideDistance - 1) / 250); 
		}
		else { board.rectangle.angle += board.velocity * deltaTimeS; }
		if (slideLeft == true) { board.rectangle.angle += (board.velocity * deltaTimeS) / 5; }
	}
	else { slideLeft = false; turnLeft = false; }
	if ((std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) != keyList.end() && 
		std::find(keyList.begin(), keyList.end(), SDLK_LEFT) == keyList.end()) ||
		controllerPad == 2 || controllerPad == 3 || controllerPad == 4) {
		turnRight = true;
		if (board.velocity > board.turnSpeed) { 
			board.velocity -= (board.breakSpeed / 6) * deltaTimeS;
			board.rectangle.angle -= (board.velocity * deltaTimeS) / 4;
			board.rectangle.angle -= (board.turnSpeed * deltaTimeS) + ((slideDistance - 1) / 250); 
		}
		else { board.rectangle.angle -= board.velocity * deltaTimeS; }
		if (slideRight == true) { board.rectangle.angle -= (board.velocity * deltaTimeS) / 5;  }
	}
	else { slideRight = false; turnRight = false; }
	if ((std::find(keyList.begin(), keyList.end(), SDLK_LALT) != keyList.end() ||
		std::find(controllerList.begin(), controllerList.end(), SDL_CONTROLLER_BUTTON_B) != controllerList.end())
		&& (turnRight == true || turnLeft == true) && releaseSlide == false) { slideLeft = true; slideRight = true; recover = true; releaseSlide = true; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_LALT) == keyList.end() &&
		std::find(controllerList.begin(), controllerList.end(), SDL_CONTROLLER_BUTTON_B) == controllerList.end()) { 
		if (recover == false) {
			startSlideAngle = board.rectangle.angle; slideDistance = 1; slideTimer = 0; 
		}
		if (releaseSlide == false && recover == false) {
			slideLeft = false; slideRight = false;
		}
		releaseSlide = false;
	}
	if (std::find(keyList.begin(), keyList.end(), SDLK_LCTRL) != keyList.end() ||
		std::find(controllerList.begin(), controllerList.end(), SDL_CONTROLLER_BUTTON_X) != controllerList.end()) {
		if (board.shoeLeft - (board.velocity * deltaTimeS) / board.shoeStrength < 0) { board.shoeLeft = 0; }
		else { board.shoeLeft -= (board.velocity * deltaTimeS) / board.shoeStrength; }
			
		if (board.shoeLeft > 0) {
			if (board.velocity - board.breakSpeed * deltaTimeS <= 0) { board.velocity = 0; }
			else { board.velocity -= board.breakSpeed * deltaTimeS; }
			if (recover == true) {
				if (startSlideAngle > board.rectangle.angle) { board.rectangle.angle += board.recoverRate * 3 * (slideDistance * slideTimer / 2); startSlideAngle -= board.recoverRate * 3 * (slideDistance * slideTimer / 2); }
				if (startSlideAngle < board.rectangle.angle) { board.rectangle.angle -= board.recoverRate * 3 * (slideDistance * slideTimer / 2); startSlideAngle += board.recoverRate * 3 * (slideDistance * slideTimer / 2); }
			}

			breakLines.push_back(board.rectangle.bottomLeft());
		}
	}

	if (pushTimer <= board.pushInterval) { pushTimer += deltaTimeS; }
	if ((std::find(keyList.begin(), keyList.end(), SDLK_SPACE) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_LCTRL) == keyList.end()) ||
		(std::find(controllerList.begin(), controllerList.end(), SDL_CONTROLLER_BUTTON_A) != controllerList.end()) && std::find(controllerList.begin(), controllerList.end(), SDL_CONTROLLER_BUTTON_X) == controllerList.end()) {
		if (pushTimer >= board.pushInterval && board.velocity < 200 && slideLeft == false && slideRight == false && recover == false) { board.velocity += board.pushSpeed; pushTimer = 0; }
		if (board.velocity > 200 && slideLeft == false && slideRight == false && recover == false) {  board.velocity += board.tuckSpeed * deltaTimeS; }
	}
	board.velocity += (board.rollSpeed + speedZone) * deltaTimeS;
	if (slideLeft == true || slideRight == true || recover == true) {
		slideTimer += deltaTimeS;
		Vector2 direction = Vector2((float)cos(((-board.rectangle.angle + ((board.rectangle.angle - startSlideAngle) / slideDistance)) * M_PI) / 180), 
										   sin(((-board.rectangle.angle + ((board.rectangle.angle - startSlideAngle) / slideDistance)) * M_PI) / 180));
		direction.normalize();

		if (startSlideAngle > board.rectangle.angle) { board.rectangle.angle += board.recoverRate * (slideDistance * slideTimer / 2); startSlideAngle -= board.recoverRate * (slideDistance * slideTimer / 2); }
		if (startSlideAngle < board.rectangle.angle) { board.rectangle.angle -= board.recoverRate * (slideDistance * slideTimer / 2); startSlideAngle += board.recoverRate * (slideDistance * slideTimer / 2); }

		if (slideTimer > 0.2) {
			if (abs(board.rectangle.angle - startSlideAngle) < 30) { recover = false; }
		}
		board.rectangle.position += (direction * deltaTimeS) * board.velocity;
		slideDistance += board.velocity * deltaTimeS / 100;
		
		double difference = abs(board.rectangle.angle - startSlideAngle) + (board.breakSpeed / 5);
		if (board.velocity - difference * deltaTimeS <= 0) { board.velocity = 0; }
		else { board.velocity -= difference * deltaTimeS; }

		double thaneAlpha = pow(board.velocity / 600, 2) * 255;
		thaneLines.push_back(Vector3(board.rectangle.topLeft(), thaneAlpha));
		thaneLines.push_back(Vector3(board.rectangle.topRight(), thaneAlpha));
		thaneLines.push_back(Vector3(board.rectangle.bottomLeft(), thaneAlpha));
		thaneLines.push_back(Vector3(board.rectangle.bottomRight(), thaneAlpha));
	}
	else {
		Vector2 direction = Vector2((float)cos((-board.rectangle.angle * M_PI) / 180), sin((-board.rectangle.angle * M_PI) / 180));
		direction.normalize();
		board.rectangle.position += (direction * deltaTimeS) * board.velocity;
	}

	if (std::find(keyList.begin(), keyList.end(), SDLK_r) != keyList.end() || std::find(controllerList.begin(), controllerList.end(), SDL_CONTROLLER_BUTTON_Y) != controllerList.end()) {
		thaneLines.clear();
		breakLines.clear();
	}

	cameraPosition.x = board.rectangle.position.x;
	cameraPosition.y = board.rectangle.position.y;
}

void resetBoard() {
	board.rectangle.position = board.initialPosition;
	cameraPosition = board.rectangle.position;
	board.rectangle.angle = 0;
	board.velocity = 0;

	slideLeft = false;
	slideRight = false;
	recover = false;
	startSlideAngle = 0;
	slideDistance = 1;
	board.shoeLeft = board.shoeLeftInitial;
	pushTimer = board.pushInterval;
	slideTimer = 0;
}

void handleCollision(Vector2* wall) {
	if (board.rectangle.checkCollision(wall) == true) {
		resetBoard();
	}
}

void handleCollision(Vector2 pointA, Vector2 pointB) {
	Vector2 tempVector[] = { pointA, pointB };
	if (board.rectangle.checkCollision(tempVector) == true) {
		resetBoard();
	}
}

void drawBoard() {
	for (Vector3 line : thaneLines) { if (line.x < visibleFrame.sRight() && line.x > visibleFrame.sLeft()) { drawPoint(Vector2(line.x, line.y), board.thaneColor, line.z); }}
	for (Vector2 line : breakLines) { if (line.x < visibleFrame.sRight() && line.x > visibleFrame.sLeft()) { drawPoint(line, board.breakColor); }}
		
	drawRect(board.rectangle.position, board.rectangle.width, board.rectangle.height, board.rectangle.angle, board.color);
	drawLine(board.rectangle.topLeft(), board.rectangle.topRight(), board.outlineColor);
	drawLine(board.rectangle.topRight(), board.rectangle.bottomRight(), board.outlineColor);
	drawLine(board.rectangle.bottomLeft(), board.rectangle.topLeft(), board.outlineColor);
	drawLine(board.rectangle.bottomLeft(), board.rectangle.bottomRight(), board.outlineColor);
}