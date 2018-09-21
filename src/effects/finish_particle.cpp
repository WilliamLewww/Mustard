#include "finish_particle.h"

int finishParticlesColor[5][3] = { {0,0,0}, {100,100,100}, {75,75,75}, {25,25,25}, {255,255,255} };

FinishParticles createFinishParticles(int count, Vector2 parentPosition) {
	FinishParticles particles = { count, 250, parentPosition };

	for (int x = 0; x < count; x++) {
		particles.particlePositions.emplace_back(parentPosition);
		particles.offsetFinalPosition.push_back(rand() % (10 + 1 + 10) - 10);
		particles.offsetDirections.push_back(((float)(rand() % (100 + 1)) - 50) / 10);
		particles.particleColorIDs.push_back(rand() % 5);
	}

	return particles;
}

void updateFinishParticles(float elapsedTimeSeconds, FinishParticles &particles) {
	particles.particleAcceleration -= 500 * elapsedTimeSeconds;
	for (int x = 0; x < particles.particlePositions.size(); x++) {
		if (particles.particlePositions[x].y + particles.offsetFinalPosition[x] < particles.parentPosition.y) {
			particles.particlePositions[x].y -= particles.particleAcceleration * elapsedTimeSeconds;
			particles.particlePositions[x].x += (particles.offsetDirections[x] * 15) * elapsedTimeSeconds;
		}
	}
}

void drawFinishParticles(FinishParticles particles) {
	for (int x = 0; x < particles.particleCount; x++) {
		drawing.drawPoint(particles.particlePositions[x], finishParticlesColor[particles.particleColorIDs[x]], 255);
	}
}