#include "board.h"

Board board;
std::vector<Vector2> thaneLines;
std::vector<Vector2> breakLines;

bool slideLeft = false, slideRight = false, recover = false;
double startSlideAngle = 0, slideDistance = 1;
double pushTimer = board.pushInterval, slideTimer = 0;
void updateBoard(int elapsedTime) {
	float deltaTimeS = (float)(elapsedTime) / 1000;

	if (std::find(keyList.begin(), keyList.end(), SDLK_LEFT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) == keyList.end()) {
		if (board.velocity > board.turnSpeed) { 
			board.velocity -= (board.breakSpeed / 5) * deltaTimeS;
			board.rectangle.angle += (board.velocity * deltaTimeS) / 4;
			board.rectangle.angle += (board.turnSpeed * deltaTimeS) + ((slideDistance - 1) / 250); 
		}
		else { board.rectangle.angle += board.velocity * deltaTimeS; }
		if (slideLeft == true) { board.rectangle.angle += (board.velocity * deltaTimeS) / 5; }
	}
	else { slideLeft = false; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_LEFT) == keyList.end()) {
		if (board.velocity > board.turnSpeed) { 
			board.velocity -= (board.breakSpeed / 5) * deltaTimeS;
			board.rectangle.angle -= (board.velocity * deltaTimeS) / 4;
			board.rectangle.angle -= (board.turnSpeed * deltaTimeS) + ((slideDistance - 1) / 250); 
		}
		else { board.rectangle.angle -= board.velocity * deltaTimeS; }
		if (slideRight == true) { board.rectangle.angle -= (board.velocity * deltaTimeS) / 5;  }
	}
	else { slideRight = false; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_LALT) != keyList.end()) { slideLeft = true; slideRight = true; recover = true; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_LALT) == keyList.end()) { 
		if (recover == false) {
			startSlideAngle = board.rectangle.angle; slideDistance = 1; slideTimer = 0; 
		}
		slideLeft = false; slideRight = false; 
	}
	if (std::find(keyList.begin(), keyList.end(), SDLK_LCTRL) != keyList.end()) {
		if (board.velocity - board.breakSpeed * deltaTimeS <= 0) { board.velocity = 0; }
		else { board.velocity -= board.breakSpeed * deltaTimeS; }
		if (recover == true) {
			if (startSlideAngle > board.rectangle.angle) { board.rectangle.angle += 0.3 * (slideDistance * slideTimer / 2); startSlideAngle -= 0.3 * (slideDistance * slideTimer / 2); }
			if (startSlideAngle < board.rectangle.angle) { board.rectangle.angle -= 0.3 * (slideDistance * slideTimer / 2); startSlideAngle += 0.3 * (slideDistance * slideTimer / 2); }
		}
		breakLines.push_back(board.rectangle.topLeft());
		breakLines.push_back(board.rectangle.topRight());
		breakLines.push_back(board.rectangle.bottomLeft());
		breakLines.push_back(board.rectangle.bottomRight());
	}

	if (pushTimer <= board.pushInterval) { pushTimer += deltaTimeS; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_SPACE) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_LCTRL) == keyList.end()) {
		if (pushTimer >= board.pushInterval && board.velocity < 200 && slideLeft == false && slideRight == false && recover == false) { board.velocity += board.pushSpeed; pushTimer = 0; }
	}
	else { board.velocity += 30 * deltaTimeS; }
	if (slideLeft == true || slideRight == true || recover == true) {
		slideTimer += deltaTimeS;
		Vector2 direction = Vector2((float)cos(((-board.rectangle.angle + ((board.rectangle.angle - startSlideAngle) / slideDistance)) * M_PI) / 180), 
										   sin(((-board.rectangle.angle + ((board.rectangle.angle - startSlideAngle) / slideDistance)) * M_PI) / 180));
		direction.normalize();
		if (slideTimer > 0.3) {
			if (startSlideAngle > board.rectangle.angle) { board.rectangle.angle += 0.1 * (slideDistance * slideTimer / 2); startSlideAngle -= 0.1 * (slideDistance * slideTimer / 2); }
			if (startSlideAngle < board.rectangle.angle) { board.rectangle.angle -= 0.1 * (slideDistance * slideTimer / 2); startSlideAngle += 0.1 * (slideDistance * slideTimer / 2); }
		}
		if (abs(abs(startSlideAngle) - abs(board.rectangle.angle)) < 20) {
			recover = false;
		}
		board.rectangle.position += (direction * deltaTimeS) * board.velocity;
		slideDistance += board.velocity * deltaTimeS / 100;
		if (board.velocity - (board.breakSpeed / 2) * deltaTimeS <= 0) { board.velocity = 0; }
		else { board.velocity -= (board.breakSpeed / 2) * deltaTimeS; }

		thaneLines.push_back(board.rectangle.topLeft());
		thaneLines.push_back(board.rectangle.topRight());
		thaneLines.push_back(board.rectangle.bottomLeft());
		thaneLines.push_back(board.rectangle.bottomRight());
	}
	else {
		Vector2 direction = Vector2((float)cos((-board.rectangle.angle * M_PI) / 180), sin((-board.rectangle.angle * M_PI) / 180));
		direction.normalize();
		board.rectangle.position += (direction * deltaTimeS) * board.velocity;
	}

	cameraPosition.x = board.rectangle.position.x;
	cameraPosition.y = board.rectangle.position.y;
}

void drawBoard() {
	int thaneColor[3] = { 255, 0, 0 };
	int breakColor[3] = { 0, 255, 0 };
	
	drawRect(board.rectangle.position, board.rectangle.width, board.rectangle.height, board.rectangle.angle);

	for (Vector2 line : thaneLines) { drawPoint(line, thaneColor); }
	for (Vector2 line : breakLines) { drawPoint(line, breakColor); }
}