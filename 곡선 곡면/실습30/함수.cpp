#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

GLvoid CRun_time_Framework::ground()
{
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	// 곡면 제어점 설정 
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 10, 0.0, 1.0, 30, 10, &point[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);

	// 그리드를 이용한 곡면 드로잉 
	glMapGrid2f(30, 0.0, 1.0, 30, 0.0, 1.0);

	// 선을 이용하여 그리드 연결 
	if (ground_line) {
		glEvalMesh2(GL_LINE, 0, 30, 0, 30);
		glPointSize(4.0); glColor3f(0.0, 0.0, 1.0);
	}
	// 면을 이용하여 그리드 연결 
	else {
		glEvalMesh2(GL_FILL, 0, 30, 0, 30);
		glPointSize(4.0); glColor3f(0.0, 0.0, 1.0);
	}

	glBegin(GL_POINTS);
	for (int k = 0; k < 10; k++)
		for (int j = 0; j < 10; j++)
			glVertex3fv(point[k][j]);
	glEnd();
	glPopMatrix();
}

GLvoid CRun_time_Framework::Piramid()
{
	// 왼쪽위
	{
		glColor3f(1, 1, 0);
		glBegin(GL_POLYGON);
		glVertex3f(point[1][0][0], 0, point[1][0][2]);
		glVertex3f(point[1][1][0], 0, point[1][1][2]);
		glVertex3f(point[0][1][0], 0, point[0][1][2]);
		glVertex3f(point[0][0][0], 0, point[0][0][2]);
		glEnd();

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(point[1][0][0], 0, point[1][0][2]);
		glVertex3f(point[1][1][0], 0, point[1][1][2]);
		glVertex3f(-355, 100, -355);
		glEnd();

		glColor3f(1, 0, 1);
		glBegin(GL_POLYGON);
		glVertex3f(point[1][0][0], 0, point[1][0][2]);
		glVertex3f(point[0][0][0], 0, point[0][0][2]);
		glVertex3f(-355, 100, -355);
		glEnd();

		glColor3f(0, 1, 1);
		glBegin(GL_POLYGON);
		glVertex3f(point[0][0][0], 0, point[0][0][2]);
		glVertex3f(point[0][1][0], 0, point[0][1][2]);
		glVertex3f(-355, 100, -355);
		glEnd();

		glColor3f(0, 1, 0);
		glBegin(GL_POLYGON);
		glVertex3f(point[0][1][0], 0, point[0][1][2]);
		glVertex3f(point[1][1][0], 0, point[1][1][2]);
		glVertex3f(-355, 100, -355);
		glEnd();
	}
	// 오른쪽위
	{
		glColor3f(1, 1, 0);
		glBegin(GL_POLYGON);
		glVertex3f(point[1][8][0], 0, point[1][8][2]);
		glVertex3f(point[1][9][0], 0, point[1][9][2]);
		glVertex3f(point[0][9][0], 0, point[0][9][2]);
		glVertex3f(point[0][8][0], 0, point[0][8][2]);
		glEnd();

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(point[1][8][0], 0, point[1][8][2]);
		glVertex3f(point[1][9][0], 0, point[1][9][2]);
		glVertex3f(365, 100, -355);
		glEnd();

		glColor3f(1, 0, 1);
		glBegin(GL_POLYGON);
		glVertex3f(point[1][8][0], 0, point[1][8][2]);
		glVertex3f(point[0][8][0], 0, point[0][8][2]);
		glVertex3f(365, 100, -355);
		glEnd();

		glColor3f(0, 1, 1);
		glBegin(GL_POLYGON);
		glVertex3f(point[0][8][0], 0, point[0][8][2]);
		glVertex3f(point[0][9][0], 0, point[0][9][2]);
		glVertex3f(365, 100, -355);
		glEnd();

		glColor3f(0, 1, 0);
		glBegin(GL_POLYGON);
		glVertex3f(point[0][9][0], 0, point[0][9][2]);
		glVertex3f(point[1][9][0], 0, point[1][9][2]);
		glVertex3f(365, 100, -355);
		glEnd();
	}

	// 왼쪽아래
	{
		glColor3f(1, 1, 0);
		glBegin(GL_POLYGON);
		glVertex3f(point[9][0][0], 0, point[9][0][2]);
		glVertex3f(point[9][1][0], 0, point[9][1][2]);
		glVertex3f(point[8][1][0], 0, point[8][1][2]);
		glVertex3f(point[8][0][0], 0, point[8][0][2]);
		glEnd();

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(point[9][0][0], 0, point[9][0][2]);
		glVertex3f(point[9][1][0], 0, point[9][1][2]);
		glVertex3f(-355, 100, 365);
		glEnd();

		glColor3f(1, 0, 1);
		glBegin(GL_POLYGON);
		glVertex3f(point[9][0][0], 0, point[9][0][2]);
		glVertex3f(point[8][0][0], 0, point[8][0][2]);
		glVertex3f(-355, 100, 365);
		glEnd();

		glColor3f(0, 1, 1);
		glBegin(GL_POLYGON);
		glVertex3f(point[8][0][0], 0, point[8][0][2]);
		glVertex3f(point[8][1][0], 0, point[8][1][2]);
		glVertex3f(-355, 100, 365);
		glEnd();

		glColor3f(0, 1, 0);
		glBegin(GL_POLYGON);
		glVertex3f(point[8][1][0], 0, point[8][1][2]);
		glVertex3f(point[9][1][0], 0, point[9][1][2]);
		glVertex3f(-355, 100, 365);
		glEnd();
	}

	// 오른쪽아래
	{
		glColor3f(1, 1, 0);
		glBegin(GL_POLYGON);
		glVertex3f(point[9][8][0], 0, point[9][9][2]);
		glVertex3f(point[9][9][0], 0, point[9][9][2]);
		glVertex3f(point[8][9][0], 0, point[8][9][2]);
		glVertex3f(point[8][8][0], 0, point[8][8][2]);
		glEnd();

		glColor3f(1, 0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(point[9][8][0], 0, point[9][8][2]);
		glVertex3f(point[9][9][0], 0, point[9][9][2]);
		glVertex3f(365, 100, 365);
		glEnd();

		glColor3f(1, 0, 1);
		glBegin(GL_POLYGON);
		glVertex3f(point[9][8][0], 0, point[9][8][2]);
		glVertex3f(point[8][8][0], 0, point[8][8][2]);
		glVertex3f(365, 100, 365);
		glEnd();

		glColor3f(0, 1, 1);
		glBegin(GL_POLYGON);
		glVertex3f(point[8][8][0], 0, point[8][8][2]);
		glVertex3f(point[8][9][0], 0, point[8][9][2]);
		glVertex3f(365, 100, 365);
		glEnd();

		glColor3f(0, 1, 0);
		glBegin(GL_POLYGON);
		glVertex3f(point[8][9][0], 0, point[8][9][2]);
		glVertex3f(point[9][9][0], 0, point[9][9][2]);
		glVertex3f(365, 100, 365);
		glEnd();
	}
}

GLvoid CRun_time_Framework::Ball()
{
	glTranslatef(ball.position[0], ball.position[1], ball.position[2]);
	glRotatef(ball.rotate, 1, 0, 0);
	glColor3f(1, 0, 0);
	glutWireSphere(ball.size, 10, 10);
}
