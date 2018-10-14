#pragma once
#include "deck.h"

class Switchblade : public Deck {
public:
	Switchblade() 
		:Deck("Landyachtz Switchblade", 1, 40, 10) { 

		setColor(103, 156, 192);
		this->price = 139;
	};
};

class RumRunnerCarbon : public Deck {
public:
	RumRunnerCarbon() 
		:Deck("Moonshine Rum Runner Carbon", 2, 36, 9) { 

		setColor(155, 24, 24);
		this->price = 246;
	};
};

class WolfsharkMini : public Deck {
public:
	WolfsharkMini() 
		:Deck("Landyachtz Wolfshark Mini", 3, 32, 10) { 

		setColor(125, 104, 221);
		this->price = 200;
	};
};