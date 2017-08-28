#pragma once
#include "vector2.h"
#include <vector>

std::vector<Vector2> generateTrackUp(int difficulty, int count, int spacing, Vector2 startPoint);
std::vector<Vector2> generateTrackDown(int difficulty, int count, int spacing, Vector2 startPoint);
std::vector<Vector2> generateTrackRand(int difficulty, int count, int spacing, Vector2 startPoint);
std::vector<Vector2> duplicateTrack(std::vector<Vector2> track, int offsetY);
std::vector<Vector2> duplicateTrackPosition(std::vector<Vector2> track, Vector2 position);