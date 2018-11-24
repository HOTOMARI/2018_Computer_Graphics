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


struct Camera {
	float degree[3] = { -180,-90,90 };
	float x = 0;
	float y = 0;
	float zoom = 0;
};

struct Tile {
	int type = 0;	// 0:일반 1:장애물 2:기둥
};

struct Robot {
	float position[3] = { 0,0,0 };
	float animation = -70;
	bool animation_state = false;
	bool state_collide = false;
	int dir = 0;
	GLfloat cloak[3][3][3] = { {{-25.0, 0.0, 45.0},{0.0, 0.0, 45.0},{25.0, 0.0, 45.0}}, 
							{{-25.0, -20.0, 0.0}, {0.0, -20.0, 0.0}, {25.0, -20.0, 0.0}}, 
							{{-25.0, -70.0, -45.0}, {0.0, -40.0, -45.0}, {25.0, -10.0, -45.0}} };
	;
	RECT bb;
};

struct Bullet {
	int dir;
	int owner;
	float position[3] = { 0,0,0 };
	bool hit;
	RECT bb;
	Bullet* next;
};


class CRun_time_Framework {
private:
	static CRun_time_Framework* myself;
	int m_nWidth;
	int m_nHeight;

	int play_mode;		// 0:탑뷰	1:사이드뷰	2:play

	GLfloat point[10][3];
	int set_pointsnum;
	bool picked[10];
	GLfloat pick_tmp[3];

	bool camera_is_front;
	int nowCamera;

	bool combined;
	float comb_t;

	GLUquadricObj *qobj = gluNewQuadric();

	GLfloat identity[16];

	Tile grounds[10][10];
	Camera camera;

	Robot Gridman[2];
	Bullet* bullets;
	RECT object[10];

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
	GLvoid Motion(int x, int y);
	GLvoid Update();

	// 만든 함수
	GLvoid background(float r, float g, float b);
	GLvoid ground();
	GLvoid set_trees();
	GLvoid set_robots();
	GLvoid Tree();
	GLvoid Robot();
	GLvoid update_bb();
	GLvoid update_robots();
	GLvoid go_comb();
	GLvoid make_bullet(int);
	GLvoid update_bullets();
	GLvoid draw_bullets();
	GLvoid delete_bullets();
	GLvoid draw_points();
	GLvoid draw_rails();
	float calc_Bezier(float, float, float, float);
	bool collide(RECT, RECT);

	// 콜백 함수
	static GLvoid Resize(int w, int h);
	static GLvoid drawscene();
	static GLvoid KeyDowninput(unsigned char key, int x, int y);
	static GLvoid KeyUpinput(unsigned char key, int x, int y);
	static GLvoid Mouseaction(int button, int state, int x, int y);
	static GLvoid Mousemotion(int x, int y);
	static GLvoid Updatecallback();
};