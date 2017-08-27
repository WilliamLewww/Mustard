#pragma once
#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>
#include <ctime>
#include "src\input.h"
#include "src\joiner.h"

static const int SCREENWIDTH = 1600, SCREENHEIGHT = 900;
static const double pi = 3.14159265359;

static SDL_Window* displayWindow;