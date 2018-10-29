#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}


GLvoid CRun_time_Framework::QBEY()
{
	// 앞
	glBegin(GL_QUADS);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(100, 100, 100);
	glVertex3f(-100, 100, 100);
	glVertex3f(-100, -100, 100);
	glVertex3f(100, -100, 100);
	glEnd();

	// 왼쪽
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(-100, 100, 100);
	glVertex3f(-100, 100, -100);
	glVertex3f(-100, -100, -100);
	glVertex3f(-100, -100, 100);
	glEnd();

	// 뒤
	glBegin(GL_QUADS);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(100, 100, -100);
	glVertex3f(100, -100, -100);
	glVertex3f(-100, -100, -100);
	glVertex3f(-100, 100, -100);
	glEnd();

	// 오른
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(100, 100, 100);
	glVertex3f(100, -100, 100);
	glVertex3f(100, -100, -100);
	glVertex3f(100, 100, -100);
	glEnd();

	// 위
	glBegin(GL_QUADS);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(100, 100, -100);
	glVertex3f(-100, 100, -100);
	glVertex3f(-100, 100, 100);
	glVertex3f(100, 100, 100);
	glEnd();

	// 아래
	glBegin(GL_QUADS);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(100, -100, -100);
	glVertex3f(100, -100, 100);
	glVertex3f(-100, -100, 100);
	glVertex3f(-100, -100, -100);
	glEnd();
}

GLvoid CRun_time_Framework::Initial_Box()
{
	
}

GLvoid CRun_time_Framework::Box()
{
	return GLvoid();
}


bool CRun_time_Framework::collide(RECT A, RECT B)
{
	if (A.left > B.right)
		return false;
	if (A.right < B.left)
		return false;
	if (A.top < B.bottom)
		return false;
	if (A.bottom > B.top)
		return false;
	return true;
}


