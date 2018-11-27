#include "n_joiner.h"

void NJoiner::linkBoard(Board *board) {
	this->board = board;
}

void NJoiner::draw() {
	for (NBoard board : nBoardList) {
		drawing.drawRect(board.getPosition(), board.getWidth(), board.getHeight(), board.getAngle());
	}
}

void NJoiner::sendPosition() {
	sendStr = "board_data:" + std::to_string(uniqueID) + ":";
	sendStr += std::to_string(board->bitmapPolygon.getPosition().x) + ":";
	sendStr += std::to_string(board->bitmapPolygon.getPosition().y) + ":";
	sendStr += std::to_string(board->bitmapPolygon.getAngle());
	sendMessage(&sendStr[0u]);
}

void NJoiner::initialNetworkMessage() {
	initializeWinsock((char *)ipAddress);

	sendStr = "connect";
	sendMessage(&sendStr[0u]);
	receiveInitialMessage();
	if (replyList[0].compare("connect") == 0) {
		replyList.erase(replyList.begin());
		netConnected = true;
		receiveMessage();
	}
}

bool NJoiner::handleNetwork(int &seed, int &rainSeed) {
	bool resetFull = false;

	if (netConnected) {
		if (replyList.size() > 0) {
			if (replyList[0].substr(0, 9).compare("unique_id") == 0) {
				uniqueID = std::stoi(replyList[0].substr(replyList[0].find(':') + 1));
				replyList.erase(replyList.begin());
			}

			if (replyList[0].substr(0, 4).compare("seed") == 0) {
				seed = std::stoi(replyList[0].substr(replyList[0].find(':') + 1));
				replyList.erase(replyList.begin());
			}

			if (replyList[0].substr(0, 9).compare("rain_seed") == 0) {
				rainSeed = std::stoi(replyList[0].substr(replyList[0].find(':') + 1));
				replyList.erase(replyList.begin());
			}

			if (replyList[0].substr(0, 10).compare("new_client") == 0) {
				nBoardList.emplace_back(NBoard(std::stoi(replyList[0].substr(replyList[0].find(':') + 1))));
				replyList.erase(replyList.begin());
			}

			if (replyList[0].substr(0, 10).compare("reset_full") == 0) {
				netStart = false;
				resetFull = true;
				replyList.erase(replyList.begin());
			}
		}

		if (advertList.size() > 0) {
			if (advertList[0].substr(0, 9).compare("rain_seed") == 0) {
				rainSeed = std::stoi(advertList[0].substr(advertList[0].find(':') + 1));
				advertList.erase(advertList.begin());
			}

			if (advertList[0].substr(0, 10).compare("new_client") == 0) {
				nBoardList.emplace_back(NBoard(std::stoi(advertList[0].substr(advertList[0].find(':') + 1))));
				advertList.erase(advertList.begin());
			}

			if (advertList[0].substr(0, 10).compare("reset_full") == 0) {
				netStart = false;
				resetFull = true;
				advertList.erase(advertList.begin());
			}

			if (advertList[0].substr(0, 5).compare("start") == 0) {
				netStart = true;
				advertList.erase(advertList.begin());
			}
		}
	}

	return resetFull;
}