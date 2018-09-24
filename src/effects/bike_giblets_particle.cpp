#include "bike_giblets_particle.h"

int bikeGibColor[5][3] = { {255,0,102}, {51,204,51}, {0,204,255}, {204,0,255}, {102,153,0} };

BikeGibParticles createBikeGibParticles(int count, Vector2 parentPosition) {
	BikeGibParticles particles = { parentPosition };

	particles.segmentWidth = 3;
	particles.segmentThickness = 1;

	for (int x = 0; x < count; x++) {
		particles.segmentList.push_back({parentPosition, (float)(rand() % 361), (float)(rand() % (200 + 1 + 150) - 150), ((float)(rand() % (100 + 1)) - 50) / 10, rand() % 6 });
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
}

void drawBikeGibParticles(BikeGibParticles particles) {
	for (BikeFrameSegment segment : particles.segmentList) {
		drawing.drawLine(segment.position, particles.segmentWidth, particles.segmentThickness, bikeGibColor[segment.colorIndex], segment.angle);
	}
}