#include "puck_particle.h"

int puckParticlesColor[3] = { 0, 179, 0 };

PuckParticles createPuckParticles(int count, Vector2 parentPosition, int alpha) {
	PuckParticles particles = { count };
	particles.alpha = alpha;
	particles.particleAcceleration = 50;
	for (int x = 0; x < count; x++) {
		particles.particlePositions.emplace_back(parentPosition);
		particles.offsetDirections.push_back((rand() % (10 + 1)) - 5);
	}

	return particles;
}

void initializePuckParticles() {
	puckParticlesColor[0] = configuration.getConfigurations()["PuckColorR"];
	puckParticlesColor[1] = configuration.getConfigurations()["PuckColorG"];
	puckParticlesColor[2] = configuration.getConfigurations()["PuckColorB"];
}

void updatePuckParticles(float elapsedTimeSeconds, PuckParticles &particles) {
	particles.particleAcceleration -= 625 * elapsedTimeSeconds;
	for (int x = 0; x < particles.particlePositions.size(); x++) {
		if (particles.particleAcceleration > -100) {
			particles.particlePositions[x].y -= particles.particleAcceleration * elapsedTimeSeconds;
			particles.particlePositions[x].x += (particles.offsetDirections[x] * 25) * elapsedTimeSeconds;
		}
	}
}

void drawPuckParticles(PuckParticles particles) {
	for (Vector2 position : particles.particlePositions) {
		drawing.drawPoint(position, puckParticlesColor, particles.alpha);
	}
}