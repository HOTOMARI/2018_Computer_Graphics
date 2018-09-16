#include <GL/freeglut.h>
GLvoid DrawScene ();
GLvoid Reshape (int w, int h);

void main (int argc, char** argv) // ������ ����ϰ� ����Լ� ���� 
{ 
// �ʱ�ȭ �Լ��� 
glutInit (&argc, argv); // glut �ʱ�ȭ 
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
glutInitWindowPosition ( 100, 100 ); // �������� ��ġ ���� 
glutInitWindowSize ( 800, 600 ); // �������� ũ�� ���� 
glutCreateWindow ( "Blue Window" ); // ������ ���� (������ �̸�) 
glutDisplayFunc ( DrawScene ); // ��� �Լ��� ���� 
glutReshapeFunc (Reshape); // �ٽ� �׸��� �Լ� ���� 
glutMainLoop (); // �̺�Ʈ ó�� ���� 
} 

GLvoid DrawScene ( ) // ��� �Լ� 
{ 
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // �������� 'blue' �� ���� 
	glClear( GL_COLOR_BUFFER_BIT ); // ������ ������ ��ü�� ĥ�ϱ� 

	glColor4f(0, 1, 0, 1);		//�簢��
	glRectf(-1, 0.8, -0.8, 1);
	glColor4f(1, 0, 1, 1);
	glRectf(0.8, 0.8, 1, 1);
	glColor4f(1, 1, 0, 1);
	glRectf(-1, -1, -0.8, -0.8);
	glColor4f(0, 1, 1, 1);
	glRectf(0.8, -0.8, 1, -1);

	glColor4f(1, 1, 1, 1); //����
	glBegin(GL_LINES);
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0, 1);
	glVertex2f(0, -1);
	glEnd();

	glColor4f(1, 0, 0, 1);		// �ﰢ��
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.2, -0.1);
	glVertex2f(0.2, -0.1);
	glVertex2f(0, 0.2);
	glEnd();
	glFlush(); // ȭ�鿡 ����ϱ� 
}

GLvoid Reshape(int w, int h) // �ٽ� �׸��� �Լ� 
{ 
	glViewport (0, 0, w, h); 
}