#pragma once
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <Windows.h>

#define PI 3.141592
#define FPS_TIME 60

// 비트연산 동시키 입력
#define DIR_X_CCW 0x01	// 반시계	
#define DIR_Y_CCW 0x02	
#define DIR_Z_CCW 0x04	
#define DIR_X_CW 0x08	// 시계
#define DIR_Y_CW 0x10	
#define DIR_Z_CW 0x20	

struct Shape {
	float rotate[3] = { 0,0,0 };
	float position[2] = { 0,0 };
	float size;
	unsigned char dir = 0;
	GLfloat identity[16];
	RECT bb;
};

struct Camera {
	float degree[3] = { -180,-90,90 };
	float x = 0;
	float y = 0;
	float zoom = 0;
};

class CRun_time_Framework {
private:
	static CRun_time_Framework* myself;
	int m_nWidth;
	int m_nHeight;

	bool camera_is_front;
	bool top_open;
	bool front_open;

	bool depth;
	bool culling;
	bool shading;

	float top_rotate;
	float front_rotate;
	float spring_stretch;
	float ball_move;
	float spring_ball;

	GLuint texture_object[2];		//텍스처 이름
	GLubyte *pBytes;				// 데이터를 가리킬 포인터
	BITMAPINFO *info;				// 비트맵 헤더 저장할 변수

	GLUquadricObj *qobj = gluNewQuadric();

	GLfloat identity[16];

	Camera camera;

	GLfloat Prevtime = 0;
	GLfloat current_time;
	GLint current_frame = 0;

	unsigned char dir = 0;	// 비트연산 동시키 입력

public:
	CRun_time_Framework();
	~CRun_time_Framework();

	// 필수 함수
	GLvoid Init();
	GLvoid Reshape(int w, int h);
	GLvoid draw();
	GLvoid KeyboardDown(unsigned char key, int x, int y);
	GLvoid KeyboardUp(unsigned char key, int x, int y);
	GLvoid Mouse(int button, int state, int x, int y);
	GLvoid Update();

	// 만든 함수
	GLvoid background(float r, float g, float b);
	GLvoid ground();
	GLvoid QBEY();		// 큐베
	GLvoid spring();	// 용수철
	GLvoid ball();		// 공
	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
	GLvoid set_texture(int n);
	bool collide(RECT, RECT);

	// 콜백 함수
	static GLvoid Resize(int w, int h);
	static GLvoid drawscene();
	static GLvoid KeyDowninput(unsigned char key, int x, int y);
	static GLvoid KeyUpinput(unsigned char key, int x, int y);
	static GLvoid Mouseaction(int button, int state, int x, int y);
	static GLvoid Updatecallback();
};