#pragma once
#include <vector>
#include "..\core\input.h"
#include "..\core\vector2.h"
#include "..\core\drawing.h"
#include "..\camera.h"

class TrackEditor {
private:
	Vector2 visibleRange = Vector2(0, 0);

	int railSpacingY = 25;
	bool canPlaceTrack = false;
	bool enabled = false;
	bool canChangeMode = false;
	bool canRemove = false;

	std::vector<std::vector<Vector2>> railList;
	int railColor[3] = { 0, 0, 0 };
	int currentRailColor[3] = { 255, 0, 0 };

	Vector2* boardPosition;
	int boardWidth, boardHeight;

	inline Vector2 getBoardCenter() { return Vector2(boardPosition->x + (boardWidth / 2), boardPosition->y + (boardHeight / 2)); };
	std::vector<Vector2> getVisibleRail(int side);

	bool overridePlacement = false;
public:
	bool spec = true;

	inline Vector2 halfBoardSize() { return Vector2(boardWidth / 2, boardHeight / 2); };

	inline bool getSpec() { return spec; };
	inline bool getEnabled() { return enabled; };
	inline void setEnabled(bool enabled, Vector2* boardPosition, int boardWidth, int boardHeight) { 
		this->enabled = enabled; 
		this->boardPosition = boardPosition;

		this->boardWidth = boardWidth;
		this->boardHeight = boardHeight;
	};

	inline void disable() { 
		this->enabled = false;
	};

	inline void enableOverride() { overridePlacement = true; };
	inline void disableOverride() { overridePlacement = false; };

	inline std::vector<std::vector<Vector2>> getRailList() { return railList; };
	inline void clearRailList() { railList.clear(); }; 

	void increaseSpacing();
	void decreaseSpacing();
	void resetSpacing();

	void placeTrack();
	void removeTrack();
	
	void update();
	void draw();
};