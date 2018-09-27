#pragma once
#include "wheel.h"

class Experimentals : public Wheel {
public:
	Experimentals(float currentHeight)
		:Wheel(48, 66, 78, false, LIP_ROUND) {

		this->currentHeight = currentHeight;
		setColor(254, 78, 0);
	};
}