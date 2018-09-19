#pragma once
#include "..\core\vector2.h"
#include "..\core\drawing.h"
#include "..\core\timer.h"

class SplitsDisplay {
private:
	float elapsedTimeSeconds;

	int color[3] = { 255, 255, 255 };
	int circleColor[3] = { 0, 153, 255 };
	int circleColorFin[3] = { 0, 204, 0 };
	
	int currentCheckpointIndex;
	int currentRun;
	float splitTimer;

	std::vector<Vector2> rectanglePositionList;
	float rectangleWidth;

	int* getColorFromSplit(int checkpoint);

public:
	std::vector<std::vector<float>> splitList;
	std::vector<int> checkpointList;
	std::vector<float> finalTimeList;
	Vector2 position;
	int width, height;
	
	SplitsDisplay(Vector2 position, int width, int height);

	int getBestTimeIndex();

	void removeRun(int index);
	
	void generateCheckpoints(int count, Vector2 firstRail, Vector2 lastRail);
	void reset();
	void update(Vector2 bPosition);
	void draw();
};