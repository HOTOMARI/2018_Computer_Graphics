#include <GL/freeglut.h>
#include<time.h>
#include<math.h>
#define PI 3.141592
GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid Timerfunction(int);


struct Shape {
	double base, height, size, radius[2];
	int stacks, slices, sides, rings;

	int type = 0;		// 0 ���� 1 ����ü 2 �� 3 ���� 4 ������
	float R, G, B;
	int rotate_degree;
	int axis;			// 1 x�� 2 y�� 2 3��
	float x, y;
	float scale;

	bool rotate_left;
	bool dead = true;
};

Shape shapes[20];


void main(int argc, char** argv) // ������ ����ϰ� ����Լ� ���� 
{
	// �ʱ�ȭ �Լ��� 
	glutInit(&argc, argv); // glut �ʱ�ȭ 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Tiles"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(DrawScene); // ��� �Լ��� ���� 
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ���� 
	glutTimerFunc(1000 / 60, Timerfunction, 1);	// Ÿ�̸� ����
	glutMouseFunc(Mouse);		// ���콺 ��ư �Է� �ޱ�
	glutKeyboardFunc(Keyboard);	// Ű���� �Է� �ޱ�

	srand(time(NULL));

	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}

GLvoid DrawScene() // ��� �Լ� 
{
	glClearColor(0, 0, 0, 1); // �������� ���� 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 
	glEnable(GL_DEPTH_TEST);	//�����׽�Ʈ
	glDepthFunc(GL_LESS);		//Passes if the fragment's depth value is less than the stored depth value.
	glMatrixMode(GL_MODELVIEW);


	for (int i = 0; i < 20; ++i) {
		if (shapes[i].dead == false) {
			glPushMatrix();
			glColor3f(shapes[i].R, shapes[i].G, shapes[i].B);
			glTranslated(shapes[i].x, shapes[i].y, 0);
			glScaled(1.0+shapes[i].scale, 1.0 + shapes[i].scale, 1.0 + shapes[i].scale);
			//glRotatef(shapes[i].rotate_degree, 0, 1, 0);
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
				shapes[i].scale = 0;
				shapes[i].dead = false;
				break;
			}
		}
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
	case 'r':
	case 'R':
		for (int i = 0; i < 20; ++i) {
			if (shapes[i].dead == false) {
				if (shapes[i].rotate_left)
					shapes[i].rotate_left = false;
				else shapes[i].rotate_left = true;
			}
		}
		break;
	}

}

GLvoid Timerfunction(int value) {
	switch (value) {
	case 1:
		for (int i = 0; i < 20; ++i) {
			if (shapes[i].dead == false) {
				shapes[i].scale -= 0.003;
				if (shapes[i].scale <= -1.0)
					shapes[i].dead = true;
				if (shapes[i].rotate_left) {
					shapes[i].rotate_degree -= 5;
					if (shapes[i].rotate_degree < 0) {
						shapes[i].rotate_degree = 360 + shapes[i].rotate_degree;
					}
				}
				else {
					shapes[i].rotate_degree += 5;
					if (shapes[i].rotate_degree > 360) {
						shapes[i].rotate_degree = shapes[i].rotate_degree - 360;
					}
				}
			}
		}
		glutPostRedisplay();
		glutTimerFunc(1000/ 60, Timerfunction, 1);
		break;
	}
}