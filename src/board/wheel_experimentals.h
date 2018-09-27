#pragma once
#include "wheel.h"

class Experimentals : public Wheel {
public:
	Experimentals(float currentHeightPercent)
		:Wheel(48, 66, 78, false, LIP_ROUND) {

		this->currentHeightPercent = currentHeightPercent;
		setColor(254, 78, 0);
	};
};
