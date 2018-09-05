#include "timer.h"

Timer timer;

int Timer::getTime() {
	return elapsedTime;
}

float Timer::getTimeSeconds() {
	return (float)(elapsedTime) / 1000;
}

void Timer::setTime(int elapsedTime) {
	this->elapsedTime = elapsedTime;
}