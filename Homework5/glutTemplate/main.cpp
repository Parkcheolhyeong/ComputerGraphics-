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

/* DDA Draw Algorithm */
void DrawLine(Point p1, Point p2, Color c) {


	int x0 = p1.x, x1 = p2.x;  
	int y0 = p1.y, y1 = p2.y;
	int x, y;
	float _x, _y;

	float dx = x1 - x0; // distance x
	float dy = y1 - y0; // distance y
	float m = (float)dy / (float)dx; // gradient


	if (dy == 0) { // Vertical
		DrawVLine(p1, p2, c);
		return;
	}

	if (dx == 0) { // Horizon
		DrawHLine(p1, p2, c);
		return;
	}

	if (m >= -1 && m <= 1) { // Gradient
		if (dx < 0) { // Up & Swap
			int temp = x0;
			x0 = x1; x1 = temp;
			temp = y0;
			y0 = y1; y1 = temp;
			dx = -1;
			dy = -1;
		}
		/*swap*/
		x = x0;
		y = y0;

		/* Init round(_x, _y)*/
		_x = x0;
		_y = y0;	

		while (x < x1) {
			x++; // Calc y
			_y = (_y + (float)m);
			y = (int)(_y + 0.5); // round Calc
			
			FrameBuffer::SetPixel(x, y, c.r, c.g, c.b);
		}
	}
	else {
		if (dy < 0) {
			int temp = x0;
			x0 = x1;
			x1 = temp;
			temp = y0;
			y0 = y1;
			y1 = temp;
			dx = -1;
			dy = -1;
		}
		x = x0;
		y = y0;
		_x = x0;
		_y = y0;
		while (y < y1) {
			y++; //Calc x
			_x = (float)(_x + 1 / m);
			x = (int)(_x + 0.5); // round Calc
			FrameBuffer::SetPixel(x, y, c.r, c.g, c.b);
		}
	}


}
void midPoint(float X1, float Y1, float X2, float Y2)		//Midpoint Line Algorithm
{
	if (X1 > X2)			//반대방향일 경우 재귀호출
	{
		midPoint(X2, Y2, X1, Y1);
		return;
	}

	float dx = X2 - X1;			//x증가량
	float dy = Y2 - Y1;			//y증가량

	float x = X1, y = Y1;		//x1,y1 좌표
	float m = sqrt(pow(dy / dx, 2));		//기울기의 절대값

	printf("%lf, %lf\n", x, y);		//x,y 좌표를 확인하기 위한 Debug log


	if (dx > 0 && dy > 0)
	{
		if (m <= 1)
		{
			float d = dy - (dx / 2);

			while (x < X2)
			{
				x++;

				if (d < 0)							// E or East is chosen
					d = d + dy;

				else								// NE or North East is chosen
				{
					d += (dy - dx);
					y++;
				}

				printf("%lf, %lf\n", x, y);		//x,y 좌표를 확인하기 위한 Debug log
				FrameBuffer::SetPixel(x, y, 0, 0, 0);			//분면 마다 색깔을 다르게 하여 구분
			}
		}
		else if (m > 1)
		{
			float d = dx - (dy / 2);

			while (y < Y2)
			{
				y++;


				if (d < 0)				// E or East is chosen
					d = d + dx;


				else					// NE or North East is chosen
				{
					d += (dx - dy);
					x++;
				}

				printf("%lf, %lf\n", x, y);		//x,y 좌표를 확인하기 위한 Debug log
				FrameBuffer::SetPixel(x, y, 0, 0, 0);			//분면 마다 색깔을 다르게 하여 구분
			}

		}
	}

	if (dy < 0 || dx < 0)
	{
		if (dy < 0)
			dy *= -1;

		if (m <= 1)
		{
			float d = dy - (dx / 2);

			while (x < X2)
			{
				x++;

				if (d > 0)				// E or East is chosen
					d = d - dy;

				else					// NE or North East is chosen
				{
					d -= (dy - dx);
					y--;
				}

				printf("%lf, %lf\n", x, y);		//x,y 좌표를 확인하기 위한 Debug log
				FrameBuffer::SetPixel(x, y, 0, 0, 0);			//분면 마다 색깔을 다르게 하여 구분
			}
		}
		if (m > 1)
		{
			float d = dx - (dy / 2);

			while (y > Y2)
			{
				y--;

				if (d > 0)				// E or East is chosen
					d = d - dx;

				else					// NE or North East is chosen
				{
					d -= (dx - dy);
					x++;
				}

				printf("%lf, %lf\n", x, y);		//x,y 좌표를 확인하기 위한 Debug log
				FrameBuffer::SetPixel(x, y, 0, 0, 0);			//분면 마다 색깔을 다르게 하여 구분
			}

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