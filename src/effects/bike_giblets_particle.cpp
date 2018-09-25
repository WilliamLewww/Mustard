#include "bike_giblets_particle.h"

int bikeBloodColor[3] = { 165, 49, 49 };
int bikeGibColor[5][3] = { {255,0,102}, {51,204,51}, {0,204,255}, {204,0,255}, {102,153,0} };

BikeGibParticles createBikeGibParticles(int count, Vector2 parentPosition) {
	BikeGibParticles particles = { parentPosition };

	particles.segmentWidth = 3;
	particles.segmentThickness = 1;

	for (int x = 0; x < count; x++) {
		particles.segmentList.push_back({parentPosition, (float)(rand() % 361), (float)(rand() % (350 + 1 + 300) - 300), ((float)(rand() % (100 + 1)) - 50) / 10, rand() % 6 });
	}

	for (int x = 0; x < count * 10; x++) {
		particles.particleList.push_back({parentPosition, (float)(rand() % (200 + 1 + 150) - 150), ((float)(rand() % (100 + 1)) - 50) / 10, (rand() % (255 + 1 + 150) - 150)});
	}

	return particles;
}

void updateBikeGibParticles(float elapsedTimeSeconds, BikeGibParticles& particles) {
	for (BikeFrameSegment& segment : particles.segmentList) {
		if (segment.position.y < particles.parentPosition.y + abs(segment.offsetDirections * 6)) {
			segment.acceleration -= 400 * elapsedTimeSeconds;
			segment.position.y -= segment.acceleration * elapsedTimeSeconds;
			segment.position.x += (segment.offsetDirections * 8) * elapsedTimeSeconds;
			segment.angle += segment.offsetDirections;
		}
	}

	for (BikeBloodParticle& particle : particles.particleList) {
		if (particle.position.y < particles.parentPosition.y + abs(particle.offsetDirections * 6)) {
			particle.acceleration -= 400 * elapsedTimeSeconds;
			particle.position.y -= particle.acceleration * elapsedTimeSeconds;
			particle.position.x += (particle.offsetDirections * 8) * elapsedTimeSeconds;
		}
	}
}

void drawBikeGibParticles(BikeGibParticles particles) {
	for (BikeFrameSegment segment : particles.segmentList) {
		drawing.drawLine(segment.position, particles.segmentWidth, particles.segmentThickness, bikeGibColor[segment.colorIndex], segment.angle);
	}

	for (BikeBloodParticle& particle : particles.particleList) {
		drawing.drawPoint(particle.position, bikeBloodColor, particle.alpha);
	}
}