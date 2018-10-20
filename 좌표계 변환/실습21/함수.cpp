#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

GLvoid CRun_time_Framework::crane()
{
	// 맨 아래 몸체
	glPushMatrix();
	glTranslatef(shapes[0].position[0], -(100 * 0.3), 0);
	glMultMatrixf(shapes[0].identity);

	glPushMatrix();
	glScalef(1.5, 1.0, 0.7);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glColor3f(1, 0, 0);
	glutSolidCube(100);
	glPopMatrix();

	// 1차팔
	glRotatef(shapes[1].rotate[1], 0.f, 1.f, 0.f);
	glMultMatrixf(shapes[1].identity);
	glTranslatef(0, 70, 0);

	glPushMatrix();
	glScalef(0.4, 1.0, 0.4);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glColor3f(0, 1, 0);
	glutSolidCube(100);
	glPopMatrix();

	// 2차팔
	glTranslatef(0, 30, 0);
	glMultMatrixf(shapes[2].identity);
	glTranslatef(0, 70, 0);

	glPushMatrix();
	glScalef(0.2, 1.0, 0.2);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glColor3f(0, 0, 1);
	glutSolidCube(100);
	glPopMatrix();

	glPopMatrix();
}

GLvoid CRun_time_Framework::ground()
{
	glColor3f(1, 1, 0);
	glTranslatef(0, -50, 0);
	glRotatef(-90, 1, 0, 0);
	glRectf(-400, -300, 400, 300);

	glColor3f(0, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex3f(-400, -300, 1);
	glVertex3f(-400, -100, 1);
	glVertex3f(-200, -300, 1);
	glEnd();
	glColor3f(1, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex3f(400, 300, 1);
	glVertex3f(400, 100, 1);
	glVertex3f(200, 300, 1);
	glEnd();
	glColor3f(1, 0.5, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(-400, 300, 1);
	glVertex3f(-400, 100, 1);
	glVertex3f(-200, 300, 1);
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex3f(400, -300, 1);
	glVertex3f(400, -100, 1);
	glVertex3f(200, -300, 1);
	glEnd();
}


