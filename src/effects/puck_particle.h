#pragma once
#include <vector>
#include "..\core\drawing.h"
#include "..\core\vector2.h"
#include "..\core\configuration.h"

struct PuckParticles {
	int particleCount;
	float particleAcceleration;
	std::vector<Vector2> particlePositions;
	std::vector<int> offsetDirections;
	int alpha;
};

PuckParticles createPuckParticles(int count, Vector2 parentPosition, int alpha);
void initializePuckParticles();
void updatePuckParticles(float elapsedTimeSeconds, PuckParticles &particles);
void drawPuckParticles(PuckParticles particles);