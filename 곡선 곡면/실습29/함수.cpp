#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

GLvoid CRun_time_Framework::Axis()
{
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(-400, 0, 0);
	glVertex3f(400, 0, 0);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 300, 0);
	glVertex3f(0, -300, 0);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, -400);
	glVertex3f(0, 0, 400);
	glEnd();

	return GLvoid();
}

GLvoid CRun_time_Framework::Draw_Points()
{
	glPushMatrix();
	//glRotatef(90, 1, 0, 0);
	glPointSize(4.0);
	for (int i = 0; i < point_num; ++i) {
		glBegin(GL_POINTS);
		glVertex3f(point[i][0], point[i][1], point[i][2]);
		glEnd();
	}
	glPopMatrix();
	return GLvoid();
}