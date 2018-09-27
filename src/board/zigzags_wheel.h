#pragma once
#include "wheel.h"

class ZigZags : public Wheel {
public:
	ZigZags(float currentHeight)
		:Wheel(53, 70, 77, true, LIP_SQUARE) {

		this->currentHeight = currentHeight;
		setColor(56, 222, 64);
	};
}