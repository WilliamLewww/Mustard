#include "particle_manager.h"

ParticleManager particleManager;

void ParticleManager::generateThaneParticles(int count, Vector2 parentPosition, int alpha) {
	thaneParticlesList.push_back(createThaneParticles(count, parentPosition, alpha));
}

void ParticleManager::generateSquirrelGibParticles(int count, Vector2 parentPosition, int alpha) {
	squirrelGibParticlesList.push_back(createSquirrelGibParticles(count, parentPosition, alpha));
}

void ParticleManager::removeOldParticles() {
	if (thaneParticlesList.size() > 400) {
		thaneParticlesList.erase(thaneParticlesList.begin(), thaneParticlesList.begin() + (thaneParticlesList.size() - 400));
	}

	if (squirrelGibParticlesList.size() > 75) {
		squirrelGibParticlesList.erase(squirrelGibParticlesList.begin(), squirrelGibParticlesList.begin() + (squirrelGibParticlesList.size() - 75));
	}
}

void ParticleManager::update() {
	elapsedTimeSeconds = timer.getTimeSeconds();

	for (ThaneParticles &particles : thaneParticlesList) {
		updateThaneParticles(elapsedTimeSeconds, particles);
	}

	for (SquirrelGibParticles &particles : squirrelGibParticlesList) {
		updateSquirrelGibParticles(elapsedTimeSeconds, particles);
	}

	removeOldParticles();
}

void ParticleManager::draw() {
	for (ThaneParticles particles : thaneParticlesList) {
		drawThaneParticles(particles);
	}

	for (SquirrelGibParticles particles : squirrelGibParticlesList) {
		drawSquirrelGibParticles(particles);
	}
}