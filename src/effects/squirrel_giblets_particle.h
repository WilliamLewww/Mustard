#pragma once
#include <vector>
#include "..\core\drawing.h"
#include "..\core\vector2.h"

struct SquirrelGibParticles {
	int particleCount;
	float particleAcceleration;
	std::vector<Vector2> particlePositions;
	Vector2 parentPosition;
	std::vector<float> offsetDirections;
	int alpha;
};

SquirrelGibParticles createSquirrelGibParticles(int count, Vector2 parentPosition, int alpha);
void updateSquirrelGibParticles(float elapsedTimeSeconds, SquirrelGibParticles &particles);
void drawSquirrelGibParticles(SquirrelGibParticles particles);