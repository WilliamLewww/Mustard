#pragma once
#include "..\vector2.h"
#include "..\geometry.h"
#include <vector>

class Shoeometer {
	std::vector<VRectangle> rectangleList;
public:
	inline void draw() { for (VRectangle rect : rectangleList) { drawRect(rect); }};

	inline void updateStyleA(int shoeLeft) { 
		if (shoeLeft == 0) { rectangleList.clear(); }
		if (rectangleList.size() < shoeLeft) {
			for (int x = 0; x < shoeLeft - rectangleList.size(); x++) {
				rectangleList.push_back(VRectangle(
					Vector2(15 + (rectangleList.size() * 8), SCREENHEIGHT - 40), 5, 5));
			}
		}
		else {
			for (int x = 0; x < rectangleList.size() - shoeLeft; x++) {
				rectangleList.erase(rectangleList.begin() + rectangleList.size() - x);
			}
		}
	};
};