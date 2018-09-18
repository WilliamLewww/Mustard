#include "crash_particle.h"

int crashParticlesColor[3] = { 103, 156, 192 };

CrashParticles createCrashParticles(int count, Vector2 parentPosition) {
	CrashParticles particles = { count, parentPosition };

	particles.width = 7;
	particles.thickness = 1;

	for (int x = 0; x < count; x++) {
		particles.crashSegmentList.push_back({parentPosition, (float)(rand() % 361), (float)(rand() % (400 + 1 + 350) - 350), ((float)(rand() % (100 + 1)) - 50) / 10 });
	}

	return particles;
}

void updateCrashParticles(float elapsedTimeSeconds, CrashParticles& particles) {
	for (CrashSegment& segment : particles.crashSegmentList) {
		if (segment.position.y < particles.parentPosition.y + abs(segment.offsetDirections * 6)) {
			segment.acceleration -= 400 * elapsedTimeSeconds;
			segment.position.y -= segment.acceleration * elapsedTimeSeconds;
			segment.position.x += (segment.offsetDirections * 8) * elapsedTimeSeconds;
			segment.angle += segment.offsetDirections;
		}
	}
}

void drawCrashParticles(CrashParticles particles) {
	for (CrashSegment segment : particles.crashSegmentList) {
		drawing.drawLine(segment.position, particles.width, particles.thickness, crashParticlesColor, segment.angle);
	}
}