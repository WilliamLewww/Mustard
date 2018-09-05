#pragma once
#include <vector>
#include "..\core\drawing.h"
#include "..\core\vector2.h"

int squirrelGibParticlesColor[3] = { 134, 45, 45 };

struct SquirrelGibParticles {
	int particleCount;
	float particleAcceleration;
	std::vector<Vector2> particlePositions;
	std::vector<int> offsetDirections;
	int alpha;
};

SquirrelGibParticles createSquirrelGibParticles(int count, Vector2 parentPosition, int alpha);
void updateSquirrelGibParticles(float elapsedTimeSeconds, SquirrelGibParticles &particles);
void drawSquirrelGibParticles(SquirrelGibParticles particles);