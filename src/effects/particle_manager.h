#pragma once
#include "..\core\vector2.h"
#include "..\core\timer.h"
#include "crash_particle.h"
#include "thane_particle.h"
#include "squirrel_giblets_particle.h"
#include "bike_giblets_particle.h"
#include "pinecone_giblets_particle.h"
#include "finish_particle.h"
#include "puck_particle.h"

enum MaxParticleCount {
	Thane = 400,
	SquirrelGib = 75,
	Finish = 75,
	Crash = 4,
	BikeGib = 5,
	PineconeGib = 12,
	Puck = 200
};

class ParticleManager {
private:
	float elapsedTimeSeconds;
	std::vector<CrashParticles> crashParticlesList;
	std::vector<ThaneParticles> thaneParticlesList;
	std::vector<FinishParticles> finishParticlesList;
	std::vector<SquirrelGibParticles> squirrelGibParticlesList;
	std::vector<BikeGibParticles> bikeGibParticlesList;
	std::vector<PineconeGibParticles> pineconeGibParticlesList;
	std::vector<PuckParticles> puckParticlesList;
public:
	ParticleManager();

	void initialize();
	
	void generatePineconeGibParticles(int count, Vector2 parentPosition);
	void generateCrashParticles(int count, Vector2 parentPosition);
	void generateThaneParticles(int count, Vector2 parentPosition, int alpha);
	void generateSquirrelGibParticles(int count, Vector2 parentPosition, int alpha);
	void generateBikeGibParticles(int count, Vector2 parentPosition);
	void generateFinishParticles(int count, Vector2 parentPosition);
	void generatePuckParticles(int count, Vector2 parentPosition, int alpha);

	void removeOldParticles();
	void clearAllParticles();
	void update();
	void draw();
};

extern ParticleManager particleManager;