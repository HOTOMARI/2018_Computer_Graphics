#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

GLvoid CRun_time_Framework::Axis()
{
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(-400, 0, 0);
	glVertex3f(400, 0, 0);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 300, 0);
	glVertex3f(0, -300, 0);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, -400);
	glVertex3f(0, 0, 400);
	glEnd();

	return GLvoid();
}


GLvoid CRun_time_Framework::Draw_Field()
{
	for (int i = 3; i < point_num; i += 2) {
		// 곡면 제어점 설정 
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 4, 0.0, 1.0, 12, 3, &point[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);

		// 그리드를 이용한 곡면 드로잉 
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);

		// 선을 이용하여 그리드 연결 
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glPointSize(4.0); glColor3f(0.0, 0.0, 1.0);

		glBegin(GL_POINTS); 
		for (int k = 0; k < 3; k++) 
			for (int j = 0; j < 4; j++) 
			glVertex3fv(point[k][j]); 
		glEnd();

	}
	return GLvoid();
}

bool CRun_time_Framework::Collide(int mouse_x, int mouse_y, int point_i, int point_j)
{
	if (pow((point[point_i][point_j][0] - mouse_x), 2) + pow((point[point_i][point_j][2] - mouse_y), 2) < 400)
		return true;
	else return false;
}
