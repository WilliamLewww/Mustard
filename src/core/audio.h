#pragma once
#include <vector>
#include <bass.h>
#include <bass_fx.h>

class Audio {
private:
	std::vector<HSTREAM> streams;
public:
	void initialize(HWND hwnd);
	void quit();

	void playSoundFile(const char* file);

	void playStream(int index);
	void stopStream(int index);
	void resetStream(int index);
	int createStreamFromFile(const char* file);
	void changeStreamPitchSemitone(int index, float amount);
};

extern Audio audio;