#include "track_editor.h"

void TrackEditor::update() {
	if (railList.size() < 1) {
		railList.push_back(std::vector<Vector2>());
		railList.push_back(std::vector<Vector2>());
	}

	if (input.checkKeyDown(SDLK_z)) { decreaseSpacing(); }
	if (input.checkKeyDown(SDLK_x)) { increaseSpacing(); }

	if (input.getKeyListSize() == 0) { canChangeMode = true; }
	if (!input.checkKeyDown(SDLK_c)) { canPlaceTrack = true; }
	if (!input.checkKeyDown(SDLK_v)) { canRemove = true; }

	if (canPlaceTrack && input.checkKeyDown(SDLK_c)) {
		placeTrack();
		canPlaceTrack = false;
	}

	if (canRemove && input.checkKeyDown(SDLK_v)) {
		removeTrack();
		canRemove = false;
	}

	if (canChangeMode && input.checkKeyDown(SDLK_m)) { spec = !spec; canChangeMode = false; }

	for (int x = 0; x < railList[0].size(); x++) {
		visibleRange.x = 0;
		if (railList[0][x].x < camera.getBoundaryLeft()) { visibleRange.x = x; }
		if (railList[0][x].x < camera.getBoundaryRight()) { visibleRange.y = x; }
	}
}

void TrackEditor::increaseSpacing() {
	railSpacingY += 3;
}

void TrackEditor::decreaseSpacing() {
	if (railSpacingY > 10) {
		railSpacingY -= 3;
	}
}

void TrackEditor::resetSpacing() {
	railSpacingY = 25;
}

void TrackEditor::placeTrack() {
	if (!overridePlacement) {
		railList[0].push_back(getBoardCenter() - Vector2(0, railSpacingY / 2));
		railList[1].push_back(getBoardCenter() + Vector2(0, railSpacingY / 2));
	}
	else {
		railList[0].push_back(input.getMousePosition() + halfBoardSize() + camera.getPosition() - Vector2(0, railSpacingY / 2));
		railList[1].push_back(input.getMousePosition() + halfBoardSize() + camera.getPosition() + Vector2(0, railSpacingY / 2));
	}
}

void TrackEditor::removeTrack() {
	if (railList[0].size() > 0) {
		railList[0].pop_back();
		railList[1].pop_back();
	}
}

std::vector<Vector2> TrackEditor::getVisibleRail(int side) {
	return std::vector<Vector2>(railList[side].begin() + visibleRange.x, railList[side].begin() + visibleRange.y);
};

void TrackEditor::draw() {
	drawing.drawRect(Vector2(0,0), boardWidth, boardHeight);
	drawing.drawLineStrip(getVisibleRail(0), railColor);
	drawing.drawLineStrip(getVisibleRail(1), railColor);
	if (railList[0].size() > 0) { 
		drawing.drawLine(railList[0][0], railList[1][0]);
	}
	if (railList[0].size() > 1) {
		drawing.drawLine(railList[0][railList[0].size() - 2], railList[0][railList[0].size() - 1], currentRailColor); 
		drawing.drawLine(railList[1][railList[1].size() - 2], railList[1][railList[1].size() - 1], currentRailColor); 
	}

	if (!overridePlacement) {
		drawing.drawLine(getBoardCenter() - Vector2(0, railSpacingY / 2), getBoardCenter() + Vector2(0, railSpacingY / 2));
	}
	else {
		drawing.drawCircle(input.getMousePosition() + halfBoardSize() + camera.getPosition(), 2);
		drawing.drawLine(input.getMousePosition() + halfBoardSize() + camera.getPosition() - Vector2(0, railSpacingY / 2), input.getMousePosition() + halfBoardSize() + camera.getPosition() + Vector2(0, railSpacingY / 2));
	}
}