#include "particle_manager.h"

ParticleManager particleManager;

void ParticleManager::generateThaneParticles(int count, Vector2 parentPosition) {
	thaneParticlesList.push_back(createThaneParticles(count, parentPosition));
}

void ParticleManager::update(int elapsedTime) {
	elapsedTimeSeconds = (float)(elapsedTime) / 1000;

	for (ThaneParticles &particles : thaneParticlesList) {
		updateThaneParticles(elapsedTimeSeconds, particles);
	}
}

void ParticleManager::draw() {
	for (ThaneParticles particles : thaneParticlesList) {
		drawThaneParticles(particles);
	}
}