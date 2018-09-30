#include <GL/freeglut.h>
#include<time.h>
#include<math.h>
#define PI 3.141592
GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid Timerfunction(int);

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
			glTranslated(0, -125, 0);
			glutWireCube(100);
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
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
		glutPostRedisplay();
		glutTimerFunc(1000 / 60, Timerfunction, 1);
		break;
	}
}