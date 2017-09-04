#pragma once
#include "..\vector2.h"
#include "..\geometry.h"
#include <vector>
#include <iostream>

class Speedometer {
	int counter = 0;
	std::vector<VRectangle> rectangleList;
public:
	inline void draw() { for (VRectangle rect : rectangleList) { drawRect(rect); }};

	inline void updateStyleA(int velocity) {
		int interval = velocity / 5;
		if (interval == 0) { rectangleList.clear(); counter = 0; }
		if (rectangleList.size() < interval) {
			for (int x = 0; x < interval - rectangleList.size(); x++) {
				switch (counter) {
				case (0):
					rectangleList.push_back(VRectangle(
					Vector2(15 + (rectangleList.size() * 10), SCREENHEIGHT - 30), 8, 8));
					counter += 1;
					break;
				case (1):
					rectangleList.push_back(VRectangle(
					Vector2(15 + (rectangleList.size() * 10), SCREENHEIGHT - 30), 8, 8));
					counter += 1;
					break;
				case (2):
					rectangleList.push_back(VRectangle(
					Vector2(15 + ((rectangleList.size() - 2) * 10), SCREENHEIGHT - 20), 8, 8));
					counter += 1;
					break;
				case (3):
					rectangleList.push_back(VRectangle(
					Vector2(15 + ((rectangleList.size() - 2) * 10), SCREENHEIGHT - 20), 8, 8));
					counter = 0;
					break;
				}
			}
		}
		else {
			for (int x = 0; x < rectangleList.size() - interval; x++) {
				counter -= 1;
				if (counter < 0) { counter = 3; }
				rectangleList.erase(rectangleList.begin() + rectangleList.size() - x);
			}
		}
	};

	inline void updateStyleB(int velocity) { 
		int interval = velocity / 5;
		if (interval == 0) { rectangleList.clear(); counter = 0; }
		if (rectangleList.size() < interval) {
			for (int x = 0; x < interval - rectangleList.size(); x++) {
				rectangleList.push_back(VRectangle(
					Vector2(15 + (rectangleList.size() * 10), SCREENHEIGHT - 30), 8, 16));
			}
		}
		else {
			for (int x = 0; x < rectangleList.size() - interval; x++) {
				rectangleList.erase(rectangleList.begin() + rectangleList.size() - x);
			}
		}
	};
};