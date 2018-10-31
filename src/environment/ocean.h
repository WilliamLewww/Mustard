#pragma once
#include <vector>
#include "..\core\vector2.h"
#include "..\core\timer.h"
#include "..\core\drawing.h"
#include "..\core\configuration.h"
#include "..\camera.h"

struct Wave {
	Vector2 position;
	int width;

	int colorID;
	double alpha;

	bool fadeIn;
	bool direction;
};

class Ocean {
private:
	std::vector<Wave> waveList;
	int waveLength = 2;
	double fadeSpeed = 100.0;

	float elapsedTimeSeconds;
public:	
	void generateWaves();
	void update();
	void drawStatic();
};