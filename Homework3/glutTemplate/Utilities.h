#pragma once

#include "windows.h"
#include "GL/glut.h"
#include "math.h"
#include "stdio.h"

#define WIDTH 640.f
#define HEIGHT 480.f

#define PI 3.14159265358979323846
#define DEG_TO_RAD (PI / 180.0)

class FrameBuffer
{
	public:
		FrameBuffer();
		~FrameBuffer();

		static void Clear(const unsigned char &r, const unsigned char &g, const unsigned char &b);

		static void Init(const unsigned int &w, const unsigned int &h);
		static void SetPixel(const int &x, const int &y, const unsigned char &r, const unsigned char &g, const unsigned char &b);
		static void GetPixel(const int &x, const int &y, unsigned char &r, unsigned char &g, unsigned char &b);
		//static void DrawLine(const int &x1, const int &y1, const int &)

	public:
		static unsigned char *buffer;
		static int width;
		static int height;
};