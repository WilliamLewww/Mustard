#include "pinecone.h"

Vector2 pineconeSegments[15] = { Vector2(0,0), Vector2(0,-1), Vector2(-1,-0.5),
						 Vector2(0,-1), Vector2(1,-0.5), Vector2(0,-1),
						 Vector2(0,-2), Vector2(-1,-1.5), Vector2(0,-2),
						 Vector2(1,-1.5),Vector2(0,-2), Vector2(0,-3),
						 Vector2(-1,-2.5), Vector2(0,-3), Vector2(1, -2.5)
};

Pinecone::Pinecone(Vector2 position, float scale) {
	this->position = position;
	this->scale = scale;

	int randomColor = rand() % 25;
	color[0] = 95 + randomColor;
	color[1] = 55 + randomColor;
	color[2] = 55 + randomColor;
}

void Pinecone::kill() {

}

void Pinecone::draw() {
	drawing.drawLineStrip(pineconeSegments, 15, position, scale, color);
}