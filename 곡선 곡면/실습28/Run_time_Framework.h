#pragma once
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define PI 3.141592
#define FPS_TIME 60

// ��Ʈ���� ����Ű �Է�
#define DIR_X_CCW 0x01	// �ݽð�	
#define DIR_Y_CCW 0x02	
#define DIR_Z_CCW 0x04	
#define DIR_X_CW 0x08	// �ð�
#define DIR_Y_CW 0x10	
#define DIR_Z_CW 0x20	

struct MYPOINT {
	float x, y;
};

class CRun_time_Framework {
private:
	static CRun_time_Framework* myself;
	int m_nWidth;
	int m_nHeight;
	int point_num;

	MYPOINT point[19];

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
	GLvoid Draw_Points();

	// �ݹ� �Լ�
	static GLvoid Resize(int w, int h);
	static GLvoid drawscene();
	static GLvoid KeyDowninput(unsigned char key, int x, int y);
	static GLvoid KeyUpinput(unsigned char key, int x, int y);
	static GLvoid Mouseaction(int button, int state, int x, int y);
	static GLvoid Mousemotion(int x, int y);
	static GLvoid Updatecallback();
};