#pragma once
#include <vector>
#include "..\core\vector2.h"
#include "..\core\drawing.h"

struct CrashSegment {
	Vector2 position;

	float angle;
	float acceleration;
	float offsetDirections;
};

struct CrashParticles {
	int particleCount;
	Vector2 parentPosition;

	std::vector<CrashSegment> crashSegmentList;
	int width, thickness;
};

CrashParticles createCrashParticles(int count, Vector2 parentPosition);
void initializeCrashParticles();
void updateCrashParticles(float elapsedTimeSeconds, CrashParticles& particles);
void drawCrashParticles(CrashParticles particles);