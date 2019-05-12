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
int circleState = 1;
Point centerPoint = { 0, 0 }, radiusPoint = { 0, 0 };
void DrawCircleEightWaySymmetric(int x, int y, int xC, int yC)
{
	FrameBuffer::SetPixel(x + xC, -y + yC, 0, 0, 0);
	FrameBuffer::SetPixel(x + xC, y + yC, 0, 0, 0);
	FrameBuffer::SetPixel(-x + xC, -y + yC, 0, 0, 0);
	FrameBuffer::SetPixel(-x + xC, y + yC, 0, 0, 0);
	FrameBuffer::SetPixel(y + xC, -x + yC, 0, 0, 0);
	FrameBuffer::SetPixel(y + xC, x + yC, 0, 0, 0);
	FrameBuffer::SetPixel(-y + xC, -x + yC, 0, 0, 0);
	FrameBuffer::SetPixel(-y + xC, x + yC, 0, 0, 0);
}
void drawcircle(int xC, int yC, float radius)
{
	int x = 0;
	int y = round(radius);
	float d = (float)(5 / 4) - radius;
	float dE = (2 * x) + 3;
	float dSE = (2 * (x - y)) + 5;
	int xStep = 1;
	int yStep = 1;

	while (x<=y) {
		if (d > 0) {
		d += dSE;
		dE += 2.f; dSE += 4.f;
		x += xStep;
		y -= yStep;
		DrawCircleEightWaySymmetric(x, y, xC, yC);
		}else if (d <= 0) {
			d += dE;
			dE += 2.f; dSE += 2.f;
			x += xStep;
			DrawCircleEightWaySymmetric(x, y, xC, yC);
		} 
	}
		
}
	
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'c':
		circleState = 0;
		break;
	case 'r':
		FrameBuffer::Clear(255, 255, 255);
		break;
	case VK_ESCAPE:
		delete[] FrameBuffer::buffer;
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
			centerPoint.x = x;
			centerPoint.y = y;
		}
		break;

	case (GLUT_RIGHT_BUTTON):
		if (state == GLUT_DOWN)
		{
			if (circleState == 0)
			{
				radiusPoint.x = x;
				radiusPoint.y = y;
				float r = sqrt(pow(radiusPoint.x - centerPoint.x, 2) + pow(radiusPoint.y - centerPoint.y, 2));
				printf("2\n");
				printf("%d, %d\n", x, y);

				drawcircle(centerPoint.x, centerPoint.y, r);
			}
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