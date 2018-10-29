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
	box[0].size = 10;
	box[0].position[2] = 40;
	box[0].position[1] = -100 + (box[0].size / 2);

	box[1].size = 20;
	box[1].position[2] = 25;
	box[1].position[1] = -100 + (box[1].size / 2);

	box[2].size = 30;
	box[2].position[1] = -100 + (box[2].size / 2);

	vector_x = 0;
	vector_y = -1;
}

GLvoid CRun_time_Framework::Box()
{
	for (int i = 0; i < 3; ++i) {
		glPushMatrix();
		glTranslatef(box[i].position[0], box[i].position[1], box[i].position[2]);
		glColor3f(1, 0, 0);
		glutSolidCube(box[i].size);
		glColor3f(0, 0, 0);
		glutWireCube(box[i].size);
		glPopMatrix();
	}
}

GLvoid CRun_time_Framework::Update_Box()
{
	vector_x = sin(degree / 180.0*PI);
	vector_y = cos(degree / 180.0*PI);
	for (int i = 0; i < 3; ++i) {
		box[i].position[0] += (vector_x / 5.0) * (current_time - Prevtime);
		box[i].position[1] += (vector_y / 5.0) * (current_time - Prevtime);
		if (box[i].position[0] < -100 + (box[i].size / 2)) {
			box[i].position[0] = -100 + (box[i].size / 2);
		}
		else if (box[i].position[0] > 100 - (box[i].size / 2)) {
			box[i].position[0] = 100 - (box[i].size / 2);
		}

		if (box[i].position[1] < -100 + (box[i].size / 2)) {
			box[i].position[1] = -100 + (box[i].size / 2);
		}
		else if (box[i].position[1] > 100 - (box[i].size / 2)) {
			box[i].position[1] = 100 - (box[i].size / 2);
		}
	}
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


