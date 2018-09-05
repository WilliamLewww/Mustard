#include "squirrel_giblets_particle.h"

SquirrelGibParticles createSquirrelGibParticles(int count, Vector2 parentPosition, int alpha) {
	SquirrelGibParticles particles = { count };
	particles.alpha = alpha;
	particles.particleAcceleration = 50;
	for (int x = 0; x < count; x++) {
		particles.particlePositions.emplace_back(parentPosition);
		particles.offsetDirections.push_back((rand() % (10 + 1)) - 5);
	}

	return particles;
}

void updateSquirrelGibParticles(float elapsedTimeSeconds, SquirrelGibParticles &particles) {
	particles.particleAcceleration -= 625 * elapsedTimeSeconds;
	for (int x = 0; x < particles.particlePositions.size(); x++) {
		if (particles.particleAcceleration > -100) {
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