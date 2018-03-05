#include "bmp_polygon.h"

void BitmapPolygon::setSize(int width, int height) {
	this->width = width;
	this->height = height;
}

void BitmapPolygon::setColor(int red, int green, int blue, int alpha) {
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	this->alpha = alpha;
}

void BitmapPolygon::setVerticesFromFile(const char* filename) {
	std::ifstream fin(filename);
	Vector2 temp_vertex = Vector2(-1, -1);

	int x;
	while (fin >> x) {
		if (temp_vertex.y != -1) { vertices.push_back(temp_vertex); temp_vertex = Vector2(-1, -1); }
		if (temp_vertex.x == -1) { temp_vertex.x = x; }
		else { temp_vertex.y = x; }
	}

	vertices.push_back(temp_vertex);

	fin.close();
};

void BitmapPolygon::drawOutline() {
	drawing.drawLineStrip(position, width, height, vertices, angle, color);
};

bool BitmapPolygon::checkCollision(BitmapPolygon rectangle) {
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

std::vector<double> BitmapPolygon::getProducts(BitmapPolygon rectangle, Vector2 axis) {
	std::vector<double> products;
	std::vector<double> minMax;

	products.push_back(dotProduct(project(axis, rectangle.getTopRight()), axis));
	products.push_back(dotProduct(project(axis, rectangle.getTopLeft()), axis));
	products.push_back(dotProduct(project(axis, rectangle.getBottomRight()), axis));
	products.push_back(dotProduct(project(axis, rectangle.getBottomLeft()), axis));

	minMax.push_back(*std::min_element(products.begin(), products.end()));
	minMax.push_back(*std::max_element(products.begin(), products.end()));
	return minMax;
}

bool BitmapPolygon::checkCollision(Vector2* line) {
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

std::vector<double> BitmapPolygon::getProducts(Vector2* line, Vector2 axis) {
	std::vector<double> products;
	std::vector<double> minMax;

	products.push_back(dotProduct(project(axis, line[0]), axis));
	products.push_back(dotProduct(project(axis, line[1]), axis));

	minMax.push_back(*std::min_element(products.begin(), products.end()));
	minMax.push_back(*std::max_element(products.begin(), products.end()));
	return minMax;
}

Vector2 BitmapPolygon::project(Vector2 axisArgs, Vector2 vertex) {
		return Vector2((((vertex.x * axisArgs.x) + (vertex.y * axisArgs.y)) / (pow(axisArgs.x, 2) + pow(axisArgs.y, 2))) * axisArgs.x, 
					   (((vertex.x * axisArgs.x) + (vertex.y * axisArgs.y)) / (pow(axisArgs.x, 2) + pow(axisArgs.y, 2))) * axisArgs.y);
}

double BitmapPolygon::dotProduct(Vector2 projection, Vector2 axis) {
		return (projection.x * axis.x) + (projection.y * axis.y);
}