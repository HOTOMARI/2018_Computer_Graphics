#include <GL/freeglut.h>
#include<time.h>
#include<math.h>
#define PI 3.141592
GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid Timerfunction(int);

time_t	now;
struct tm curr_time;

int nums[6];

void main(int argc, char** argv) // ������ ����ϰ� ����Լ� ���� 
{
	// �ʱ�ȭ �Լ��� 
	glutInit(&argc, argv); // glut �ʱ�ȭ 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Tiles"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(DrawScene); // ��� �Լ��� ���� 
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ���� 
	glutTimerFunc(1000 / 60, Timerfunction, 1);	// Ÿ�̸� ����
	glutKeyboardFunc(Keyboard);	// Ű���� �Է� �ޱ�

	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}

GLvoid DrawScene() // ��� �Լ� 
{
	glClearColor(0, 0, 0, 1); // �������� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glScaled(0.6, 0.6, 1.0);
	glTranslated(-460, 0, 0);

	for (int j = 0; j < 6; ++j) {
		if (j != 0) {
			glTranslated(170, 0, 0);
			if (j % 2 == 0)
				glTranslated(40, 0, 0);
		}
		glPushMatrix();
		glTranslated(0, 125, 0);
		for (int i = 0; i < 3; ++i) {
			if (i)
				glTranslated(0, -125, 0);
			glPushMatrix();
			glScaled(1.0, 0.25, 1.0);
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(100);
			switch (i) {
			case 0:
				if (nums[j] == 2 || nums[j] == 3 || nums[j] == 5 || nums[j] == 6 || nums[j] == 7 || nums[j] == 8 || nums[j] == 9 || nums[j] == 0) {
					glColor3f(0, 1.0, 0);
					glutSolidCube(100);
				}
				break;
			case 1:
				if (nums[j] == 2 || nums[j] == 3 || nums[j] == 4 || nums[j] == 5 || nums[j] == 6 || nums[j] == 8 || nums[j] == 9) {
					glColor3f(0, 1.0, 0);
					glutSolidCube(100);
				}
				break;
			case 2:
				if (nums[j] == 2 || nums[j] == 3 || nums[j] == 5 || nums[j] == 6 || nums[j] == 8 || nums[j] == 0) {
					glColor3f(0, 1.0, 0);
					glutSolidCube(100);
				}
				break;
			}
			glPopMatrix();
		}
		glTranslated(-63, 187, 0);
		for (int i = 0; i < 2; ++i) {
			if (i)
				glTranslated(125, 0, 0);
			glPushMatrix();
			glScaled(0.25, 1.0, 1.0);
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(100);
			switch (i) {
			case 0:
				if (nums[j] == 4 || nums[j] == 5 || nums[j] == 6 || nums[j] == 8 || nums[j] == 9 || nums[j] == 0) {
					glColor3f(0, 1.0, 0);
					glutSolidCube(100);
				}
				break;
			case 1:
				if (nums[j] == 1 || nums[j] == 2 || nums[j] == 3 || nums[j] == 4 || nums[j] == 7 || nums[j] == 8 || nums[j] == 9 || nums[j] == 0) {
					glColor3f(0, 1.0, 0);
					glutSolidCube(100);
				}
			}
			glTranslated(0, -125, 0);
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(100);
			switch (i) {
			case 0:
				if (nums[j] == 2 || nums[j] == 6 || nums[j] == 8 || nums[j] == 0) {
					glColor3f(0, 1.0, 0);
					glutSolidCube(100);
				}
				break;
			case 1:
				if (nums[j] == 1 || nums[j] == 3 || nums[j] == 4 || nums[j] == 5 || nums[j] == 6 || nums[j] == 7 || nums[j] == 8 || nums[j] == 9 || nums[j] == 0) {
					glColor3f(0, 1.0, 0);
					glutSolidCube(100);
				}
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();

	if (nums[5] % 2) {
		glPushMatrix();
		glTranslated(-112, 30, 0);
		for (int j = 0; j < 2; ++j) {
			glPushMatrix();
			if (j)
				glTranslated(230, 0, 0);
			for (int i = 0; i < 2; ++i) {
				if (i)
					glTranslated(0, -75, 0);
				glColor3f(0, 0, 0);
				glutWireCube(20);
				glColor3f(1.0, 1.0, 1.0);
				glutSolidCube(20);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}

	glutSwapBuffers(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h) // �ٽ� �׸��� �Լ� 
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);
}


GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
		glutLeaveMainLoop();
		break;
	}

}

GLvoid Timerfunction(int value) {
	switch (value) {
	case 1:
		now = time(0);
		localtime_s(&curr_time, &now);
		nums[0] = curr_time.tm_hour / 10;
		nums[1] = curr_time.tm_hour % 10;
		nums[2] = curr_time.tm_min / 10;
		nums[3] = curr_time.tm_min % 10;
		nums[4] = curr_time.tm_sec / 10;
		nums[5] = curr_time.tm_sec % 10;
		glutPostRedisplay();
		glutTimerFunc(1000 / 60, Timerfunction, 1);
		break;
	}
}