#include "preset_models.h"

SDL_Color tutorialColor1 = { 30, 87, 100 };
SDL_Color tutorialColor2 = { 115, 55, 80 };
SDL_Color tutorialColor3 = { 76, 59, 42 };
int tutorialColor4[3] = { 209, 185, 175 };

void drawModelWelcome() {
	drawing.drawRect(Vector2(-175, -275), 375, 125, tutorialColor4);
	drawing.drawText("Welcome to Thane!!!", Vector2(-100, -250), 24, tutorialColor1);
	drawing.drawText("(Press any key to start rolling)", Vector2(-150, -220), 24, tutorialColor2);
	drawing.drawText("You are at the peak of a very very very very very very very very very large hill", Vector2(600, 75), 24, tutorialColor2);
}

void drawModelTurn() {
	drawing.drawText("Use the left and right arrow keys to carve", Vector2(70, 65), 24, tutorialColor3);
}

void drawModelSlide() {
	drawing.drawText("Uh oh, the corners just got tighter", Vector2(50, 65), 24, tutorialColor1);
	drawing.drawText("Hold \"A\" when turning to preform a slide/drift", Vector2(10, 90), 24, tutorialColor2);
}

void drawModelTuck() {
	drawing.drawText("As your speed increases, you might get speedwobbles if your form is stinky", Vector2(10, 65), 24, tutorialColor1);
	drawing.drawText("Hold \"SPACEBAR\" to preform a tuck", Vector2(75, 90), 24, tutorialColor2);
	drawing.drawText("You will gain speed and increase your stability in a tuck", Vector2(800, 120), 24, tutorialColor3);
}

void drawModelTech() {
	drawing.drawText("Technical slides are fast, flashy, and stylish", Vector2(50, 65), 24, tutorialColor1);
	drawing.drawText("Hold \"S\" when turning to preform a technical slide", Vector2(10, 90), 24, tutorialColor2);
}

void drawModelShutdown() {
	drawing.drawText("Going too fast?", Vector2(200, 65), 24, tutorialColor1);
	drawing.drawText("Hold \"D\" when turning to preform a shutdown slide", Vector2(10, 90), 24, tutorialColor2);
}

void drawModelMenu() {
	drawing.drawText("Beware of cars, cyclists, gravel pits, road squirrels, steep hills, speedwobbles, potholes, pinecones, trees, rain, puddles, oh god please help me, I think I just failed my stats final", Vector2(100, -90), 24, tutorialColor1);
	drawing.drawText("Smash pinecones to gain money", Vector2(50, 65), 24, tutorialColor2);
	drawing.drawText("You can show the main menu by pressing \"1\"", Vector2(10, 90), 24, tutorialColor2);
}