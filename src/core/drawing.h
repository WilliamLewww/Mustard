#pragma once
#include <vector>
#include <SDL2\SDL_opengl.h>
#include "vector2.h"
#include "configuration.h"

class Drawing {
private:
	double convertColorFloatToRGB(int rgbValue);
public:
	const double PI = 3.14159265359;

	void drawPoint(Vector2 position);
	void drawPoint(Vector2 position, int alpha);
	void drawPoint(Vector2 position, int color[3]);
	void drawPoint(Vector2 position, int color[3], int alpha);
	void drawRect(Vector2 position, int width, int height);
	void drawRect(Vector2 position, int width, int height, double angle);
	void drawRect(Vector2 position, int width, int height, double angle, int color[3]);
	void drawRect(Vector2 position, int width, int height, int color[3]);
	void drawEdgesOfRect(Vector2 position, int width, int height, double angle, int color[3]);
	void drawLine(Vector2 a, Vector2 b);
	void drawLine(Vector2 a, Vector2 b, int color[3]);
	void drawLine(Vector2 a, Vector2 b, int color[3], int alpha);
	void drawLine(Vector2 position, int width, int thickness, int color[3], double angle);
	void drawLineStrip(Vector2 *points, int count, Vector2 position, float scale, int color[3]);
	void drawLineStrip(std::vector<Vector2> points, int color[3]);
	void drawLineStrip(std::vector<Vector2> points, int color[3], int alpha);
	void drawLineStrip(std::vector<Vector2> points, int offset, int color[3], int alpha);
	void drawLineStrip(std::vector<Vector2> points, std::vector<Vector2> pointsB, int color[3]);
	void drawLineStrip(std::vector<Vector2> points, std::vector<Vector2> pointsB, int offset, int color[3], int alpha);
	void drawLineStrip(Vector2 position, double width, double height, std::vector<Vector2> vertices, double angle, int color[3]);
	void drawPolygon(std::vector<Vector2> points, float color, int alpha);
	void drawPolygon(std::vector<Vector2> points, int color, int alpha);
	void drawPolygon(std::vector<Vector2> points, int color[3], int alpha);
	void drawPolygon(Vector2 position, std::vector<Vector2> vertices, int color[3], int alpha);
	void drawPolygon(Vector2 position, double width, double height, std::vector<Vector2> vertices, double angle, int color[3], int alpha);
	void drawCircle(Vector2 position, float radius);
	void drawCircle(Vector2 position, float radius, int color[3]);
	void drawCircleFill(Vector2 position, float radius, int color[3]);
	void drawTriangle(Vector2 position, int width, int height);
	void drawTriangle(Vector2 position, int width, int height, double angle);
};

extern Drawing drawing;