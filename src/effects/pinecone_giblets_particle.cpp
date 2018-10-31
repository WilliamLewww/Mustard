#include "pinecone_giblets_particle.h"

int pineconeGibColor[3][3] = { {152,101,0}, {255,191,128}, {0,153,0} };

PineconeGibParticles createPineconeGibParticles(int count, Vector2 parentPosition) {
	PineconeGibParticles particles = { parentPosition };

	particles.segmentWidth = 2;
	particles.segmentThickness = 1;

	for (int x = 0; x < count; x++) {
		particles.segmentList.push_back({parentPosition, (float)(rand() % 361), (float)(rand() % (250 + 1 + 200) - 200), ((float)(rand() % (100 + 1)) - 50) / 10, rand() % 3 });
	}

	return particles;
}

void updatePineconeGibParticles(float elapsedTimeSeconds, PineconeGibParticles& particles) {
	for (PineconeSegment& segment : particles.segmentList) {
		if (segment.position.y < particles.parentPosition.y + abs(segment.offsetDirections * 6)) {
			segment.acceleration -= 400 * elapsedTimeSeconds;
			segment.position.y -= segment.acceleration * elapsedTimeSeconds;
			segment.position.x += (segment.offsetDirections * 5) * elapsedTimeSeconds;
			segment.angle += segment.offsetDirections;
		}
	}
}

void drawPineconeGibParticles(PineconeGibParticles particles) {
	for (PineconeSegment segment : particles.segmentList) {
		drawing.drawLine(segment.position, particles.segmentWidth, particles.segmentThickness, pineconeGibColor[segment.colorIndex], segment.angle);
	}
}