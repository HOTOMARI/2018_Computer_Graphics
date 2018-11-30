#pragma once
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include<stdio.h>
#include<Windows.h>

#define PI 3.141592
#define FPS_TIME 60

// ��Ʈ���� ����Ű �Է�
#define DIR_X_CCW 0x01	// �ݽð�	
#define DIR_Y_CCW 0x02	
#define DIR_Z_CCW 0x04	
#define DIR_X_CW 0x08	// �ð�
#define DIR_Y_CW 0x10	
#define DIR_Z_CW 0x20	


struct Camera {
	float degree[3] = { -180,-90,90 };
	float x = 0;
	float y = 0;
	float zoom = 0;
};

struct Tile {
	int type = 0;	// 0:�Ϲ� 1:��ֹ� 2:���
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

struct Cart {
	float t = 0.0;
	float pos[3] = { 0,0,0 };
	int nowline = 0;
	GLfloat identity[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
};

struct Snow {
	GLint x = 0;
	GLint y = 0;
	GLfloat height = 0.0;
	GLfloat speed = 0.0;
	Snow* next;
};

class CRun_time_Framework {
private:
	static CRun_time_Framework* myself;
	int m_nWidth;
	int m_nHeight;

	int play_mode;		// 0:ž��	1:���̵��	2:play

	GLfloat point[10][3];
	int set_pointsnum;
	bool picked[10];
	GLfloat pick_tmp[3];

	GLfloat Scroll[5];
	GLuint texture[6];		//�ؽ�ó �̸�
	GLubyte *pBytes;				// �����͸� ����ų ������
	BITMAPINFO *info;				// ��Ʈ�� ��� ������ ����

	bool camera_is_front;
	int nowCamera;
	
	int weather;
	Snow* snow;
	float snowstack;

	bool combined;
	float comb_t;

	int tunnel;

	GLUquadricObj *qobj = gluNewQuadric();

	GLfloat identity[16];

	Tile grounds[10][10];
	Camera camera;

	Robot Gridman[2];
	Bullet* bullets;
	RECT object[10];
	RECT pillar[10];
	Cart cart[3];
	GLfloat cart_nextP[3];

	GLfloat Prevtime = 0;
	GLfloat current_time;
	GLint current_frame = 0;

	unsigned char dir = 0;	// ��Ʈ���� ����Ű �Է�

public:
	CRun_time_Framework();
	~CRun_time_Framework();

	// �ʼ� �Լ�
	GLvoid Init();
	GLvoid Reshape(int w, int h);
	GLvoid draw();
	GLvoid KeyboardDown(unsigned char key, int x, int y);
	GLvoid KeyboardUp(unsigned char key, int x, int y);
	GLvoid Mouse(int button, int state, int x, int y);
	GLvoid Motion(int x, int y);
	GLvoid Update();

	// ���� �Լ�
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
	GLvoid draw_pillars();
	GLvoid draw_rails();
	GLvoid draw_carts();
	GLvoid update_carts();
	GLvoid Make_Snow();
	GLvoid UpdateSnow();
	GLvoid Draw_Snow();
	GLvoid Delete_Snow();
	float calc_Bezier(float, float, float, float);
	bool collide(RECT, RECT);
	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
	GLvoid set_texture();
	GLvoid Skybox();
	GLvoid Pilar();

	// �ݹ� �Լ�
	static GLvoid Resize(int w, int h);
	static GLvoid drawscene();
	static GLvoid KeyDowninput(unsigned char key, int x, int y);
	static GLvoid KeyUpinput(unsigned char key, int x, int y);
	static GLvoid Mouseaction(int button, int state, int x, int y);
	static GLvoid Mousemotion(int x, int y);
	static GLvoid Updatecallback();
};