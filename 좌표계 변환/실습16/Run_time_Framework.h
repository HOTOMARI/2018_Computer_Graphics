#pragma once
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>

#define pi 3.141592
#define FPS_TIME 60


class CRun_time_Framework {
private:
	static CRun_time_Framework* myself;
	int m_nWidth;
	int m_nHeight;
	float rotatey = 0;
	GLfloat Prevtime = 0;
	GLfloat current_time;
	GLint current_frame = 0;

public:
	CRun_time_Framework();
	~CRun_time_Framework();

	// 필수 함수
	GLvoid Reshape(int w, int h);
	GLvoid draw();
	GLvoid Keyboard(unsigned char key, int x, int y);
	GLvoid Mouse(int button, int state, int x, int y);
	GLvoid Update();

	// 만든 함수
	GLvoid background(float r, float g, float b);
	GLvoid initialization();
	GLvoid Timerfunction(int value);
	GLvoid shape_draw();
	GLvoid draw_digital(int clock, int sequence);
	GLvoid draw_clock(int clock, int sequence);
	GLvoid shape_init();
	GLvoid Init();

	// 콜백 함수
	static GLvoid Resize(int w, int h);
	static GLvoid drawscene();
	static GLvoid Keyinput(unsigned char key, int x, int y);
	static GLvoid Mouseaction(int button, int state, int x, int y);
	static GLvoid Updatecallback();
};