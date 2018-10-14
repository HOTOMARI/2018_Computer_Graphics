#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

GLvoid CRun_time_Framework::draw_planet(int n)
{
	glPushMatrix();
	switch (n)
	{
	case 0:
		break;
	case 1:
		glRotatef(45, 0, 1, 0);
		break;
	case 2:
		glRotatef(-45, 0, 1, 0);
		break;
	}
	glColor3f(1, 1, 1);
	for (int i = 0; i < 360; ++i) {
		glBegin(GL_LINES);
		glVertex3f(100 * cos(i / 180.0 * PI), 100 * sin(i / 180.0 * PI), 0);
		glVertex3f(100 * cos((i + 1) / 180.0 * PI), 100 * sin((i + 1) / 180.0 * PI), 0);
		glEnd();
	}
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(cos(shapes[n].degree / 180 * PI) * 100, sin(shapes[n].degree / 180 * PI) * 100, 0);
	glRotatef(zazeon, 0, 0, 1);
	if (wire_frame)
		glutWireSphere(10, 10, 10);
	else
		glutSolidSphere(10, 10, 10);
	glPopMatrix();

	glColor3f(1, 1, 1);
	glTranslatef(cos(shapes[n].degree / 180 * PI) * 100, sin(shapes[n].degree / 180 * PI) * 100, 0);
	for (int i = 0; i < 360; ++i) {
		glBegin(GL_LINES);
		glVertex3f(50 * cos(i / 180.0 * PI), 50 * sin(i / 180.0 * PI), 0);
		glVertex3f(50 * cos((i + 1) / 180.0 * PI), 50 * sin((i + 1) / 180.0 * PI), 0);
		glEnd();
	}

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(cos((shapes[n].satellite_degree + 50) / 180 * PI) * 50, sin((shapes[n].satellite_degree + 50) / 180 * PI) * 50, 0);
	glRotatef(zazeon, 0, 0, 1);
	if (wire_frame)
		glutWireSphere(5, 10, 10);
	else
		glutSolidSphere(5, 10, 10);
	glPopMatrix();

	glPopMatrix();
}
