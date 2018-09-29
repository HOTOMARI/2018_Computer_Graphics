#include <GL/freeglut.h>
#include<time.h>
#include<math.h>
#define PI 3.141592
GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Timerfunction(int);


struct Shape {
	double base, height, size, radius[2];
	int stacks, slices, sides, rings;

	int type = 0;		// 0 ���� 1 ����ü 2 �� 3 ���� 4 ������
	float R, G, B;
	int rotate_degree;
	int axis;			// 1 x�� 2 y�� 2 3��
	float x, y;

	bool rotate_left;
	bool dead = true;
};

Shape shapes[20];


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
	glutMouseFunc(Mouse);		// ���콺 ��ư �Է� �ޱ�

	srand(time(NULL));

	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}

GLvoid DrawScene() // ��� �Լ� 
{
	glClearColor(0, 0, 0, 1); // �������� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 
	glMatrixMode(GL_MODELVIEW);


	for (int i = 0; i < 20; ++i) {
		if (shapes[i].dead == false) {
			glPushMatrix();
			glColor3f(shapes[i].R, shapes[i].G, shapes[i].B);
			glTranslated(shapes[i].x, shapes[i].y, 0);
			glRotatef(shapes[i].rotate_degree, shapes[i].axis / 1, shapes[i].axis / 2, shapes[i].axis / 3);

			switch (shapes[i].type) {
			case 0:
				glutWireCone(shapes[i].base, shapes[i].height, shapes[i].slices, shapes[i].stacks);
				break;
			case 1:
				glutWireCube(shapes[i].size);
				break;
			case 2:
				glutWireSphere(shapes[i].radius[0], shapes[i].slices, shapes[i].stacks);
				break;
			case 3:
				glutWireTorus(shapes[i].radius[0], shapes[i].radius[1], shapes[i].sides, shapes[i].rings);
				break;
			case 4:
				glutWireTeapot(shapes[i].size);
				break;
			}
			glPopMatrix();
		}
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
		for (int i = 0; i < 20; ++i) {
			if (shapes[i].dead) {
				shapes[i].type = rand() % 5;
				switch (shapes[i].type) {
				case 0:
					shapes[i].base = rand() % 200 + 50;
					shapes[i].height = rand() % 200 + 50;
					shapes[i].slices = rand() % 10 + 3;
					shapes[i].stacks = rand() % 10 + 3;
					break;
				case 1:
				case 4:
					shapes[i].size = rand() % 100 + 50;
					break;
				case 2:
					shapes[i].radius[0] = rand() % 100 + 50;
					shapes[i].slices = rand() % 10 + 3;
					shapes[i].stacks = rand() % 10 + 3;
					break;
				case 3:
					shapes[i].radius[0] = rand() % 30 + 50;
					shapes[i].radius[1] = rand() % 30 + 100;
					shapes[i].sides = rand() % 10 + 5;
					shapes[i].rings = rand() % 10 + 8;
					break;
				}
				shapes[i].x = x - 400;
				shapes[i].y = -1 * y + 300;
				shapes[i].rotate_degree = rand() % 360;
				shapes[i].R = rand() % 255 / 255.0;
				shapes[i].G = rand() % 255 / 255.0;
				shapes[i].B = rand() % 255 / 255.0;
				shapes[i].axis = rand() % 3 + 1;
				if (rand() % 2)
					shapes[i].rotate_left = true;
				else shapes[i].rotate_left = false;
				shapes[i].dead = false;
				break;
			}
		}
	}
	glutPostRedisplay();
}

GLvoid Timerfunction(int value) {
	switch (value) {
	case 1:
		for (int i = 0; i < 20; ++i) {
			
		}
		glutPostRedisplay();
		glutTimerFunc(1000 / 60, Timerfunction, 1);
		break;
	}
}