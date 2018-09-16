#include <GL/freeglut.h>
#include<time.h>
GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Timerfunction(int);

struct Shape {
	int size = 0;		// 1 ~ 10 ��ȭ
	bool bigger_size = true;	// �簢�� Ŀ������ �۾�������
	bool alive = false;			// ���̱� �Ⱥ��̱�
	float R, G, B;				// ����
	RECT rect;
};

Shape shape[10];

int now_shape = 0;

void main(int argc, char** argv) // ������ ����ϰ� ����Լ� ���� 
{
	// �ʱ�ȭ �Լ��� 
	glutInit(&argc, argv); // glut �ʱ�ȭ 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Tiles"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(DrawScene); // ��� �Լ��� ���� 
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ���� 
	glutTimerFunc(1000 / 60, Timerfunction, 1);	// Ÿ�̸� ����
	glutMouseFunc(Mouse);		// ���콺 ��ư �Է� �ޱ�

	srand(time(NULL));

	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}

GLvoid DrawScene() // ��� �Լ� 
{
	glClearColor(0, 0, 0, 1); // �������� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

	for (int i = 0; i < 10; ++i) {
		if (shape[i].alive) {
			glColor4f(shape[i].R, shape[i].G, shape[i].B, 1);
			glRectf(shape[i].rect.left - shape[i].size * 5, shape[i].rect.top + shape[i].size * 5,
				shape[i].rect.right + shape[i].size * 5, shape[i].rect.bottom - shape[i].size * 5);
		}
	}


	glFlush(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h) // �ٽ� �׸��� �Լ� 
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);
}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		shape[now_shape].alive = true;
		shape[now_shape].R = rand() % 255 / 255.0;
		shape[now_shape].G = rand() % 255 / 255.0;
		shape[now_shape].B = rand() % 255 / 255.0;
		shape[now_shape].size = rand() % 8 + 1;
		shape[now_shape].rect.left = x - 400;
		shape[now_shape].rect.right = shape[now_shape].rect.left + shape[now_shape].size * 5;
		shape[now_shape].rect.bottom = -1*y + 300;
		shape[now_shape].rect.top = shape[now_shape].rect.bottom + shape[now_shape].size * 5;
		now_shape++;
		if (now_shape > 9)
			now_shape = 0;
	}
	glutPostRedisplay();
}

GLvoid Timerfunction(int value) {
	switch (value) {
	case 1:
		for (int i = 0; i < 10; ++i) {
			shape[i].R = 1.0 - (rand() % 255 / 255.0);
			shape[i].G = 1.0 - (rand() % 255 / 255.0);
			shape[i].B = 1.0 - (rand() % 255 / 255.0);
			if (shape[i].alive) {
				if (shape[i].bigger_size) {
					shape[i].size++;
					if (shape[i].size >= 10) {
						shape[i].bigger_size = false;
					}
				}
				else {
					shape[i].size--;
					if (shape[i].size <= 1) {
						shape[i].bigger_size = true;
					}
				}
			}
		}
		glutPostRedisplay();
		glutTimerFunc(1000/60, Timerfunction, 1);
		break;
	}
}