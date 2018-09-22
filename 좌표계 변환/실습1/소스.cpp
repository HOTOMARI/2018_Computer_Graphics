#include <GL/freeglut.h>
#include<time.h>
#include<math.h>
#define PI 3.141592

GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid SpecialKeyboard(int, int, int);
GLvoid Timerfunction(int);


int shape_mode = 0;	// 0 ���ΰ 1 ������ 2 ���� 3 �簢��

int animation_speed = 1000;
bool animation_switch[2] = { false, };	// ����, ������ �̵�

float moveX = 0, moveY = 0;
float transformSize = 1;

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
	glutTimerFunc(animation_speed / 60, Timerfunction, 2);
	glutMouseFunc(Mouse);		// ���콺 ��ư �Է� �ޱ�
	glutKeyboardFunc(Keyboard);	// Ű���� �Է� �ޱ�
	glutSpecialFunc(SpecialKeyboard);	// Ű���� Ư����ư �Է� �ޱ�

	srand(time(NULL));

	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}

GLvoid DrawScene() // ��� �Լ� 
{
	glClearColor(0, 0, 0, 1); // �������� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

	glPointSize(3.0);
	
	// �߽ɼ�
	glBegin(GL_LINES);
	glVertex3f(0, 300 ,0);
	glVertex3f(0, -300, 0);
	glVertex3f(400, 0, 0);
	glVertex3f(-400, 0, 0);
	glEnd();

	switch (shape_mode) {
	case 0:
		for (int i = -400 ; i < 400; ++i) {
			glBegin(GL_LINES);
			glVertex3f(i, cos(((i*transformSize) + moveX) / 180.0 * PI) * 200 + moveY, 0);
			glVertex3f(i + 1, cos(((i + 1)*transformSize + moveX) / 180.0 * PI) * 200 + moveY, 0);
			glEnd();
		}
		break;
	case 1:
		for (int i = -800; i < 800; ++i) {
			glBegin(GL_LINES);
			glVertex3f(200 * sin(((i*transformSize) + moveX) / 180.0 * PI) + i, cos(((i*transformSize)+ moveX) / 180.0 * PI) * 200 + moveY, 0);
			glVertex3f(200*sin(((i + 1)*transformSize + moveX) / 180.0 * PI) + i+1, cos(((i + 1)*transformSize + moveX) / 180.0 * PI) * 200 + moveY, 0);
			glEnd();
		}
		break;
	case 2:
		// ���ʺκ�
		glBegin(GL_POLYGON);
		glVertex3f(-0.5 * 400 + moveX - ((transformSize - 1) * 100), 0.5 * 300 + moveY, 0);
		glVertex3f(-0.5 * 400 + moveX - ((transformSize - 1) * 100), -0.5 * 300 + moveY, 0);
		glVertex3f(0 + moveX, 0 + moveY, 0);
		glEnd();
		// �����ʺκ�
		glBegin(GL_POLYGON);
		glVertex3f(0 + moveX, 0, 0);
		glVertex3f(0.5 * 400 + moveX + ((transformSize - 1) * 100), 0.5 * 300 + moveY, 0);
		glVertex3f(0.5 * 400 + moveX + ((transformSize - 1) * 100), -0.5 * 300 + moveY, 0);
		glEnd();
		break;
	case 3:
		glBegin(GL_POLYGON);
		glVertex3f(-0.5 * 400 + moveX - ((transformSize - 1) * 100), 0.5 * 300 + moveY, 0);
		glVertex3f(-0.5 * 400 + moveX - ((transformSize - 1) * 100), -0.5 * 300 + moveY, 0);
		glVertex3f(0.5 * 400 + moveX + ((transformSize - 1) * 100), -0.5 * 300 + moveY, 0);
		glVertex3f(0.5 * 400 + moveX + ((transformSize - 1) * 100), 0.5 * 300 + moveY, 0);
		glEnd();
		break;
	}

	
	glutSwapBuffers(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h) // �ٽ� �׸��� �Լ� 
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);
}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
	}
	glutPostRedisplay();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
		glutLeaveMainLoop();
		break;
	case 'x':
		moveX++;
		break;
	case 'X':
		moveX--;
		break;
	case 'y':
		moveY++;
		break;
	case 'Y':
		moveY--;
		break;
	case 's':
		transformSize += 0.05;
		break;
	case 'S':
		//if (transformSize > 0.05) {
			transformSize -= 0.05;
		//}
		break;
	case 'r':
		moveX += 20;
		break;
	case 'R':
		moveX += 20;
		break;
	case 'a':
		animation_switch[0] = true;
		animation_switch[1] = false;
		break;
	case 'A':
		animation_switch[0] = false;
		animation_switch[1] = true;
		break;
	case 't':
	case 'T':
		animation_switch[0] = false;
		animation_switch[1] = false;
		break;
	case '1':
		shape_mode = 0;
		moveX = 0, moveY = 0;
		animation_switch[0] = false, animation_switch[1] = false;
		transformSize = 1;
		break;
	case '2':
		shape_mode = 1;
		moveX = 0, moveY = 0;
		animation_switch[0] = false, animation_switch[1] = false;
		transformSize = 1;
		break;
	case '3':
		shape_mode = 2;
		moveX = 0, moveY = 0;
		animation_switch[0] = false, animation_switch[1] = false;
		transformSize = 1;
		break;
	case '4':
		shape_mode = 3;
		moveX = 0, moveY = 0;
		animation_switch[0] = false, animation_switch[1] = false;
		transformSize = 1;
		break;
	}
	glutPostRedisplay();
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		if (animation_speed > 100)
			animation_speed -= 100;
		break;
	case GLUT_KEY_DOWN:
		animation_speed += 100;
		break;
	}
}

GLvoid Timerfunction(int value) {
	switch (value) {
	case 1:
		if (animation_switch[0]) {
			moveX++;
		}
		else if (animation_switch[1]) {
			moveX--;
		}
		glutPostRedisplay();
		glutTimerFunc(animation_speed / 60, Timerfunction, 1);
		break;
	}
}