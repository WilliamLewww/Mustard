#include "gui.h"

void GUI::draw() {
	speedometer.draw();
	for (GButton button : buttonList) {
		drawRect(button.position, button.width, button.height, button.color);
	}
}