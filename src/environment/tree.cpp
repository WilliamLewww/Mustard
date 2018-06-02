#include "tree.h"

Vector2 segments[18] = { Vector2(-0.5,0.5), Vector2(0,0), Vector2(0.5,0.5),
						 Vector2(0,0), Vector2(0,-1), Vector2(-1,-0.5),
						 Vector2(0,-1), Vector2(1,-0.5), Vector2(0,-1),
						 Vector2(0,-2), Vector2(-1,-1.5), Vector2(0,-2),
						 Vector2(1,-1.5),Vector2(0,-2), Vector2(0,-3),
						 Vector2(-1,-2.5), Vector2(0,-3), Vector2(1, -2)
};

Tree::Tree(Vector2 position, float scale) {
	this->position = position;
	this->scale = scale;
};

void Tree::draw() {
	drawing.drawLineStrip(segments, 15, position, scale, color);
};