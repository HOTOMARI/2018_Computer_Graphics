#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
}

GLvoid CRun_time_Framework::Draw_Points()
{
	glColor3f(1, 1, 1);
	glPointSize(4.0);
	for (int i = 0; i < point_num; ++i) {
		glBegin(GL_POINTS);
		glVertex2f(point[i].x, point[i].y);
		glEnd();
	}
	return GLvoid();
}

