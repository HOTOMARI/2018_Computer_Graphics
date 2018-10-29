#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
}


GLvoid CRun_time_Framework::QBEY()
{
	// ��
	glBegin(GL_QUADS);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(100, 100, 100);
	glVertex3f(-100, 100, 100);
	glVertex3f(-100, -100, 100);
	glVertex3f(100, -100, 100);
	glEnd();

	// ����
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(-100, 100, 100);
	glVertex3f(-100, 100, -100);
	glVertex3f(-100, -100, -100);
	glVertex3f(-100, -100, 100);
	glEnd();

	// ��
	glBegin(GL_QUADS);
	glColor3f(0.8, 0.8, 0.8);
	glVertex3f(100, 100, -100);
	glVertex3f(100, -100, -100);
	glVertex3f(-100, -100, -100);
	glVertex3f(-100, 100, -100);
	glEnd();

	// ����
	glBegin(GL_QUADS);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(100, 100, 100);
	glVertex3f(100, -100, 100);
	glVertex3f(100, -100, -100);
	glVertex3f(100, 100, -100);
	glEnd();

	// ��
	glBegin(GL_QUADS);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(100, 100, -100);
	glVertex3f(-100, 100, -100);
	glVertex3f(-100, 100, 100);
	glVertex3f(100, 100, 100);
	glEnd();

	// �Ʒ�
	glBegin(GL_QUADS);
	glColor3f(0.4, 0.4, 0.4);
	glVertex3f(100, -100, -100);
	glVertex3f(100, -100, 100);
	glVertex3f(-100, -100, 100);
	glVertex3f(-100, -100, -100);
	glEnd();
}

GLvoid CRun_time_Framework::Initial_Box()
{
	
}

GLvoid CRun_time_Framework::Box()
{
	return GLvoid();
}


bool CRun_time_Framework::collide(RECT A, RECT B)
{
	if (A.left > B.right)
		return false;
	if (A.right < B.left)
		return false;
	if (A.top < B.bottom)
		return false;
	if (A.bottom > B.top)
		return false;
	return true;
}


