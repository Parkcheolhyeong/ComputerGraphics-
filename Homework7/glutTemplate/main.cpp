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

Color Black = { 0, 0, 0 };
int winID;	// window's name
int flagCenter = 1;	// flag to prevent double draw
int flagX = 1;	// flag to active key 'c'
int flagY = 1;
Point pC = { 0, 0 }, pX = { 0, 0 }, pY = { 0, 0 };	// Point of center, x, y

/* FourWaySymmetric */
void DrawCircleFourWaySymmetric(int x, int y, int xC, int yC)
{
	FrameBuffer::SetPixel(x + xC, y + yC, 0, 0, 0);
	FrameBuffer::SetPixel(-x + xC, y + yC, 0, 0, 0);
	FrameBuffer::SetPixel(x + xC, -y + yC, 0, 0, 0);
	FrameBuffer::SetPixel(-x + xC, -y + yC, 0, 0, 0);
}

/* Midpoint Ellipse Drawing */
void MidpointEllipseDraw(int xC, int yC, int a, int b)
{
	int x, y;
	int d1, dE1, dSE1;
	int d2, dS2, dSE2;
	int powA, powB;


	int x0 = pow(a, 2) / sqrt(pow(a, 2) + pow(b, 2)); // x of Gradient Value for -1 
	int y0 = pow(b, 2) / sqrt(pow(a, 2) + pow(b, 2)); // y of Gradient Value for -1
	/* Init x, y */
	x = 0;
	y = round(b);
	powA = pow(a, 2); powB = pow(b, 2);

	/* Init decision variables */
	d1 = powB - (powA * b) + (powA / 4);
	dE1 = (3 * powB);
	dSE1 = (3 * powB) - (2 * powA * b) + (2 * powA);

	/* Init xStep, yStep */
	int xStep = 1;
	int yStep = 1;

	while (x <= x0) {


		if (d1 > 0) {	// Outside of Circle
		/* Update decision variables and coordinate*/
			x += xStep;
			y -= yStep;

			DrawCircleFourWaySymmetric(x, y, xC, yC);
			d1 += dSE1;
			dE1 += 2 * powB;
			dSE1 += ((2 * powB) + (2 * powA));
		}
		else if (d1 <= 0) {	// Inside of CIrcle or Boundary of Circle
		 /* Update decision variables and coordinate*/
			x += xStep;
			DrawCircleFourWaySymmetric(x, y, xC, yC);
			d1 += dE1;
			dE1 += 2 * powB;
			dSE1 += 2 * powB;

		}


	}

	/* Init decision variables */
	d2 = (powB*x) - (2 * powA * y) + powA + (powB / 4);
	dS2 = -(2 * powA*y) + (3 * powA);
	dSE2 = (2 * powB* x) - (2 * powA * y) + (3 * powA);

	while (y >= 0) {

		/* Init x, y */

		if (d2 > 0) {
			y -= yStep;

			DrawCircleFourWaySymmetric(x, y, xC, yC);
			d2 += dS2;
			dS2 += 2 * powA;
			dSE2 += 2 * powA;

		}
		else if (d2 <= 0) {	// Inside of CIrcle or Boundary of Circle
		   /* Update decision variables and coordinate*/
			y -= yStep;
			x += xStep;

			DrawCircleFourWaySymmetric(x, y, xC, yC);
			d2 += dSE2;
			dS2 += 2 * powA;
			dSE2 += (2 * powB) + (2 * powA);

		}

	}

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'e':
		flagCenter = 0;	// Set step1 of flag

		break;
	case 'r':
		FrameBuffer::Clear(255, 255, 255);		// Init view
		flagCenter = 1; flagX = 1; flagY = 1;	// Init flag variables

		break;

	}
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case (GLUT_LEFT_BUTTON):
		if (state == GLUT_DOWN && flagCenter == 0)	// Save CenterPoint & Set flagDoubleDraw
		{
			printf("LEFT: ");
			printf("%d, %d\n", x, y);

			pC.x = x;
			pC.y = y;
			flagX = 0; // Set step2 of flag
		}
		break;

	case (GLUT_RIGHT_BUTTON):	// Value of b
		if (state == GLUT_DOWN)	// Save radiusPoint & Drawing Circle & Set flagDoubleDraw
		{
			if (flagCenter == 0 && flagX == 0 && flagY == 0)
			{
				int rX = 0, rY = 0;
				pY.x = x;
				pY.y = y;
				printf("Right:");
				printf("%d, %d\n", x, y);

				rX = sqrt(pow(pX.x - pC.x, 2) + pow(pX.y - pC.y, 2)); // Majoir axis
				rY = sqrt(pow(pY.x - pC.x, 2) + pow(pY.y - pC.y, 2)); // Minor axis
				printf("%f, %f\n", rX, rY);
				MidpointEllipseDraw(pC.x, pC.y, rX, rY);
				flagX = 1; flagY = 1; // Unset step2, 3 of flag
			}
		}
		break;

	case (GLUT_MIDDLE_BUTTON):	// Value of a
		if (state == GLUT_DOWN)
		{
			if (flagCenter == 0 && flagX == 0)
			{
				pX.x = x;
				pX.y = y;

				printf("Middle: ");
				printf("%d, %d\n", x, y);
				flagY = 0; // Set step3 of flag
			}
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

int main(int argc, char **argv)
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