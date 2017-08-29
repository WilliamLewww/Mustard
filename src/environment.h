#pragma once
#include "vector2.h"
#include <vector>

std::vector<Vector2> generateLongTrackRand(int difficulty, int count, int points, int pointSpacing, Vector2 startPoint);
std::vector<Vector2> generateTrackUp(int difficulty, int points, int pointSpacing, Vector2 startPoint);
std::vector<Vector2> generateTrackDown(int difficulty, int points, int pointSpacing, Vector2 startPoint);
std::vector<Vector2> generateTrackRand(int difficulty, int points, int pointSpacing, Vector2 startPoint);
std::vector<Vector2> generateTrackComp(std::vector<Vector2> track, Vector2 startPoint, int offsetY, int limitTop, int limitBottom);
std::vector<Vector2> duplicateTrack(std::vector<Vector2> track, int offsetY);
std::vector<Vector2> duplicateTrackPosition(std::vector<Vector2> track, Vector2 position);