#pragma once
#include "gbutton.h"
#include "speedometer.h"
#include <vector>

class GUI {
	Speedometer speedometer;
	std::vector<GButton> buttonList;
public:
	void draw();
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