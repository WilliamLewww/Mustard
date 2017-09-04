#pragma once
#include "gbutton.h"
#include <vector>

class GUI {
	std::vector<GButton> buttonList;
public:
	void draw();
	inline void addButton(GButton button) { buttonList.push_back(button); }
};