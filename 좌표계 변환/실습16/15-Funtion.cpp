#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

GLvoid CRun_time_Framework::shape_draw() {
	int i;

	time_t now = time(0);
	struct tm curr_time;
	localtime_s(&curr_time, &now);

	int hour = curr_time.tm_hour;	//시간
	int min = curr_time.tm_min;	//분
	int sec = curr_time.tm_sec;	//초

	glPushMatrix();
	glRotatef(30.f, 1.f, 0.f, 0.f);
	glRotatef(30.f, 0.f, 1.f, 0.f);
	glRotatef(rotatey, 0.f, 1.f, 0.f);

	glColor4f(0.f, 0.f, 1.f, 1.f);
	draw_digital(hour / 10, 0);
	draw_digital(hour % 10, 1);
	draw_digital(min / 10, 2);
	draw_digital(min % 10, 3);
	draw_digital(sec / 10, 4);
	draw_digital(sec % 10, 5);

	glColor4f(1.f, 1.f, 1.f, 1.f);

	for (i = 0; i < 6; ++i) {
		glPushMatrix();
		glTranslatef(75.f - 400 + i * 130, 400.f - 300, 0.f);
		glScalef(1.f, 0.25f, 1.f);
		glutWireCube(80.f);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(25.f - 400 + i * 130, 350.f - 300, 0.f);
		glScalef(0.25f, 1.f, 1.f);
		glutWireCube(80.f);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(125.f - 400 + i * 130, 350.f - 300, 0.f);
		glScalef(0.25f, 1.f, 1.f);
		glutWireCube(80.f);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(75.f - 400 + i * 130, 300.f - 300, 0.f);
		glScalef(1.f, 0.25f, 1.f);
		glutWireCube(80.f);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(25.f - 400 + i * 130, 250.f - 300, 0.f);
		glScalef(0.25f, 1.f, 1.f);
		glutWireCube(80.f);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(125.f - 400 + i * 130, 250.f - 300, 0.f);
		glScalef(0.25f, 1.f, 1.f);
		glutWireCube(80.f);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(75.f - 400 + i * 130, 200.f - 300, 0.f);
		glScalef(1.f, 0.25f, 1.f);
		glutWireCube(80.f);
		glPopMatrix();
	}
	glPopMatrix();
}

GLvoid CRun_time_Framework::draw_digital(int clock, int sequence) {
	int i;
	switch (clock) {
	case 0:
		for (i = 0; i < 7; ++i) {
			if (i != 3) {
				draw_clock(i, sequence);
			}
		}
		break;
	case 1:
		draw_clock(2, sequence);
		draw_clock(5, sequence);
		break;
	case 2:
		draw_clock(0, sequence);
		draw_clock(2, sequence);
		draw_clock(3, sequence);
		draw_clock(4, sequence);
		draw_clock(6, sequence);
		break;
	case 3:
		draw_clock(0, sequence);
		draw_clock(2, sequence);
		draw_clock(3, sequence);
		draw_clock(5, sequence);
		draw_clock(6, sequence);
		break;
	case 4:
		draw_clock(1, sequence);
		draw_clock(2, sequence);
		draw_clock(3, sequence);
		draw_clock(5, sequence);
		break;
	case 5:
		draw_clock(0, sequence);
		draw_clock(1, sequence);
		draw_clock(3, sequence);
		draw_clock(5, sequence);
		draw_clock(6, sequence);
		break;
	case 6:
		draw_clock(0, sequence);
		draw_clock(1, sequence);
		draw_clock(3, sequence);
		draw_clock(4, sequence);
		draw_clock(5, sequence);
		draw_clock(6, sequence);
		break;
	case 7:
		draw_clock(0, sequence);
		draw_clock(2, sequence);
		draw_clock(5, sequence);
		break;
	case 8:
		for (i = 0; i < 7; ++i) {
			draw_clock(i, sequence);
		}
		break;
	case 9:
		for (i = 0; i < 7; ++i) {
			if (i != 4) {
				draw_clock(i, sequence);
			}
		}
		break;
	}
}

GLvoid CRun_time_Framework::draw_clock(int num, int sequence) {
	switch (num) {
	case 0:
		glPushMatrix();
		glTranslatef(75.f - 400 + sequence * 130, 400.f - 300, 0.f);
		glScalef(1.f, 0.25f, 1.f);
		glutSolidCube(80.f);
		glPopMatrix();
		break;
	case 1:
		glPushMatrix();
		glTranslatef(25.f - 400 + sequence * 130, 350.f - 300, 0.f);
		glScalef(0.25f, 1.f, 1.f);
		glutSolidCube(80.f);
		glPopMatrix();
		break;
	case 2:
		glPushMatrix();
		glTranslatef(125.f - 400 + sequence * 130, 350.f - 300, 0.f);
		glScalef(0.25f, 1.f, 1.f);
		glutSolidCube(80.f);
		glPopMatrix();
		break;
	case 3:
		glPushMatrix();
		glTranslatef(75.f - 400 + sequence * 130, 300.f - 300, 0.f);
		glScalef(1.f, 0.25f, 1.f);
		glutSolidCube(80.f);
		glPopMatrix();
		break;
	case 4:
		glPushMatrix();
		glTranslatef(25.f - 400 + sequence * 130, 250.f - 300, 0.f);
		glScalef(0.25f, 1.f, 1.f);
		glutSolidCube(80.f);
		glPopMatrix();
		break;
	case 5:
		glPushMatrix();
		glTranslatef(125.f - 400 + sequence * 130, 250.f - 300, 0.f);
		glScalef(0.25f, 1.f, 1.f);
		glutSolidCube(80.f);
		glPopMatrix();
		break;
	case 6:
		glPushMatrix();
		glTranslatef(75.f - 400 + sequence * 130, 200.f - 300, 0.f);
		glScalef(1.f, 0.25f, 1.f);
		glutSolidCube(80.f);
		glPopMatrix();
		break;
	}
}

GLvoid CRun_time_Framework::shape_init() {
}