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

bool VRectangle::checkCollision(Vector2* line) {
	std::vector<double> productsA, productsB;

	productsA = getProducts(*this, axisA());
	productsB = getProducts(line, axisA());
	if (productsB[0] > productsA[1] || productsB[1] < productsA[0]) return false;

	productsA = getProducts(*this, axisB());
	productsB = getProducts(line, axisB());
	if (productsB[0] > productsA[1] || productsB[1] < productsA[0]) return false;

	Vector2 opposite = Vector2(line[1].y - line[0].y, line[0].x - line[1].x);
	productsA = getProducts(*this, opposite);
	productsB = getProducts(line, opposite);
	if (productsB[0] > productsA[1] || productsB[1] < productsA[0]) return false;

	return true;
}

std::vector<double> getProducts(Vector2* line, Vector2 axis) {
	std::vector<double> products;
	std::vector<double> minMax;

	products.push_back(dotProduct(project(axis, line[0]), axis));
	products.push_back(dotProduct(project(axis, line[1]), axis));

	minMax.push_back(*std::min_element(products.begin(), products.end()));
	minMax.push_back(*std::max_element(products.begin(), products.end()));
	return minMax;
}

// a_left <= b_right
// a_right >= b_left
// a_top <= b_bottom
// a_bottom >= b_top
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

	products.push_back(dotProduct(project(axis, rectangle.topRight()), axis));
	products.push_back(dotProduct(project(axis, rectangle.topLeft()), axis));
	products.push_back(dotProduct(project(axis, rectangle.bottomRight()), axis));
	products.push_back(dotProduct(project(axis, rectangle.bottomLeft()), axis));

	minMax.push_back(*std::min_element(products.begin(), products.end()));
	minMax.push_back(*std::max_element(products.begin(), products.end()));
	return minMax;
}

Vector2 project(Vector2 axisArgs, Vector2 vertex) {
		return Vector2((((vertex.x * axisArgs.x) + (vertex.y * axisArgs.y)) / (pow(axisArgs.x, 2) + pow(axisArgs.y, 2))) * axisArgs.x, 
					   (((vertex.x * axisArgs.x) + (vertex.y * axisArgs.y)) / (pow(axisArgs.x, 2) + pow(axisArgs.y, 2))) * axisArgs.y);
}

double dotProduct(Vector2 projection, Vector2 axis) { return (projection.x * axis.x) + (projection.y * axis.y); }