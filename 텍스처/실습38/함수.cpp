#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

GLvoid CRun_time_Framework::Draw_Shapes()
{

	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	for (int i = 0; i < 9; ++i) {
		glPushMatrix();
		glTranslatef(-270 + ((i % 3) * 300), 320 - (i / 3 * 300), 0);

		switch (i) {
		case 0:
			glBlendFunc(GL_ONE, GL_ZERO);
			break;
		case 1:
			glBlendFunc(GL_ZERO, GL_ONE);
			break;
		case 2:
			glBlendFunc(GL_ONE, GL_ONE);
			break;
		case 3:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
		case 4:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
		case 5:
			glBlendFunc(GL_ZERO, GL_SRC_COLOR);
			break;
		case 6:
			glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
			break;
		case 7:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
		case 8:
			glBlendFunc(GL_ONE, GL_ONE);
			break;
		}

		glPushMatrix();
		glColor4f(0, 1, 0, shape[i].alpha[0]);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(50, 50, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glColor4f(0, 0, 1, shape[i].alpha[1]);
		glTranslatef(0, -50, 100);
		glutSolidSphere(50, 20, 20);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-50, 0, 200);
		glColor4f(1, 0, 0, shape[i].alpha[2]);
		glutSolidTeapot(50);
		glPopMatrix();

		glPopMatrix();
	}
}

GLvoid CRun_time_Framework::Draw_fonts()
{
	for (int i = 0; i < 9; ++i) {
		glPushMatrix();
		glTranslatef(-270 + ((i % 3) * 300), 320 - (i / 3 * 300), 0);

		glColor4f(0, 1, 0, 1);
		switch (i) {
		case 0:
			string = "(GL_ONE, GL_ZERO)";
			break;
		case 1:
			string = "(GL_ZERO, GL_ONE)";
			break;
		case 2:
			string = "(GL_ONE, GL_ONE)";
			break;
		case 3:
			string = "(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)";
			break;
		case 4:
			string = "(GL_SRC_ALPHA, GL_ONE)";
			break;
		case 5:
			string = "(GL_ZERO, GL_SRC_COLOR)";
			break;
		case 6:
			string = "(GL_ONE_MINUS_DST_COLOR, GL_ZERO)";
			break;
		case 7:
			string = "(GL_SRC_ALPHA, GL_ONE)";
			break;
		case 8:
			string = "(GL_ONE, GL_ONE)";
			break;
		}

		len = (int)strlen(string);
		glRasterPos3f(-100, -150, 400);
		for (int k = 0; k < len; k++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[k]);

		if (i == sel) {
			glTranslatef(-30, -20, 0);
			glutWireCube(300);
		}

		glPopMatrix();
	}
}
