#include "splits_display.h"

SplitsDisplay::SplitsDisplay(Vector2 position, int width, int height) {
	this->position = position;
	this->width = width;
	this->height = height;
}

void SplitsDisplay::removeRun(int index) {
	if (index != finalTimeList.size() - 1) {
		finalTimeList.erase(finalTimeList.begin() + index);
		splitList.erase(splitList.begin() + index);
		currentRun -= 1;
	}
}

int SplitsDisplay::getBestTimeIndex() {
	int highestIndex = 0;
	float highestValue = finalTimeList[0];

	for (int x = 0; x < finalTimeList.size(); x++) {
		if (highestValue < finalTimeList[x]) {
			highestIndex = x;
			highestValue = finalTimeList[x];
		}
	}

	return highestIndex;
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

void SplitsDisplay::update(Vector2 bPosition) {
	elapsedTimeSeconds = timer.getTimeSeconds();
	
	splitTimer += elapsedTimeSeconds;
	if (bPosition.x > checkpointList[currentCheckpointIndex] && currentCheckpointIndex < checkpointList.size()) {
		splitList[currentRun].push_back(splitTimer);

		splitTimer = 0;
		currentCheckpointIndex += 1;
	}
	else {
		if (currentCheckpointIndex == checkpointList.size() && finalTimeList[currentRun] == 0) {
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
		drawing.drawRect(rectanglePositionList[x], rectangleWidth, height, getColorFromSplit(x));
	}

	if (currentCheckpointIndex == checkpointList.size()) {
		drawing.drawCircleFill(rectanglePositionList[currentCheckpointIndex - 1] + Vector2(rectangleWidth / 2, height / 2), 10, circleColorFin);
	}
	else {
		drawing.drawCircleFill(rectanglePositionList[currentCheckpointIndex] + Vector2(rectangleWidth / 2, height / 2), 5, circleColor);
	}
}

int* SplitsDisplay::getColorFromSplit(int checkpoint) {
	int* tempColor = (int*)malloc(3 * sizeof(int));
	tempColor[0] = 100;
	tempColor[1] = 100;
	tempColor[2] = 100;

	float average = 0, latest = 0;
	int count = 0;

	if (checkpoint > checkpointList.size() - 1) {
		return tempColor;
	}

	for (int x = 0; x < splitList.size(); x++) {
		if (splitList[x].size() > checkpoint) {
			latest = splitList[x][checkpoint];
			average += splitList[x][checkpoint];
			count += 1;
		}
	}

	if (count > 0) {
		average /= count;
	}

	if (latest < average) {
		tempColor[0] = 0;
		tempColor[1] = 255;
		tempColor[2] = 0;
	}
	if (latest > average) {
		tempColor[0] = 255;
		tempColor[1] = 0;
		tempColor[2] = 0;
	}

	if (count == 1) {
		tempColor[0] = 128;
		tempColor[1] = 128;
		tempColor[2] = 0;
	}

	return tempColor;
}