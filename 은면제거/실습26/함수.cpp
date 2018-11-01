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

GLvoid CRun_time_Framework::Initial_Ball()
{
	for (int i = 0; i < 5; ++i) {
		ball[i].size = 10;
		for (int j = 0; j < 3; ++j) {
			ball[i].position[j] = 0;
		}
		Set_Ball_vector(i);
	}
}

GLvoid CRun_time_Framework::Ball()
{
	for (int i = 0; i < ball_count; ++i) {
		glPushMatrix();
		glTranslatef(ball[i].position[0], ball[i].position[1], ball[i].position[2]);
		glColor3f(0, 0, 1);
		glutSolidSphere(ball[i].size, 10, 10);
		glColor3f(0, 0, 0);
		glutWireSphere(ball[i].size, 10, 10);
		glPopMatrix();
	}
}

GLvoid CRun_time_Framework::Update_Ball()
{
	for (int i = 0; i < 5; ++i) {
		ball[i].position[0] += (ball[i].vector[0] / 5.0) * (current_time - Prevtime);
		ball[i].position[1] += (ball[i].vector[1] / 5.0) * (current_time - Prevtime);
		ball[i].position[2] += (ball[i].vector[2] / 5.0) * (current_time - Prevtime);

		if (ball[i].position[0] < -100 + (ball[i].size)) {
			ball[i].position[0] = -100 + (ball[i].size);
			Set_Ball_vector(i);
		}
		else if (ball[i].position[0] > 100 - (ball[i].size)) {
			ball[i].position[0] = 100 - (ball[i].size);
			Set_Ball_vector(i);
		}

		if (ball[i].position[1] < -100 + (ball[i].size)) {
			ball[i].position[1] = -100 + (ball[i].size);
			Set_Ball_vector(i);
		}
		else if (ball[i].position[1] > 100 - (ball[i].size)) {
			ball[i].position[1] = 100 - (ball[i].size);
			Set_Ball_vector(i);
		}

		if (ball[i].position[2] < -100 + (ball[i].size)) {
			ball[i].position[2] = -100 + (ball[i].size);
			Set_Ball_vector(i);
		}
		else if (ball[i].position[2] > 100 - (ball[i].size)) {
			ball[i].position[2] = 100 - (ball[i].size);
			Set_Ball_vector(i);
		}
	}
}


GLvoid CRun_time_Framework::Set_Ball_vector(int shape_index)
{
	switch (rand() % 8) {
	case 0:
		ball[shape_index].vector[0] = 1;
		ball[shape_index].vector[1] = 1;
		ball[shape_index].vector[2] = 0;
		break;
	case 1:
		ball[shape_index].vector[0] = 1;
		ball[shape_index].vector[1] = -1;
		ball[shape_index].vector[2] = 0;
		break;
	case 2:
		ball[shape_index].vector[0] = 1;
		ball[shape_index].vector[1] = 0;
		ball[shape_index].vector[2] = 1;
		break;
	case 3:
		ball[shape_index].vector[0] = 1;
		ball[shape_index].vector[1] = 0;
		ball[shape_index].vector[2] = -1;
		break;
	case 4:
		ball[shape_index].vector[0] = -1;
		ball[shape_index].vector[1] = 1;
		ball[shape_index].vector[2] = 0;
		break;
	case 5:
		ball[shape_index].vector[0] = -1;
		ball[shape_index].vector[1] = -1;
		ball[shape_index].vector[2] = 0;
		break;
	case 6:
		ball[shape_index].vector[0] = -1;
		ball[shape_index].vector[1] = 0;
		ball[shape_index].vector[2] = 1;
		break;
	case 7:
		ball[shape_index].vector[0] = -1;
		ball[shape_index].vector[1] = 0;
		ball[shape_index].vector[2] = -1;
		break;
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


