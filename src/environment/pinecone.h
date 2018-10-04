#pragma once
#include "..\bmp_polygon.h"

class Pinecone {
private:
	Vector2 position;
	float scale;

	bool isDead = false;

	int color[3];
public:
	BitmapPolygon polygon;

	inline Vector2 getPosition() { return position; };

	Pinecone(Vector2 position, float scale);

	void kill();
	void draw();
};