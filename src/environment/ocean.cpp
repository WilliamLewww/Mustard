#include "ocean.h"

int waveColor[5][3] = { {153,235,255}, {230,250,255}, {26,209,255}, {179,240,255}, {51,214,255} };

void Ocean::generateWaves() {
	for (int x = 0; x < configuration.getScreenWidth(); x += 5) {
		for (int y = 0; y < configuration.getScreenHeight(); y += 5) {
			if (rand() % 100 == 0) {
				waveList.push_back({Vector2(x, y), rand() % (100 + 1 - 75) + 75, rand() % 3, (double)(rand() % 126), rand() % 2, rand() % 2});
			}
		}
	}
}

void Ocean::update() {
	elapsedTimeSeconds = timer.getTimeSeconds();

	for (Wave& wave : waveList) {
		if (wave.fadeIn) {
			if (wave.alpha + (fadeSpeed * elapsedTimeSeconds) >= 125) {
				wave.alpha = 125;
				wave.direction = !wave.direction;
				wave.fadeIn = false;
			}
			else {
				wave.alpha += (fadeSpeed * elapsedTimeSeconds);
			}
		}
		else {
			if (wave.alpha - (fadeSpeed * elapsedTimeSeconds) <= 0) {
				wave.alpha = 0;
				wave.position = Vector2((rand() % configuration.getScreenWidth()) - 50, rand() % configuration.getScreenHeight());
				wave.width = rand() % (100 + 1 - 75) + 75;
				wave.colorID = rand() % 3;
				wave.direction = !wave.direction;
				wave.fadeIn = true;
			}
			else {
				wave.alpha -= (fadeSpeed * elapsedTimeSeconds);
			}
		}

		if (wave.direction) { wave.position.x += 5.0 * elapsedTimeSeconds; }
		else { wave.position.x -= 5.0 * elapsedTimeSeconds; }
	}
}

void Ocean::drawStatic() {
	for (Wave wave : waveList) {
		drawing.drawRect(wave.position, wave.width, waveLength, waveColor[wave.colorID], wave.alpha);
	}
}