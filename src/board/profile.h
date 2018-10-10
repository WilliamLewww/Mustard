#pragma once
#include <vector>
#include "wheel.h"
#include "deck.h"

class Profile {
private:
	std::vector<Wheel> wheelList;
	std::vector<std::string> wheelNameList;

	std::vector<Deck> deckList;
	std::vector<std::string> deckNameList;

	float score;
public:
	inline Profile() { 
		addWheel(1);
		addDeck(1);
	 };

	inline void addScore(float score) { this->score += score; };
	inline void setScore(float score) { this->score = score; };
	inline float getScore() { return score; };

	inline std::vector<std::string>& getWheelNameList() { return wheelNameList; };
	inline std::vector<std::string>& getDeckNameList() { return deckNameList; };

	inline void addWheel(int wheelID) {
		wheelList.push_back(getWheel(wheelID));
		wheelNameList.push_back(getWheel(wheelID).getName());
	}

	inline void addDeck(int deckID) {
		deckList.push_back(getDeck(deckID));
		deckNameList.push_back(getDeck(deckID).getName());
	}
};

extern Profile profile;