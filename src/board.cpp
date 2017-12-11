#include "board.h"

Board board;
std::vector<Vector3> thaneLines;
std::vector<Vector2> breakLines;

bool slide = false;
double movementAngle = 0;
void updateBoard(int elapsedTime, int speedZone) {
	float deltaTimeS = (float)(elapsedTime) / 1000;

	if (std::find(keyList.begin(), keyList.end(), SDLK_SPACE) != keyList.end()) {
		board.velocity += 0.5;
	}

	if (std::find(keyList.begin(), keyList.end(), SDLK_LCTRL) != keyList.end() && board.velocity > 0) {
		board.velocity -= 0.5;
	}

	if ((std::find(keyList.begin(), keyList.end(), SDLK_LEFT) != keyList.end() && 
		std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) == keyList.end())) {
		if (std::find(keyList.begin(), keyList.end(), SDLK_a) != keyList.end()) {
			board.rectangle.angle += (board.velocity * deltaTimeS) / 2;
			movementAngle += (board.velocity * deltaTimeS) / 3;

			slide = true;
		}
		else {
			board.rectangle.angle += (board.velocity * deltaTimeS) / 4;
			movementAngle += (board.velocity * deltaTimeS) / 4;
		}
	}

	if ((std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) != keyList.end() && 
		std::find(keyList.begin(), keyList.end(), SDLK_LEFT) == keyList.end())) {
		if (std::find(keyList.begin(), keyList.end(), SDLK_d) != keyList.end()) {
			board.rectangle.angle -= (board.velocity * deltaTimeS) / 2;
			movementAngle -= (board.velocity * deltaTimeS) / 3;

			slide = true;
		}
		else {
			board.rectangle.angle -= (board.velocity * deltaTimeS) / 4;
			movementAngle -= (board.velocity * deltaTimeS) / 4;
		}
	}

	if (movementAngle > board.rectangle.angle) { 
		if (slide == false) {
			board.rectangle.angle += 0.5; 
		}

		board.rectangle.angle += 0.01; 
	}
	if (movementAngle < board.rectangle.angle) { 
		if (slide == false) {
			board.rectangle.angle -= 0.5; 
		}

		board.rectangle.angle += 0.01; 
	}

	Vector2 direction = Vector2((float)cos((-movementAngle * M_PI) / 180), sin((-movementAngle * M_PI) / 180));
	direction.normalize();
	board.rectangle.position += (direction * deltaTimeS) * board.velocity;
	slide = false;
}

void resetBoard() {
	board.rectangle.position = board.initialPosition;
	board.rectangle.angle = 0;
	movementAngle = 0;
	board.velocity = 0;

	board.shoe.left = board.shoe.initial;
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
	for (Vector3 line : thaneLines) { if (line.x < visibleFrame.sRight() && line.x > visibleFrame.sLeft()) { drawPoint(Vector2(line.x, line.y), board.wheel.thaneColor, line.z); }}
	for (Vector2 line : breakLines) { if (line.x < visibleFrame.sRight() && line.x > visibleFrame.sLeft()) { drawPoint(line, board.shoe.breakColor); }}
		
	// if (isTuck == true) {
	// 	drawRect(board.rectangle.position, board.rectangle.width, board.rectangle.height, board.rectangle.angle, board.tuckColor);
	// }
	// else {
	// 	drawRect(board.rectangle.position, board.rectangle.width, board.rectangle.height, board.rectangle.angle, board.color);
	// }
	// drawLine(board.rectangle.topLeft(), board.rectangle.topRight(), board.outlineColor);
	// drawLine(board.rectangle.topRight(), board.rectangle.bottomRight(), board.outlineColor);
	// drawLine(board.rectangle.bottomLeft(), board.rectangle.topLeft(), board.outlineColor);
	// drawLine(board.rectangle.bottomLeft(), board.rectangle.bottomRight(), board.outlineColor);

	//board.polylist.draw();
	board.polylist.drawOutline();
}

void linkBoard(const char* path, Vector2 initialPosition, double width, double height) {
	board.polylist = { width, height, {board.boardColor[0], board.boardColor[1], board.boardColor[2]}};

	board.initialPosition = initialPosition;
	board.rectangle = VRectangle(initialPosition, width, height, 0);
	board.polylist.setVertices("board_1.txt");
}