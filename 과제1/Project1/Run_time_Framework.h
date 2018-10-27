#pragma once
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define PI 3.141592
#define FPS_TIME 60

// 비트연산 동시키 입력
#define DIR_X_CCW 0x01	// 반시계	
#define DIR_Y_CCW 0x02	
#define DIR_Z_CCW 0x04	
#define DIR_X_CW 0x08	// 시계
#define DIR_Y_CW 0x10	
#define DIR_Z_CW 0x20	

struct MYPOINT {
	float x, y;
};

struct Tri {
	float size;
	float center_x, center_y;
	float rotate;
	MYPOINT p[3];
	Tri* next = NULL;
};

struct Rect {
	float size;
	int type;
	MYPOINT p[4];
	Rect* next = NULL;
};

struct Line {
	float x1, y1;
	float x2, y2;
	bool see = false;
};


class CRun_time_Framework {
private:
	static CRun_time_Framework* myself;
	int m_nWidth;
	int m_nHeight;
	int make_stack[2];

	GLfloat Prevtime = 0;
	GLfloat current_time;
	GLint current_frame = 0;

	Tri* triangle;
	Tri* star;

	Rect* rectangle;

	Line line;

	unsigned char dir = 0;	// 비트연산 동시키 입력
	bool line_finished;

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
	void Make_Tri();
	void Draw_Tri();
	void Delete_ScreenOut_Tri();
	void Update_Tri();

	void Make_Rect();
	void Draw_Rect();
	void Delete_ScreenOut_Rect();
	void Saparate_Rect(Rect*);
	void Update_Rect();

	void Draw_Line();

	bool collide(RECT, RECT);
	bool collide_Line_and_Line(float x1, float x2, float x3, float x4, float y1, float y2, float y3, float y4);

	// 콜백 함수
	static GLvoid Resize(int w, int h);
	static GLvoid drawscene();
	static GLvoid KeyDowninput(unsigned char key, int x, int y);
	static GLvoid KeyUpinput(unsigned char key, int x, int y);
	static GLvoid Mouseaction(int button, int state, int x, int y);
	static GLvoid Mousemotion(int x, int y);
	static GLvoid Updatecallback();
};