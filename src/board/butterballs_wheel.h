#pragma once
#include "wheel.h"

class Butterballs : public Wheel {
public:
	Butterballs(float currentHeight)
		:Wheel(48, 70, 80, false, LIP_ROUND) {

		this->currentHeight = currentHeight;
		setColor(255, 255, 255);
	};
}