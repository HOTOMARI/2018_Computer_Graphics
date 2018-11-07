#pragma once
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>

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
	float rotate = 0;
	float position[3] = { 0,350,0 };
	float size = 70;
	float line = 4;
	float t = 0;
	GLfloat identity[16];
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

	GLfloat point[10][10][3];

	bool camera_is_front;

	bool depth;
	bool culling;
	bool ground_line;

	int ani_step;
	float ball_rotate;
	float ball_radius;

	GLUquadricObj *qobj = gluNewQuadric();

	GLfloat identity[16];

	Shape ball;
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
	GLvoid Piramid();
	GLvoid Ball();
	bool collide(RECT, RECT);

	// 콜백 함수
	static GLvoid Resize(int w, int h);
	static GLvoid drawscene();
	static GLvoid KeyDowninput(unsigned char key, int x, int y);
	static GLvoid KeyUpinput(unsigned char key, int x, int y);
	static GLvoid Mouseaction(int button, int state, int x, int y);
	static GLvoid Updatecallback();
};