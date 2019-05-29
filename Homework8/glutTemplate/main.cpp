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

struct point2d_Float {
	float x, y;
};


Color Black = { 0, 0, 0 };
int winID;	// window's name
int counter = 0;
point2d_Float rVertices[3] = { {0.f, 0.f}, {0.f, 0.f}, {0.f, 0.f} }; // Three Point of vertice, x, y


/* DDA Triangle Drawing */
void DrawTriangle(point2d_Float p0, point2d_Float p1, point2d_Float p2)
{
	point2d_Float Top = { 0.f, 0.f }, Middle = { 0.f, 0.f}, Bottom = {0.f, 0.f};
	bool middleIsLeft = NULL;

	if (p0.y < p1.y)                    // case: 4, 5, 6
	{
		if (p2.y < p0.y)        // case: 4
		{
			Top = p2;
			Middle = p0;
			Bottom = p1;
			middleIsLeft = true;
		}
		else if (p1.y < p2.y) {	// case: 5

			Top = p0;
			Middle = p1;
			Bottom = p2;
			middleIsLeft = true;
		}
		else if (p1.y > p2.y) {	// case: 5

			Top = p0;
			Middle = p2;
			Bottom = p1;
			middleIsLeft = false;
		}
	}
	else {                    // case: 1, 2, 3
		if (p2.y < p1.y) {		// case: 2
			Top = p2;
			Middle = p1;
			Bottom = p0;
			middleIsLeft = false;
		} else if (p0.y < p2.y) {	// case: 3
			Top = p1;
			Middle = p0;
			Bottom = p2;
			middleIsLeft = false;
		} else if (p0.y > p2.y) {	// case: 4
			Top = p1;
			Middle = p2;
			Bottom = p0;
			middleIsLeft = true;
		}
	}


	float InverseSlope[3] = { 0.f, 0.f, 0.f };

	float xLeft, xRight;
	xLeft = xRight = Top.x;
	float leftEdge, rightEdge;
	InverseSlope[0] = (Top.x - Bottom.x) / (Top.y - Bottom.y);
	InverseSlope[1] = (Top.x - Middle.x) / (Top.y - Middle.y);
	InverseSlope[2] = (Middle.x - Bottom.x) / (Middle.y - Bottom.y);

	// Region 1

	for (int y = ceil(Top.y); y <= ceil(Middle.y) - 1; y++)
	{
		if (middleIsLeft)
		{
			leftEdge = InverseSlope[1];
			rightEdge = InverseSlope[0];
		}
		else
		{
			leftEdge = InverseSlope[0];
			rightEdge = InverseSlope[1];
		}

		for (int x = ceil(xLeft); x <= ceil(xRight) - 1; x++)
		{
			FrameBuffer::SetPixel(x, y, 0, 0, 0);

		}
		xLeft += leftEdge;
		xRight += rightEdge;
	}

	// Region 2 


	for (int y = ceil(Middle.y); y <= ceil(Bottom.y) - 1; y++)
	{
		if (middleIsLeft)
		{
			leftEdge = InverseSlope[2];
		}
		else
		{
			rightEdge = InverseSlope[2];
		}
		for (int x = ceil(xLeft); x <= ceil(xRight) - 1; x++)
		{
			FrameBuffer::SetPixel(x, y, 0, 0, 0);
		}
		xLeft += leftEdge;
		xRight += rightEdge;

	}

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'e':

		break;
	case 'r':
		FrameBuffer::Clear(255, 255, 255);		// Init view

		break;

	}
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case (GLUT_LEFT_BUTTON):
		if (state == GLUT_DOWN)	// Save CenterPoint & Set flagDoubleDraw
		{
			printf("LEFT: ");

			printf("%d: %d, %d\n", counter, x, y);
			rVertices[counter].x = x;
			rVertices[counter].y = y;

			if (counter == 2)
			{
				DrawTriangle(rVertices[0], rVertices[1], rVertices[2]);	//그리기
				counter = 0;
				break;
			}
			counter++;
		}
		break;

	case (GLUT_RIGHT_BUTTON):	// Value of b
		if (state == GLUT_DOWN)	// Save radiusPoint & Drawing Circle & Set flagDoubleDraw
		{
			printf("Right:");
		}
		break;

	case (GLUT_MIDDLE_BUTTON):	// Value of a
		if (state == GLUT_DOWN)
		{
			printf("Middle: ");
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

	winID = glutCreateWindow("5293564_박철형");	// Window name

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