#include "board.h"

Board board;
std::vector<Vector3> thaneLines;
std::vector<Vector2> breakLines;

bool slide = false, coleman = false;
bool turnLeft = false, turnRight = false;

double movementAngle = 0;
bool flipped = false;
void updateBoard(int elapsedTime, int speedZone) {
	float deltaTimeS = (float)(elapsedTime) / 1000;

	board.velocity += (board.wheel.rollSpeed + speedZone) * deltaTimeS;

	if (std::find(keyList.begin(), keyList.end(), SDLK_SPACE) != keyList.end() && slide == false) {
		if (board.velocity > board.pushMax) {
			board.velocity += board.tuckSpeed * deltaTimeS;
		}
		else {
			if (board.pushTimer >= board.pushInterval) {
				board.velocity += board.pushSpeed;
				board.pushTimer = 0;
			}
		}
	}

	if (board.pushTimer < board.pushInterval) {
		board.pushTimer += deltaTimeS;
	}

	if (std::find(keyList.begin(), keyList.end(), SDLK_LCTRL) != keyList.end() && slide == false) {
		if (board.shoe.left - (board.velocity * deltaTimeS) / board.shoe.strength < 0) { board.shoe.left = 0; }
		else { board.shoe.left -= (board.velocity * deltaTimeS) / board.shoe.strength; }

		if (board.shoe.left > 0) {
			if (board.velocity - (board.shoe.strength * 15) * deltaTimeS <= 0) { board.velocity = 0; }
			else { board.velocity -= (board.shoe.strength * 15) * deltaTimeS; }

			breakLines.push_back(board.rectangle.bottomLeft());
		}
	}

	if ((std::find(keyList.begin(), keyList.end(), SDLK_LEFT) != keyList.end() && 
		std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) == keyList.end())) {
		turnLeft = true;

		if (std::find(keyList.begin(), keyList.end(), SDLK_d) != keyList.end()) {
			coleman = true;
			slide = true;

			board.rectangle.angle += board.turnSpeed * deltaTimeS * 3;
			movementAngle += board.turnSpeed * deltaTimeS;
		}
		else {
			if (std::find(keyList.begin(), keyList.end(), SDLK_s) != keyList.end()) {
				slide = true;

				if (coleman == true) {
					board.rectangle.angle += (board.turnSpeed * deltaTimeS) * 5;
					movementAngle += (board.turnSpeed * deltaTimeS) / 2;
				}
				else {
					board.rectangle.angle += (board.turnSpeed * deltaTimeS) * 6;
					movementAngle += (board.turnSpeed * deltaTimeS) / 2;
				}
			}
			else {
				if (std::find(keyList.begin(), keyList.end(), SDLK_a) != keyList.end()) {
					slide = true;

					board.rectangle.angle += board.turnSpeed * deltaTimeS * 3;
					movementAngle += board.turnSpeed * deltaTimeS * 2;
				}
				else {
					board.rectangle.angle += board.turnSpeed * deltaTimeS;
					movementAngle += board.turnSpeed * deltaTimeS;
				}	
			}
		}
	}
	else {
		turnLeft = false;
	}

	if ((std::find(keyList.begin(), keyList.end(), SDLK_RIGHT) != keyList.end() && 
		std::find(keyList.begin(), keyList.end(), SDLK_LEFT) == keyList.end())) {
		turnRight = true;

		if (std::find(keyList.begin(), keyList.end(), SDLK_d) != keyList.end()) {
			coleman = true;
			slide = true;

			board.rectangle.angle -= board.turnSpeed * deltaTimeS * 3;
			movementAngle -= board.turnSpeed * deltaTimeS;
		}
		else {
			if (std::find(keyList.begin(), keyList.end(), SDLK_s) != keyList.end()) {
				slide = true;

				if (coleman == true) {
					board.rectangle.angle -= board.turnSpeed * deltaTimeS * 5;
					movementAngle -= board.turnSpeed * deltaTimeS / 3;
				}
				else {
					board.rectangle.angle -= board.turnSpeed * deltaTimeS * 6;
					movementAngle -= board.turnSpeed * deltaTimeS / 3;
				}
			}
			else {
				if (std::find(keyList.begin(), keyList.end(), SDLK_a) != keyList.end()) {
					slide = true;

					board.rectangle.angle -= board.turnSpeed * deltaTimeS * 3;
					movementAngle -= board.turnSpeed * deltaTimeS * 2;
				}
				else {
					board.rectangle.angle -= board.turnSpeed * deltaTimeS;
					movementAngle -= board.turnSpeed * deltaTimeS;
				}
			}
		}
	}
	else {
		turnRight = false;
	}

	double difference;
	if (coleman) { difference = abs(board.rectangle.angle - movementAngle) * 3 * deltaTimeS; }
	else { difference = abs(board.rectangle.angle - movementAngle) * 1.5 * deltaTimeS; }

	if (movementAngle > board.rectangle.angle) { 
		if ((slide == false && turnRight == false) || turnLeft == true) {
			if (turnLeft == true) {
				board.rectangle.angle += 120 * deltaTimeS; 
			}
			board.rectangle.angle += 150 * deltaTimeS; 
		}

		if (movementAngle - board.rectangle.angle > 5) {
			if (board.velocity - difference < 0) {
				board.velocity = 0;
			}
			else {
				board.velocity -= difference;
			}

			if (coleman) { generateThane(255); }
			else { generateThane(100); }
		}
		else {
			coleman = false;
		}

		board.rectangle.angle += 20 * deltaTimeS; 

		if (movementAngle - board.rectangle.angle > 90) {
			movementAngle -= 180;
			flipped = !flipped;
		}
	}

	if (movementAngle < board.rectangle.angle) { 
		if ((slide == false && turnLeft == false) || turnRight == true) {
			if (turnRight == true) {
				board.rectangle.angle -= 120 * deltaTimeS; 
			}
			board.rectangle.angle -= 150 * deltaTimeS; 
		}
		if (board.rectangle.angle - movementAngle > 5) {
			if (board.velocity - difference < 0) {
				board.velocity = 0;
			}
			else {
				board.velocity -= difference;
			}

			if (coleman) { generateThane(255); }
			else { generateThane(100); }
		}
		else {
			coleman = false;
		}

		board.rectangle.angle -= 20 * deltaTimeS;

		if (board.rectangle.angle - movementAngle > 90) {
			movementAngle += 180;
			flipped = !flipped;
		}
	}

	if (std::find(keyList.begin(), keyList.end(), SDLK_i) != keyList.end()) {
		thaneLines.clear();
		breakLines.clear();
	}

	Vector2 direction = Vector2((float)cos((-movementAngle * M_PI) / 180), sin((-movementAngle * M_PI) / 180));
	direction.normalize();
	if (flipped) { board.rectangle.position -= (direction * deltaTimeS) * board.velocity; }
	else { board.rectangle.position += (direction * deltaTimeS) * board.velocity; }

	slide = false;
	//coleman = false;
}

void generateThane(int multiplier) {
	double thaneAlpha = pow(board.velocity / 600, 2) * multiplier;
	thaneLines.push_back(Vector3(board.rectangle.topLeft(), thaneAlpha));
	thaneLines.push_back(Vector3(board.rectangle.topRight(), thaneAlpha));
	thaneLines.push_back(Vector3(board.rectangle.bottomLeft(), thaneAlpha));
	thaneLines.push_back(Vector3(board.rectangle.bottomRight(), thaneAlpha));
}

void resetBoard() {
	board.rectangle.position = board.initialPosition;
	board.rectangle.angle = 0;
	movementAngle = 0;
	board.velocity = 0;
	flipped = false;

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