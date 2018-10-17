#pragma once
#include "deck.h"

class Switchblade : public Deck {
public:
	Switchblade(int life) 
		:Deck("Landyachtz Switchblade", 1, 40, 10) { 

		setColor(103, 156, 192);
		this->price = 139;
		this->life = life;
		this->currentLife = life;
	};
};

class RumRunnerCarbon : public Deck {
public:
	RumRunnerCarbon(int life) 
		:Deck("Moonshine Rum Runner Carbon", 2, 36, 9) { 

		setColor(155, 24, 24);
		this->price = 246;
		this->life = life;
		this->currentLife = life;
	};
};

class WolfsharkMini : public Deck {
public:
	WolfsharkMini(int life) 
		:Deck("Landyachtz Wolfshark Mini", 3, 32, 10) { 

		setColor(125, 104, 221);
		this->price = 200;
		this->life = life;
		this->currentLife = life;
	};
};