#include "n_board.h"

NBoard::NBoard(int ID) {
	this->ID = ID;

	position = Vector2(0, 0);
	positionSpeed = Vector2(0, 0);
	angle = 0;
	angleSpeed = 0;
	startTime = timer.getTotalTimeSeconds();
	endTime = timer.getTotalTimeSeconds();
}

void NBoard::addDataFromString(std::string data) {
	std::string tempMessage(data);

	if (!isAlive) {
		position = Vector2(0, 0);
		positionSpeed = Vector2(0, 0);
		angle = 0;
		angleSpeed = 0;
		startTime = timer.getTotalTimeSeconds();
		endTime = timer.getTotalTimeSeconds();

		isAlive = true;
	}
	else {
		Vector2 tempPosition;
		tempPosition.x = std::stod(tempMessage.substr(0, tempMessage.find(':')));
		tempMessage = tempMessage.substr(tempMessage.find(':') + 1);

		tempPosition.y = std::stod(tempMessage.substr(0, tempMessage.find(':')));
		tempMessage = tempMessage.substr(tempMessage.find(':') + 1);

		positionList.push(tempPosition);
		angleList.push(std::stod(tempMessage));

		startTime = endTime;
		endTime = timer.getTotalTimeSeconds();
	}
}

void NBoard::update() {
	if (!angleList.empty()) {
		if (angleSpeed == 0) {
			angleSpeed = (angleList.front() - angle) * (timer.getTimeSeconds() / (endTime - startTime));
		}

		if ((angle < angleList.front() + 2.5 && angleSpeed <= 0) || (angle > angleList.front() - 2.5 && angleSpeed >= 0)) {
			angleSpeed = 0;
			angleList.pop();
		}
		else {
			angle += angleSpeed;
		}
	}

	if (!positionList.empty()) {
		if (positionSpeed.x == 0 && positionSpeed.y == 0) {
			positionSpeed = (positionList.front() - position) * (timer.getTimeSeconds() / (endTime - startTime));
		}

		if (((position.x < positionList.front().x + 2.5 && positionSpeed.x <= 0) || (position.x > positionList.front().x - 2.5 && positionSpeed.x >= 0)) &&
			((position.y < positionList.front().y + 2.5 && positionSpeed.y <= 0) || (position.y > positionList.front().y - 2.5 && positionSpeed.y >= 0))) {
			positionSpeed = Vector2(0, 0);
			positionList.pop();
		}
		else {
			position += positionSpeed;
		}
	}
}

void NBoard::draw() {
	drawing.drawRect(position, width, height, angle);
}