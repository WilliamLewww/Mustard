#pragma once
#include "..\vector2.h"
#include "..\geometry.h"

class GButton {
public:
	Vector2 position;
	int width, height;

	int color[3];

	inline GButton(Vector2 posArgs, int wArgs, int hArgs) {
		position = posArgs;
		width = wArgs;
		height = hArgs;

		color[0] = 0;
		color[1] = 0;
		color[2] = 255;
	};

	inline GButton(Vector2 posArgs, int wArgs, int hArgs, int cArgs[3]) {
		position = posArgs;
		width = wArgs;
		height = hArgs;

		color[0] = cArgs[0];
		color[1] = cArgs[1];
		color[2] = cArgs[2];
	};
};