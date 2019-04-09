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

/* Structure Type of Matrix*/
typedef struct tagMatrix {
	float m[3][3];
} Matrix;

/* Same Structure Type of Point*/
typedef Point Vector;

// windows name
int winID;

// Init Points, Color
Point pTriangle[3] = { {0, 1}, {-1, -1}, {1, -1}};
Point pSquare[4] = { {-1, 1}, {-1, -1}, {1, -1}, {1, 1}};
Point pCross[4] = { {-1, 1}, {-1, -1},{1, -1}, {1,1} };

Color cTriangle = { 0, 0, 0 };
Color cSquare = { 255, 0, 0 };
Color cCross = { 255, 128, 0 };

Point xPos;
float ang2;
float ang3;
float ang4;
float ang5;

int rot;

Matrix Translate(const Vector &p)
{
	Matrix m;

	m.m[0][0] = 1.0f; m.m[0][1] = 0.0f; m.m[0][2] = p.x;
	m.m[1][0] = 0.0f; m.m[1][1] = 1.0f; m.m[1][2] = p.y;
	m.m[2][0] = 0.0f; m.m[2][1] = 0.0f; m.m[2][2] = 1.0f;

	return m;
}
/*
Matrix Scale(const Vector &s)
{
	Matrix m;
	// Fiil this part
	return m;
}

Matrix Rotate(const float &alpha)
{
	Matrix m;
	// Fill this part

	return m;
}
*/
Point matpoiMul(const Matrix &m, const Point &p)
{
	Point result;

	result.x = m.m[0][0] * p.x + m.m[0][1] * p.y + m.m[0][2];
	result.y = m.m[1][0] * p.x + m.m[1][1] * p.y + m.m[1][2];
	float w = m.m[2][0] * p.x + m.m[2][1] * p.y + m.m[2][2];

	result.x /= w;
	result.y /= w;

	return result;
}
/*
Matrix matmatMul(const Matrix &m1, const Matrix &m2)
{
	Matrix result;
	// Fill this part

	return result;
}
*/
/* Convert from Window To View*/
Point WindowToViewport(const Point &p)
{
	Point vPoint;
	vPoint.x = (int)((WIDTH / CWIDTH) *p.x + (WIDTH / 2.f));
	vPoint.y = (int)((-HEIGHT / CHEIGHT) *p.y + (HEIGHT / 2.f));

	return vPoint;
}

/* Draw to Line (Method of Normalized Vector, etc) */
void DrawLine(Point p1, Point p2, Color c) {
	/* Draw to Line (Horizon) */
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
	/* Draw to Line (Vertical) */
	else if (p1.x - p2.x == 0) {
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
	} else { 	// Draw to Line (Normalized vector)
		float vectorSize = sqrt(pow(p1.y - p2.y, 2) + pow(p1.x - p2.x, 2));		// Distance of point to point

		float UVectorx = (p1.x - p2.x) / vectorSize;		// Unit vector x
		float UVectory = (p1.y - p2.y) / vectorSize;		// Unit vector y

		for (int i = 0; i < vectorSize; i++) {
			FrameBuffer::SetPixel(p2.x + (i*UVectorx), p2.y + (i*UVectory), c.r, c.g, c.b);
		}
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		xPos.y += 1.0f;
		break;
	case 'a':
		xPos.x -= 1.0f;
		break;
	case 's':
		xPos.y -= 1.0f;
		break;
	case 'd':
		xPos.x += 1.0f;
		break;
	case VK_SPACE:
		if (rot == 1) rot = 0;
		else rot = 1;
		
		break;
	case VK_ESCAPE:
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
	FrameBuffer::Clear(255, 255, 255);

	//Put your rendering code here

	// Draw figure 1('x')

	/*
	DrawLine(points[1], points[2], b);
	DrawLine(points[2], points[3], b);
	DrawLine(points[3], points[4], b);
	DrawLine(points[4], points[1], b);
	
	DrawLine(points[5], points[6], b);
	DrawLine(points[6], points[7], b);
	DrawLine(points[7], points[8], b);
	DrawLine(points[8], points[5], b);
	DrawLine(points[8], points[9], b);
	*/

	glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, FrameBuffer::buffer);
	glutSwapBuffers();
}

void init(void)
{
	FrameBuffer::Init(WIDTH, HEIGHT);

	rot = 1;

	xPos.x = xPos.y = 0.0f;
	ang2 = 0.0f, ang3 = 45.0f; ang4 = 0.0f; ang5 = 60.0f;
/*
	int i = 0;
	printf("Goal: Camera(%d X %d) -> View (%d X %d)\n\n\n", (int)CWIDTH, (int)CHEIGHT, (int)WIDTH, (int)HEIGHT);

	// Convert from Camerat to View
	for (i = 1; i < 10; i++)
	{
		printf("P_c[%4d](%4d, %4d) -> ", i, points[i].x, points[i].y);
		points[i] = CameraToViewport(points[i]);
		printf("P_v[%4d](%4d, %4d)\n", i, points[i].x, points[i].y);
	}
	*/
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