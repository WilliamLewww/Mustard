#pragma once
#include "board.h"
#include "camera.h"
#include "configuration.h"

class Joiner {
private:
	Board board;
public:
	void initialize();
	void draw();
	void update(int elapsedTime);
};

extern Joiner joiner;