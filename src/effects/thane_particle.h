#pragma once
#include <vector>
#include "..\core\drawing.h"
#include "..\core\vector2.h"

int thaneParticlesColor[3] = { 255, 255, 255 };

struct ThaneParticles {
	int particleCount;
	float particleAcceleration;
	std::vector<Vector2> particlePositions;
	std::vector<int> offsetDirections;
	int alpha;
};

ThaneParticles createThaneParticles(int count, Vector2 parentPosition, int alpha);
void updateThaneParticles(float elapsedTimeSeconds, ThaneParticles &particles);
void drawThaneParticles(ThaneParticles particles);