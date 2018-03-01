#include "camera.h"

Camera camera;

void Camera::linkPosition(Vector2* position) {
	linkedPosition = position;
}

bool Camera::checkEntityInVisibleRange(Vector2 position, int width, int height) {
	if (position.x < configuration.getScreenWidth() + linkedPosition->x + rangeWidth &&
		position.x + width > linkedPosition->x - rangeWidth - (configuration.getScreenWidth() / 2) &&
		position.y < configuration.getScreenHeight() + linkedPosition->y + rangeHeight &&
		position.y + height > linkedPosition->y - rangeHeight - (configuration.getScreenHeight() / 2)) {

		return true;
	}
	return false;
}

double Camera::getBoundaryLeft() {
	return (linkedPosition->x - rangeWidth - (configuration.getScreenWidth() / 2));
}

double Camera::getBoundaryRight() {
	return (configuration.getScreenWidth() + linkedPosition->x + rangeWidth);
}