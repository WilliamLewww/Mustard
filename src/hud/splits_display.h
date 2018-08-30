#pragma once
#include "..\core\vector2.h"
#include "..\core\drawing.h"

class SplitsDisplay {
private:
	float elapsedTimeSeconds;

	int color[3] = { 255, 255, 255 };
	int circleColor[3] = { 0, 153, 255 };
	
	std::vector<int> checkpointList;
	std::vector<std::vector<float>> splitList;
	int currentCheckpointIndex;
	float splitTimer;

	std::vector<Vector2> rectanglePositionList;
	float rectangleWidth;

	int* getColorFromSplit(std::vector<float> splitHistory);

public:
	Vector2 position;
	int width, height;
	
	SplitsDisplay(Vector2 position, int width, int height);
	void generateCheckpoints(int count, Vector2 firstRail, Vector2 lastRail);
	void reset();
	void update(int elapsedTime, Vector2 bPosition);
	void draw();
};