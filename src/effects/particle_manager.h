#pragma once
#include "..\core\vector2.h"
#include "..\core\timer.h"
#include "crash_particle.h"
#include "thane_particle.h"
#include "squirrel_giblets_particle.h"
#include "bike_giblets_particle.h"
#include "finish_particle.h"

enum MaxParticleCount {
	Thane = 400,
	SquirrelGib = 75,
	Finish = 75,
	Crash = 4,
	BikeGib = 5
};

class ParticleManager {
private:
	float elapsedTimeSeconds;
	std::vector<CrashParticles> crashParticlesList;
	std::vector<ThaneParticles> thaneParticlesList;
	std::vector<FinishParticles> finishParticlesList;
	std::vector<SquirrelGibParticles> squirrelGibParticlesList;
	std::vector<BikeGibParticles> bikeGibParticlesList;
public:
	ParticleManager();

	void initialize();
	
	void generateCrashParticles(int count, Vector2 parentPosition);
	void generateThaneParticles(int count, Vector2 parentPosition, int alpha);
	void generateSquirrelGibParticles(int count, Vector2 parentPosition, int alpha);
	void generateBikeGibParticles(int count, Vector2 parentPosition);
	void generateFinishParticles(int count, Vector2 parentPosition);

	void removeOldParticles();
	void clearAllParticles();
	void update();
	void draw();
};

extern ParticleManager particleManager;