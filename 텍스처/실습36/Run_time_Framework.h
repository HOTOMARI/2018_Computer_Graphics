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

struct Ground {
	GLfloat left;
	GLfloat right;
	GLfloat top;
	GLfloat bottom;
};
struct Light {
	GLfloat position[4] = { 0.0,0.0,0.0,1.0 };
	GLfloat AmbientColor[4] = { 0.0,0.0,0.0,1.0 };
	GLfloat DiffuseColor[4] = { 0.0,0.0,0.0,1.0 };
	GLfloat SpecularColor[4] = { 1.0,1.0,1.0,1.0 };
	GLfloat degree = 0.0;
	bool on = true;
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
	bool move_light;
	bool normal;

	GLUquadricObj *qobj = gluNewQuadric();

	GLfloat identity[16];
	GLfloat WhiteLight[4] = { 1.0, 1.0, 1.0, 1.0 };

	Camera camera;

	Ground ground[50][50];

	Light light[2];

	GLfloat Prevtime = 0;
	GLfloat current_time;
	GLint current_frame = 0;

	GLuint texture[2];		//�ؽ�ó �̸�
	GLubyte *pBytes;				// �����͸� ����ų ������
	BITMAPINFO *info;				// ��Ʈ�� ��� ������ ����

	unsigned char dir = 0;	// ��Ʈ���� ����Ű �Է�

	float moon_degree;

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
	GLvoid Update();

	// ���� �Լ�
	GLvoid background(float r, float g, float b);
	GLvoid Draw_Ball();
	GLvoid Draw_Cone();
	GLvoid Init_Light();
	GLvoid UpdateLight();
	GLvoid Draw_Ground();
	GLvoid Draw_Piramid();
	GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
	GLvoid set_texture(int n);

	// �ݹ� �Լ�
	static GLvoid Resize(int w, int h);
	static GLvoid drawscene();
	static GLvoid KeyDowninput(unsigned char key, int x, int y);
	static GLvoid KeyUpinput(unsigned char key, int x, int y);
	static GLvoid Mouseaction(int button, int state, int x, int y);
	static GLvoid Updatecallback();
};