#include <windows.h>

#include "GL/glut.h"

const int window_side_size = 700;

const int view_side_size = 30;

const int period = 500;

struct color_t

{

	double r, g, b, a;

	void setThis() const

	{

		const color_t& color = *this;

		glColor4d(color.r, color.g, color.b, color.a);

	}

};

const color_t black = { 0, 0, 0, 1 };

const color_t blue = { 0, 0.1, 0.8, 1 };

const color_t green = { 0.4, 0.9, 0.0, 1 };

const color_t red = { 1, 0, 0, 1 };

const color_t orange = { 1, 0.5, 0.0, 1 };

const color_t grey = { 0.2, 0.2, 0.2, 0.5 };

const color_t violet = { 0.85, 0.0, 0.85, 1 };

void draw_fat_pixel(int x, int y, color_t color = black)

{

	color.setThis();

	glBegin(GL_POLYGON);

	glVertex2d(x - 0.5, y - 0.5);

	glVertex2d(x - 0.5, y + 0.5);

	glVertex2d(x + 0.5, y + 0.5);

	glVertex2d(x + 0.5, y - 0.5);

	glEnd();

}

void draw_cell()

{

	glLineWidth(1);

	black.setThis();

	for (int i = -view_side_size; i <= view_side_size; ++i)

	{

		glBegin(GL_LINES);

		glVertex2f(i + 0.5f, -view_side_size + .0f);

		glVertex2f(i + 0.5f, view_side_size + .0f);

		glVertex2f(-view_side_size + .0f, i + 0.5f);

		glVertex2f(view_side_size + .0f, i + 0.5f);

		glEnd();

	}

}

void draw_axises()

{

	glLineWidth(2);

	red.setThis();

	glBegin(GL_LINES);

	glVertex2i(-view_side_size, 0);

	glVertex2i(view_side_size, 0);

	glVertex2i(0, -view_side_size);

	glVertex2i(0, view_side_size);

	glEnd();

}

void initialize()

{

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glOrtho(-view_side_size, view_side_size, -view_side_size, view_side_size, -1.0, 1.0);

}

void drawBR(int x1, int x2, int y1, int y2) {

	const int minX = -15, maxX = 8, minY = -9, maxY = 13; //Прорисовка квадрата

	int px, py, error, lasty = -100;

	int x, y, deltaerr;

	x = x1;

	y = y1;

	px = abs(x2 - x1);

	py = abs(y2 - y1);

	error = 0;

	if (px >= py) deltaerr = py;

	else deltaerr = px;

	while (((x2 >= x1 && x <= x2) || (x2 < x1 && x >= x2)) && ((y2 >= y1 && y <= y2) || (y2 < y1 && y >= y2))) {

		if (x >= minX && x < maxX && y >= minY && y < maxY) {

			draw_fat_pixel(x, y, orange);

		}

		else {

			if (x <= minX && y < maxY && y > minY) draw_fat_pixel(minX, y, green);

			else if (y <= minY && x < maxX && x >= minX) draw_fat_pixel(x, minY, green);

			else if (y > maxY && x < maxX && x > minX) draw_fat_pixel(x, maxY - 1, green);

			else if (x >= maxX && y < maxY && y > minY) draw_fat_pixel(maxX - 1, y, green);

			draw_fat_pixel(x, y, violet);

		}

		error = error + deltaerr;

		if (px >= py) {

			if (2 * error >= deltaerr) {

				if (y2 < y1) {

					y--;

				}

				else y++;

				error = error - px;

			}

			if (x2 > x1) x++;

			else if (x2 < x1) x--;

		}

		else {

			if (2 * error >= deltaerr) {

				if (x2 > x1) x++;

				else if (x2 < x1) x--;

				error = error - py;

			}

			if (y2 > y1) y++;

			else if (y2 < y1) y--;

		}

	}

}

void Draw()

{

	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	int X1 = -7, Y1 = 5, 
	X2 = 5, Y2 = 1, 
	X3 = -8, Y3 = -6, 
	X4 = 0, Y4 = 0,
	X5 = 0, Y5 = 0,
	X6 = 0, Y6 = 0,
	X7 = 0, Y7 = 0,
	X8 = 0, Y8 = 0,
	X9 = 0, Y9 = 0,
	X10 = 0, Y10 = 0;

	drawBR(X1, X2, Y1, Y2);

	drawBR(X2, X3, Y2, Y3);

	drawBR(X3, X1, Y3, Y1);

	X1 = -10, Y1 = 13, 
	X2 = 17, Y2 = 11, 
	X3 = 11, Y3 = -13,
	X4 = -16, Y4 = -9;

	drawBR(X1, X2, Y1, Y2);

	drawBR(X2, X3, Y2, Y3);

	drawBR(X3, X4, Y3, Y4);

	drawBR(X4, X1, Y4, Y1);

	X1 = -13, Y1 = 20, 
	X2 = 22, Y2 = 15, 
	X3 = 14, Y3 = -24, 
	X4 = -23, Y4 = -17,
	X5 = -24, Y5 = 5;

	drawBR(X1, X2, Y1, Y2);

	drawBR(X2, X3, Y2, Y3);

	drawBR(X3, X4, Y3, Y4);

	drawBR(X4, X5, Y4, Y5);

	drawBR(X5, X1, Y5, Y1);

	glPopMatrix();

	draw_axises();

	draw_cell();

	glFlush();

}

void timf(int value)

{

	glutPostRedisplay();

	glutTimerFunc(period, timf, 0);

}

int main(int argc, char** argv)

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(window_side_size, window_side_size);

	glutInitWindowPosition(25, 25);

	glutCreateWindow("АБ-021");

	initialize();

	glutDisplayFunc(Draw);

	glutTimerFunc(period, timf, 0);

	glutMainLoop();

	return 0;

}