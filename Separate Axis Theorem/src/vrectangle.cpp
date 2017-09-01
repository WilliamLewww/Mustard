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

// a_left <= b_right
// a_right >= b_left
// a_top <= b_bottom
// a_bottom >= b_top
std::vector<double> getProducts(VRectangle rectangle, Vector2 axis);
bool VRectangle::checkCollision(VRectangle rectangle) {
	std::vector<double> productsA, productsB;

	productsA = getProducts(*this, axisA());
	productsB = getProducts(rectangle, axisA());
	if (productsB[0] > productsA[1] || productsB[1] < productsA[0]) return false;

	productsA = getProducts(*this, axisB());
	productsB = getProducts(rectangle, axisB());
	if (productsB[0] > productsA[1] || productsB[1] < productsA[0]) return false;

	productsA = getProducts(*this, rectangle.axisA());
	productsB = getProducts(rectangle, rectangle.axisA());
	if (productsB[0] > productsA[1] || productsB[1] < productsA[0]) return false;

	productsA = getProducts(*this, rectangle.axisB());
	productsB = getProducts(rectangle, rectangle.axisB());
	if (productsB[0] > productsA[1] || productsB[1] < productsA[0]) return false;
	
	return true;
}

std::vector<double> getProducts(VRectangle rectangle, Vector2 axis) {
	std::vector<double> products;
	std::vector<double> minMax;

	products.push_back(rectangle.dotProduct(rectangle.project(axis, rectangle.topRight()), axis));
	products.push_back(rectangle.dotProduct(rectangle.project(axis, rectangle.topLeft()), axis));
	products.push_back(rectangle.dotProduct(rectangle.project(axis, rectangle.bottomRight()), axis));
	products.push_back(rectangle.dotProduct(rectangle.project(axis, rectangle.bottomLeft()), axis));

	minMax.push_back(*std::min_element(products.begin(), products.end()));
	minMax.push_back(*std::max_element(products.begin(), products.end()));
	return minMax;
}