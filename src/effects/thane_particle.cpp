#include "thane_particle.h"

ThaneParticles createThaneParticles(int count, Vector2 parentPosition) {
	ThaneParticles particles = { count };
	particles.particleAcceleration = 50;
	for (int x = 0; x < count; x++) {
		particles.particlePositions.emplace_back(parentPosition);
		particles.offsetDirections.push_back((rand() % (10 + 1)) - 5);
	}

	return particles;
}

void updateThaneParticles(float elapsedTimeSeconds, ThaneParticles &particles) {
	particles.particleAcceleration -= 5;
	for (int x = 0; x < particles.particlePositions.size(); x++) {
		if (particles.particleAcceleration > -100) {
			particles.particlePositions[x].y -= particles.particleAcceleration * elapsedTimeSeconds;
			particles.particlePositions[x].x += (particles.offsetDirections[x] * 25) * elapsedTimeSeconds;
		}
	}
}

void drawThaneParticles(ThaneParticles particles) {
	for (Vector2 position : particles.particlePositions) {
		drawing.drawPoint(position);
	}
}