#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

void CRun_time_Framework::Make_Triangle()
{
	Tri* t = triangle;

	if (t == NULL) {
		t = (Tri*)malloc(sizeof(Tri));
		t->next = NULL;
		t->center_x = -400.0;
		t->center_y = 250.0;
		t->size = 30;
		t->rotate = rand() % 360;
		triangle = t;
	}
	else {
		while (t->next != NULL)
			t = t->next;
		t->next = (Tri*)malloc(sizeof(Tri));
		t = t->next;
		t->next = NULL;
		t->center_x = -400.0;
		t->center_y = 250.0;
		t->size = 30;
		t->rotate = rand() % 360;
	}
}

void CRun_time_Framework::Draw_Triangle()
{
	Tri* t = triangle;

	while (t != NULL) {
		glPushMatrix();

		glTranslatef(t->center_x, t->center_y, 0);
		glRotatef(t->rotate, 0, 0, 1);
		glBegin(GL_POLYGON);
		glVertex2f(t->size*cos(90.0 / 180.0 * PI), t->size*sin(90.0 / 180.0 * PI));
		glVertex2f(t->size*cos(210.0 / 180.0 * PI), t->size*sin(210.0 / 180.0 * PI));
		glVertex2f(t->size*cos(330.0 / 180.0 * PI), t->size*sin(330.0 / 180.0 * PI));
		glEnd();

		glPopMatrix();

		t = t->next;
	}
	
}

void CRun_time_Framework::Update_Triangle()
{
	Tri* t = triangle;
	while (t != NULL) {
		t->rotate += 0.1*(current_time - Prevtime);
		t->center_x += 0.05 * (current_time - Prevtime);
		t = t->next;
	}
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


