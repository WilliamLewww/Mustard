#pragma once
#include "..\..\constants.h"
#include "gbutton.h"
#include "shoeometer.h"
#include "speedometer.h"
#include "minimap.h"
#include <vector>

class GUI {
	Minimap minimap = Minimap(Vector2(5, 5), 200, 200);
	Speedometer speedometer;
	Shoeometer shoeometer;
	std::vector<GButton> buttonList;
public:
	void draw();

	inline void initializeMinimap(std::vector<std::vector<Vector2>> railList, Vector2 boardInitialPosition) {
		minimap.initialize(railList, boardInitialPosition);
	};

	inline void updateMinimap(Vector2 position, double angle) {
		minimap.update(position, angle);
	};

	inline void resetMinimap() {
		minimap.resetVisibleRange();
	}

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