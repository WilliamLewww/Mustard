#include "profile.h"

Profile profile;

void Profile::addWheel(int wheelID) {
	wheelList.push_back(getWheel(wheelID));
	wheelNameList.push_back(getWheel(wheelID).getName());
}

bool Profile::buyWheel(int wheelID) {
	if (getWheel(wheelID).getPrice() <= score) {
		wheelList.push_back(getWheel(wheelID));
		wheelNameList.push_back(getWheel(wheelID).getName());
		score -= getWheel(wheelID).getPrice();

		return true;
	}

	return false;
}

void Profile::addDeck(int deckID) {
	deckList.push_back(getDeck(deckID));
	deckNameList.push_back(getDeck(deckID).getName());
}

bool Profile::buyDeck(int deckID) {
	if (getDeck(deckID).getPrice() <= score) {
		deckList.push_back(getDeck(deckID));
		deckNameList.push_back(getDeck(deckID).getName());
		score -= getDeck(deckID).getPrice();

		return true;
	}

	return false;
}