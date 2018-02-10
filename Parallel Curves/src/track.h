#pragma once
#include "vector2.h"
#include <SDL2\SDL_opengl.h>
#include <vector>

int SCREENWIDTH = 1600, SCREENHEIGHT = 900;

double convertColor(int rgbValue) {
	return (double)rgbValue / 255;
}

void drawLineStrip(std::vector<Vector2> points, int color[3]) {
	glBegin(GL_LINE_STRIP);
	glColor4f(convertColor(color[0]), convertColor(color[1]), convertColor(color[2]), 1);
	for (int x = 0; x < points.size(); x++) { glVertex2f(points[x].x - (SCREENWIDTH / 2), points[x].y - (SCREENHEIGHT / 2)); }
	glEnd();
}

class Track {
	int sideColor[3] = { 225, 225, 225 };
	int centerColor[3] = { 255, 173, 71 };
	int roadColor[3] = { 60, 60, 60 };
public:
	std::vector<std::vector<Vector2>> railList;
	
	inline void draw() {
		drawLineStrip(railList[0], sideColor);
		drawLineStrip(railList[1], sideColor);
	};

	inline addRail(int count) {
		for (int x = 0; x < count; x++) {
			railList.push_back(std::vector<Vector2>());
		}
	};

	inline addVertex(int indexTop, int indexBottom, Vector2 position, int spacing) {
		railList[indexTop].push_back(Vector2(position.x, position.y));
		railList[indexBottom].push_back(Vector2(position.x, position.y + spacing));
	};

	inline addVertexSingle(int index, Vector2 position) {
		railList[index].push_back(Vector2(position.x, position.y));
	};

	inline addVertexRelative(int indexTop, int indexBottom, int topY, int spacingX, int bottomY) {
		railList[indexTop].push_back(Vector2(railList[indexTop][railList[indexTop].size() - 1].x + spacingX, railList[indexTop][railList[indexTop].size() - 1].y + topY));
		railList[indexBottom].push_back(Vector2(railList[indexBottom][railList[indexBottom].size() - 1].x + spacingX, railList[indexBottom][railList[indexBottom].size() - 1].y + bottomY));
	};

	inline addVertexRelativeTop(int index, int topY, int spacingX) {
		railList[index].push_back(Vector2(railList[index][railList[index].size() - 1].x + spacingX, railList[index][railList[index].size() - 1].y + topY));
	};

	inline addVertexRelativeBottom(int index, int slope) {
		railList[index].push_back(Vector2(railList[0][railList[index].size() - 1].x, railList[0][railList[index].size() - 1].y));
	};

	inline addVertexComp(int indexTop, int indexBottom, int topY, int spacingX) {
		railList[indexTop].push_back(Vector2(railList[indexTop][railList[indexTop].size() - 1].x + spacingX, railList[indexTop][railList[indexTop].size() - 1].y + topY));
		railList[indexBottom].push_back(Vector2(railList[indexBottom][railList[indexBottom].size() - 1].x + spacingX, railList[indexBottom][railList[indexBottom].size() - 1].y + topY));
	};

	inline addVertexComp(int indexTop, int indexBottom, int topY, int spacingX, int offsetY, int limitTop, int limitBottom) {
		railList[indexTop].push_back(Vector2(railList[indexTop][railList[indexTop].size() - 1].x + spacingX, railList[indexTop][railList[indexTop].size() - 1].y + topY));
		railList[indexBottom].push_back(Vector2(railList[indexBottom][railList[indexBottom].size() - 1].x + spacingX, railList[indexTop][railList[indexTop].size() - 1].y + offsetY + (rand() % (limitBottom - limitTop + 1) - limitTop)));
	};
};