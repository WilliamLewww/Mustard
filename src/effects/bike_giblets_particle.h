#pragma once
#include <vector>
#include "..\core\drawing.h"
#include "..\core\vector2.h"

struct BikeBloodParticle {
	Vector2 position;

	float acceleration;
	float offsetDirections;
	int alpha;
};

struct BikeFrameSegment {
	Vector2 position;

	float angle;
	float acceleration;
	float offsetDirections;

	int colorIndex;
};

struct BikeGibParticles {
	Vector2 parentPosition;

	std::vector<BikeFrameSegment> segmentList;
	int segmentWidth, segmentThickness;

	std::vector<BikeBloodParticle> particleList;
};

BikeGibParticles createBikeGibParticles(int count, Vector2 parentPosition);
void updateBikeGibParticles(float elapsedTimeSeconds, BikeGibParticles& particles);
void drawBikeGibParticles(BikeGibParticles particles);