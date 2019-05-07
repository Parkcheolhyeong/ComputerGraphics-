#include "Utilities.h"

#define CHEIGHT 600.f
#define CWIDTH 800.f


/* Structure Type of Point */
typedef struct Point {
	int x, y;
} Point;

/* Structure Type of Color */
typedef struct Color {
	unsigned char r, g, b;
} Color;

int winID;
Point p1 = { 0, 0 }, p2 = { 0, 0 };

// Init Points, Color
Point points[10] = { {0, 0}, {-300, 200},{-300, -200},
					{-100, -150}, {-100, 150},
					{300, 0}, {300, 200},
					{100, 200}, {100, 0}, {100, -200} };
Color b = { 0, 0, 0 };

/* Convert from Camera To View*/
Point CameraToViewport(const Point &p)
{
	Point vPoint;
	vPoint.x = (int)((WIDTH / CWIDTH) *p.x + (WIDTH / 2.f));
	vPoint.y = (int)((-HEIGHT / CHEIGHT) *p.y + (HEIGHT / 2.f));

	return vPoint;
}

/* Draw to Line (Vertical, Horizon, Gradient */

void DrawVLine(Point p1, Point p2, Color c)
{
	if (p1.y - p2.y == 0)
	{
		if (p1.x < p2.x)
		{
			// p1 to p2
			for (int i = p1.x; i < p2.x; i++)
				FrameBuffer::SetPixel(i, p1.y, c.r, c.g, c.b);
		}
		else {
			// p2 to p1
			for (int i = p2.x; i < p1.x; i++)
				FrameBuffer::SetPixel(i, p2.y, c.r, c.g, c.b);
		}
	}
}
void DrawHLine(Point p1, Point p2, Color c)
{
	if (p1.x - p2.x == 0) {
		if (p1.y < p2.y)
		{
			// p1 to p2
			for (int i = p1.y; i < p2.y; i++)
				FrameBuffer::SetPixel(p1.x, i, c.r, c.g, c.b);
		}
		else {
			// p2 to p1
			for (int i = p2.y; i < p1.y; i++)
				FrameBuffer::SetPixel(p2.x, i, c.r, c.g, c.b);
		}
	}
}

void midPoint(float X1, float Y1, float X2, float Y2)		//Midpoint Line Algorithm
{

	if (X1 > X2)			// Opposite direction
	{
		midPoint(X2, Y2, X1, Y1);
		return;
	}

	float dx = X2 - X1;			// Distance of X
	float dy = Y2 - Y1;			// Distance of Y

	float x = X1, y = Y1;		// Values of x1, x2
	float m = fabs(dy / dx);		// Absolute gradient value

	float xStep = 0.f, yStep = 0.f;
	printf("%lf, %lf\n", x, y);		// print of x, y coordinate


	xStep = (dx > 0) ? 1.f : -1.f;
	dx = (dx > 0) ? dx : -dx;
	yStep = (dy > 0) ? 1.f : -1.f;
	dy = (dy > 0) ? dy : -dy;

	if (m <= 1)
	{
		float d = (2 * dy) - (dx);
		float de = (2 * dy);
		float dne = (2 * dy - 2 * dx);

		FrameBuffer::SetPixel(x, y, 0, 0, 0);

		while (dx > 0)
		{
			x+=xStep;

			if (d <= 0)							// E or East is chosen
				d += de;

			else								// NE or North East is chosen
			{
				d += dne;
				y+=yStep;
			}

			printf("%lf, %lf\n", x, y);		// print of x, y coordinate
			FrameBuffer::SetPixel(x, y, 0, 0, 0);
			dx--;
		}
	}
	else if (m > 1)
	{
		float d = (2 * dx) - dy;
		float dn = 2 * dx;
		float dne = (2 * dx) - (2 * dy);

		FrameBuffer::SetPixel(x, y, 0, 0, 0);

		while (dy>0)
		{
			y+=yStep;


			if (d <= 0)				// E or East is chosen
				d += dn;


			else					// NE or North East is chosen
			{
				d += dne;
				x+=xStep;
			}

			printf("%lf, %lf\n", x, y);		// print of x, y coordinate
			FrameBuffer::SetPixel(x, y, 0, 0, 0);
			dy--;
		}

	}
}
	
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'c':
		FrameBuffer::Clear(255, 255, 255);
		break;
			delete [] FrameBuffer::buffer;
			glutDestroyWindow(winID);
			exit(0);
			break;
	}
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case (GLUT_LEFT_BUTTON):
		if (state == GLUT_DOWN)
		{
			printf("1\n");
			printf("%d, %d\n", x, y);
			p1.x = x;
			p1.y = y;
		}
		break;

	case (GLUT_RIGHT_BUTTON):
		if (state == GLUT_DOWN)
		{
			printf("2\n");
			printf("%d, %d\n", x, y);
			p2.x = x;
			p2.y = y;
			//DrawLine(p1, p2, c);
			midPoint(p1.x,p1.y,p2.x,p2.y);
		}
		break;

	case (GLUT_MIDDLE_BUTTON):
		if (state == GLUT_DOWN)
		{
			printf("3\n");
		}
		break;
	}	
}


void mouseMove(int x, int y)
{
}

void loop(void)
{
	glutPostRedisplay();
}

void render(void)
{

	

	glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, FrameBuffer::buffer);
	glutSwapBuffers();
}

void init(void)
{
	FrameBuffer::Init(WIDTH, HEIGHT);
	int i = 0;
	printf("Goal: Camera(%d X %d) -> View (%d X %d)\n\n\n", (int)CWIDTH, (int)CHEIGHT, (int)WIDTH, (int)HEIGHT);

	// Convert from Camerat to View
	for (i = 1; i < 10; i++)
	{
		printf("P_c[%4d](%4d, %4d) -> ", i, points[i].x, points[i].y);
		points[i] = CameraToViewport(points[i]);
		printf("P_v[%4d](%4d, %4d)\n", i, points[i].x, points[i].y);
	}
}

int main (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	
	winID = glutCreateWindow("5293564_¹ÚÃ¶Çü");	// Window name

	glClearColor(0, 0, 0, 1);

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(render);
	glutIdleFunc(loop);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);

	init();

	glutMainLoop();

	return 0;
}