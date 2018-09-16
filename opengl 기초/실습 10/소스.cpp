#include <GL/freeglut.h>
#include<time.h>

struct Shape {
	bool alive = false;			// ���̱� �Ⱥ��̱�
	bool morp_to_triangle = false;		// �ﰢ�� Ȱ��ȭ
	bool morp_to_rectangle = false;		// �簢�� Ȱ��ȭ
	float R, G, B;				// ����
	int tri_morp = 0;
	int move_dirrection;	// �»� ���� ���� ���
	int morp_stack;
	RECT rect;
};

GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Motion(int, int);
GLvoid Timerfunction(int);

bool collide_rec_rec(Shape, Shape);

Shape background_rect[30];
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
	glutTimerFunc(1000 / 60, Timerfunction, 2);	
	glutMouseFunc(Mouse);		// ���콺 ��ư �Է� �ޱ�
	glutMotionFunc(Motion);		// ���콺 ������ �Է¹ޱ�

	srand(time(NULL));

	// ��� �簢�� ����
	for (int i = 0; i < 30; ++i) {
		background_rect[i].alive = true;
		background_rect[i].R = rand() % 255 / 255.0;
		background_rect[i].G = rand() % 255 / 255.0;
		background_rect[i].B = rand() % 255 / 255.0;
		background_rect[i].rect.left = rand() % 800 - 400;
		background_rect[i].rect.right = background_rect[i].rect.left + 20;
		background_rect[i].rect.top = -1 * (rand() % 600) + 300;
		background_rect[i].rect.bottom = background_rect[i].rect.top - 20;
		background_rect[i].move_dirrection = rand() % 4;
	}

	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}

GLvoid DrawScene() // ��� �Լ� 
{
	glClearColor(0, 0, 0, 1); // �������� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

	//���簢��
	for (int i = 0; i < 30; ++i) {
		if (background_rect[i].alive) {
			glColor4f(background_rect[i].R, background_rect[i].G, background_rect[i].B, 1);
			glBegin(GL_POLYGON);
			glVertex2f(background_rect[i].rect.left, background_rect[i].rect.top);
			glVertex2f(background_rect[i].rect.left, background_rect[i].rect.bottom);
			glVertex2f(background_rect[i].rect.right, background_rect[i].rect.bottom+background_rect[i].tri_morp);
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
		for (int i = 0; i < 30; ++i) {
			if (background_rect[i].morp_to_rectangle == false && background_rect[i].morp_to_triangle==false&&background_rect[i].alive&&collide_rec_rec(background_rect[i], eraser_rect)) {
				background_rect[i].alive = background_rect[i].morp_to_triangle = true;
				background_rect[i].rect.left -= 5;
				background_rect[i].rect.right += 5;
				background_rect[i].rect.top += 5;
				background_rect[i].rect.bottom -= 5;
				background_rect[i].R = rand() % 255 / 255.0;
				background_rect[i].G = rand() % 255 / 255.0;
				background_rect[i].B = rand() % 255 / 255.0;
			}
		}
	}
}

GLvoid Timerfunction(int value) {
	switch (value) {
	case 1:
		for (int i = 0; i < 30; ++i) {
			if (background_rect[i].morp_to_triangle) {
				if (background_rect[i].tri_morp < 30) {
					background_rect[i].tri_morp++;
				}
				background_rect[i].morp_stack++;
				if (background_rect[i].morp_stack == 200) {
					background_rect[i].morp_to_rectangle = true;
					background_rect[i].morp_to_triangle = false;
				}
			}
			if (background_rect[i].morp_to_rectangle == true && background_rect[i].morp_to_triangle == false) {
				background_rect[i].morp_stack++;
				if (background_rect[i].morp_stack == 250) {
					background_rect[i].rect.left += 5;
					background_rect[i].rect.right -= 5;
					background_rect[i].rect.top -= 5;
					background_rect[i].rect.bottom += 5;
					background_rect[i].tri_morp = 20;
				}
				else if(background_rect[i].morp_stack >= 300&& background_rect[i].tri_morp>0){
					background_rect[i].tri_morp--;
					if (background_rect[i].tri_morp == 0) {
						background_rect[i].morp_to_rectangle = false;
						background_rect[i].morp_to_triangle = false;
						background_rect[i].morp_stack = 0;
					}
				}
			}
		}
		glutPostRedisplay();
		glutTimerFunc(1000 / 60, Timerfunction, 1);
		break;
	case 2:
		int move_x = 2;
		int move_y = 2;
		for (int i = 0; i < 30; ++i) {
			if (background_rect[i].alive) {
				switch (background_rect[i].move_dirrection) {
				case 0:
					background_rect[i].rect.left -= move_x;
					background_rect[i].rect.right -= move_x;
					background_rect[i].rect.top += move_y;
					background_rect[i].rect.bottom += move_y;
					if (background_rect[i].rect.top >= 300 || background_rect[i].rect.left <= -400) {
						if (rand() % 2) {
							background_rect[i].move_dirrection = 1;
						}
						else {
							background_rect[i].move_dirrection = 2;
						}
					}
					break;
				case 1:
					background_rect[i].rect.left -= move_x;
					background_rect[i].rect.right -= move_x;
					background_rect[i].rect.top -= move_y;
					background_rect[i].rect.bottom -= move_y;
					if (background_rect[i].rect.left <= -400 || background_rect[i].rect.bottom <= -300) {
						if (rand() % 2) {
							background_rect[i].move_dirrection = 2;
						}
						else {
							background_rect[i].move_dirrection = 3;
						}
					}
					break;
				case 2:
					background_rect[i].rect.left += move_x;
					background_rect[i].rect.right += move_x;
					background_rect[i].rect.top -= move_y;
					background_rect[i].rect.bottom -= move_y;
					if (background_rect[i].rect.bottom <= -300 || background_rect[i].rect.right >= 400) {
						if (rand() % 2) {
							background_rect[i].move_dirrection = 0;
						}
						else {
							background_rect[i].move_dirrection = 3;
						}
					}
					break;
				case 3:
					background_rect[i].rect.left += move_x;
					background_rect[i].rect.right += move_x;
					background_rect[i].rect.top += move_y;
					background_rect[i].rect.bottom += move_y;
					if (background_rect[i].rect.right >= 400 || background_rect[i].rect.top >= 300) {
						if (rand() % 2) {
							background_rect[i].move_dirrection = 0;
						}
						else {
							background_rect[i].move_dirrection = 1;
						}
					}
					break;
				}
			}
		}
		glutTimerFunc(1000 / 60, Timerfunction, 2);
	}
}

bool collide_rec_rec(Shape background, Shape eraser) {
	if (background.rect.left<eraser.rect.right&&background.rect.right>eraser.rect.left
		&&background.rect.top > eraser.rect.bottom&&background.rect.bottom < eraser.rect.top)
		return true;
	else return false;
}