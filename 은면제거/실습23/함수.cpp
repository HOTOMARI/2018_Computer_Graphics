#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

GLvoid CRun_time_Framework::ground()
{
	glColor3f(1, 1, 0);
	glTranslatef(0, -50, 0);
	glRotatef(-90, 1, 0, 0);
	glRectf(-400, -300, 400, 300);

}


GLvoid CRun_time_Framework::QBEY()
{
	// 앞
	glBegin(GL_QUADS);
	glColor3f(0, 1, 1);
	glVertex3f(100, 100 - front_rotate, 100 + front_rotate);
	glColor3f(1, 1, 1);
	glVertex3f(-100, 100 - front_rotate, 100 + front_rotate);
	glColor3f(1, 0, 1);
	glVertex3f(-100, -100, 100);
	glColor3f(0, 0, 1);
	glVertex3f(100, -100, 100);
	glEnd();

	// 왼쪽
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(-100, 100, 100);
	glColor3f(1, 1, 0);
	glVertex3f(-100, 100, -100);
	glColor3f(1, 0, 0);
	glVertex3f(-100, -100, -100);
	glColor3f(1, 0, 1);
	glVertex3f(-100, -100, 100);
	glEnd();

	// 뒤
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex3f(100, 100, -100);
	glColor3f(0, 0, 0);
	glVertex3f(100, -100, -100);
	glColor3f(1, 0, 0);
	glVertex3f(-100, -100, -100);
	glColor3f(1, 1, 0);
	glVertex3f(-100, 100, -100);
	glEnd();

	// 오른
	glBegin(GL_QUADS);
	glColor3f(0, 1, 1);
	glVertex3f(100, 100, 100);
	glColor3f(0, 0, 1);
	glVertex3f(100, -100, 100);
	glColor3f(0, 0, 0);
	glVertex3f(100, -100, -100);
	glColor3f(0, 1, 0);
	glVertex3f(100, 100, -100);
	glEnd();

	// 위
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex3f(100, 100, -100);
	glColor3f(1, 1, 0);
	glVertex3f(-100, 100, -100);
	glColor3f(1, 1, 1);
	glVertex3f(-100, 100 + top_rotate, 100 - top_rotate);
	glColor3f(0, 1, 1);
	glVertex3f(100, 100+top_rotate, 100-top_rotate);
	glEnd();

	// 아래
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(100, -100, -100);
	glColor3f(0, 0, 1);
	glVertex3f(100, -100, 100);
	glColor3f(1, 0, 1);
	glVertex3f(-100, -100, 100);
	glColor3f(1, 0, 0);
	glVertex3f(-100, -100, -100);
	glEnd();
}

GLvoid CRun_time_Framework::spring()
{
	glColor3f(1, 1, 1);
	for (float i = 0; i < 1800; ++i) {
		glBegin(GL_LINES);
		glVertex3f(50 * sin(i / 180 * PI), i*spring_stretch, 50 * cos(i / 180 * PI));
		glVertex3f(50 * sin((i+1) / 180 * PI), (i+1)*spring_stretch, 50 * cos((i + 1) / 180 * PI));
		glEnd();
	}
}

GLvoid CRun_time_Framework::ball()
{
	glTranslatef(0, -50, ball_move);
	glRotatef(ball_move, 1, 0, 0);
	glColor3f(1, 1, 1);
	glutWireSphere(50, 10, 10);
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


