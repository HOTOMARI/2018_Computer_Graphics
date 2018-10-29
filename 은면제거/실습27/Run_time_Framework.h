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

struct Robot {
	float position[3] = { 0,0,0 };
	float animation = -70;
	bool animation_state = false;
	int dir = 0;
	bool state_walk;
	bool state_jump;
	RECT bb;
};

class CRun_time_Framework {
private:
	static CRun_time_Framework* myself;
	int m_nWidth;
	int m_nHeight;
	int crane_dir;
	int ball_dir;

	float tree_size;
	float metal_pole_rotate;
	float treadmill_rotate;
	float leg_rotate;
	float propeller_rotate;
	float airplane_rotate = 0;
	float airplane_spin = 0;
	float bench;
	float front_ani;
	RECT object[4];

	bool camera_is_front;
	bool crane_right;
	bool tree_bigger;
	bool bench_up;
	bool leg_up;
	bool see_collide;
	bool airplane_dir;
	bool front_up;

	bool depth;
	bool culling;

	GLUquadricObj *qobj = gluNewQuadric();

	GLfloat identity[16];

	Robot Gridman;
	Shape Smoke[3];
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
	GLvoid wall();
	GLvoid tree();
	GLvoid metal_pole();
	GLvoid bench_press();
	GLvoid treadmill();
	GLvoid airplane();
	GLvoid robot();
	GLvoid update_bb();
	bool collide(RECT, RECT);

	// 콜백 함수
	static GLvoid Resize(int w, int h);
	static GLvoid drawscene();
	static GLvoid KeyDowninput(unsigned char key, int x, int y);
	static GLvoid KeyUpinput(unsigned char key, int x, int y);
	static GLvoid Mouseaction(int button, int state, int x, int y);
	static GLvoid Updatecallback();
};