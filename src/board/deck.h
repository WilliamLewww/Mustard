#pragma once

class Deck {
protected:
	std::string name;
	int length, width;

	int color[3];

	inline void setColor(int r, int g, int b) {
		color[0] = r; color[1] = g; color[2] = b;
	};
public:
	inline Deck() { };
	inline Deck(std::string name, int length, int width) {
		this->name = name;
		this->length = length;
		this->width = width;
	}

	inline std::string getName() { return name; }
	inline int getLength() { return length; }
	inline int getWidth() { return width; }

	inline int* getColor() { return color; }
};

#include "deck_presets.h"

enum {
	DECK_SWITCHBLADE = 1,
	DECK_RUMRUNNERCARBON = 2,
	DECK_WOLFSHARKMINI = 3
};

static Deck getDeck(int deckID) {
	Deck deck;

	switch (deckID) {
		case DECK_SWITCHBLADE: deck = Switchblade(); break;
		case DECK_RUMRUNNERCARBON: deck = RumRunnerCarbon(); break;
		case DECK_WOLFSHARKMINI: deck = WolfsharkMini(); break;	
	}

	return deck;
};