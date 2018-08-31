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
	splitList.push_back(std::vector<float>());
	finalTimeList.push_back(0.00);

	for (int x = 0; x < count; x++) {
		rectanglePositionList.emplace_back(position.x + (rectangleWidth * x), position.y);
		checkpointList.push_back(((lastRail.x - firstRail.x) / count) * x);
	}
}

void SplitsDisplay::reset() {
	splitList.push_back(std::vector<float>());
	finalTimeList.push_back(0.00);
	splitTimer = 0;
	currentCheckpointIndex = 0;
	currentRun += 1;
}

void SplitsDisplay::update(int elapsedTime, Vector2 bPosition) {
	elapsedTimeSeconds = (float)(elapsedTime) / 1000;

	splitTimer += elapsedTimeSeconds;
	if (bPosition.x > checkpointList[currentCheckpointIndex] && currentCheckpointIndex < checkpointList.size() - 1) {
		splitList[currentRun].push_back(splitTimer);

		splitTimer = 0;
		currentCheckpointIndex += 1;
	}
	else {
		if (currentCheckpointIndex == checkpointList.size() - 1 && finalTimeList[currentRun] == 0) {
			float totalTime = 0;
			for (float time : splitList[currentRun]) {
				totalTime += time;
			}

			finalTimeList[currentRun] = totalTime;
		}
	}
}

void SplitsDisplay::draw() {
	for (int x = 0; x < checkpointList.size(); x++) {
		drawing.drawRect(rectanglePositionList[x], rectangleWidth, height, getColorFromSplit());
		//drawing.drawRect(rectanglePositionList[x], rectangleWidth, height, getColorFromSplit(splitList[x]));
	}

	drawing.drawCircleFill(rectanglePositionList[currentCheckpointIndex] + Vector2(rectangleWidth / 2, height / 2), 5, circleColor);
}

int* SplitsDisplay::getColorFromSplit() {
	int* tempColor = (int*)malloc(3 * sizeof(int));
	tempColor[0] = 128;
	tempColor[1] = 128;
	tempColor[2] = 0;

	return tempColor;
}