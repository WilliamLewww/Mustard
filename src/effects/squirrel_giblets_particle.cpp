#include "squirrel_giblets_particle.h"

int squirrelGibParticlesColor[3] = { 134, 45, 45 };

SquirrelGibParticles createSquirrelGibParticles(int count, Vector2 parentPosition, int alpha) {
	SquirrelGibParticles particles = { count };
	particles.parentPosition = parentPosition;

	particles.alpha = alpha;
	particles.particleAcceleration = 100;
	for (int x = 0; x < count; x++) {
		particles.particlePositions.emplace_back(parentPosition);
		// particles.offsetDirections.push_back((rand() % (10 + 1)) - 5);
		particles.offsetDirections.push_back(((float)(rand() % (100 + 1)) - 50) / 10);
	}

	return particles;
}

void updateSquirrelGibParticles(float elapsedTimeSeconds, SquirrelGibParticles &particles) {
	particles.particleAcceleration -= 500 * elapsedTimeSeconds;
	for (int x = 0; x < particles.particlePositions.size(); x++) {
		if ((particles.particlePositions[x].y < particles.parentPosition.y) || (particles.particleAcceleration > 0)) {
			particles.particlePositions[x].y -= particles.particleAcceleration * elapsedTimeSeconds;
			particles.particlePositions[x].x += (particles.offsetDirections[x] * 25) * elapsedTimeSeconds;
		}
	}
}

void drawSquirrelGibParticles(SquirrelGibParticles particles) {
	for (Vector2 position : particles.particlePositions) {
		drawing.drawPoint(position, squirrelGibParticlesColor, particles.alpha);
	}
}