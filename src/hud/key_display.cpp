#include "key_display.h"

KeyDisplay::KeyDisplay(Vector2 position, float scale) {
	this->scale = scale;

	boxList.push_back({Vector2(position.x, position.y), 50, 50});
	boxList.push_back({Vector2(position.x + 55, position.y), 50, 50});
	boxList.push_back({Vector2(position.x + 110, position.y), 50, 50});

	boxList.push_back({Vector2(position.x, position.y + 105), 200, 50});

	boxList.push_back({Vector2(position.x + 250, position.y + 105), 50, 50});
	boxList.push_back({Vector2(position.x + 305, position.y + 105), 50, 50});
	boxList.push_back({Vector2(position.x + 305, position.y + 50), 50, 50});
	boxList.push_back({Vector2(position.x + 360, position.y + 105), 50, 50});
}

void KeyDisplay::draw() {
	if (input.checkKeyDown(SDLK_a)) { drawing.drawRect(boxList[0].position, boxList[0].width, boxList[0].height, pressColor); }
	else { drawing.drawRect(boxList[0].position, boxList[0].width, boxList[0].height, releaseColor); }

	if (input.checkKeyDown(SDLK_s)) { drawing.drawRect(boxList[1].position, boxList[1].width, boxList[1].height, pressColor); }
	else { drawing.drawRect(boxList[1].position, boxList[1].width, boxList[1].height, releaseColor); }

	if (input.checkKeyDown(SDLK_d)) { drawing.drawRect(boxList[2].position, boxList[2].width, boxList[2].height, pressColor); }
	else { drawing.drawRect(boxList[2].position, boxList[2].width, boxList[2].height, releaseColor); }

	if (input.checkKeyDown(SDLK_SPACE)) { drawing.drawRect(boxList[3].position, boxList[3].width, boxList[3].height, pressColor); }
	else { drawing.drawRect(boxList[3].position, boxList[3].width, boxList[3].height, releaseColor); }

	if (input.checkKeyDown(SDLK_LEFT)) { drawing.drawRect(boxList[4].position, boxList[4].width, boxList[4].height, pressColor); }
	else { drawing.drawRect(boxList[4].position, boxList[4].width, boxList[4].height, releaseColor); }

	if (input.checkKeyDown(SDLK_DOWN)) { drawing.drawRect(boxList[5].position, boxList[5].width, boxList[5].height, pressColor); }
	else { drawing.drawRect(boxList[5].position, boxList[5].width, boxList[5].height, releaseColor); }

	if (input.checkKeyDown(SDLK_UP)) { drawing.drawRect(boxList[6].position, boxList[6].width, boxList[6].height, pressColor); }
	else { drawing.drawRect(boxList[6].position, boxList[6].width, boxList[6].height, releaseColor); }

	if (input.checkKeyDown(SDLK_RIGHT)) { drawing.drawRect(boxList[7].position, boxList[7].width, boxList[7].height, pressColor); }
	else { drawing.drawRect(boxList[7].position, boxList[7].width, boxList[7].height, releaseColor); }
}