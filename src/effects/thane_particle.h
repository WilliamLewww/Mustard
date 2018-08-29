#pragma once
#include <vector>
#include "..\core\drawing.h"
#include "..\core\vector2.h"

struct ThaneParticles {
	int particleCount;
	float particleAcceleration;
	std::vector<Vector2> particlePositions;
	std::vector<int> offsetDirections;
	bool dead;
};

ThaneParticles createThaneParticles(int count, Vector2 parentPosition);
void updateThaneParticles(float elapsedTime, ThaneParticles &particles);
void drawThaneParticles(ThaneParticles particles);