#pragma once
#include "src\vector2.h"
#include "src\geometry.h"
#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>
#include <ctime>

static const int SCREENWIDTH = 1600, SCREENHEIGHT = 900;
static const double pi = 3.14159265359;

static SDL_Window* displayWindow;