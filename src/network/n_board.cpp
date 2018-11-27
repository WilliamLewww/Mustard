#include "n_board.h"

NBoard::NBoard(int ID) {
	this->ID = ID;
}

void NBoard::setFromString(std::string data) {

}

void NBoard::draw() {
	drawing.drawRect(position, width, height, angle);
}