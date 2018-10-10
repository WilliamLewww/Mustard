#include "pinecone.h"

Vector2 pineconeSegments[11] = { Vector2(-0.5,0), Vector2(0.5,0), Vector2(0,0), Vector2(0,-0.5),
								 Vector2(0,0.5), Vector2(0,0), Vector2(-0.5,-0.5), Vector2(0.5, 0.5),
								 Vector2(0,0), Vector2(0.5,-0.5), Vector2(-0.5,0.5)
};

Pinecone::Pinecone(Vector2 position, float scale) {
	this->position = position;
	this->scale = scale;

	polygon.setPosition(position);
	polygon.setSize(scale, scale);

	int randomColor = rand() % 25;
	color[0] = 95 + randomColor;
	color[1] = 55 + randomColor;
	color[2] = 55 + randomColor;
}

float Pinecone::kill(float velocity) {
	isDead = true;

	return sqrt(velocity);
}

void Pinecone::draw() {
	if (!isDead) {
		drawing.drawLineStrip(pineconeSegments, 11, position, scale, color);
	}
}