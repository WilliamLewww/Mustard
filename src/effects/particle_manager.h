#pragma once
#include "..\core\vector2.h"
#include "thane_particle.h"

class ParticleManager {
private:
	float elapsedTimeSeconds;
	std::vector<ThaneParticles> thaneParticlesList;
public:
	void generateThaneParticles(int count, Vector2 parentPosition);
	void update(int elapsedTime);
	void draw();
};

extern ParticleManager particleManager;