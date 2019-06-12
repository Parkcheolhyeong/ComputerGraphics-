// OpenGL.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "Loader.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

GLuint vaoHandle;  //id

ShaderProgram *shaderProgram;

int winID;



unsigned char *gTex;
GLuint g_texName;
unsigned char *CreateChessBoardImage()
{
	unsigned char * chessBoard = (unsigned char *)::operator new(128 * 128 * 4);
	bool black = false;

	for (int j = 0; j < 128; j++)
	{
		if (j % 32 == 0)
			black = !black;

		for (int i = 0; i < 128; i++)
		{
			if (i % 32 == 0) black = !black;
			*(chessBoard + (j * 128 * 4) + (i * 4) + 0) = black ? 0 : 255;
			*(chessBoard + (j * 128 * 4) + (i * 4) + 1) = black ? 0 : 255;
			*(chessBoard + (j * 128 * 4) + (i * 4) + 2) = black ? 0 : 255;
			*(chessBoard + (j * 128 * 4) + (i * 4) + 3) = 128;
		}
	}

	return chessBoard;
}



void init(void)
{
	shaderProgram = new ShaderProgram();

	//load shaders
	shaderProgram->initFromFiles("simple.vert", "simple.frag");
	gTex = CreateChessBoardImage();

	glGenTextures(1, &g_texName);
	glBindTexture(GL_TEXTURE_2D, g_texName);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 128, 128, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)gTex);
	glBindTexture(GL_TEXTURE_2D, 0);


	shaderProgram->addAttribute("coord3d");
	shaderProgram->addAttribute("v_color");

	//create vao
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);


	shaderProgram->addAttribute("aTexCoord");  //vertex texture

	GLuint vbo_cube_texture;
	const float vertexTexture[] = {
	0.4, 0.2,
	0.2, 0.8,
	0.8, 0.4,
	};

	//create vbo for texture
	glGenBuffers(1, &vbo_cube_texture);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_texture);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 3, &vertexTexture, GL_STATIC_DRAW);


	glVertexAttribPointer(
		shaderProgram->attribute("aTexCoord"),
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		0);

	glEnableVertexAttribArray(shaderProgram->attribute("aTexCoord"));



	GLuint vbo_cube_vertices;
	const float vertexPositions[] = {
		-0.2f, -0.2f, 0.0f, 1.0f,
		0, 0.2f, 0.0f, 1.0f,
		0.2f, -0.2f, 0.0f, 1.0f,
	};

	glGenBuffers(1, &vbo_cube_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 3, &vertexPositions, GL_STATIC_DRAW);
	glVertexAttribPointer(
		shaderProgram->attribute("coord3d"),
		4,
		GL_FLOAT,
		GL_FALSE,
		0,
		0);

	glEnableVertexAttribArray(shaderProgram->attribute("coord3d"));

	//create vbo for colors
	GLuint vbo_cube_colors;


	const float vertexColors[] = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1,
	};
	glGenBuffers(1, &vbo_cube_colors);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * 3, &vertexColors,
		GL_STATIC_DRAW);
	glVertexAttribPointer(
		shaderProgram->attribute("v_color"),
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		0);
	glEnableVertexAttribArray(shaderProgram->attribute("v_color"));




	glBindVertexArray(0);  //unbounding the VAO


}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, (float)w / h, 0.1f, 100.0f);

	glutPostRedisplay();
}

void render(void)
{

	glClearColor(1.0, 1.0, 1.0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, g_texName);
	shaderProgram->use();

	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	shaderProgram->disable();
	glBindTexture(GL_TEXTURE_2D, 0);

	glutSwapBuffers();

}

void idle()
{
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{

}

void motion(int x, int y)
{

}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);

	winID = glutCreateWindow("26861-01");

	glewInit();
	init();

	glutReshapeFunc(resize);
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutMotionFunc(motion);

	glutMainLoop();
}


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
