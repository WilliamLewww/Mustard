#include "pinecone.h"

Vector2 pineconeSegments[11] = { Vector2(-0.5,0), Vector2(0.5,0), Vector2(0,0), Vector2(0,-0.5),
								 Vector2(0,0.5), Vector2(0,0), Vector2(-0.5,-0.5), Vector2(0.5, 0.5),
								 Vector2(0,0), Vector2(0.5,-0.5), Vector2(-0.5,0.5)
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
	drawing.drawLineStrip(pineconeSegments, 11, position, scale, color);
}