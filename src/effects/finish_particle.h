#pragma once
#include <vector>
#include "..\core\vector2.h"
#include "..\core\drawing.h"

struct FinishParticles {
	int particleCount;
	float particleAcceleration;
	Vector2 parentPosition;
	std::vector<int> particleColorIDs;
	std::vector<Vector2> particlePositions;
	std::vector<int> offsetFinalPosition;
	std::vector<float> offsetDirections;
};

FinishParticles createFinishParticles(int count, Vector2 parentPosition);
void updateFinishParticles(float elapsedTimeSeconds, FinishParticles& particles);
void drawFinishParticles(FinishParticles particles);