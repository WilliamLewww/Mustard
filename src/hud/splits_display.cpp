#include "splits_display.h"

SplitsDisplay::SplitsDisplay(Vector2 position, int width, int height) {
	this->position = position;
	this->width = width;
	this->height = height;
}

void SplitsDisplay::generateCheckpoints(int count, Vector2 firstRail, Vector2 lastRail) {
	currentCheckpointIndex = 0;
	splitTimer = 0;
	rectangleWidth = width / count;

	for (int x = 0; x < count; x++) {
		splitList.push_back(std::vector<float>());

		rectanglePositionList.emplace_back(position.x + (rectangleWidth * x), position.y);
		checkpointList.push_back(((lastRail.x - firstRail.x) / count) * x);
	}
}

void SplitsDisplay::reset() {
	splitTimer = 0;
	currentCheckpointIndex = 0;
}

void SplitsDisplay::update(int elapsedTime, Vector2 bPosition) {
	elapsedTimeSeconds = (float)(elapsedTime) / 1000;

	splitTimer += elapsedTimeSeconds;
	if (bPosition.x > checkpointList[currentCheckpointIndex]) {
		splitList[currentCheckpointIndex].push_back(splitTimer);

		std::cout << splitList[currentCheckpointIndex][splitList[currentCheckpointIndex].size() - 1] << ":" << currentCheckpointIndex << std::endl;

		splitTimer = 0;
		currentCheckpointIndex += 1;
	}
}

void SplitsDisplay::draw() {
	for (int x = 0; x < splitList.size(); x++) {
		drawing.drawRect(rectanglePositionList[x], rectangleWidth, height, getColorFromSplit(splitList[x]));
	}
	
	// for (Vector2 rectanglePosition : rectanglePositionList) {
	// 	drawing.drawRect(rectanglePosition, rectangleWidth, height, color);
	// }

	//drawing.drawRect(position, width, height, color);
}

int* SplitsDisplay::getColorFromSplit(std::vector<float> splitHistory) {
	int* tempColor = (int*)malloc(3 * sizeof(int));
	if (splitHistory.size() > 1) {
		float average = 0;
		for (int x = 0; x < splitHistory.size() - 1; x++) {
			average += splitHistory[x];
		}

		average /= splitHistory.size() - 1;

		if (splitHistory[splitHistory.size() - 1] < average) {
			tempColor[0] = 0;
			tempColor[1] = 255;
			tempColor[2] = 0;
		}
		if (splitHistory[splitHistory.size() - 1] > average) {
			tempColor[0] = 255;
			tempColor[1] = 0;
			tempColor[2] = 0;
		}
	}
	else {
		if (splitHistory.size() == 0) {
			tempColor[0] = 100;
			tempColor[1] = 100;
			tempColor[2] = 100;
		}
		else {
			if (splitHistory.size() == 1) {
				tempColor[0] = 128;
				tempColor[1] = 128;
				tempColor[2] = 0;
			}
		}
	}

	return tempColor;
}