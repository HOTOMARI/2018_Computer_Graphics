#include <GL/freeglut.h>
#include<time.h>
#include<math.h>
#define PI 3.141592
GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Timerfunction(int);


struct Shape {
	int x, y;
	float r = 0;
	int type = 0;
	Shape* next;
};

Shape* head = NULL;


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
	Shape* t = head;

	glPointSize(3.0);
	glLineWidth(3.0);
	while (t != NULL) {
		for (int i = 0; i < 360; ++i) {
			if (t->type == 0) {
				glColor3f(1, 1, 1);
				glBegin(GL_LINES);
				glVertex2f(t->r*cos(i*PI / 180) + t->x, t->r*sin(i*PI / 180) + t->y);
				glVertex2f(t->r*cos((i + 1)*PI / 180) + t->x, t->r*sin((i + 1)*PI / 180) + t->y);
				glEnd();
			}
			else {
				if (i % 4==0) {
					glColor3f(rand()%255/255.0, rand() % 255 / 255.0, rand() % 255 / 255.0);
					glBegin(GL_POINTS);
					glVertex2f(t->r*cos(i*PI / 180) + t->x, t->r*sin(i*PI / 180) + t->y);
					glEnd();
				}
			}
		}
		t = t->next;
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
		Shape* t = head;
		if (head == NULL) {
			head = (Shape*)malloc(sizeof(Shape));
			head->next = NULL;
			head->x = x - 400;
			head->y = -1 * y + 300;
			head->r = 0;
			head->type = rand() % 2;
		}
		else {
			while (t->next != NULL) {
				t = t->next;
			}
			t->next = (Shape*)malloc(sizeof(Shape));
			t = t->next;
			t->next = NULL;
			t->x = x - 400;
			t->y = -1 * y + 300;
			t->r = 0;
			t->type = rand() % 2;
		}
	}
	glutPostRedisplay();
}

GLvoid Timerfunction(int value) {
	switch (value) {
	case 1:
		Shape* t = head;
		while (t != NULL) {
			t->r = t->r + 1;
			if (t->type == 0 && t->r > 20) {
				t->r = 0;
			}
			t = t->next;
		}
		glutPostRedisplay();
		glutTimerFunc(1000 / 60, Timerfunction, 1);
		break;
	}
}