#include "screen_filter.h"

ScreenFilter screenFilter;

void ScreenFilter::update() {
	if (show) {
		elapsedTimeSeconds = timer.getTimeSeconds();

		if (isFlashing) {
			if (flashTimer >= flashInterval) {
				flashAlpha = 255;
				flashTimer = 0;
				flashInterval = rand() % (200 + 1 - 150) + 150;
			}
			else {
				flashTimer += 15.0 * elapsedTimeSeconds;
			}

			if (flashAlpha > 0) {
				if (flashAlpha - (300.0 * elapsedTimeSeconds) <= 0) {
					flashAlpha = 0;
				}
				else {
					flashAlpha -= (300.0 * elapsedTimeSeconds);
				}
			}
		}

		if (isWaveringA) {
			if (!flipWaveA) {
				if (currentWaveA + (waveSpeedA * elapsedTimeSeconds) <= waverMaxA) {
					currentWaveA += (waveSpeedA * elapsedTimeSeconds);
				}
				else {
					currentWaveA = waverMaxA;
					flipWaveA = true;
				}
			}
			else {
				if (currentWaveA - (waveSpeedA * elapsedTimeSeconds) >= waverMinA) {
					currentWaveA -= (waveSpeedA * elapsedTimeSeconds);
				}
				else {
					currentWaveA = waverMinA;
					flipWaveA = false;
				}
			}

			waveAlpha = alpha + currentWaveA;
		}
		else {
			if (currentWaveA != 0) {
				waveAlpha -= currentWaveA;
				currentWaveA = 0;
			}
		}
	}
}

void ScreenFilter::draw() {
	if (show) {
		if (isWaveringA) {
			drawing.drawRect(Vector2(0, 0), configuration.getScreenWidth(), configuration.getScreenHeight(), color, (double)waveAlpha);	
		}
		else {
			drawing.drawRect(Vector2(0, 0), configuration.getScreenWidth(), configuration.getScreenHeight(), color, alpha);	
		}

		if (isFlashing) {
			drawing.drawRect(Vector2(0, 0), configuration.getScreenWidth(), configuration.getScreenHeight(), flashColor, flashAlpha);	
		}
	}
}