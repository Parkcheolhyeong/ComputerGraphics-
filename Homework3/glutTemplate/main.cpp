#include "Utilities.h"

#define CHEIGHT 600.f
#define CWIDTH 800.f

using namespace std;

/* Structure Type of Point */
typedef struct tagPoint {
	int x, y;
} Point;

/* Structure Type of Color */
typedef struct tagColor {
	unsigned char r, g, b;
} Color;

/*Structure Type of Matrix*/
typedef struct tagMatrix {
	float m[3][3];
} Matrix;

typedef Point Vector;

/* Global Varies*/
int winID; 
float ang2, ang3, ang4, ang5;
int rot;
Point xPos;

// Init points
Point pTriangle[] = { {0, 1}, {-1, -1}, {1, -1} };
Point pSquare[] = { {-1, 1}, {-1, -1}, {1, -1}, {1, 1} };
Point pCross[] = { {-1, 1}, {-1, -1}, {1, -1}, {1, 1} };

/* Calc T */
Matrix Translate(const Vector &p)
{
	Matrix m;

	m.m[0][0] = 1.0f; m.m[0][1] = 0.0f; m.m[0][2] = p.x;
	m.m[1][0] = 0.0f; m.m[1][1] = 1.0f; m.m[1][2] = p.y;
	m.m[2][0] = 0.0f; m.m[2][1] = 0.0f; m.m[2][2] = 1.0f;

	return m;
}

/* Calc S */
Matrix Scale(const Vector &s)
{
	Matrix m;

	m.m[0][0] = s.x; m.m[0][1] = 0.0f; m.m[0][2] = 0.0f;
	m.m[1][0] = 0.0f; m.m[1][1] = s.y; m.m[1][2] = 0.0f;
	m.m[2][0] = 0.0f; m.m[2][1] = 0.0f; m.m[2][2] = 1.0f;

	return m;
}

/* Calc R */
Matrix Rotate(const float &alpha)
{
	Matrix m;

	m.m[0][0] = cosf(alpha); m.m[0][1] = -sinf(alpha); m.m[0][2] = 0;
	m.m[1][0] = sinf(alpha); m.m[1][1] = cosf(alpha); m.m[1][2] = 0;
	m.m[2][0] = 0; m.m[2][1] = 0; m.m[2][2] = 1;

	return m;
}

/* Calc Point Mul Matrix */
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

/* Calc Matrix Mul Matrix*/
Matrix matmatMul(const Matrix &m1, const Matrix &m2)
{
	Matrix result;

	int i = 0;
	int j = 0;
	int k = 0;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			result.m[i][j] = 0.f;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			for (k = 0; k < 3; k++)
			{
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}

		}
	}
	return result;
}




/* Convert from Camera To View*/
Point ModelToViewport(const Point &p)
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
	}
	else { 	// Draw to Line (Normalized vector)
		float vectorSize = sqrt(pow(p1.y - p2.y, 2) + pow(p1.x - p2.x, 2));		// Distance of point to point

		float UVectorx = (p1.x - p2.x) / vectorSize;		// Unit vector x
		float UVectory = (p1.y - p2.y) / vectorSize;		// Unit vector y

		for (int i = 0; i < vectorSize; i++) {
			FrameBuffer::SetPixel(p2.x + (i*UVectorx), p2.y + (i*UVectory), c.r, c.g, c.b);
		}
	}
}

/* Set keyboard setting */
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

	// Put your rendering code here

	// object1_cross
	Vector pScale, pTranslate, points[4];
	Matrix mScale, mRotate, mTranslate;

	// Init T,R,S
	pScale.x = pScale.y = 8;
	pTranslate = xPos;

	mScale = Scale(pScale);
	mRotate = Rotate(0.0f * DEG_TO_RAD);
	mTranslate = Translate(pTranslate);

	// Multiple T, R, S
	Matrix result = matmatMul(mTranslate, mRotate);
	result = matmatMul(result, mScale);

	points[0] = matpoiMul(result, pCross[0]); 
	points[1] = matpoiMul(result, pCross[1]);
	points[2] = matpoiMul(result, pCross[2]); 
	points[3] = matpoiMul(result, pCross[3]);
	
	// Convert Model to View
	points[0] = ModelToViewport(points[0]); 
	points[1] = ModelToViewport(points[1]);
	points[2] = ModelToViewport(points[2]); 
	points[3] = ModelToViewport(points[3]);

	// Set RGB
	Color c;
	c.r = 255, c.g = 128, c.b = 0;

	// Draw
	DrawLine(points[0], points[2], c);
	DrawLine(points[1], points[3], c);

	// Object2_square

	// Init T,R,S
	pScale.x = 60, pScale.y = 20;
	pTranslate.x = 100 + xPos.x, pTranslate.y = 100 + xPos.y;

	mScale = Scale(pScale);
	mRotate = Rotate(ang2 * DEG_TO_RAD);
	mTranslate = Translate(pTranslate);

	// Multiple T, R, S
	result = matmatMul(mTranslate, mRotate);
	result = matmatMul(result, mScale);

	points[0] = matpoiMul(result, pSquare[0]);
	points[1] = matpoiMul(result, pSquare[1]);
	points[2] = matpoiMul(result, pSquare[2]);
	points[3] = matpoiMul(result, pSquare[3]);

	// Convert Model to View
	points[0] = ModelToViewport(points[0]);
	points[1] = ModelToViewport(points[1]);
	points[2] = ModelToViewport(points[2]);
	points[3] = ModelToViewport(points[3]);

	// Set RGB
	c.r = 255, c.g = 0, c.b = 0;

	// Draw
	DrawLine(points[0], points[1], c);
	DrawLine(points[1], points[2], c);
	DrawLine(points[2], points[3], c);
	DrawLine(points[3], points[0], c);

	if (rot) ang2 += (1);
	
	// Object 3_triangle
	// Init T,R,S
	pScale.x = 10, pScale.y = 100;
	pTranslate.x = -100 + xPos.x, pTranslate.y = 100 + xPos.y;
	mScale = Scale(pScale);
	mRotate = Rotate(ang3 * DEG_TO_RAD);
	mTranslate = Translate(pTranslate);

	// Multipe T,R,S
	result = matmatMul(mTranslate, mRotate);
	result = matmatMul(result, mScale);

	points[0] = matpoiMul(result, pTriangle[0]);
	points[1] = matpoiMul(result, pTriangle[1]);
	points[2] = matpoiMul(result, pTriangle[2]);

	// Convert Model to View
	points[0] = ModelToViewport(points[0]);
	points[1] = ModelToViewport(points[1]);
	points[2] = ModelToViewport(points[2]);

	// Set RGB
	c.r = 0, c.g = 0, c.b = 0;

	// Draw
	DrawLine(points[0], points[1], c);
	DrawLine(points[1], points[2], c);
	DrawLine(points[2], points[0], c);
	
	if (rot) ang3 -= (1);
	
	// Object4_triangle2
	// Init T,R,S
	pScale.x = 110, pScale.y = 50;
	pTranslate.x = 100 + xPos.x, pTranslate.y = -100 + xPos.y;

	mScale = Scale(pScale);
	mRotate = Rotate(ang2 * DEG_TO_RAD);
	mTranslate = Translate(pTranslate);

	// Multipe T,R,S
	result = matmatMul(mTranslate, mRotate);
	result = matmatMul(result, mScale);

	points[0] = matpoiMul(result, pTriangle[0]);
	points[1] = matpoiMul(result, pTriangle[1]);
	points[2] = matpoiMul(result, pTriangle[2]);

	// Convert Model to View
	points[0] = ModelToViewport(points[0]);
	points[1] = ModelToViewport(points[1]);
	points[2] = ModelToViewport(points[2]);

	// Set RGB
	c.r = 0, c.g = 0, c.b = 255;

	// Draw
	DrawLine(points[0], points[1], c);
	DrawLine(points[1], points[2], c);
	DrawLine(points[2], points[0], c);

	if (rot) ang2 += (1);
	
	// Object5_square
	// Init T,R,S

	pScale.x = 100, pScale.y = 25;
	pTranslate.x = -100 + xPos.x, pTranslate.y = -100 + xPos.y;

	mScale = Scale(pScale);
	mRotate = Rotate(ang5 * DEG_TO_RAD);
	mTranslate = Translate(pTranslate);

	// Multipe T,R,S
	result = matmatMul(mTranslate, mRotate);
	result = matmatMul(result, mScale);

	points[0] = matpoiMul(result, pSquare[0]);
	points[1] = matpoiMul(result, pSquare[1]);
	points[2] = matpoiMul(result, pSquare[2]);
	points[3] = matpoiMul(result, pSquare[3]);

	// Convert Model to View
	points[0] = ModelToViewport(points[0]);
	points[1] = ModelToViewport(points[1]);
	points[2] = ModelToViewport(points[2]);
	points[3] = ModelToViewport(points[3]);

	// Set RGB
	c.r = 128, c.g = 128, c.b = 128;

	// Draw
	DrawLine(points[0], points[1], c);
	DrawLine(points[1], points[2], c);
	DrawLine(points[2], points[3], c);
	DrawLine(points[3], points[0], c);

	if (rot) ang5 -= (1);



	glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, FrameBuffer::buffer);
	glutSwapBuffers();
}

void init(void)
{
	FrameBuffer::Init(WIDTH, HEIGHT);

	//Initialize everything here
	rot = 1;

	xPos.x = xPos.y = 0.0f;
	ang2 = 0.0f, ang3 = 45.0f, ang4 = 0.0f, ang5 = 60.0f;
	
	int i = 0;
	printf("Goal: Model(%d X %d) -> View (%d X %d)\n\n\n", (int)CWIDTH, (int)CHEIGHT, (int)WIDTH, (int)HEIGHT);

		
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