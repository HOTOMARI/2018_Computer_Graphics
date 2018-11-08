#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

GLvoid CRun_time_Framework::Draw_Points()
{
	glPointSize(4.0);
	for (int i = 0; i < point_num; ++i) {
		glBegin(GL_POINTS);
		glVertex2f(point[i][0], point[i][1]);
		glEnd();
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::Draw_Curve()
{
	for (int i = 3; i < point_num; i += 3) {

		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &point[i-3][0]);
		glEnable(GL_MAP1_VERTEX_3);

		glMapGrid1f(10.0, 0.0, 1.0);
		glEvalMesh1(GL_LINE, 0, 10);
		glDisable(GL_MAP1_VERTEX_3);

		for (int j = i - 3; j < i; ++j) {

			glPointSize(5.0);

			glBegin(GL_POINTS);
			glVertex3fv(&point[j][0]);

			glEnd();
		}
	}
	return GLvoid();
}

bool CRun_time_Framework::Collide(int mouse_x, int mouse_y, int point_i)
{
	if (pow((point[point_i][0] - mouse_x), 2) + pow((point[point_i][1] - mouse_y), 2) < 400)
		return true;
	else return false;
}