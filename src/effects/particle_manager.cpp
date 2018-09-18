#include "particle_manager.h"

ParticleManager particleManager;

ParticleManager::ParticleManager() {
	
}

void ParticleManager::generateCrashParticles(int count, Vector2 parentPosition) {
	crashParticlesList.push_back(createCrashParticles(count, parentPosition));
}

void ParticleManager::generateThaneParticles(int count, Vector2 parentPosition, int alpha) {
	thaneParticlesList.push_back(createThaneParticles(count, parentPosition, alpha));
}

void ParticleManager::generateSquirrelGibParticles(int count, Vector2 parentPosition, int alpha) {
	squirrelGibParticlesList.push_back(createSquirrelGibParticles(count, parentPosition, alpha));
}

void ParticleManager::removeOldParticles() {
	if (thaneParticlesList.size() > MaxParticleCount::Thane) {
		thaneParticlesList.erase(thaneParticlesList.begin(), thaneParticlesList.begin() + (thaneParticlesList.size() - 400));
	}

	if (squirrelGibParticlesList.size() > MaxParticleCount::SquirrelGib) {
		squirrelGibParticlesList.erase(squirrelGibParticlesList.begin(), squirrelGibParticlesList.begin() + (squirrelGibParticlesList.size() - 75));
	}

	if (crashParticlesList.size() > MaxParticleCount::Crash) {
		crashParticlesList.erase(crashParticlesList.begin(), crashParticlesList.begin() + (crashParticlesList.size() - 5));
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

	for (CrashParticles &particles : crashParticlesList) {
		updateCrashParticles(elapsedTimeSeconds, particles);
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

	for (CrashParticles particles : crashParticlesList) {
		drawCrashParticles(particles);
	}
}