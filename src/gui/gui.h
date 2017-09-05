#pragma once
#include "gbutton.h"
#include "shoeometer.h"
#include "speedometer.h"
#include <vector>

class GUI {
	Speedometer speedometer;
	Shoeometer shoeometer;
	std::vector<GButton> buttonList;
public:
	void draw();

	inline void updateSpeedometer(int velocity, int style) { 
		switch (style) {
			case 0: break;
			case 1: speedometer.updateStyleA(velocity); break;
			case 2: speedometer.updateStyleB(velocity); break;
		}
	};

	inline void updateShoeometer(int shoeLeft, int style) { 
		switch (style) {
			case 0: break;
			case 1: shoeometer.updateStyleA(shoeLeft); break;
		}
	};

	inline void addButton(GButton button) { buttonList.push_back(button); };
	inline void addButtonArrayX(Vector2 initialPosition, int width, int height, int spacingX, int count) { 
		for (int x = 0; x < count; x++) {
			buttonList.push_back(GButton(Vector2(initialPosition.x + (spacingX * x), initialPosition.y), width, height)); 
		} 
	};
	inline void addButtonArrayY(Vector2 initialPosition, int width, int height, int spacingY, int count) { 
		for (int y = 0; y < count; y++) {
			buttonList.push_back(GButton(Vector2(initialPosition.x, initialPosition.y + (spacingY * y)), width, height)); 
		} 
	};
};   