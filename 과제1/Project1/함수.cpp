#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

void CRun_time_Framework::Make_Tri()
{
	Tri* t = triangle;

	if (t == NULL) {
		t = (Tri*)malloc(sizeof(Tri));
		t->next = NULL;
		t->center_x = -430.0;
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
		t->center_x = -430.0;
		t->center_y = 250.0;
		t->size = 30;
		t->rotate = rand() % 360;
	}
}

void CRun_time_Framework::Draw_Tri()
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

void CRun_time_Framework::Delete_ScreenOut_Tri()
{
	Tri* t = triangle;
	if (t != NULL) {
		if (t->center_x > 400+t->size) {
			triangle = t->next;
			free(t);
		}
	}
}

void CRun_time_Framework::Update_Tri()
{
	Tri* t = triangle;
	while (t != NULL) {
		t->rotate += 0.1*(current_time - Prevtime);
		t->center_x += 0.05 * (current_time - Prevtime);
		t = t->next;
	}
}

void CRun_time_Framework::Make_Rect()
{
	Rect* t = rectangle;

	if (t == NULL) {
		t = (Rect*)malloc(sizeof(Rect));
		t->next = NULL;
		t->type = rand() % 2;
		t->size = 30;
		rectangle = t;
	}
	else {
		while (t->next != NULL)
			t = t->next;
		t->next = (Rect*)malloc(sizeof(Rect));
		t = t->next;
		t->next = NULL;
		t->size = 30;
		t->type = rand() % 2;
	}

	switch (t->type) {
	case 0:
		t->p[0].x = 30, t->p[0].y = -300;
		t->p[1].x = 30, t->p[1].y = -360;
		t->p[2].x = -30, t->p[2].y = -360;
		t->p[3].x = -30, t->p[3].y = -300;
		break;
	case 1:
		t->p[0].x = 0, t->p[0].y = -300;
		t->p[1].x = 30, t->p[1].y = -330;
		t->p[2].x = 0, t->p[2].y = -360;
		t->p[3].x = -30, t->p[3].y = -330;
		break;
	}
}

void CRun_time_Framework::Draw_Rect()
{
	Rect* t = rectangle;

	while (t != NULL) {
		glPushMatrix();

		glBegin(GL_POLYGON);
		glVertex2f(t->p[0].x, t->p[0].y);
		glVertex2f(t->p[1].x, t->p[1].y);
		glVertex2f(t->p[2].x, t->p[2].y);
		glVertex2f(t->p[3].x, t->p[3].y);
		glEnd();

		glPopMatrix();

		t = t->next;
	}
}

void CRun_time_Framework::Delete_ScreenOut_Rect()
{
	Rect* t = rectangle;
	if (t != NULL) {
		if (t->p[2].y > 300 + t->size) {
			rectangle = t->next;
			free(t);
		}
	}
}

void CRun_time_Framework::Delete_LineCollide_Rect()
{
}

void CRun_time_Framework::Update_Rect()
{
	Rect* t = rectangle;
	while (t != NULL) {
		for (int i = 0; i < 4; ++i) {
			t->p[i].y += 0.05 * (current_time - Prevtime);
		}
		t = t->next;
	}
}

void  CRun_time_Framework::Draw_Line()
{
	glBegin(GL_LINES);
	glVertex2f(line.x1, line.y1);
	glVertex2f(line.x2, line.y2);
	glEnd();
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

bool CRun_time_Framework::collide_Line_and_Line(float x1, float x2, float x3, float x4, float y1, float y2, float y3, float y4)
{
	float den = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);

	if (den != 0) {
		float ua, ub;
		ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / den;
		ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / den;
		if (ua < 1 && ua>0 && ub < 1 && ub>0)
			return true;
		else return false;
	}
	else return false;
}


