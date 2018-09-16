#include <GL/freeglut.h>
#include<time.h>
GLvoid DrawScene();
GLvoid Reshape(int w, int h);

float R, G, B;
float garo, sero;

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

	srand(time(NULL));

	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}

GLvoid DrawScene() // ��� �Լ� 
{
	R = rand() % 100;		//�ʱ�� ����
	G = rand() % 100;
	B = rand() % 100;

	R = R / 255.0;
	G = G / 255.0;
	B = B / 255.0;

	garo = rand() % 10 + 5;	// �ʱ� ĭ ����
	sero = rand() % 10 + 5;

	glClearColor(R, G, B, 1); // �������� 'blue' �� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 


	for (int i = 0; i < sero; ++i) {
		for (int j = 0; j < garo; ++j) {
			glColor4f(R+0.05*j, G + 0.02*i, B + 0.02*i+0.05*j, 1);		//�簢��
			glRectf(-400.0 + ((800.0 / garo)*j), 300.0 - ((600.0 / sero)*i),
				(-400.0 + ((800.0 / garo)*(j + 1))), 300.0 - ((600.0 / sero)*(i + 1)));
		}
	}
	

	glFlush(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h) // �ٽ� �׸��� �Լ� 
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);
}