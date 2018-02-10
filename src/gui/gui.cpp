#include "gui.h"

void GUI::draw() {
	minimap.draw();
	speedometer.draw();
	shoeometer.draw();
	for (GButton button : buttonList) {
		drawRect(button.position, button.width, button.height, button.color);
	}
}