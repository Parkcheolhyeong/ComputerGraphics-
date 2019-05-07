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