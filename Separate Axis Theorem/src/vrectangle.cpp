#include "vrectangle.h"

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

bool VRectangle::checkCollision(VRectangle rectangle) {
	dotProduct(project(axisA(), topRight()), axisA());
	dotProduct(project(axisA(), topLeft()), axisA());
	dotProduct(project(axisA(), bottomRight()), axisA());
	dotProduct(project(axisA(), bottomLeft()), axisA());
}