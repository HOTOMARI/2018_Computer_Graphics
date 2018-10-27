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
		t->rt.bottom = -360;
		t->rt.top = -300;
		t->rt.left = -30;
		t->rt.right = 30;
		t->size = 30;
		t->type = rand() % 2;
		rectangle = t;
	}
	else {
		while (t->next != NULL)
			t = t->next;
		t->next = (Rect*)malloc(sizeof(Rect));
		t = t->next;
		t->next = NULL;
		t->rt.bottom = -360;
		t->rt.top = -300;
		t->rt.left = -30;
		t->rt.right = 30;
		t->size = 30;
		t->type = rand() % 2;
	}
}

void CRun_time_Framework::Draw_Rect()
{
	Rect* t = rectangle;

	while (t != NULL) {
		glPushMatrix();

		switch (t->type) {
		case 0:
			glBegin(GL_POLYGON);
			glVertex2f(t->rt.right, t->rt.top);
			glVertex2f(t->rt.right, t->rt.bottom);
			glVertex2f(t->rt.left, t->rt.bottom);
			glVertex2f(t->rt.left, t->rt.top);
			glEnd();
			break;
		case 1:
			glBegin(GL_POLYGON);
			glVertex2f(t->rt.right - 30, t->rt.top);
			glVertex2f(t->rt.right, t->rt.bottom + 30);
			glVertex2f(t->rt.left + 30, t->rt.bottom);
			glVertex2f(t->rt.left, t->rt.top - 30);
			glEnd();
			break;
		}

		glPopMatrix();

		t = t->next;
	}
}

void CRun_time_Framework::Delete_ScreenOut_Rect()
{
	Rect* t = rectangle;
	if (t != NULL) {
		if (t->rt.bottom > 300 + t->size) {
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
		t->rt.bottom += 0.05 * (current_time - Prevtime);
		t->rt.top += 0.05 * (current_time - Prevtime);
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


