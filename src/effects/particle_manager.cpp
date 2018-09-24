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

void ParticleManager::generateBikeGibParticles(int count, Vector2 parentPosition) {
	bikeGibParticlesList.push_back(createBikeGibParticles(count, parentPosition));
}


void ParticleManager::generateFinishParticles(int count, Vector2 parentPosition) {
	finishParticlesList.push_back(createFinishParticles(count, parentPosition));
}

void ParticleManager::removeOldParticles() {
	if (thaneParticlesList.size() > MaxParticleCount::Thane) {
		thaneParticlesList.erase(thaneParticlesList.begin(), thaneParticlesList.begin() + (thaneParticlesList.size() - MaxParticleCount::Thane));
	}

	if (squirrelGibParticlesList.size() > MaxParticleCount::SquirrelGib) {
		squirrelGibParticlesList.erase(squirrelGibParticlesList.begin(), squirrelGibParticlesList.begin() + (squirrelGibParticlesList.size() - MaxParticleCount::SquirrelGib));
	}

	if (bikeGibParticlesList.size() > MaxParticleCount::BikeGib) {
		bikeGibParticlesList.erase(bikeGibParticlesList.begin(), bikeGibParticlesList.begin() + (bikeGibParticlesList.size() - MaxParticleCount::BikeGib));
	}

	if (finishParticlesList.size() > MaxParticleCount::Finish) {
		finishParticlesList.erase(finishParticlesList.begin(), finishParticlesList.begin() + (finishParticlesList.size() - MaxParticleCount::Finish));
	}

	if (crashParticlesList.size() > MaxParticleCount::Crash) {
		crashParticlesList.erase(crashParticlesList.begin(), crashParticlesList.begin() + (crashParticlesList.size() - MaxParticleCount::Crash));
	}
}

void ParticleManager::clearAllParticles() {
	thaneParticlesList.clear();
	squirrelGibParticlesList.clear();
	bikeGibParticlesList.clear();
	finishParticlesList.clear();
	crashParticlesList.clear();
}

void ParticleManager::update() {
	elapsedTimeSeconds = timer.getTimeSeconds();

	for (ThaneParticles &particles : thaneParticlesList) {
		updateThaneParticles(elapsedTimeSeconds, particles);
	}

	for (SquirrelGibParticles &particles : squirrelGibParticlesList) {
		updateSquirrelGibParticles(elapsedTimeSeconds, particles);
	}

	for (BikeGibParticles &particles : bikeGibParticlesList) {
		updateBikeGibParticles(elapsedTimeSeconds, particles);
	}

	for (FinishParticles &particles : finishParticlesList) {
		updateFinishParticles(elapsedTimeSeconds, particles);
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

	for (BikeGibParticles particles : bikeGibParticlesList) {
		drawBikeGibParticles(particles);
	}

	for (FinishParticles particles : finishParticlesList) {
		drawFinishParticles(particles);
	}

	for (CrashParticles particles : crashParticlesList) {
		drawCrashParticles(particles);
	}
}