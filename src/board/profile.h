#pragma once
#include <string>
#include <vector>
#include "..\core\file.h"
#include "wheel.h"
#include "deck.h"

class Profile {
private:
	std::vector<Wheel> wheelList;
	std::vector<std::string> wheelNameList;

	std::vector<Deck> deckList;
	std::vector<std::string> deckNameList;

	std::vector<std::vector<Vector2>> deckModelList;
	
	float score = 30;
public:
	inline void initialize() { 
		deckModelList = file.getVerticesFromFileFull("board.data");
		addWheel(1); addDeck(1); 
	};

	inline std::vector<Vector2> getDeckModel(int ID) { return deckModelList[ID - 1]; };

	inline Wheel* getWheelFromList(int ID) { return &wheelList[ID]; };
	inline Deck* getDeckFromList(int ID) { return &deckList[ID]; };

	inline std::vector<Wheel> getWheelList() { return wheelList; };
	inline std::vector<Deck> getDeckList() { return deckList; };

	inline void addScore(float score) { this->score += score; };
	inline void setScore(float score) { this->score = score; };
	inline float getScore() { return score; };

	inline std::vector<std::string>& getWheelNameList() { return wheelNameList; };
	inline std::vector<std::string>& getDeckNameList() { return deckNameList; };

	void addWheel(int wheelID);
	bool buyWheel(int wheelID);

	void addDeck(int deckID);
	bool buyDeck(int deckID);

	void setWheelName(int index);
	void setAllWheelNames();

	void setDeckName(int index);
	void setAllDeckNames();
};

extern Profile profile;