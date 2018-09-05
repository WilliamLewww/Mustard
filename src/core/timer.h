#pragma once

class Timer {
private:
	int elapsedTime;
public:
	int getTime();
	float getTimeSeconds();

	void setTime(int elapsedTime);
};

extern Timer timer;