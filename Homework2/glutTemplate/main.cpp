#include "Utilities.h"

#define CHEIGHT 600.f
#define CWIDTH 800.f

int winID;	// Windows Name
static bool cvt_val = true;	// Once Print Values of Converting

/* Structure Type of Point */
typedef struct Point {
	int x, y;
} Point;

/* Structure Type of Line(Prepare) */
typedef struct Line {
	int p0, p1;
} Line;

/* Structure Type of Color */
typedef struct Color {
	unsigned char r, g, b;
} Color;

/* Convert from Camera To View*/
Point CameraToViewport(const Point &p)
{
	Point vPoint;
	vPoint.x = (int)((WIDTH / CWIDTH) *p.x + (WIDTH / 2.f));
	vPoint.y = (int)((-HEIGHT / CHEIGHT) *p.y + (HEIGHT / 2.f));

	return vPoint;
}

/* Draw to Line (Method of Normalized Vector) */
void DrawLine(Point p1, Point p2, Color c) {

	float vectorSize = sqrt(pow(p1.y - p2.y, 2) + pow(p1.x - p2.x, 2));		// Distance of point to point

	float UVectorx = (p1.x - p2.x) / vectorSize;		// Unit vector x
	float UVectory = (p1.y - p2.y) / vectorSize;		// Unit vector y

	// Draw
	for (int i = 0; i < vectorSize; i++) {
		FrameBuffer::SetPixel(p2.x + (i*UVectorx), p2.y + (i*UVectory), c.r, c.g, c.b);
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
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
	int i;
	FrameBuffer::Clear(255, 255, 255);

	//Put your rendering code here

	// Init Points, Color
	Point points[] = { {0, 0}, {-300, 200},{-300, -200},
						{-100, -150}, {-100, 150},
						{300, 0}, {300, 200},
						{100, 200}, {100, 0}, {100, -200} };
	Color b = { 0, 0, 0 };

	// Convert from Camerat to View
	for (i = 1; i < 10; i++)
	{
		if (cvt_val == true) {
			printf("P_c[%4d](%4d, %4d) -> ", i, points[i].x, points[i].y);
		}
		points[i] = CameraToViewport(points[i]);
		if (cvt_val == true) {
			printf("P_v[%4d](%4d, %4d)\n", i, points[i].x, points[i].y);
		}
	}

	cvt_val = false; // Lock Printf
	// Draw figure
	DrawLine(points[1], points[2], b);
	DrawLine(points[2], points[3], b);
	DrawLine(points[3], points[4], b);
	DrawLine(points[4], points[1], b);
	
	DrawLine(points[5], points[6], b);
	DrawLine(points[6], points[7], b);
	DrawLine(points[7], points[8], b);
	DrawLine(points[8], points[5], b);
	DrawLine(points[8], points[9], b);
	

	glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, FrameBuffer::buffer);
	glutSwapBuffers();
}

void init(void)
{
	FrameBuffer::Init(WIDTH, HEIGHT);
	printf("Goal: Camera(%d X %d) -> View (%d X %d)\n\n\n", (int)CWIDTH, (int)CHEIGHT, (int)WIDTH, (int)HEIGHT);

	//Initialize everything here
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