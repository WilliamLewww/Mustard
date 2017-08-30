#include "vrectangle.h"
static const double pi = 3.14159265359;

VRectangle::VRectangle() {
	position = Vector2(0,0);
	width = 0;
	height = 0;
	angle = 0;
}

VRectangle::VRectangle(Vector2 posArgs, double wArgs, double hArgs) {
	position = posArgs;
	width = wArgs;
	height = hArgs;
	angle = 0;
}

VRectangle::VRectangle(Vector2 posArgs, double wArgs, double hArgs, double aArgs) {
	position = posArgs;
	width = wArgs;
	height = hArgs;
	angle = aArgs;
}

Vector2 VRectangle::topLeft() {
	return Vector2((-width / 2) * cos((angle * pi) / 180) - (height / 2) * sin((angle * pi) / 180) + position.x + (width / 2),
				   (width / 2) * sin((angle * pi) / 180) - (height / 2) * cos((angle * pi) / 180) + position.y + (height / 2));
}

Vector2 VRectangle::topRight() {
	return Vector2((width / 2) * cos((angle * pi) / 180) - (height / 2) * sin((angle * pi) / 180) + position.x + (width / 2),
				   (-width / 2) * sin((angle * pi) / 180) - (height / 2) * cos((angle * pi) / 180) + position.y + (height / 2));
}

Vector2 VRectangle::bottomLeft() {
	return Vector2((-width / 2) * cos((angle * pi) / 180) - (-height / 2) * sin((angle * pi) / 180) + position.x + (width / 2),
				   (width / 2) * sin((angle * pi) / 180) - (-height / 2) * cos((angle * pi) / 180) + position.y + (height / 2));
}

Vector2 VRectangle::bottomRight() {
	return Vector2((width / 2) * cos((angle * pi) / 180) - (-height / 2) * sin((angle * pi) / 180) + position.x + (width / 2),
				   (-width / 2) * sin((angle * pi) / 180) - (-height / 2) * cos((angle * pi) / 180) + position.y + (height / 2));
}