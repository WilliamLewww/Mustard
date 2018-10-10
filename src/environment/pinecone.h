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
	inline bool getDead() { return isDead; };

	Pinecone(Vector2 position, float scale);

	float kill(float velocity);
	void draw();
};