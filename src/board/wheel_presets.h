#pragma once
#include "wheel.h"

class Mids : public Wheel {
public:
	Mids(float currentHeightPercent)
		:Wheel("Mids", 50, 68, 77, 50, LIP_ROUND, false) {

		this->currentHeightPercent = currentHeightPercent;
		setColor(204, 204, 204);
	};
};


class Butterballs : public Wheel {
public:
	Butterballs(float currentHeightPercent)
		:Wheel("Butterballs", 48, 70, 80, 60, LIP_ROUND, false) {

		this->currentHeightPercent = currentHeightPercent;
		setColor(255, 255, 255);
	};
};

class Experimentals : public Wheel {
public:
	Experimentals(float currentHeightPercent)
		:Wheel("Experimentals", 48, 66, 78, 75, LIP_ROUND, false) {

		this->currentHeightPercent = currentHeightPercent;
		setColor(254, 78, 0);
	};
};

class Snakes : public Wheel {
public:
	Snakes(float currentHeightPercent)
		:Wheel("Snakes", 48, 66, 83, 65, LIP_ROUND, false) {

		this->currentHeightPercent = currentHeightPercent;
		setColor(255, 107, 95);
	};
};

class Stimulus : public Wheel {
public:
	Stimulus(float currentHeightPercent)
		:Wheel("Stimulus", 49, 70, 80, 93, LIP_ROUND, false) {

		this->currentHeightPercent = currentHeightPercent;
		setColor(255, 95, 59);
	};
};

class ZigZags : public Wheel {
public:
	ZigZags(float currentHeightPercent)
		:Wheel("ZigZags", 53, 70, 77, 95, LIP_SQUARE, true) {

		this->currentHeightPercent = currentHeightPercent;
		setColor(56, 222, 64);
	};
};