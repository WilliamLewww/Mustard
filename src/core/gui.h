#pragma once
#include <SDL2\SDL.h>
#include <SDL2\SDL_opengl.h>
#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl_gl2.h"

class GUI {
private:
	SDL_DisplayMode current;

	SDL_Event* event;
	SDL_Window* displayWindow;
public:
	void setDisplayWindow(SDL_Window *displayWindow);
	void setEvent(SDL_Event *event);

	void setupWindow();
	void bindWindow();
	void processEvent();
	void newFrame();
	void draw();
};

extern GUI gui;