#include "particle_manager.h"

ParticleManager particleManager;

void ParticleManager::generateThaneParticles(int count, Vector2 parentPosition, int alpha) {
	thaneParticlesList.push_back(createThaneParticles(count, parentPosition, alpha));
}

void ParticleManager::removeOldParticles() {
	if (thaneParticlesList.size() > 400) {
		thaneParticlesList.erase(thaneParticlesList.begin(), thaneParticlesList.begin() + (thaneParticlesList.size() - 400));
	}
}

void ParticleManager::update(int elapsedTime) {
	elapsedTimeSeconds = (float)(elapsedTime) / 1000;

	for (ThaneParticles &particles : thaneParticlesList) {
		updateThaneParticles(elapsedTimeSeconds, particles);
	}

	removeOldParticles();
}

void ParticleManager::draw() {
	for (ThaneParticles particles : thaneParticlesList) {
		drawThaneParticles(particles);
	}
}