#pragma once

class Boulder {
private:
	std::vector<Vector2> vertexList;

	int color[3];
public:
	Vector2 position;

	inline Boulder(Vector2 position) {
		this->position = position;
		vertexList.push_back(Vector2(position.x + (rand() % 75), position.y + (rand() % 75)));
		vertexList.push_back(Vector2(position.x + 25 + (rand() % 75), position.y + (rand() % 75)));
		vertexList.push_back(Vector2(position.x + 50 + (rand() % 75), position.y + 25 + (rand() % 75)));
		vertexList.push_back(Vector2(position.x + 25 + (rand() % 75), position.y + 60 + (rand() % 75)));
		vertexList.push_back(Vector2(position.x + (rand() % 75), position.y + 60 + (rand() % 75)));
		vertexList.push_back(Vector2(position.x - 10 + (rand() % 75), position.y + 45 + (rand() % 75)));

		int randomColor = rand() % (115 + 1 - 50) + 50;
		setColor(randomColor, randomColor, randomColor);
	};

	inline void setColor(int r, int g, int b) {
		color[0] = r;
		color[1] = g;
		color[2] = b;
	};

	inline void draw() {
		drawing.drawPolygon(vertexList, color, 255);
	};
};