#include <GL/freeglut.h>
#include<time.h>
GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid SpecialKeyboard(int, int, int);
GLvoid Timerfunction(int);

struct Shape {
	int size = 0;		// 1 ~ 10 ��ȭ
	int type = 0;		// 0 �簢�� 1 �ﰢ��
	bool bigger_size = true;	// �簢�� Ŀ������ �۾�������
	bool alive = false;			// ���̱� �Ⱥ��̱�
	float R, G, B;				// ����
	int move_dirrection;	// �»� ���� ���� ���
	RECT rect;
};

Shape shape[10];

int shape_cursor = 0;
int shape_make_mode = 0;	// 0 �簢�� 1 �ﰢ��
int animation_speed = 1000;

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

	for (int i = 0; i < 10; ++i) {
		if (shape[i].alive) {
			glColor4f(shape[i].R, shape[i].G, shape[i].B, 1);
			switch (shape[i].type) {
			case 0:
				glBegin(GL_POLYGON);
				glVertex2f(shape[i].rect.left - shape[i].size * 5, shape[i].rect.top + shape[i].size * 5);
				glVertex2f(shape[i].rect.left - shape[i].size * 5, shape[i].rect.bottom - shape[i].size * 5);
				glVertex2f(shape[i].rect.right + shape[i].size * 5, shape[i].rect.bottom - shape[i].size * 5);
				glVertex2f(shape[i].rect.right + shape[i].size * 5, shape[i].rect.top + shape[i].size * 5);
				glEnd();
				break;
			case 1:
				glBegin(GL_POLYGON);
				glVertex2f(((shape[i].rect.right + shape[i].size * 5)-(shape[i].rect.left - shape[i].size * 5))/2+ shape[i].rect.left - shape[i].size * 5, shape[i].rect.top + shape[i].size * 5);
				glVertex2f(shape[i].rect.left - shape[i].size * 5, shape[i].rect.bottom - shape[i].size * 5);
				glVertex2f(shape[i].rect.right + shape[i].size * 5, shape[i].rect.bottom - shape[i].size * 5);
				
				glEnd();
				break;
			}
			
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
	//�簢�� ����
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		shape[shape_cursor].alive = true;
		shape[shape_cursor].R = rand() % 255 / 255.0;
		shape[shape_cursor].G = rand() % 255 / 255.0;
		shape[shape_cursor].B = rand() % 255 / 255.0;

		shape[shape_cursor].size = rand() % 8 + 1;
		shape[shape_cursor].rect.left = x - 400;
		shape[shape_cursor].rect.right = shape[shape_cursor].rect.left + shape[shape_cursor].size * 5;
		shape[shape_cursor].rect.bottom = -1 * y + 300;
		shape[shape_cursor].rect.top = shape[shape_cursor].rect.bottom + shape[shape_cursor].size * 5;

		shape[shape_cursor].move_dirrection = rand() % 4;
		shape[shape_cursor].type = shape_make_mode;

		shape_cursor++;
		if (shape_cursor > 9)
			shape_cursor = 0;
	}
	glutPostRedisplay();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'r':
	case 'R':
		shape_make_mode = 0;
		break;
	case 't':
	case 'T':
		shape_make_mode = 1;
		break;
	}
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
		for (int i = 0; i < 10; ++i) {
			shape[i].R = 1.0 - (rand() % 255 / 255.0);
			shape[i].G = 1.0 - (rand() % 255 / 255.0);
			shape[i].B = 1.0 - (rand() % 255 / 255.0);
			if (shape[i].alive) {
				if (shape[i].bigger_size) {
					shape[i].size++;
					if (shape[i].size >= 5) {
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
		glutTimerFunc(1000 / 60, Timerfunction, 1);
		break;
	case 2:
		for (int i = 0; i < 10; ++i) {
			if (shape[i].alive) {
				switch (shape[i].move_dirrection) {
				case 0:
					shape[i].rect.left -= 3;
					shape[i].rect.right -= 3;
					shape[i].rect.top += 3;
					shape[i].rect.bottom += 3;
					if (shape[i].rect.top >= 300|| shape[i].rect.left <= -400) {
						shape[i].move_dirrection = 1;
					}
					break;
				case 1:
					shape[i].rect.left -= 3;
					shape[i].rect.right -= 3;
					shape[i].rect.top -= 3;
					shape[i].rect.bottom -= 3;
					if (shape[i].rect.left <= -400|| shape[i].rect.bottom <= -300) {
						shape[i].move_dirrection = 2;
					}
					break;
				case 2:
					shape[i].rect.left += 3;
					shape[i].rect.right += 3;
					shape[i].rect.top -= 3;
					shape[i].rect.bottom -= 3;
					if (shape[i].rect.bottom <= -300|| shape[i].rect.right >= 400) {
						shape[i].move_dirrection = 3;
					}
					break;
				case 3:
					shape[i].rect.left += 3;
					shape[i].rect.right += 3;
					shape[i].rect.top += 3;
					shape[i].rect.bottom += 3;
					if (shape[i].rect.right >= 400|| shape[i].rect.top >= 300) {
						shape[i].move_dirrection = 0;
					}
					break;
				}
				
			}
		}
		glutPostRedisplay();
		glutTimerFunc(animation_speed / 60, Timerfunction, 2);
		break;
	}
}