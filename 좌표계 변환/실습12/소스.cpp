#include <GL/freeglut.h>
#include<time.h>
#include<math.h>
#define PI 3.141592

GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid Motion(int, int);
GLvoid Timerfunction(int);
void InitialShape();

struct Shape {
	bool is_triangle = true;
	bool is_now_morp = false;
	bool morp_bigger = true;
	float size = 20;
	int rotate_shape = 0;
	int position_shape = 0;
};
struct Line {
	float startX, startY, endX, endY;
	bool is_live = false;
};


int shape_mode = 0;	// 0 �� 1 ���� 2 ȸ���� 3 ������� 4 ��α׸���
int line_index = -1;

int animation_speed = 1000;

float moveX = 0, moveY = 0;
float global_rotate = 0;

Shape shape;
Line lines[4];

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
	glutPassiveMotionFunc(Motion);		// ���콺 ������ �ޱ�

	//shape.cx = 0;
	//shape.cy = 200;

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

	glRotatef(global_rotate, 0, 1.0, 0);
	switch (shape_mode)
	{
	case 0:
		for (int i = 0; i < 360; ++i) {
			glBegin(GL_LINES);
			glVertex3f(200 * cos(i / 180.0 * PI), 200 * sin(i / 180.0 * PI), 0);
			glVertex3f(200 * cos((i + 1) / 180.0 * PI), 200 * sin((i + 1) / 180.0 * PI), 0);
			glEnd();
		}
		glTranslated(200 * cos(shape.position_shape / 180.0 * PI),
			200 * sin(shape.position_shape / 180.0 * PI), 0);
		glRotatef(shape.rotate_shape, 0, 0, 1.0);
		break;
	case 1:
		for (int i = -400; i < 400; ++i) {
			glBegin(GL_LINES);
			glVertex3f(i, 200 * sin(i / 180.0 * PI), 0);
			glVertex3f(i + 1, 200 * sin((i + 1) / 180.0 * PI), 0);
			glEnd();
		}
		if (shape.position_shape > 400 + shape.size) {
			shape.position_shape = -400;
		}
		else if (shape.position_shape < -400 - shape.size) {
			shape.position_shape = 400;
		}
		glTranslated(shape.position_shape, 200 * sin(shape.position_shape / 180.0 * PI), 0);
		break;
	case 2:
		glRotatef(90, 0, 0, 1.0);
		for (int i = -800; i < 800; ++i) {
			glBegin(GL_LINES);
			glVertex3f(200 * cos(i / 180.0 * PI) + i, 200 * sin(i / 180.0 * PI), 0);
			glVertex3f(200 * cos((i + 1) / 180.0 * PI) + i + 1, 200 * sin((i + 1) / 180.0 * PI), 0);
			glEnd();
		}
		if (shape.position_shape > 450 + shape.size) {
			shape.position_shape = -450;
		}
		else if (shape.position_shape < -450 - shape.size) {
			shape.position_shape = 450;
		}
		glTranslated(200 * cos(shape.position_shape / 180.0 * PI) + shape.position_shape
			, 200 * sin(shape.position_shape / 180.0 * PI), 0);
		glRotatef(-90, 0, 0, 1.0);
		break;
	case 3:
		for (int i = 1; i < 800; ++i) {
			glBegin(GL_LINES);
			if (i % 100 != 99) {
				if (i / 100 % 2 == 0) {
					glVertex3f(i - 400, 100 - (i % 100) * 2, 0);
					glVertex3f((i + 1) - 400, 100 - ((i + 1) % 100) * 2, 0);
				}
				else {
					glVertex3f(i - 400, -100 + (i % 100) * 2, 0);
					glVertex3f((i + 1) - 400, -100 + ((i + 1) % 100) * 2, 0);
				}
			}
			glEnd();
		}
		if (shape.position_shape > 800 + shape.size) {
			shape.position_shape = 0;
		}
		else if (shape.position_shape < 0 - shape.size) {
			shape.position_shape = 800;
		}
		if (shape.position_shape % 100 != 99) {
			if (shape.position_shape / 100 % 2 == 0) {
				glTranslated(shape.position_shape - 400, 100 - (shape.position_shape % 100) * 2, 0);
			}
			else {
				glTranslated(shape.position_shape - 400, -100 + (shape.position_shape % 100) * 2, 0);
			}
		}
		break;
	case 4:
		for (int j = 0; j < 4; ++j) {
			if (lines[j].is_live) {
				glBegin(GL_LINES);
				glVertex3f(lines[j].startX, lines[j].startY, 0);
				glVertex3f(lines[j].endX, lines[j].endY, 0);
				glEnd();
			}
		}
		break;
	default:
		break;
	}
	if (shape.is_triangle) {
		glColor3f(1.0, 1.0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(shape.size * cos(90.0 / 180.0 * PI), shape.size * sin(90.0 / 180.0 * PI), 0);
		glVertex3f(shape.size * cos(210.0 / 180.0 * PI), shape.size * sin(210.0 / 180.0 * PI), 0);
		glVertex3f(shape.size * cos(330.0 / 180.0 * PI), shape.size * sin(330.0 / 180.0 * PI), 0);
		glEnd();
	}
	else {
		glColor3f(1.0, 1.0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(shape.size * -1.0, shape.size * 1.0, 0);
		glVertex3f(shape.size * -1.0, shape.size * -1.0, 0);
		glVertex3f(shape.size * 1.0, shape.size * -1.0, 0);
		glVertex3f(shape.size * 1.0, shape.size * 1.0, 0);
		glEnd();
	}

	glPopMatrix();
	glutSwapBuffers(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h) // �ٽ� �׸��� �Լ� 
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);
}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (shape_mode == 4 && line_index >= 4) {
			line_index = -1;
			for (int i = 0; i < 4; ++i) {
				lines[i].is_live = false;
			}
		}
		if (shape_mode == 4 && line_index < 4) {
			if (line_index == -1) {
				line_index++;
				if (lines[line_index].is_live == false) {
					lines[line_index].is_live = true;
					lines[line_index].startX = x - 400;
					lines[line_index].startY = -1 * y + 300;
					lines[line_index].endX = x - 400;
					lines[line_index].endY = -1 * y + 300;
				}
			}
			else {
				lines[line_index].endX = x - 400;
				lines[line_index].endY = -1 * y + 300;
				line_index++;
				if (lines[line_index].is_live == false) {
					lines[line_index].is_live = true;
					lines[line_index].startX = x - 400;
					lines[line_index].startY = -1 * y + 300;
					lines[line_index].endX = x - 400;
					lines[line_index].endY = -1 * y + 300;
				}
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
	case 't':
		if (shape.is_triangle) {
			shape.is_triangle = false;
		}
		else {
			shape.is_triangle = true;
		}
		break;
	case 'r':
		if (shape_mode == 0) {
			shape.rotate_shape += 5;
			shape.position_shape += 5;
		}
		break;
	case 'R':
		if (shape_mode == 0) {
			shape.rotate_shape -= 5;
			shape.position_shape -= 5;
		}
		break;
	case 'e':
		shape.position_shape += 5;
		break;
	case 'E':
		shape.position_shape -= 5;
		break;
	case 's':
		if (shape.is_now_morp) {
			shape.is_now_morp = false;
		}
		else {
			shape.is_now_morp = true;
		}
		break;
	case 'y':
		global_rotate += 5;
		break;
	case 'Y':
		global_rotate -= 5;
		break;
	case '0':
		shape_mode = 0;
		InitialShape();
		break;
	case '1':
		shape_mode = 1;
		InitialShape();
		break;
	case '2':
		shape_mode = 2;
		InitialShape();
		break;
	case '3':
		shape_mode = 3;
		InitialShape();
		break;
	case '4':
		shape_mode = 4;
		InitialShape();
		break;
	}
	glutPostRedisplay();
}

GLvoid Motion(int x, int y)
{
	if (line_index >= 0 && line_index <= 4 && shape_mode == 4) {
		lines[line_index].endX = x - 400;
		lines[line_index].endY = -1 * y + 300;
	}
}

GLvoid Timerfunction(int value) {
	switch (value) {
	case 1:
		if (shape.is_now_morp) {
			if (shape.morp_bigger) {
				shape.size++;
				if (shape.size > 40) {
					shape.morp_bigger = false;
				}
			}
			else {
				shape.size--;
				if (shape.size < 10) {
					shape.morp_bigger = true;
				}
			}
		}
		glutPostRedisplay();
		glutTimerFunc(animation_speed / 60, Timerfunction, 1);
		break;
	}
}

void InitialShape()
{
	shape.is_triangle = true;
	shape.is_now_morp = false;
	shape.morp_bigger = true;
	shape.size = 20;
	shape.rotate_shape = 0;
	shape.position_shape = 0;
	global_rotate = 0;
	line_index = -1;
}
