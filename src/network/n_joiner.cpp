#include "n_joiner.h"

void NJoiner::linkBoard(Board *board) {
	this->board = board;
}

void NJoiner::update() {
	for (NBoard &nBoard : nBoardList) {
		nBoard.update();
	}
}

void NJoiner::draw() {
	for (NBoard nBoard : nBoardList) {
		drawing.drawRect(nBoard.getPosition(), nBoard.getWidth(), nBoard.getHeight(), nBoard.getAngle());
	}
}

void NJoiner::sendPosition() {
	sendStr = "board_data:";
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
	if (replyList.front().compare("connect") == 0) {
		replyList.pop();
		netConnected = true;
		receiveMessage();
	}
}

bool NJoiner::handleNetwork(int *seed, int *rainSeed) {
	bool resetFull = false;

	if (netConnected) {
		if (!replyList.empty()) {
			if (replyList.front().substr(0, 9).compare("unique_id") == 0) {
				uniqueID = std::stoi(replyList.front().substr(replyList.front().find(':') + 1));
				replyList.pop();
			}

			if (replyList.front().substr(0, 4).compare("seed") == 0) {
				*seed = std::stoi(replyList.front().substr(replyList.front().find(':') + 1));
				replyList.pop();
			}

			if (replyList.front().substr(0, 9).compare("rain_seed") == 0) {
				*rainSeed = std::stoi(replyList.front().substr(replyList.front().find(':') + 1));
				replyList.pop();
			}

			if (replyList.front().substr(0, 10).compare("new_client") == 0) {
				nBoardList.emplace_back(NBoard(std::stoi(replyList.front().substr(replyList.front().find(':') + 1))));
				replyList.pop();
			}

			if (replyList.front().substr(0, 10).compare("reset_full") == 0) {
				netStart = false;
				resetFull = true;
				replyList.pop();
			}
		}

		if (!advertList.empty()) {
			if (advertList.front().substr(0, 9).compare("rain_seed") == 0) {
				*rainSeed = std::stoi(advertList.front().substr(advertList.front().find(':') + 1));
				advertList.pop();
			}

			if (advertList.front().substr(0, 10).compare("new_client") == 0) {
				nBoardList.emplace_back(NBoard(std::stoi(advertList.front().substr(advertList.front().find(':') + 1))));
				advertList.pop();
			}

			if (advertList.front().substr(0, 10).compare("reset_full") == 0) {
				netStart = false;
				resetFull = true;
				advertList.pop();
			}

			if (advertList.front().substr(0, 5).compare("start") == 0) {
				netStart = true;
				advertList.pop();
			}

			if (advertList.front().substr(0, 10).compare("board_data") == 0) {
				std::string tempMessage(advertList.front().substr(advertList.front().find(':') + 1));
				int id = std::stoi(tempMessage.substr(0, tempMessage.find(':')));
				tempMessage = tempMessage.substr(tempMessage.find(':') + 1);

				for (NBoard &nboard : nBoardList) {
					if (nboard.getID() == id) {
						nboard.addDataFromString(tempMessage);
					}
				}

				advertList.pop();
			}
		}
	}

	return resetFull;
}