#pragma once
#include "..\core\vector2.h"
#include "..\core\timer.h"
#include "thane_particle.h"
#include "squirrel_giblets_particle.h"

class ParticleManager {
private:
	float elapsedTimeSeconds;
	std::vector<ThaneParticles> thaneParticlesList;
	std::vector<SquirrelGibParticles> squirrelGibParticlesList;
public:
	void generateThaneParticles(int count, Vector2 parentPosition, int alpha);
	void generateSquirrelGibParticles(int count, Vector2 parentPosition, int alpha);

	void removeOldParticles();
	void update();
	void draw();
};

extern ParticleManager particleManager;