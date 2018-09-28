#include <GL/freeglut.h>
#include<time.h>
#include<math.h>
#define PI 3.141592

GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid Timerfunction(int);
void InitialShape();

struct Shape {
	float size = 150;
	int movestack = 0;
};

int animation_speed = 1000;

float bigTriangle_rotate = 0;

Shape shape;

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
	glutTimerFunc(animation_speed / 60, Timerfunction, 1);
	glutKeyboardFunc(Keyboard);	// Ű���� �Է� �ޱ�

	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}

GLvoid DrawScene() // ��� �Լ� 
{
	glClearColor(0, 0, 0, 1); // �������� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 
	glMatrixMode(GL_MODELVIEW);

	glPointSize(3.0);

	glPushMatrix();
	// �߽ɼ�
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0, 300, 0);
	glVertex3f(0, -300, 0);
	glVertex3f(400, 0, 0);
	glVertex3f(-400, 0, 0);
	glEnd();

	glRotatef(bigTriangle_rotate, 0, 1.0, 0);
	glPushMatrix();

	glBegin(GL_LINE_LOOP);
	glVertex3f(shape.size * cos(90.0 / 180.0 * PI), shape.size * sin(90.0 / 180.0 * PI), 0);
	glVertex3f(shape.size * cos(210.0 / 180.0 * PI), shape.size * sin(210.0 / 180.0 * PI), 0);
	glVertex3f(shape.size * cos(330.0 / 180.0 * PI), shape.size * sin(330.0 / 180.0 * PI), 0);
	glEnd();

	if (shape.movestack<=60) {
		glTranslated(shape.size * cos(90.0 / 180.0 * PI) + ((shape.size * cos(210.0 / 180.0 * PI) - shape.size * cos(90.0 / 180.0 * PI)) / 60.0*(shape.movestack - 0)),
			shape.size * sin(90.0 / 180.0 * PI) + ((shape.size * sin(210.0 / 180.0 * PI) - shape.size * sin(90.0 / 180.0 * PI)) / 60.0*(shape.movestack - 0)), 0);
	}
	else if (shape.movestack <= 120) {
		glTranslated(shape.size * cos(210.0 / 180.0 * PI) + ((shape.size * cos(330.0 / 180.0 * PI) - shape.size * cos(210.0 / 180.0 * PI)) / 60.0*(shape.movestack - 60)),
			shape.size * sin(210.0 / 180.0 * PI) + ((shape.size * sin(330.0 / 180.0 * PI) - shape.size * sin(210.0 / 180.0 * PI)) / 60.0*(shape.movestack - 60)), 0);
	}
	else if (shape.movestack <= 180) {
		glTranslated(shape.size * cos(330.0 / 180.0 * PI) + ((shape.size * cos(90.0 / 180.0 * PI) - shape.size * cos(330.0 / 180.0 * PI)) / 60.0*(shape.movestack - 120)),
			shape.size * sin(330.0 / 180.0 * PI) + ((shape.size * sin(90.0 / 180.0 * PI) - shape.size * sin(330.0 / 180.0 * PI)) / 60.0*(shape.movestack - 120)), 0);
	}

	glColor3f(1.0, 1.0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(20 * cos(90.0 / 180.0 * PI), 20 * sin(90.0 / 180.0 * PI), 0);
	glVertex3f(20 * cos(210.0 / 180.0 * PI), 20 * sin(210.0 / 180.0 * PI), 0);
	glVertex3f(20 * cos(330.0 / 180.0 * PI), 20 * sin(330.0 / 180.0 * PI), 0);
	glEnd();
	glPopMatrix();

	glRotatef(90, 0, 1.0, 0);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(shape.size * cos(90.0 / 180.0 * PI), shape.size * sin(90.0 / 180.0 * PI), 0);
	glVertex3f(shape.size * cos(210.0 / 180.0 * PI), shape.size * sin(210.0 / 180.0 * PI), 0);
	glVertex3f(shape.size * cos(330.0 / 180.0 * PI), shape.size * sin(330.0 / 180.0 * PI), 0);
	glEnd();

	if (shape.movestack <= 60) {
		glTranslated(shape.size * cos(90.0 / 180.0 * PI) + ((shape.size * cos(210.0 / 180.0 * PI) - shape.size * cos(90.0 / 180.0 * PI)) / 60.0*(shape.movestack - 0)),
			shape.size * sin(90.0 / 180.0 * PI) + ((shape.size * sin(210.0 / 180.0 * PI) - shape.size * sin(90.0 / 180.0 * PI)) / 60.0*(shape.movestack - 0)), 0);
	}
	else if (shape.movestack <= 120) {
		glTranslated(shape.size * cos(210.0 / 180.0 * PI) + ((shape.size * cos(330.0 / 180.0 * PI) - shape.size * cos(210.0 / 180.0 * PI)) / 60.0*(shape.movestack - 60)),
			shape.size * sin(210.0 / 180.0 * PI) + ((shape.size * sin(330.0 / 180.0 * PI) - shape.size * sin(210.0 / 180.0 * PI)) / 60.0*(shape.movestack - 60)), 0);
	}
	else if (shape.movestack <= 180) {
		glTranslated(shape.size * cos(330.0 / 180.0 * PI) + ((shape.size * cos(90.0 / 180.0 * PI) - shape.size * cos(330.0 / 180.0 * PI)) / 60.0*(shape.movestack - 120)),
			shape.size * sin(330.0 / 180.0 * PI) + ((shape.size * sin(90.0 / 180.0 * PI) - shape.size * sin(330.0 / 180.0 * PI)) / 60.0*(shape.movestack - 120)), 0);
	}

	glColor3f(0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(20 * cos(90.0 / 180.0 * PI), 20 * sin(90.0 / 180.0 * PI), 0);
	glVertex3f(20 * cos(210.0 / 180.0 * PI), 20 * sin(210.0 / 180.0 * PI), 0);
	glVertex3f(20 * cos(330.0 / 180.0 * PI), 20 * sin(330.0 / 180.0 * PI), 0);
	glEnd();

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
	case 's':
		shape.size += 5;
		break;
	case 'S':
		shape.size -= 5;
		break;
	case 'y':
		bigTriangle_rotate += 5;
		break;
	case 'Y':
		bigTriangle_rotate -= 5;
		break;
	}
	
}


GLvoid Timerfunction(int value) {
	switch (value)
	{
	case 1:
		shape.movestack = (shape.movestack + 1) % 180;
		glutTimerFunc(animation_speed / 60, Timerfunction, 1);
		glutPostRedisplay();
		break;
	}
}

void InitialShape()
{
	shape.size = 20;
	bigTriangle_rotate = 0;
	shape.movestack = 0;
}
