#pragma once
#include "..\core\configuration.h"
#include "..\core\drawing.h"
#include "..\core\vector2.h"
#include "..\core\timer.h"

class ScreenFilter {
private:
	int flashColor[3] = { 255, 255, 255 };
	float flashTimer = 0;
	float flashInterval = 50;
	float flashAlpha = 0;

	bool isFlashing = true;

	int color[3] = { 66, 91, 131 };
	int alpha = 60;
	int waveAlpha;

	bool isWaveringA = true;

	bool flipWaveA = false;
	float currentWaveA = 0;
	int waverMinA = -20, waverMaxA = 40;
	float waveSpeedA = 15;

	float elapsedTimeSeconds;

	bool show = false;
public:
	inline void setShow(bool show) { this->show = show; };

	inline void setR(int r) { this->color[0] = r; };
	inline void setG(int g) { this->color[1] = g; };
	inline void setB(int b) { this->color[2] = b; };

	inline void setColor(int r, int g, int b) {  this->color[0] = r; this->color[1] = g; this->color[2] = b; };
	inline void setColor(int* color) {  this->color[0] = color[0]; this->color[1] = color[1]; this->color[2] = color[2]; };

	inline void setAlpha(int a) { this->alpha = a; }

	void update();
	void draw();
};

extern ScreenFilter screenFilter;