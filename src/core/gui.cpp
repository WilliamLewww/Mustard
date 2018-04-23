#include "gui.h"

GUI gui;

void GUI::setupWindow() {
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GetCurrentDisplayMode(0, &current);
}

void GUI::bindWindow() {
	ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplSdlGL2_Init(displayWindow);
}

void GUI::processEvent() {
	ImGui_ImplSdlGL2_ProcessEvent(event);
}

void GUI::newFrame() {
	ImGui_ImplSdlGL2_NewFrame(displayWindow);
}

void GUI::draw() {
	ImGui::Render();
	ImGui_ImplSdlGL2_RenderDrawData(ImGui::GetDrawData());
}

void GUI::setDisplayWindow(SDL_Window *displayWindow) {
	this->displayWindow = displayWindow;
}

void GUI::setEvent(SDL_Event *event) {
	this->event = event;
}