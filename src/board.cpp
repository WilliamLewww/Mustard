#include "board.h"

Board board;
std::vector<Vector2> thaneLines;
std::vector<double> thaneAngle;
std::vector<Vector2> breakLines;
std::vector<double> breakAngle;

bool slideLeft = false, slideRight = false, recover = false;
double startSlideAngle = 0, slideDistance = 1;
double pushTimer = board.pushInterval, slideTimer = 0;
void updateBoard(int elapsedTime) {
	float deltaTimeS = (float)(elapsedTime) / 1000;

	if (std::find(keyList.begin(), keyList.end(), SDLK_LEFT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) == keyList.end()) {
		if (board.velocity > board.turnSpeed) { board.rotation += (board.turnSpeed * deltaTimeS) + ((slideDistance - 1) / 250); }
		else { board.rotation += board.velocity * deltaTimeS; }
		if (slideLeft == true) { board.rotation += (board.velocity * deltaTimeS) / 5; }
	}
	else { slideLeft = false; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_LEFT) == keyList.end()) {
		if (board.velocity > board.turnSpeed) { board.rotation -= (board.turnSpeed * deltaTimeS) + ((slideDistance - 1) / 250); }
		else { board.rotation -= board.velocity * deltaTimeS; }
		if (slideRight == true) { board.rotation -= (board.velocity * deltaTimeS) / 5;  }
	}
	else { slideRight = false; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_LALT) != keyList.end()) { slideLeft = true; slideRight = true; recover = true; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_LALT) == keyList.end()) { 
		if (recover == false) {
			startSlideAngle = board.rotation; slideDistance = 1; slideTimer = 0; 
		}
		slideLeft = false; slideRight = false; 
	}
	if (std::find(keyList.begin(), keyList.end(), SDLK_LCTRL) != keyList.end()) {
		if (board.velocity - board.breakSpeed * deltaTimeS <= 0) { board.velocity = 0; }
		else { board.velocity -= board.breakSpeed * deltaTimeS; }
		if (recover == true) {
			if (startSlideAngle > board.rotation) { board.rotation += 0.3 * (slideDistance * slideTimer / 2); startSlideAngle -= 0.3 * (slideDistance * slideTimer / 2); }
			if (startSlideAngle < board.rotation) { board.rotation -= 0.3 * (slideDistance * slideTimer / 2); startSlideAngle += 0.3 * (slideDistance * slideTimer / 2); }
		}
		breakAngle.push_back(board.rotation);
		breakLines.push_back(board.position);
	}

	if (pushTimer <= board.pushInterval) { pushTimer += deltaTimeS; }
	if (std::find(keyList.begin(), keyList.end(), SDLK_SPACE) != keyList.end() && std::find(keyList.begin(), keyList.end(), SDLK_LCTRL) == keyList.end()) {
		if (pushTimer >= board.pushInterval && board.velocity < 200 && slideLeft == false && slideRight == false && recover == false) { board.velocity += board.pushSpeed; pushTimer = 0; }
	}
	else { board.velocity += 10 * deltaTimeS; }
	if (slideLeft == true || slideRight == true || recover == true) {
		slideTimer += deltaTimeS;
		Vector2 direction = Vector2((float)cos(((-board.rotation + ((board.rotation - startSlideAngle) / slideDistance)) * M_PI) / 180), 
										   sin(((-board.rotation + ((board.rotation - startSlideAngle) / slideDistance)) * M_PI) / 180));
		direction.Normalize();
		if (slideTimer > 0.3) {
			if (startSlideAngle > board.rotation) { board.rotation += 0.1 * (slideDistance * slideTimer / 2); startSlideAngle -= 0.1 * (slideDistance * slideTimer / 2); }
			if (startSlideAngle < board.rotation) { board.rotation -= 0.1 * (slideDistance * slideTimer / 2); startSlideAngle += 0.1 * (slideDistance * slideTimer / 2); }
		}
		if (abs(abs(startSlideAngle) - abs(board.rotation)) < 20) {
			recover = false;
		}
		board.position += (direction * deltaTimeS) * board.velocity;
		slideDistance += board.velocity * deltaTimeS / 100;
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

	cameraPosition.x = board.position.x;
	cameraPosition.y = board.position.y;
}

void drawBoard() {
	drawRect(board.position, board.length, board.width, board.rotation);

	//GPU heavy due to transformations and rotations
	for (int x = 0; x < thaneLines.size(); x++) {
		int thaneColor[3] = { 255, 0, 0 };
		drawEdgesOfRect(thaneLines[x], board.length, board.width, thaneAngle[x], thaneColor);
	}

	for (int x = 0; x < breakLines.size(); x++) {
		int breakColor[3] = { 0, 255, 0 };
		drawEdgesOfRect(breakLines[x], board.length, board.width, breakAngle[x], breakColor);
	}
}