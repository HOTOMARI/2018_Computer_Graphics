#include "김호진.h"


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
		triangle = t;
	}
	else {
		while (t->next != NULL)
			t = t->next;
		t->next = (Tri*)malloc(sizeof(Tri));
		t = t->next;
		t->next = NULL;
	}
	t->live = true;
	t->center_x = -430.0;
	t->center_y = 250.0;
	t->size = 30;
	for (int i = 0; i < 3; ++i) {
		t->p[i].x = t->center_x + t->size*cos((90.0 + 120.0*i) / 180.0*PI);
		t->p[i].y = t->center_y + t->size*sin((90.0 + 120.0*i) / 180.0*PI);
	}
	t->rotate = rand() % 360;
}

void CRun_time_Framework::Draw_Tri()
{
	Tri* t = triangle;

	glColor3f(1, 1, 1);
	while (t != NULL) {
		glPushMatrix();

		if (t->live) {
			glBegin(GL_POLYGON);
			glVertex2f(t->p[0].x, t->p[0].y);
			glVertex2f(t->p[1].x, t->p[1].y);
			glVertex2f(t->p[2].x, t->p[2].y);
			glEnd();
		}

		glPopMatrix();

		t = t->next;
	}

	glBegin(GL_LINES);
	glVertex2f(-400, 200);
	glVertex2f(400, 200);
	glEnd();
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
		for (int i = 0; i < 3; ++i) {
			t->p[i].x = t->center_x + t->size*cos((90.0 + 120.0*i + t->rotate) / 180.0*PI);
			t->p[i].y = t->center_y + t->size*sin((90.0 + 120.0*i + t->rotate) / 180.0*PI);
		}
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
		rectangle = t;
	}
	else {
		while (t->next != NULL)
			t = t->next;
		t->next = (Rect*)malloc(sizeof(Rect));
		t = t->next;
		t->next = NULL;
		t->type = rand() % 2;
	}
	t->size = 30;
	t->live = true;
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
	glColor3f(1, 1, 1);

	while (t != NULL) {
		if (t->live) {
			glPushMatrix();

			glBegin(GL_POLYGON);
			glVertex2f(t->p[0].x, t->p[0].y);
			glVertex2f(t->p[1].x, t->p[1].y);
			glVertex2f(t->p[2].x, t->p[2].y);
			glVertex2f(t->p[3].x, t->p[3].y);
			glEnd();

			glPopMatrix();
		}
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

void CRun_time_Framework::Update_Rect()
{
	Rect* t = rectangle;
	while (t != NULL) {
		for (int i = 0; i < 4; ++i) {
			t->p[i].y += 0.1 * (current_time - Prevtime);
		}
		t = t->next;
	}
}

void CRun_time_Framework::Make_Fragments(Rect* t)
{
	switch (t->type) {
	case 0:
		if ((line.x2 - line.x1) / (line.y2 - line.y1) <= 1 &&
			(line.x2 - line.x1) / (line.y2 - line.y1) >= -1) {
			printf("세로 SLICE!!\n");
			fragments[0].live = true;

			fragments[0].p[0].x = t->p[0].x - 5;
			fragments[0].p[0].y = t->p[0].y;
			fragments[0].p[1].x = t->p[3].x - 5;
			fragments[0].p[1].y = t->p[3].y;
			fragments[0].p[2].x = t->p[2].x - 5;
			fragments[0].p[2].y = t->p[2].y;

			fragments[1].live = true;

			fragments[1].p[0].x = t->p[0].x + 5;
			fragments[1].p[0].y = t->p[0].y;
			fragments[1].p[1].x = t->p[2].x + 5;
			fragments[1].p[1].y = t->p[2].y;
			fragments[1].p[2].x = t->p[1].x + 5;
			fragments[1].p[2].y = t->p[1].y;
		}
		else {
			printf("가로 SLICE!!\n");
			fragments[0].live = true;

			fragments[0].p[0].x = t->p[3].x - 5;
			fragments[0].p[0].y = t->p[3].y;
			fragments[0].p[1].x = t->p[2].x - 5;
			fragments[0].p[1].y = t->p[2].y;
			fragments[0].p[2].x = t->p[1].x - 5;
			fragments[0].p[2].y = t->p[1].y;

			fragments[1].live = true;

			fragments[1].p[0].x = t->p[0].x + 5;
			fragments[1].p[0].y = t->p[0].y;
			fragments[1].p[1].x = t->p[3].x + 5;
			fragments[1].p[1].y = t->p[3].y;
			fragments[1].p[2].x = t->p[1].x + 5;
			fragments[1].p[2].y = t->p[1].y;
		}
		break;
	case 1:
		if ((line.x2 - line.x1) / (line.y2 - line.y1) <= 1 &&
			(line.x2 - line.x1) / (line.y2 - line.y1) >= -1) {
			printf("세로 SLICE!!\n");
			fragments[0].live = true;

			fragments[0].p[0].x = t->p[0].x - 5;
			fragments[0].p[0].y = t->p[0].y;
			fragments[0].p[1].x = t->p[3].x - 5;
			fragments[0].p[1].y = t->p[3].y;
			fragments[0].p[2].x = t->p[2].x - 5;
			fragments[0].p[2].y = t->p[2].y;

			fragments[1].live = true;

			fragments[1].p[0].x = t->p[0].x + 5;
			fragments[1].p[0].y = t->p[0].y;
			fragments[1].p[1].x = t->p[2].x + 5;
			fragments[1].p[1].y = t->p[2].y;
			fragments[1].p[2].x = t->p[1].x + 5;
			fragments[1].p[2].y = t->p[1].y;
		}
		else {
			printf("가로 SLICE!!\n");
			fragments[0].live = true;

			fragments[0].p[0].x = t->p[0].x - 5;
			fragments[0].p[0].y = t->p[0].y;
			fragments[0].p[1].x = t->p[3].x - 5;
			fragments[0].p[1].y = t->p[3].y;
			fragments[0].p[2].x = t->p[1].x - 5;
			fragments[0].p[2].y = t->p[1].y;

			fragments[1].live = true;

			fragments[1].p[0].x = t->p[1].x + 5;
			fragments[1].p[0].y = t->p[1].y;
			fragments[1].p[1].x = t->p[3].x + 5;
			fragments[1].p[1].y = t->p[3].y;
			fragments[1].p[2].x = t->p[2].x + 5;
			fragments[1].p[2].y = t->p[2].y;
		}
		break;
	}
	fragments[0].speed = 0;
	fragments[1].speed = 0;
}

void CRun_time_Framework::Draw_Fragments()
{
	glPushMatrix();

	for (int i = 0; i < 2; ++i) {
		if (fragments[i].live) {
			if (fragments[i].clicked == false) {
				glColor3f(1, 0, 0);
				glBegin(GL_POLYGON);
				for (float k = 0.0; k < 360.0; k += 1.0) {
					glVertex2f(30 * cos(k / 180.0*PI) + fragments[i].center_x,
						30 * sin(k / 180.0*PI) + fragments[i].center_y);
				}
				glEnd();
			}
			glColor3f(1, 1, 1);
			glBegin(GL_POLYGON);
			glVertex2f(fragments[i].p[0].x, fragments[i].p[0].y);
			glVertex2f(fragments[i].p[1].x, fragments[i].p[1].y);
			glVertex2f(fragments[i].p[2].x, fragments[i].p[2].y);
			glEnd();
		}
	}

	glPopMatrix();
}

void CRun_time_Framework::Update_Fragments()
{
	if (fragments[0].live) {
		if (fragments[0].clicked == false) {
			for (int i = 0; i < 3; ++i) {
				fragments[0].p[i].x -= 0.03 * (current_time - Prevtime);
				fragments[0].p[i].y -= fragments[0].speed * (current_time - Prevtime);
				if (fragments[0].p[i].y < -190) {
					fragments[0].live = false;
					Make_Trash();
					break;
				}
			}
			fragments[0].center_x = (fragments[0].p[0].x + fragments[0].p[1].x + fragments[0].p[2].x) / 3.0;
			fragments[0].center_y = (fragments[0].p[0].y + fragments[0].p[1].y + fragments[0].p[2].y) / 3.0;
			fragments[0].speed+=0.001 * (current_time - Prevtime);
		}
	}
	if (fragments[1].live) {
		if (fragments[1].clicked == false) {
			for (int i = 0; i < 3; ++i) {
				fragments[1].p[i].x += 0.03 * (current_time - Prevtime);
				fragments[1].p[i].y -= fragments[1].speed * (current_time - Prevtime);
				if (fragments[1].p[i].y < -190) {
					fragments[1].live = false;
					Make_Trash();
					break;
				}
			}
			fragments[1].center_x = (fragments[1].p[0].x + fragments[1].p[1].x + fragments[1].p[2].x) / 3.0;
			fragments[1].center_y = (fragments[1].p[0].y + fragments[1].p[1].y + fragments[1].p[2].y) / 3.0;
			fragments[1].speed += 0.002 * (current_time - Prevtime);
		}
	}
}

void CRun_time_Framework::Draw_Trash()
{
	glColor3f(1, 1, 0);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 20; ++j) {
			glBegin(GL_LINE_LOOP);
			glVertex2f(-400 + j * 40, -300 + i * 40);
			glVertex2f(-400 + (j + 1) * 40, -300 + i * 40);
			glVertex2f(-400 + (j + 1) * 40, -300 + (i + 1) * 40);
			glVertex2f(-400 + j * 40, -300 + (i + 1) * 40);
			glEnd();

			if (trash[i][j].fill) {
				glBegin(GL_POLYGON);
				glVertex2f(-400 + j * 40, -300 + i * 40);
				for (float k = 0.0; k < 360.0; k += 1.0) {
					glVertex2f(-400 + j * 40 + (40.0 / 360.0) * k,
						-300 + i * 40 + (trash[i][j].height-4.0) + 5.0*sin((k + trash[i][j].ani_stack * 10.0) / 180.0*PI));
				}
				glVertex2f(-400 + (j + 1) * 40, -300 + i * 40);
				glEnd();
			}
		}
	}
}

void CRun_time_Framework::Make_Trash()
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 20; ++j) {
			if (trash[i][j].fill == false) {
				trash[i][j].fill = true;
				return;
			}
		}
	}
}

void CRun_time_Framework::Update_Trash()
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 20; ++j) {
			if (trash[i][j].fill&&trash[i][j].height < 40) {
				trash[i][j].height += 0.02 * (current_time - Prevtime);
				if (trash[i][j].height > 40.0) {
					trash[i][j].height = 40.0;
				}
			}
			if (trash[i][j].fill)
				trash[i][j].ani_stack += 0.02 * (current_time - Prevtime);
		}
	}
}

void  CRun_time_Framework::Draw_Line()
{
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(line.x1, line.y1);
	glVertex2f(line.x2, line.y2);
	glEnd();
}

void CRun_time_Framework::Make_Star(float x, float y)
{
	Star* t = star;

	if (t == NULL) {
		t = (Star*)malloc(sizeof(Star));
		t->next = NULL;
		star = t;
	}
	else {
		while (t->next != NULL)
			t = t->next;
		t->next = (Star*)malloc(sizeof(Star));
		t = t->next;
		t->next = NULL;
	}
	t->T = 0;
	t->x = x;
	t->y = y;
	t->final_x = rand() % 800 - 400;
	t->final_y = rand() % 200 - 100;
	t->size = rand() % 20 + 30;
	t->R = rand() % 255 / 255.0;
	t->G = rand() % 255 / 255.0;
	t->B = rand() % 255 / 255.0;
}

void CRun_time_Framework::Draw_Star()
{
	Star* t = star;

	while (t != NULL) {
		glPushMatrix();

		glColor3f(t->R, t->G, t->B);
		glBegin(GL_POLYGON);
		for (int k = 0; k < 360; ++k) {
			if (k % 20 == 10) {
				glVertex2f(t->size*cos(k / 180.0*PI) + t->x, t->size*sin(k / 180.0*PI) + t->y);
			}
			else if(k % 20 == 0){
				glVertex2f((t->size-10)*cos(k / 180.0*PI) + t->x, (t->size - 10)*sin(k / 180.0*PI) + t->y);
			}
		}
		glEnd();

		glPopMatrix();

		t = t->next;
	}
}

void CRun_time_Framework::Update_Star()
{
	Star* t = star;
	while (t != NULL) {
		t->R = rand() % 255 / 255.0;
		t->G = rand() % 255 / 255.0;
		t->B = rand() % 255 / 255.0;
		
		if (t->final_x > t->x) {
			t->x = t->T*t->final_x + (1 - t->T)*t->x;
		}
		if (t->final_y < t->y) {
			t->y = t->T*t->final_y + (1 - t->T)*t->y;
		}
		t->T += 0.0001*(current_time - Prevtime);
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

bool CRun_time_Framework::collide_UpTri_and_Frag(Tri* t, Frag fragment)
{
	if((sqrt(pow(t->center_x - fragment.center_x, 2) + pow(t->center_y - fragment.center_y, 2)) < 30.0)&&
		t->live&&fragment.live)
		return true;
	else return false;
}


