#include <GL/freeglut.h>
#include<time.h>

struct Shape {
	bool alive = false;			// ���̱� �Ⱥ��̱�
	float R, G, B;				// ����
	RECT rect;
};

GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Motion(int, int);
GLvoid Timerfunction(int);

bool collide_rec_rec(Shape, Shape);

Shape background_rect[100];
Shape eraser_rect;


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
	glutMotionFunc(Motion);		// ���콺 ������ �Է¹ޱ�

	srand(time(NULL));

	// ��� �簢�� ����
	for (int i = 0; i < 100; ++i) {
		background_rect[i].alive = true;
		background_rect[i].R = rand()%255/255.0;
		background_rect[i].G = rand() % 255 / 255.0;
		background_rect[i].B = rand() % 255 / 255.0;
		background_rect[i].rect.left = rand() % 800 - 400;
		background_rect[i].rect.right = background_rect[i].rect.left + 20;
		background_rect[i].rect.top = -1 * (rand() % 600) + 300;
		background_rect[i].rect.bottom = background_rect[i].rect.top - 20;
	}

	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}

GLvoid DrawScene() // ��� �Լ� 
{
	glClearColor(0, 0, 0, 1); // �������� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

	//���簢��
	for (int i = 0; i < 100; ++i) {
		if (background_rect[i].alive) {
			glColor4f(background_rect[i].R, background_rect[i].G, background_rect[i].B, 1);
			glBegin(GL_POLYGON);
			glVertex2f(background_rect[i].rect.left, background_rect[i].rect.top);
			glVertex2f(background_rect[i].rect.left, background_rect[i].rect.bottom);
			glVertex2f(background_rect[i].rect.right, background_rect[i].rect.bottom);
			glVertex2f(background_rect[i].rect.right, background_rect[i].rect.top);
			glEnd();
		}
	}
	//���찳�簢��
	if (eraser_rect.alive) {
		glColor4f(1, 1, 1, 1);
		glBegin(GL_POLYGON);
		glVertex2f(eraser_rect.rect.left, eraser_rect.rect.top);
		glVertex2f(eraser_rect.rect.left, eraser_rect.rect.bottom);
		glVertex2f(eraser_rect.rect.right, eraser_rect.rect.bottom);
		glVertex2f(eraser_rect.rect.right, eraser_rect.rect.top);
		glEnd();
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
		eraser_rect.alive = true;
		eraser_rect.rect.left = x - 20 - 400;
		eraser_rect.rect.right = eraser_rect.rect.left + 40;
		eraser_rect.rect.top = -1 * (y - 20) + 300;
		eraser_rect.rect.bottom = eraser_rect.rect.top - 40;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		eraser_rect.alive = false;
	}
	glutPostRedisplay();
}

GLvoid Motion(int x, int y) {
	if (eraser_rect.alive) {
		eraser_rect.rect.left = x - 20 - 400;
		eraser_rect.rect.right = eraser_rect.rect.left + 40;
		eraser_rect.rect.top = -1 * (y - 20) + 300;
		eraser_rect.rect.bottom = eraser_rect.rect.top - 40;
		for (int i = 0; i < 100; ++i) {
			if (background_rect[i].alive&&collide_rec_rec(background_rect[i], eraser_rect)) {
				background_rect[i].alive = false;
			}
		}
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

bool collide_rec_rec(Shape background, Shape eraser) {
	if (background.rect.left<eraser.rect.right&&background.rect.right>eraser.rect.left
		&&background.rect.top>eraser.rect.bottom&&background.rect.bottom<eraser.rect.top)
		return true;
	else return false;
}