#pragma once

class Deck {
protected:
	std::string name;
	int length, width;

	int price;
	int ID;

	int life;
	int currentLife;

	int color[3];

	inline void setColor(int r, int g, int b) {
		color[0] = r; color[1] = g; color[2] = b;
	};
public:
	inline Deck() { };
	inline Deck(std::string name, int ID, int length, int width) {
		this->name = name;
		this->ID = ID;
		this->length = length;
		this->width = width;
	};

	inline int getLife() { return life; };
	inline int getCurrentLife() { return currentLife; };

	inline int getID() { return ID; };

	inline std::string getName() { return name; };
	inline int getLength() { return length; };
	inline int getWidth() { return width; };

	inline int getPrice() { return price; };

	inline int* getColor() { return color; };

	inline float getTurnRadius() {
		if (currentLife == 0) { return 0.5; }
		return ((45.0 - length) / 7.0);
	};

	inline void damage(int amount) { 
		if (currentLife - amount < 0) { currentLife = 0; }
		else { currentLife -= amount; }
	}
};

#include "deck_presets.h"

enum {
	DECK_SWITCHBLADE = 1,
	DECK_RUMRUNNERCARBON = 2,
	DECK_WOLFSHARKMINI = 3,

	DECK_COUNT = 3
};

static int getDeckCount() {
	return DECK_COUNT;
}

static Deck getDeck(int deckID) {
	Deck deck;

	switch (deckID) {
		case DECK_SWITCHBLADE: deck = Switchblade(15); break;
		case DECK_RUMRUNNERCARBON: deck = RumRunnerCarbon(30); break;
		case DECK_WOLFSHARKMINI: deck = WolfsharkMini(10); break;	
	}

	return deck;
};