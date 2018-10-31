#pragma once
#include <vector>
#include "..\core\drawing.h"
#include "..\core\vector2.h"

struct PineconeSegment {
	Vector2 position;

	float angle;
	float acceleration;
	float offsetDirections;

	int colorIndex;
};

struct PineconeGibParticles {
	Vector2 parentPosition;

	std::vector<PineconeSegment> segmentList;
	int segmentWidth, segmentThickness;
};

PineconeGibParticles createPineconeGibParticles(int count, Vector2 parentPosition);
void updatePineconeGibParticles(float elapsedTimeSeconds, PineconeGibParticles& particles);
void drawPineconeGibParticles(PineconeGibParticles particles);