#include <GL/freeglut.h>
#include<time.h>
GLvoid DrawScene();
GLvoid Reshape(int w, int h);

struct Shape {
	int type;	// 0 �� 1 �ﰢ�� 2 �簢�� 3 ������
};

Shape shape[3][3];

bool type_set_mode = false;	//false ������  true ������
int type_set_num = 0;

void main(int argc, char** argv) // ������ ����ϰ� ����Լ� ���� 
{
	// �ʱ�ȭ �Լ��� 
	glutInit(&argc, argv); // glut �ʱ�ȭ 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ ���� 
	glutInitWindowSize(900, 600); // �������� ũ�� ���� 
	glutCreateWindow("Tiles"); // ������ ���� (������ �̸�) 
	glutDisplayFunc(DrawScene); // ��� �Լ��� ���� 
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �Լ� ���� 

	srand(time(NULL));

	type_set_num = rand() % 4;
	shape[0][0].type = type_set_num;	//ó�� ���� ����
	if (shape[0][0].type == 3) {
		type_set_mode = true;
	}

	for (int i = 0; i < 3; ++i)		// ������ ���� ����
		for (int j = 0; j < 3; ++j) 
			if (!(i == 0 && j == 0)) {		// ó���� ����
				if (type_set_mode) {		// ������
					shape[i][j].type = --type_set_num;
					if (type_set_num == 0)
						type_set_mode = false;
				}
				else {						// ������
					shape[i][j].type = ++type_set_num;
					if (type_set_num == 3) 
						type_set_mode = true;
				}
			}

	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}

GLvoid DrawScene() // ��� �Լ� 
{
	glClearColor(0, 0, 0, 1); // �������� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

	glColor4f(1, 1, 1, 1); //����
	for (int i = 1; i <= 2; ++i) {
		glBegin(GL_LINES);				// ����
		glVertex2f(-450 + i * 300, -300);
		glVertex2f(-450 + i * 300, 300);
		glEnd();
		glBegin(GL_LINES);				// ����
		glVertex2f(-450, -300 + 200 * i);
		glVertex2f(450, -300 + 200 * i);
		glEnd();
	}

	glPointSize(5);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			switch (shape[i][j].type) {
			case 0:
				glBegin(GL_LINES);
				glVertex2f(-450 + j * 300 + 50, 300 - i * 200 - 100);
				glVertex2f(-450 + j * 300 + 250, 300 - i * 200 - 100);
				glEnd();
				break;
			case 1:
				glBegin(GL_TRIANGLES);
				glVertex2f(-450 + j * 300 + 300 / 3, 300 - i * 200 - 150);
				glVertex2f(-450 + j * 300 + 300 / 3 * 2, 300 - i * 200 - 150);
				glVertex2f(-450 + j * 300 + 300 / 2, 300 - i * 200 - 50);
				glEnd();
				break;
			case 2:
				glBegin(GL_POLYGON);
				glVertex2f(-450 + j * 300 + 300 / 3, 300 - i * 200 - 150);
				glVertex2f(-450 + j * 300 + 300 / 3 * 2, 300 - i * 200 - 150);
				glVertex2f(-450 + j * 300 + 300 / 3 * 2, 300 - i * 200 - 50);
				glVertex2f(-450 + j * 300 + 300 / 3, 300 - i * 200 - 50);
				glEnd();
				break;
			case 3:
				glBegin(GL_POLYGON);
				glVertex2f(-450 + j * 300 + 300 / 5*2, 300 - i * 200 - 150);
				glVertex2f(-450 + j * 300 + 300 / 5*3, 300 - i * 200 - 150);
				glVertex2f(-450 + j * 300 + 300 / 3 * 2, 300 - i * 200 - 100);
				glVertex2f(-450 + j * 300 + 300 / 2, 300 - i * 200 - 50);
				glVertex2f(-450 + j * 300 + 300 / 3, 300 - i * 200 - 100);
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
	glOrtho(-450.0, 450.0, -300.0, 300.0, -1.0, 1.0);
}