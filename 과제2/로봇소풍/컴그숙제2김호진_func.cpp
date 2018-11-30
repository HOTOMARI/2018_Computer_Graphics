#include "컴그숙제2김호진.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

GLvoid CRun_time_Framework::ground()
{
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(-400, -300, -400);
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (grounds[i][j].type == 0) {
				glColor3f(1.0, 1.0, 0.0);
			}
			else if (grounds[i][j].type == 1) {
				glColor3f(1.0, 1.0, 1.0);
			}
			else if (grounds[i][j].type == 2) {
				glColor3f(1.0, 0.0, 1.0);
			}
			glBegin(GL_POLYGON);
			glVertex3f((j + 1) * 80, 0, i * 80);
			glVertex3f((j + 1) * 80, 0, (i + 1) * 80);
			glVertex3f(j * 80, 0, (i + 1) * 80);
			glVertex3f(j * 80, 0, i * 80);
			glEnd();
		}
	}
	glPopMatrix();

	// 충돌바닥
	// 나무
	for (int i = 0; i < 10; ++i) {
		glColor3f(1, 0, 1);
		glBegin(GL_POLYGON);
		glVertex3f(object[i].left, -290, object[i].bottom);
		glVertex3f(object[i].left, -290, object[i].top);
		glVertex3f(object[i].right, -290, object[i].top);
		glVertex3f(object[i].right, -290, object[i].bottom);
		glEnd();
	}
	//로봇
	for (int i = 0; i < 2; ++i) {
		glColor3f(1, 1, 1);
		glBegin(GL_POLYGON);
		glVertex3f(Gridman[i].bb.left, -290, Gridman[i].bb.bottom);
		glVertex3f(Gridman[i].bb.left, -290, Gridman[i].bb.top);
		glVertex3f(Gridman[i].bb.right, -290, Gridman[i].bb.top);
		glVertex3f(Gridman[i].bb.right, -290, Gridman[i].bb.bottom);
		glEnd();
	}
	// 기둥
	for (int i = 0; i < set_pointsnum; ++i) {
		glColor3f(0, 0, 1);
		glBegin(GL_POLYGON);
		glVertex3f(pillar[i].left, -290, pillar[i].bottom);
		glVertex3f(pillar[i].left, -290, pillar[i].top);
		glVertex3f(pillar[i].right, -290, pillar[i].top);
		glVertex3f(pillar[i].right, -290, pillar[i].bottom);
		glEnd();
	}
	// 총알
	Bullet* t = bullets;
	glColor3f(0.8, 0, 0);
	while (t != NULL) {
		glBegin(GL_POLYGON);
		glVertex3f(t->bb.left, -290, t->bb.bottom);
		glVertex3f(t->bb.left, -290, t->bb.top);
		glVertex3f(t->bb.right, -290, t->bb.top);
		glVertex3f(t->bb.right, -290, t->bb.bottom);
		glEnd();
		t = t->next;
	}
}

GLvoid CRun_time_Framework::set_trees()
{
	int nums = 0;
	while (nums != 10) {
		int x = rand() % 10;
		int y = rand() % 10;
		if (grounds[y][x].type == 0) {
			grounds[y][x].type = 1;
			object[nums].left = x * 80 - 400 + 20;
			object[nums].right = object[nums].left + 40;
			object[nums].top = y * 80 - 400 + 20;
			object[nums].bottom = object[nums].top + 40;
			nums++;
		}
	}
}

GLvoid CRun_time_Framework::set_robots()
{
	int nums = 0;
	while (nums != 2) {
		int x = rand() % 10;
		int y = rand() % 10;
		if (grounds[y][x].type == 0) {
			Gridman[nums].position[0] = x * 80 - 360;
			Gridman[nums].position[1] = -200;
			Gridman[nums].position[2] = y * 80 - 360;
			Gridman[nums].dir = rand() % 4;
			nums++;
		}
	}
}

GLvoid CRun_time_Framework::Tree()
{
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			if (grounds[i][j].type == 1) {

				glPushMatrix();
				glTranslatef(j * 80 - 360, -250, i * 80 - 360);

				// 몸통
				glPushMatrix();
				glScalef(0.2, 1.0, 0.2);
				glColor3f(1, 0.5, 0.5);
				glutSolidCube(100);
				glColor3f(1, 1, 1);
				glutWireCube(100);
				glPopMatrix();

				// 머리
				glPushMatrix();
				glTranslatef(0, 50, 0);
				glColor3f(0, 1, 0);
				glutWireSphere(40, 10, 10);
				glPopMatrix();

				glPopMatrix();
			}
		}
	}
}

GLvoid CRun_time_Framework::Robot()
{
	for (int k = 0; k < 2; ++k) {
		glPushMatrix();
		if (!(k == 0 && nowCamera == 1)) {
			glTranslatef(Gridman[k].position[0], Gridman[k].position[1], Gridman[k].position[2]);
			glRotatef(Gridman[k].dir * 90, 0, 1, 0);
			// 머리
			glPushMatrix();
			if (k == 1)
				glColor3f(0, 0, 0);
			else
				glColor3f(0, 0.5, 0.5);
			glutSolidCube(30);
			glColor3f(1, 1, 1);
			glutWireCube(30);
			glPopMatrix();
			// 코
			glPushMatrix();
			glTranslatef(0, 0, 18);
			glColor3f(1, 1, 1);
			glutSolidCube(5);
			glColor3f(1, 1, 1);
			glutWireCube(5);
			glPopMatrix();
			// 몸통
			glPushMatrix();
			glTranslatef(0, -40, 0);
			glColor3f(0.5, 0.5, 0.5);
			glutSolidCube(50);
			glColor3f(1, 1, 1);
			glutWireCube(50);
			glPopMatrix();
			// 왼팔
			glPushMatrix();
			glTranslatef(-30, -10, 0);
			glRotatef(-Gridman[k].animation, 1, 0, 0);
			glTranslatef(0, -25, 0);
			glScalef(0.2, 1, 0.2);
			glColor3f(1, 0, 0);
			glutSolidCube(50);
			glColor3f(1, 1, 1);
			glutWireCube(50);
			glPopMatrix();
			// 오른팔
			glPushMatrix();
			glTranslatef(30, -10, 0);
			glRotatef(Gridman[k].animation, 1, 0, 0);
			glTranslatef(0, -25, 0);
			glScalef(0.2, 1, 0.2);
			glColor3f(0, 0, 1);
			glutSolidCube(50);
			glColor3f(1, 1, 1);
			glutWireCube(50);
			glPopMatrix();
			// 왼다리
			glPushMatrix();
			glTranslatef(-15, -50, 0);
			glRotatef(Gridman[k].animation, 1, 0, 0);
			glTranslatef(0, -25, 0);
			glScalef(0.3, 1, 0.3);
			glColor3f(1, 0, 1);
			glutSolidCube(50);
			glColor3f(1, 1, 1);
			glutWireCube(50);
			glPopMatrix();
			// 오른다리
			glPushMatrix();
			glTranslatef(15, -50, 0);
			glRotatef(-Gridman[k].animation, 1, 0, 0);
			glTranslatef(0, -25, 0);
			glScalef(0.3, 1, 0.3);
			glColor3f(0, 1, 1);
			glutSolidCube(50);
			glColor3f(1, 1, 1);
			glutWireCube(50);
			glPopMatrix();
			// 망토
			glPushMatrix();
			glTranslatef(0, -10, -60);
			// 곡면 제어점 설정
			glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &Gridman[k].cloak[0][0][0]);
			glEnable(GL_MAP2_VERTEX_3);
			// 그리드를 이용한 곡면 드로잉 
			glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
			// 면을 이용하여 그리드 연결 
			if (k == 1)
				glColor3f(0.0, 0.0, 1.0);
			else
				glColor3f(1.0, 0.0, 1.0);
			glEvalMesh2(GL_FILL, 0, 10, 0, 10);

			glPopMatrix();
		}
		glPopMatrix();
	}
}

GLvoid CRun_time_Framework::update_bb()
{
	for (int i = 0; i < 2; ++i) {
		Gridman[i].bb.left = Gridman[i].position[0] - 40;
		Gridman[i].bb.right = Gridman[i].position[0] + 40;
		Gridman[i].bb.top = Gridman[i].position[2] - 40;
		Gridman[i].bb.bottom = Gridman[i].position[2] + 40;
	}

	Bullet* t = bullets;
	while (t != NULL) {
		t->bb.left = t->position[0] - 5;
		t->bb.right = t->position[0] + 5;
		t->bb.top = t->position[2] - 5;
		t->bb.bottom = t->position[2] + 5;
		t = t->next;
	}
}

GLvoid CRun_time_Framework::update_robots()
{
	for (int i = 0; i < 2; ++i) {
		// 애니메이션
		if (Gridman[i].animation_state) {
			Gridman[i].animation += 0.2 * (current_time - Prevtime);
			Gridman[i].cloak[2][0][1] += 0.15 * (current_time - Prevtime);
			Gridman[i].cloak[2][2][1] -= 0.15 * (current_time - Prevtime);
			if (Gridman[i].animation > 60) {
				Gridman[i].animation_state = false;
			}
		}
		else {
			Gridman[i].animation -= 0.2 * (current_time - Prevtime);
			Gridman[i].cloak[2][0][1] -= 0.15 * (current_time - Prevtime);
			Gridman[i].cloak[2][2][1] += 0.15 * (current_time - Prevtime);
			if (Gridman[i].animation < -60) {
				Gridman[i].animation_state = true;
			}
		}

		//방향조절
		switch (Gridman[i].dir) {
		case 0:
			if (Gridman[i].state_collide) {
				Gridman[i].position[2] -= 0.2 * (current_time - Prevtime);
				Gridman[i].dir = rand() % 4;
			}
			else {
				Gridman[i].position[2] += 0.1 * (current_time - Prevtime);
			}
			if (Gridman[i].position[2] >= 360) {
				Gridman[i].position[2] = 360;
				Gridman[i].dir = rand() % 4;
			}
			break;
		case 1:
			if (Gridman[i].state_collide) {
				Gridman[i].position[0] -= 0.2 * (current_time - Prevtime);
				Gridman[i].dir = rand() % 4;
			}
			else {
				Gridman[i].position[0] += 0.1 * (current_time - Prevtime);
			}
			if (Gridman[i].position[0] >= 360) {
				Gridman[i].position[0] = 360;
				Gridman[i].dir = rand() % 4;
			}
			break;
		case 2:
			if (Gridman[i].state_collide) {
				Gridman[i].position[2] += 0.2 * (current_time - Prevtime);
				Gridman[i].dir = rand() % 4;
			}
			else {
				Gridman[i].position[2] -= 0.1 * (current_time - Prevtime);
			}
			if (Gridman[i].position[2] <= -360) {
				Gridman[i].position[2] = -360;
				Gridman[i].dir = rand() % 4;
			}
			break;
		case 3:
			if (Gridman[i].state_collide) {
				Gridman[i].position[0] += 0.2 * (current_time - Prevtime);
				Gridman[i].dir = rand() % 4;
			}
			else {
				Gridman[i].position[0] -= 0.1 * (current_time - Prevtime);
			}
			if (Gridman[i].position[0] <= -360) {
				Gridman[i].position[0] = -360;
				Gridman[i].dir = rand() % 4;
			}
			break;
		}
	}
}

GLvoid CRun_time_Framework::go_comb()
{
	if (combined) {
		Gridman[1].position[0] = comb_t * (Gridman[0].position[0]) + (1 - comb_t)*(Gridman[0].position[0]);
		Gridman[1].position[1] = comb_t * -120 + (1 - comb_t) * -120;
		Gridman[1].position[2] = comb_t * (Gridman[0].position[2]) + (1 - comb_t)*(Gridman[0].position[2]);
		comb_t += 0.001*(current_time - Prevtime);
		if (comb_t >= 1.0) {
			Gridman[1].position[0] = Gridman[0].position[0];
			Gridman[1].position[2] = Gridman[0].position[2];
		}
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::make_bullet(int Rindex)
{
	if (bullets == NULL) {
		bullets = (Bullet*)malloc(sizeof(Bullet));
		for (int i = 0; i < 3; ++i) {
			bullets->position[i] = Gridman[Rindex].position[i];
		}
		bullets->owner = Rindex;
		bullets->dir = Gridman[Rindex].dir;
		bullets->hit = false;
		bullets->next = NULL;
	}
	else {
		Bullet* t;
		t = bullets;
		while (t->next != NULL) {
			t = t->next;
		}
		t->next = (Bullet*)malloc(sizeof(Bullet));
		t = t->next;
		for (int i = 0; i < 3; ++i) {
			t->position[i] = Gridman[Rindex].position[i];
		}
		t->owner = Rindex;
		t->dir = Gridman[Rindex].dir;
		t->hit = false;
		t->next = NULL;
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::update_bullets()
{
	Bullet* t = bullets;
	while (t != NULL) {
		switch (t->dir) {
		case 0:
			t->position[2] += 0.3 * (current_time - Prevtime);
			break;
		case 1:
			t->position[0] += 0.3 * (current_time - Prevtime);
			break;
		case 2:
			t->position[2] -= 0.3 * (current_time - Prevtime);
			break;
		case 3:
			t->position[0] -= 0.3 * (current_time - Prevtime);
			break;
		}
		t = t->next;
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::draw_bullets()
{
	Bullet* t = bullets;

	glColor3f(0.8, 0, 0);
	while (t != NULL) {
		glPushMatrix();
		glTranslatef(t->position[0], t->position[1], t->position[2]);
		glutSolidSphere(5, 3, 3);
		glPopMatrix();
		t = t->next;
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::delete_bullets()
{
	Bullet* t = bullets;
	Bullet* before = bullets;

	while (t != NULL) {
		if (t->hit && t == bullets) {
			bullets = t->next;
			delete(t);
			t = bullets;
			before = bullets;
		}
		else if (t->hit && t != bullets) {
			before->next = t->next;
			delete(t);
			t = before->next;
		}
		else {
			before = t;
			t = t->next;
		}
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::draw_points()
{
	glColor3f(0.7, 0, 0.7);
	for (int i = 0; i < set_pointsnum; ++i) {
		glPushMatrix();
		glTranslatef(point[i][0], point[i][1], point[i][2]);
		glutSolidSphere(20, 10, 10);
		glPopMatrix();
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::draw_pillars()
{
	for (int i = 0; i < set_pointsnum; ++i) {
		float height = point[i][1] + 300;
		glPushMatrix();
		glTranslatef(point[i][0], (height/2)-300, point[i][2]);
		glScalef(40, height, 40);
		glColor3f(0, 0, 1);
		glutSolidCube(1);
		glColor3f(1, 1, 1);
		glutWireCube(1);
		glPopMatrix();
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::draw_rails()
{
	if (set_pointsnum >= 2) {
		glColor3f(0.0, 0, 1.0);
		for (int i = 0; i < set_pointsnum; ++i) {
			float tmpCP[3];
			if (i != set_pointsnum - 1) {
				tmpCP[0] = (point[i + 1][0] - point[i][0]) / 2.0 + point[i][0];
				tmpCP[1] = (point[i + 1][1] - point[i][1]) / 2.0 + point[i][1];
				if (point[i + 1][2]> point[i][2]) {
					tmpCP[2] = (point[i + 1][2] - point[i][2]) / 2.0 + point[i][2] + 100;
				}
				else {
					tmpCP[2] = (point[i + 1][2] - point[i][2]) / 2.0 + point[i][2] - 100;
				}
				for (float t = 0.0; t < 1.00; t += 0.05) {
					glBegin(GL_LINES);
					glVertex3f(calc_Bezier(point[i][0], tmpCP[0], point[i + 1][0], t),
						calc_Bezier(point[i][1], tmpCP[1], point[i + 1][1], t),
						calc_Bezier(point[i][2], tmpCP[2], point[i + 1][2], t));

					glVertex3f(calc_Bezier(point[i][0], tmpCP[0], point[i + 1][0], t + 0.05),
						calc_Bezier(point[i][1], tmpCP[1], point[i + 1][1], t + 0.05),
						calc_Bezier(point[i][2], tmpCP[2], point[i + 1][2], t + 0.05));

					glEnd();
				}
			}
			else {
				tmpCP[0] = (point[0][0] - point[i][0]) / 2.0 + point[i][0];
				tmpCP[1] = (point[0][1] - point[i][1]) / 2.0 + point[i][1];
				if (i % 2) {
					tmpCP[2] = (point[0][2] - point[i][2]) / 2.0 + point[i][2] - 100;
				}
				else {
					tmpCP[2] = (point[0][2] - point[i][2]) / 2.0 + point[i][2] + 100;
				}
				for (float t = 0.0; t < 1.00; t += 0.05) {
					glBegin(GL_LINES);
					glVertex3f(calc_Bezier(point[i][0], tmpCP[0], point[0][0], t),
						calc_Bezier(point[i][1], tmpCP[1], point[0][1], t),
						calc_Bezier(point[i][2], tmpCP[2], point[0][2], t));

					glVertex3f(calc_Bezier(point[i][0], tmpCP[0], point[0][0], t + 0.05),
						calc_Bezier(point[i][1], tmpCP[1], point[0][1], t + 0.05),
						calc_Bezier(point[i][2], tmpCP[2], point[0][2], t + 0.05));

					glEnd();
				}
			}
		}


		glLineWidth(5.0);
		glPushMatrix();
		glColor3f(0.0, 1.0, 1.0);
		glScalef(1.1, 1.0, 1.1);
		for (int i = 0; i < set_pointsnum; ++i) {
			float tmpCP[3];
			if (i != set_pointsnum - 1) {
				tmpCP[0] = (point[i + 1][0] - point[i][0]) / 2.0 + point[i][0];
				tmpCP[1] = (point[i + 1][1] - point[i][1]) / 2.0 + point[i][1];
				if (point[i + 1][2] > point[i][2]) {
					tmpCP[2] = (point[i + 1][2] - point[i][2]) / 2.0 + point[i][2] + 100;
				}
				else {
					tmpCP[2] = (point[i + 1][2] - point[i][2]) / 2.0 + point[i][2] - 100;
				}
				for (float t = 0.0; t < 1.00; t += 0.05) {
					glBegin(GL_LINES);
					glVertex3f(calc_Bezier(point[i][0], tmpCP[0], point[i + 1][0], t),
						calc_Bezier(point[i][1], tmpCP[1], point[i + 1][1], t),
						calc_Bezier(point[i][2], tmpCP[2], point[i + 1][2], t));

					glVertex3f(calc_Bezier(point[i][0], tmpCP[0], point[i + 1][0], t + 0.05),
						calc_Bezier(point[i][1], tmpCP[1], point[i + 1][1], t + 0.05),
						calc_Bezier(point[i][2], tmpCP[2], point[i + 1][2], t + 0.05));

					glEnd();
				}
			}
			else {
				tmpCP[0] = (point[0][0] - point[i][0]) / 2.0 + point[i][0];
				tmpCP[1] = (point[0][1] - point[i][1]) / 2.0 + point[i][1];
				if (i % 2) {
					tmpCP[2] = (point[0][2] - point[i][2]) / 2.0 + point[i][2] - 100;
				}
				else {
					tmpCP[2] = (point[0][2] - point[i][2]) / 2.0 + point[i][2] + 100;
				}
				for (float t = 0.0; t < 1.00; t += 0.05) {
					glBegin(GL_LINES);
					glVertex3f(calc_Bezier(point[i][0], tmpCP[0], point[0][0], t),
						calc_Bezier(point[i][1], tmpCP[1], point[0][1], t),
						calc_Bezier(point[i][2], tmpCP[2], point[0][2], t));

					glVertex3f(calc_Bezier(point[i][0], tmpCP[0], point[0][0], t + 0.05),
						calc_Bezier(point[i][1], tmpCP[1], point[0][1], t + 0.05),
						calc_Bezier(point[i][2], tmpCP[2], point[0][2], t + 0.05));

					glEnd();
				}
			}
		}
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0, 1.0, 1.0);
		glScalef(0.9, 1.0, 0.9);
		for (int i = 0; i < set_pointsnum; ++i) {
			float tmpCP[3];
			if (i != set_pointsnum - 1) {
				tmpCP[0] = (point[i + 1][0] - point[i][0]) / 2.0 + point[i][0];
				tmpCP[1] = (point[i + 1][1] - point[i][1]) / 2.0 + point[i][1];
				if (point[i + 1][2] > point[i][2]) {
					tmpCP[2] = (point[i + 1][2] - point[i][2]) / 2.0 + point[i][2] + 100;
				}
				else {
					tmpCP[2] = (point[i + 1][2] - point[i][2]) / 2.0 + point[i][2] - 100;
				}
				for (float t = 0.0; t < 1.00; t += 0.05) {
					glBegin(GL_LINES);
					glVertex3f(calc_Bezier(point[i][0], tmpCP[0], point[i + 1][0], t),
						calc_Bezier(point[i][1], tmpCP[1], point[i + 1][1], t),
						calc_Bezier(point[i][2], tmpCP[2], point[i + 1][2], t));

					glVertex3f(calc_Bezier(point[i][0], tmpCP[0], point[i + 1][0], t + 0.05),
						calc_Bezier(point[i][1], tmpCP[1], point[i + 1][1], t + 0.05),
						calc_Bezier(point[i][2], tmpCP[2], point[i + 1][2], t + 0.05));

					glEnd();
				}
			}
			else {
				tmpCP[0] = (point[0][0] - point[i][0]) / 2.0 + point[i][0];
				tmpCP[1] = (point[0][1] - point[i][1]) / 2.0 + point[i][1];
				if (i % 2) {
					tmpCP[2] = (point[0][2] - point[i][2]) / 2.0 + point[i][2] - 100;
				}
				else {
					tmpCP[2] = (point[0][2] - point[i][2]) / 2.0 + point[i][2] + 100;
				}
				for (float t = 0.0; t < 1.00; t += 0.05) {
					glBegin(GL_LINES);
					glVertex3f(calc_Bezier(point[i][0], tmpCP[0], point[0][0], t),
						calc_Bezier(point[i][1], tmpCP[1], point[0][1], t),
						calc_Bezier(point[i][2], tmpCP[2], point[0][2], t));

					glVertex3f(calc_Bezier(point[i][0], tmpCP[0], point[0][0], t + 0.05),
						calc_Bezier(point[i][1], tmpCP[1], point[0][1], t + 0.05),
						calc_Bezier(point[i][2], tmpCP[2], point[0][2], t + 0.05));

					glEnd();
				}
			}
		}
		glPopMatrix();

		if (play_mode == 2) {
			glLineWidth(10.0);
			glColor3f(0.5, 0.5, 0.5);
			{
				float tmpCP[3];

				tmpCP[0] = (point[tunnel + 1][0] - point[tunnel][0]) / 2.0 + point[tunnel][0];
				tmpCP[1] = (point[tunnel + 1][1] - point[tunnel][1]) / 2.0 + point[tunnel][1];
				if (point[tunnel + 1][2] > point[tunnel][2]) {
					tmpCP[2] = (point[tunnel + 1][2] - point[tunnel][2]) / 2.0 + point[tunnel][2] + 100;
				}
				else {
					tmpCP[2] = (point[tunnel + 1][2] - point[tunnel][2]) / 2.0 + point[tunnel][2] - 100;
				}

				for (float t = 0.3; t < 0.7; t += 0.01) {
					glPushMatrix();
					double chk = acos((point[tunnel+1][0] - point[tunnel][0]) / sqrt(pow((point[tunnel + 1][0] - point[tunnel][0]), 2) + pow((point[tunnel + 1][1] - point[tunnel][1]), 2) + pow((point[tunnel + 1][2] - point[tunnel][2]), 2))) * 180 / PI;
					glTranslatef(calc_Bezier(point[tunnel][0], tmpCP[0], point[tunnel + 1][0], t),
						calc_Bezier(point[tunnel][1], tmpCP[1], point[tunnel + 1][1], t),
						calc_Bezier(point[tunnel][2], tmpCP[2], point[tunnel + 1][2], t));
					if ((point[tunnel + 1][2] - point[tunnel][2]) <= 0) {
						glRotatef(chk+90, 0, 1, 0);
					}
					else {
						glRotatef(-chk+90, 0, 1, 0);
					}
					glBegin(GL_LINES);
					for (float r = 0; r < 360; r+=0.5) {
						glVertex3f(100 * cos(r / 180.0*PI), 100 * sin(r / 180.0*PI), 0);
						glVertex3f(100 * cos((r + 0.5) / 180.0*PI), 100 * sin((r + 0.5) / 180.0*PI), 0);
					}
					glEnd();
					glPopMatrix();
				}

			}
			
		}
	}

	glLineWidth(1.0);
	return GLvoid();
}

GLvoid CRun_time_Framework::draw_carts()
{
	for (int i = 0; i < 3; ++i) {
		glPushMatrix();
		glTranslatef(cart[i].pos[0], cart[i].pos[1], cart[i].pos[2]);
		glMultMatrixf(cart[i].identity);
		glColor3f(1, 0, 0);
		glutSolidCube(50);
		glTranslatef(30, 0, 0);
		glColor3f(1, 1, 1);
		glutSolidSphere(20, 5, 5);
		glPopMatrix();
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::update_carts()
{
	for (int k = 0; k < 3; ++k) {
		
		if (point[cart[k].nowline][1] <= point[(cart[k].nowline + 1) % set_pointsnum][1])
			cart[k].t += 0.0002 * (current_time - Prevtime);
		else
			cart[k].t += 0.0007 * (current_time - Prevtime);
		
		if (cart[k].t >= 1.0) {
			cart[k].nowline++;
			cart[k].nowline = cart[k].nowline%set_pointsnum;
			cart[k].t = 0.0;
		}

		if (set_pointsnum >= 2) {
			int i = cart[k].nowline;

			float tmpCP[3];
			float tmpPOS[3];

			tmpPOS[0] = cart[k].pos[0];
			tmpPOS[1] = cart[k].pos[1];
			tmpPOS[2] = cart[k].pos[2];

			if (i != set_pointsnum - 1) {
				tmpCP[0] = (point[i + 1][0] - point[i][0]) / 2.0 + point[i][0];
				tmpCP[1] = (point[i + 1][1] - point[i][1]) / 2.0 + point[i][1];
				if (point[i + 1][2] > point[i][2]) {
					tmpCP[2] = (point[i + 1][2] - point[i][2]) / 2.0 + point[i][2] + 100;
				}
				else {
					tmpCP[2] = (point[i + 1][2] - point[i][2]) / 2.0 + point[i][2] - 100;
				}
				float t = cart[k].t;
				cart[k].pos[0] = calc_Bezier(point[i][0], tmpCP[0], point[i + 1][0], t);
				cart[k].pos[1] = calc_Bezier(point[i][1], tmpCP[1], point[i + 1][1], t);
				cart[k].pos[2] = calc_Bezier(point[i][2], tmpCP[2], point[i + 1][2], t);

				if (k == 0) {
					cart_nextP[0] = calc_Bezier(point[i][0], tmpCP[0], point[i + 1][0], t + 0.1);
					cart_nextP[1] = calc_Bezier(point[i][1], tmpCP[1], point[i + 1][1], t + 0.1);
					cart_nextP[2] = calc_Bezier(point[i][2], tmpCP[2], point[i + 1][2], t + 0.1);
				}

			}

			else {
				tmpCP[0] = (point[0][0] - point[i][0]) / 2.0 + point[i][0];
				tmpCP[1] = (point[0][1] - point[i][1]) / 2.0 + point[i][1];
				if (i % 2) {
					tmpCP[2] = (point[0][2] - point[i][2]) / 2.0 + point[i][2] - 100;
				}
				else {
					tmpCP[2] = (point[0][2] - point[i][2]) / 2.0 + point[i][2] + 100;
				}
				float t = cart[k].t;
				cart[k].pos[0] = calc_Bezier(point[i][0], tmpCP[0], point[0][0], t);
				cart[k].pos[1] = calc_Bezier(point[i][1], tmpCP[1], point[0][1], t);
				cart[k].pos[2] = calc_Bezier(point[i][2], tmpCP[2], point[0][2], t);

				if (k == 0) {
					cart_nextP[0] = calc_Bezier(point[i][0], tmpCP[0], point[0][0], t + 0.1);
					cart_nextP[1] = calc_Bezier(point[i][1], tmpCP[1], point[0][1], t + 0.1);
					cart_nextP[2] = calc_Bezier(point[i][2], tmpCP[2], point[0][2], t + 0.1);
				}
			}

			memset(cart[k].identity, 0, sizeof(cart[k].identity));
			cart[k].identity[0] = cart[k].identity[5] = cart[k].identity[10] = cart[k].identity[15] = 1;

			glPushMatrix();
			{
				float vec[3] = { (cart[k].pos[0] - tmpPOS[0]) ,(cart[k].pos[1] - tmpPOS[1]) ,(cart[k].pos[2] - tmpPOS[2]) };
				float sizeofvec = sqrt(pow(vec[0], 2) + pow(vec[1], 2) + pow(vec[2], 2));
				float degree = acos(vec[0] / sizeofvec) * 180 / PI;
				 
				glRotatef( - degree, 0, vec[2] / sqrt(pow(vec[1], 2) + pow(vec[2], 2)), -vec[1] / sqrt(pow(vec[1], 2) + pow(vec[2], 2)));

				glMultMatrixf(cart[k].identity);
				glGetFloatv(GL_MODELVIEW_MATRIX, cart[k].identity);
			}
			glPopMatrix();


		

		}

	}
	return GLvoid();
}

GLvoid CRun_time_Framework::Make_Snow()
{
	if (snow == NULL) {
		snow = (Snow*)malloc(sizeof(Snow));
		snow->height = 2000;
		snow->x = rand() % 50;
		snow->y = rand() % 50;
		snow->speed = 1.0;
		snow->next = NULL;
	}
	else {
		Snow* t;
		t = snow;
		while (t->next != NULL) {
			t = t->next;
		}
		t->next = (Snow*)malloc(sizeof(Snow));
		t = t->next;
		t->height = 2000;
		t->x = rand() % 50;
		t->y = rand() % 50;
		t->speed = 1.0;
		t->next = NULL;
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::UpdateSnow()
{
	Snow* t = snow;
	while (t != NULL) {
		t->height -= t->speed*(current_time - Prevtime);
		t = t->next;
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::Draw_Snow()
{
	Snow* t = snow;

	while (t != NULL) {
		glPushMatrix();
		if (weather == 1) {
			glColor3f(1, 1, 1);
			glPointSize(5);
			glTranslatef(t->x * 16 - 400, t->height, t->y * 16 - 400);
			glBegin(GL_POINTS);
			glVertex3f(0, 0, 0);
			glEnd();
		}
		else if (weather == 2) {
			glColor3f(0, 0, 1);
			glTranslatef(t->x * 16 - 400, t->height, t->y * 16 - 400);
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(0, -150, 0);
			glEnd();
		}
		glPopMatrix();
		t = t->next;
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::Delete_Snow()
{
	Snow* t = snow;
	Snow* before = snow;

	while (t != NULL) {
		if (t->height < -300 && t == snow) {
			snow = t->next;
			delete(t);
			t = snow;
			before = snow;
		}
		else if (t->height < -300 && t != snow) {
			before->next = t->next;
			delete(t);
			t = before->next;
		}
		else {
			before = t;
			t = t->next;
		}
	}
	return GLvoid();
}

float CRun_time_Framework::calc_Bezier(float S, float M, float E, float T)
{
	float result;
	result = pow(1 - T, 2)*S + 2 * T*(1 - T)*M + pow(T, 2)*E;

	return result;
}

bool CRun_time_Framework::collide(RECT A, RECT B)
{
	if (A.left > B.right)
		return false;
	if (A.right < B.left)
		return false;
	if (-A.top < -B.bottom)
		return false;
	if (-A.bottom > -B.top)
		return false;
	return true;
}

GLubyte * CRun_time_Framework::LoadDIBitmap(const char *filename, BITMAPINFO ** info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	// 바이너리 읽기 모드로 파일을 연다 
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;

	// 비트맵 파일 헤더를 읽는다. 
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}

	// 파일이 BMP 파일인지 확인한다. 
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	// BITMAPINFOHEADER 위치로 간다. 
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다. 
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}

	// 비트맵 인포 헤더를 읽는다. 
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵의 크기 설정 
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 *  abs((*info)->bmiHeader.biHeight);

	// 비트맵의 크기만큼 메모리를 할당한다. 
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다. 
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info);
		free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}

GLvoid CRun_time_Framework::set_texture()
{
	// n개의 이미지 텍스처 매핑을 한다.
	glGenTextures(6, texture);

	//텍스처와 객체를 결합한다. --- (1) 
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	//이미지 로딩을 한다. --- (2) 
	pBytes = LoadDIBitmap("Skybox0.bmp", &info);

	//텍스처 설정 정의를 한다. --- (3) 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	//텍스처 파라미터 설정 --- (4) 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 텍스처 모드 설정 
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// 나머지 n-1개의 텍스처에도 (1) ~ (4)까지의 과정을 진행하여 텍스처를 설정한다.
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	pBytes = LoadDIBitmap("Skybox1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	pBytes = LoadDIBitmap("Skybox2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	pBytes = LoadDIBitmap("Pilar0.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	pBytes = LoadDIBitmap("Pilar1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	pBytes = LoadDIBitmap("Pilar2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	return GLvoid();
}

GLvoid CRun_time_Framework::Skybox()
{
	glBindTexture(GL_TEXTURE_2D, texture[weather]);
	// 앞
	glBegin(GL_QUADS);
	glTexCoord2f(4.0 / 4.0, 1.0 / 3.0); // 텍스처 위치 설정 
	glVertex3f(2000, 2000, 2000);
	glTexCoord2f(3.0 / 4.0, 1.0 / 3.0); // 텍스처 위치 설정 
	glVertex3f(-2000, 2000, 2000);
	glTexCoord2f(3.0 / 4.0, 2.0 / 3.0); // 텍스처 위치 설정 
	glVertex3f(-2000, -2000, 2000);
	glTexCoord2f(4.0 / 4.0, 2.0 / 3.0); // 텍스처 위치 설정 
	glVertex3f(2000, -2000, 2000);
	glEnd();

	// 왼쪽
	glBegin(GL_QUADS);
	glTexCoord2f(3.0 / 4.0, 1.0 / 3.0);
	glVertex3f(-2000, 2000, 2000);
	glTexCoord2f(2.0 / 4.0, 1.0 / 3.0);
	glVertex3f(-2000, 2000, -2000);
	glTexCoord2f(2.0 / 4.0, 2.0 / 3.0);
	glVertex3f(-2000, -2000, -2000);
	glTexCoord2f(3.0 / 4.0, 2.0 / 3.0);
	glVertex3f(-2000, -2000, 2000);
	glEnd();

	// 뒤
	glBegin(GL_QUADS);
	glTexCoord2f(2.0 / 4.0, 1.0 / 3.0);
	glVertex3f(-2000, 2000, -2000);
	glTexCoord2f(1.0 / 4.0, 1.0 / 3.0);
	glVertex3f(2000, 2000, -2000);
	glTexCoord2f(2.0 / 4.0, 2.0 / 3.0);
	glVertex3f(2000, -2000, -2000);
	glTexCoord2f(1.0 / 4.0, 2.0 / 3.0);
	glVertex3f(-2000, -2000, -2000);
	glEnd();

	// 오른
	glBegin(GL_QUADS);
	glTexCoord2f(1.0 / 4.0, 1.0 / 3.0);
	glVertex3f(2000, 2000, -2000);
	glTexCoord2f(0.0 / 4.0, 1.0 / 3.0);
	glVertex3f(2000, 2000, 2000);
	glTexCoord2f(0.0 / 4.0, 2.0 / 3.0);
	glVertex3f(2000, -2000, 2000);
	glTexCoord2f(1.0 / 4.0, 2.0 / 3.0);
	glVertex3f(2000, -2000, -2000);
	glEnd();

	// 위
	glBegin(GL_QUADS);
	glTexCoord2f(1.0 / 4.0, 1.0 / 3.0);
	glVertex3f(2000, 2000, -2000);

	glTexCoord2f(2.0 / 4.0, 1.0 / 3.0);
	glVertex3f(-2000, 2000, -2000);

	glTexCoord2f(2.0 / 4.0, 0.0 / 3.0);
	glVertex3f(-2000, 2000, 2000);

	glTexCoord2f(1.0 / 4.0, 0.0 / 3.0);
	glVertex3f(2000, 2000, 2000);
	glEnd();

	// 아래
	glBegin(GL_QUADS);
	glTexCoord2f(2.0 / 4.0, 2.0 / 3.0);
	glVertex3f(-2000, -2000, -2000);
	glTexCoord2f(1.0 / 4.0, 2.0 / 3.0);
	glVertex3f(2000, -2000, -2000);
	glTexCoord2f(1.0 / 4.0, 3.0 / 3.0);
	glVertex3f(2000, -2000, 2000);
	glTexCoord2f(2.0 / 4.0, 3.0 / 3.0);
	glVertex3f(-2000, -2000, 2000);
	glEnd();
}

GLvoid CRun_time_Framework::Pilar()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[weather + 3]);
	glTranslatef(0, 400, 0);
	// 앞
	glBegin(GL_QUADS);
	glTexCoord2f(Scroll[4], 0); // 텍스처 위치 설정 
	glVertex3f(100, 200, 100);
	glTexCoord2f(Scroll[3], 0); // 텍스처 위치 설정 
	glVertex3f(-100, 200, 100);
	glTexCoord2f(Scroll[3], 1); // 텍스처 위치 설정 
	glVertex3f(-100, -200, 100);
	glTexCoord2f(Scroll[4], 1); // 텍스처 위치 설정 
	glVertex3f(100, -200, 100);
	glEnd();

	// 왼쪽
	glBegin(GL_QUADS);
	glTexCoord2f(Scroll[3], 0);
	glVertex3f(-100, 200, 100);
	glTexCoord2f(Scroll[2], 0);
	glVertex3f(-100, 200, -100);
	glTexCoord2f(Scroll[2], 1);
	glVertex3f(-100, -200, -100);
	glTexCoord2f(Scroll[3], 1);
	glVertex3f(-100, -200, 100);
	glEnd();

	// 뒤
	glBegin(GL_QUADS);
	glTexCoord2f(Scroll[2], 0);
	glVertex3f(-100, 200, -100);
	glTexCoord2f(Scroll[1], 0);
	glVertex3f(100, 200, -100);
	glTexCoord2f(Scroll[1], 1);
	glVertex3f(100, -200, -100);
	glTexCoord2f(Scroll[2], 1);
	glVertex3f(-100, -200, -100);
	glEnd();

	// 오른
	glBegin(GL_QUADS);
	glTexCoord2f(Scroll[1], 0);
	glVertex3f(100, 200, -100);
	glTexCoord2f(Scroll[0], 0);
	glVertex3f(100, 200, 100);
	glTexCoord2f(Scroll[0], 1);
	glVertex3f(100, -200, 100);
	glTexCoord2f(Scroll[1], 1);
	glVertex3f(100, -200, -100);
	glEnd();

	// 위
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(100, 200, -100);
	glTexCoord2f(0.05, 0);
	glVertex3f(-100, 200, -100);
	glTexCoord2f(0.05, 0.1);
	glVertex3f(-100, 200, 100);
	glTexCoord2f(0, 0.1);
	glVertex3f(100, 200, 100);
	glEnd();

	// 아래
	glBegin(GL_QUADS);
	glTexCoord2f(0.05, 0);
	glVertex3f(-100, -200, -100);
	glTexCoord2f(0, 0);
	glVertex3f(100, -200, -100);
	glTexCoord2f(0, 0.1);
	glVertex3f(100, -200, 100);
	glTexCoord2f(0.05, 0.1);
	glVertex3f(-100, -200, 100);
	glEnd();
	glPopMatrix();
	return GLvoid();
}