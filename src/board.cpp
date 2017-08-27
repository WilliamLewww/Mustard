#include "board.h"

Board board;
std::vector<Vector2> thaneLines;
std::vector<double> thaneAngle;

bool slideLeft = false, slideRight = false;
double startSlideAngle = 0, slideDistance = 1;
void updateBoard(int elapsedTime) {
	float deltaTimeS = (float)(elapsedTime) / 1000;

	if (std::find(keyList.begin(), keyList.end(), SDLK_LEFT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) == keyList.end()) {
		if (board.velocity > board.turnSpeed) { board.rotation += (board.turnSpeed * deltaTimeS) + ((slideDistance - 1) / 250); }
		else { board.rotation += board.velocity * deltaTimeS; }
		if (slideLeft == true) { board.rotation += (board.velocity * deltaTimeS) / 8; }
	}
	else { slideLeft = false; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_LEFT) == keyList.end()) {
		if (board.velocity > board.turnSpeed) { board.rotation -= (board.turnSpeed * deltaTimeS) + ((slideDistance - 1) / 250); }
		else { board.rotation -= board.velocity * deltaTimeS; }
		if (slideRight == true) { board.rotation -= (board.velocity * deltaTimeS) / 8;  }
	}
	else { slideRight = false; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_LALT) != keyList.end()) { slideLeft = true; slideRight = true; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_LALT) == keyList.end()) { startSlideAngle = board.rotation; slideDistance = 1; slideLeft = false; slideRight = false; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_LCTRL) != keyList.end()) {
		if (board.velocity - board.breakSpeed * deltaTimeS <= 0) { board.velocity = 0; }
		else { board.velocity -= board.breakSpeed * deltaTimeS; }
	}
	if (std::find(keyList.begin(), keyList.end(), SDLK_SPACE) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_LCTRL) == keyList.end()) {
		if (board.velocity < board.pushSpeed) { board.velocity = board.pushSpeed; }
		else { board.velocity += 50 * deltaTimeS; }
	}
	else { board.velocity += 10 * deltaTimeS; }
	if (slideLeft == true || slideRight == true) {
		Vector2 direction = Vector2((float)cos(((-board.rotation + ((board.rotation - startSlideAngle) / slideDistance)) * M_PI) / 180), 
										   sin(((-board.rotation + ((board.rotation - startSlideAngle) / slideDistance)) * M_PI) / 180));
		direction.Normalize();
		if (slideDistance > 3.5) {
			if (startSlideAngle > board.rotation) { board.rotation += 0.2; startSlideAngle -= 0.2; }
			if (startSlideAngle < board.rotation) { board.rotation -= 0.2; startSlideAngle += 0.2; }
		}
		board.position += (direction * deltaTimeS) * board.velocity;
		slideDistance += board.velocity * deltaTimeS / 100;
		std::cout << slideDistance << std::endl;
		if (board.velocity - (board.breakSpeed / 4) * deltaTimeS <= 0) { board.velocity = 0; }
		else { board.velocity -= (board.breakSpeed / 3) * deltaTimeS; }

		thaneAngle.push_back(board.rotation);
		thaneLines.push_back(board.position);
	}
	else {
		Vector2 direction = Vector2((float)cos((-board.rotation * M_PI) / 180), sin((-board.rotation * M_PI) / 180));
		direction.Normalize();
		board.position += (direction * deltaTimeS) * board.velocity;
	}
}

void drawBoard() {
	drawRect(board.position, board.length, board.width, board.rotation);

	//GPU heavy due to transformations and rotations
	for (int x = 0; x < thaneLines.size(); x++) {
		int thaneColor[3] = { 255, 0, 0 };
		drawEdgesOfRect(thaneLines[x], board.length, board.width, thaneAngle[x], thaneColor);
	}
}