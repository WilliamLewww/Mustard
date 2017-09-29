#include "geometry.h"

double convertColor(int rgbValue) {
	return (double)rgbValue / 255;
}

void drawPoint(Vector2 position, int color[3]) {
	glBegin(GL_POINTS);
	glColor4f(convertColor(color[0]), convertColor(color[1]), convertColor(color[2]), 1);
	glVertex2d(position.x - (SCREENWIDTH / 2), position.y - (SCREENHEIGHT / 2));
	glEnd();
}

void drawEdgesOfRect(Vector2 position, int width, int height, double angle, int color[3]) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x + (width / 2) - (SCREENWIDTH / 2), position.y + (height / 2) - (SCREENHEIGHT / 2), 0);
	glRotatef(-angle, 0, 0, 1);
	glTranslatef(-(position.x + (width / 2) - (SCREENWIDTH / 2)), -(position.y + (height / 2) - (SCREENHEIGHT / 2)), 0);
	glBegin(GL_POINTS);
	glColor4f(convertColor(color[0]), convertColor(color[1]), convertColor(color[2]), 1);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glPopMatrix();
}

void drawRect(VRectangle rectangle) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(rectangle.position.x + (rectangle.width / 2) - (SCREENWIDTH / 2), rectangle.position.y + (rectangle.height / 2) - (SCREENHEIGHT / 2), 0);
	glRotatef(-rectangle.angle, 0, 0, 1);
	glTranslatef(-(rectangle.position.x + (rectangle.width / 2) - (SCREENWIDTH / 2)), -(rectangle.position.y + (rectangle.height / 2) - (SCREENHEIGHT / 2)), 0);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= rectangle.width;
		vectors[x].y *= rectangle.height;
		vectors[x] += Vector2(rectangle.position.x, rectangle.position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glPopMatrix();
}

void drawRect(Vector2 position, int width, int height) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
}

void drawRect(Vector2 position, int width, int height, double angle) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x + (width / 2) - (SCREENWIDTH / 2), position.y + (height / 2) - (SCREENHEIGHT / 2), 0);
	glRotatef(-angle, 0, 0, 1);
	glTranslatef(-(position.x + (width / 2) - (SCREENWIDTH / 2)), -(position.y + (height / 2) - (SCREENHEIGHT / 2)), 0);
	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glPopMatrix();
}

void drawRect(Vector2 position, int width, int height, int color[3]) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glBegin(GL_QUADS);
	glColor4f(convertColor(color[0]), convertColor(color[1]), convertColor(color[2]), 1);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
}

void drawLine(Vector2 a, Vector2 b) {
	glBegin(GL_LINES);
	glColor4f(1, 1, 1, 1);
	glVertex2f(a.x - (SCREENWIDTH / 2), a.y - (SCREENHEIGHT / 2));
	glVertex2f(b.x - (SCREENWIDTH / 2), b.y - (SCREENHEIGHT / 2));
	glEnd();
}

void drawLine(Vector2 a, Vector2 b, int color[3]) {
	glBegin(GL_LINES);
	glColor4f(convertColor(color[0]), convertColor(color[1]), convertColor(color[2]), 1);
	glVertex2f(a.x - (SCREENWIDTH / 2), a.y - (SCREENHEIGHT / 2));
	glVertex2f(b.x - (SCREENWIDTH / 2), b.y - (SCREENHEIGHT / 2));
	glEnd();
}

void drawLine(Vector2 a, Vector2 b, int color[3], int alpha) {
	glBegin(GL_LINES);
	glColor4f(convertColor(color[0]), convertColor(color[1]), convertColor(color[2]), convertColor(alpha));
	glVertex2f(a.x - (SCREENWIDTH / 2), a.y - (SCREENHEIGHT / 2));
	glVertex2f(b.x - (SCREENWIDTH / 2), b.y - (SCREENHEIGHT / 2));
	glEnd();
}

void drawLineStrip(std::vector<Vector2> points, int color[3]) {
	glBegin(GL_LINE_STRIP);
	//glEnable(GL_LINE_SMOOTH);
	glColor4f(convertColor(color[0]), convertColor(color[1]), convertColor(color[2]), 1);
	for (int x = 0; x < points.size(); x++) { glVertex2f(points[x].x - (SCREENWIDTH / 2), points[x].y - (SCREENHEIGHT / 2)); }
	glEnd();
}

void drawCircle(Vector2 position, float radius) {
	glBegin(GL_LINE_LOOP);
	glColor4f(1, 1, 1, 1);

	double radians = pi / 180;
	for (int i = 0; i < 360; i++) {
		glVertex2d((cos(i * radians)*radius) - (SCREENWIDTH / 2) + position.x, (sin(i * radians)*radius) - (SCREENHEIGHT / 2) + position.y);
	}

	glEnd();
}

void drawCircle(Vector2 position, float radius, int color[3]) {
	glBegin(GL_LINE_LOOP);
	glColor4f(convertColor(color[0]), convertColor(color[1]), convertColor(color[2]), 1);

	double radians = pi / 180;
	for (int i = 0; i < 360; i++) {
		glVertex2d((cos(i * radians)*radius) - (SCREENWIDTH / 2) + position.x, (sin(i * radians)*radius) - (SCREENHEIGHT / 2) + position.y);
	}

	glEnd();
}

void drawTriangle(Vector2 position, int width, int height) {
	Vector2 vectors[3]{
		Vector2(0, 0),
		Vector2(.5, 1),
		Vector2(1, 0),
	};

	glBegin(GL_TRIANGLES);
	glColor4f(1, 1, 1, 1);
	for (int x = 0; x < 3; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
}

void drawTriangle(Vector2 position, int width, int height, double angle) {
	Vector2 vectors[3]{
		Vector2(0, 1),
		Vector2(1, .5),
		Vector2(0, 0),
	};

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(position.x + (width / 2) - (SCREENWIDTH / 2), position.y + (height / 2) - (SCREENHEIGHT / 2), 0);
	glRotatef(-angle, 0, 0, 1);
	glTranslatef(-(position.x + (width / 2) - (SCREENWIDTH / 2)), -(position.y + (height / 2) - (SCREENHEIGHT / 2)), 0);
	glBegin(GL_TRIANGLES);
	glColor4f(1, 1, 1, 1);
	for (int x = 0; x < 3; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glPopMatrix();
}