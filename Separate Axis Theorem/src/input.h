#pragma once
#include "vector2.h"
#include <SDL2\SDL.h>
#include <vector>
#include <algorithm>

void getKeys(SDL_Event event);
void removeInitialPress();
extern std::vector<SDL_Keycode> keyList;
extern std::vector<SDL_Keycode> pressKeyList;

void getButtons(SDL_Event event);
extern bool leftButtonDown, leftButtonPress;
extern bool middleMouseDown, middleMousePress;
extern bool scrollUp, scrollDown;
extern int mouseX, mouseY;

void getController();
extern int controllerPad;
extern std::vector<int> controllerList;
extern std::vector<int> controllerPressList;

bool checkMouseOnEntity(Vector2 position, int width, int height);