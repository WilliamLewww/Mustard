#pragma once
#include <vector>
#include <string>
#include "..\board\board.h"
#include "..\core\gui.h"
#include "network.h"
#include "n_board.h"

class NJoiner {
private:
	int uniqueID = -1;

	Board *board;
	std::string sendStr;
	std::vector<NBoard> nBoardList;
public:
	bool netStart = false;
	char ipAddress[512] = "127.0.0.1";

	void linkBoard(Board *board);
	void update();
	void draw();
	void sendPosition();
	bool handleNetwork(int *seed, int *rainSeed);
	void initialNetworkMessage();
};