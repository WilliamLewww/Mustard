#pragma once
#include "..\vector2.h"
#include "..\geometry.h"
#include <vector>
#include <iostream>

class Speedometer {
	std::vector<VRectangle> rectangleList;
public:
	inline void draw() { for (VRectangle rect : rectangleList) { drawRect(rect); }};

	inline void update(int velocity) {
		int interval = velocity / 5;
		if (rectangleList.size() < interval) {
			for (int x = 0; x < interval - rectangleList.size(); x++) {
				rectangleList.push_back(VRectangle(
					Vector2(25 + (rectangleList.size() * 10), 100), 5, 5));
			}
		}
		else {
			for (int x = 0; x < rectangleList.size() - interval; x++) {
				rectangleList.erase(rectangleList.begin() + rectangleList.size() - x);
			}
		}
	};
};