#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
}

GLvoid CRun_time_Framework::Draw_Ball()
{
	GLfloat a[] = { 0.2,0.2,0.2,1.0 };
	GLfloat d[] = { 0.8,0.8,0.8,1.0 };
	glPushMatrix();

	glTranslatef(100 * sin(moon_degree / 180.0*PI), 0, -100 * cos(moon_degree / 180.0*PI));

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WhiteLight);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 80.0f);
	glutSolidSphere(50, 30, 30);
	glPopMatrix();
}

GLvoid CRun_time_Framework::Draw_Cone()
{
	//glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(light[0].position[0], light[0].position[1], light[0].position[2]);
	glRotatef(90 - light[0].degree, 0, 1, 0);
	gluCylinder(qobj, 20, 0.0, 20, 20, 8);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(light[1].position[0], light[1].position[1], light[1].position[2]);
	glRotatef(90 - light[1].degree, 0, 1, 0);
	gluCylinder(qobj, 20, 0.0, 20, 20, 8);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
}

GLvoid CRun_time_Framework::Init_Light()
{
	light[0].degree = 90.0;
	light[0].AmbientColor[1] = 0.2;
	light[0].DiffuseColor[1] = 0.8;

	light[1].degree = 270.0;
	light[1].AmbientColor[0] = 0.2;
	light[1].DiffuseColor[0] = 0.8;

	light[1].degree = 270.0;
	light[1].AmbientColor[2] = 0.2;
	light[1].DiffuseColor[2] = 0.8;

	Downvector[0] = 0;
	Downvector[1] = -1.0;
	Downvector[2] = 0;

	return GLvoid();
}

GLvoid CRun_time_Framework::UpdateLight()
{
	light[0].position[0] = 300.0*cos(light[0].degree / 180.0*PI);
	light[0].position[2] = 300.0*sin(light[0].degree / 180.0*PI);
	light[1].position[0] = 300.0*cos(light[1].degree / 180.0*PI);
	light[1].position[2] = 300.0*sin(light[1].degree / 180.0*PI);

	light[2].position[0] = Gridman.position[0];
	light[2].position[1] = 0;
	light[2].position[2] = Gridman.position[2];


	return GLvoid();
}

GLvoid CRun_time_Framework::Draw_Ground()
{
	glPushMatrix();

	glLineWidth(5.0);
	glBegin(GL_LINES);
	glVertex3f(0, 1000, 0);
	glVertex3f(0, -1000, 0);
	glEnd();

	glTranslatef(0, -300, 0);
	for (int i = 0; i < 50; ++i) {
		for (int j = 0; j < 50; ++j) {
			if (normal)
				glNormal3f(0.0, 1.0, 0.0);
			glBegin(GL_QUADS);
			glVertex3f(ground[i][j].left, 0, ground[i][j].top);
			glVertex3f(ground[i][j].right, 0, ground[i][j].top);
			glVertex3f(ground[i][j].right, 0, ground[i][j].bottom);
			glVertex3f(ground[i][j].left, 0, ground[i][j].bottom);
			glEnd();
		}
	}
	glPopMatrix();

	// 충돌바닥
	for (int i = 0; i < 5; ++i) {
		glColor3f(1, 0, 1);
		glBegin(GL_POLYGON);
		glVertex3f(objects[i].left, -290, objects[i].bottom);
		glVertex3f(objects[i].left, -290, objects[i].top);
		glVertex3f(objects[i].right, -290, objects[i].top);
		glVertex3f(objects[i].right, -290, objects[i].bottom);
		glEnd();
	}
}

GLvoid CRun_time_Framework::Draw_Piramid()
{
	GLfloat a[] = { 0.2,0.2,0.2,1.0 };
	GLfloat d[] = { 0.8,0.8,0.8,1.0 };

	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, a);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
	glMaterialfv(GL_FRONT, GL_SPECULAR, WhiteLight);

	glTranslatef(0, -300, 0);
	glColor3f(1, 1, 1);
	//왼쪽위
	{
		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-360, 40, -360);
		glVertex3f(ground[4][4].right, 0, ground[4][4].bottom);
		glVertex3f(ground[4][0].left, 0, ground[4][0].bottom);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-360, 40, -360);
		glVertex3f(ground[4][0].left, 0, ground[4][0].bottom);
		glVertex3f(ground[0][0].left, 0, ground[0][0].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-360, 40, -360);
		glVertex3f(ground[0][0].left, 0, ground[0][0].top);
		glVertex3f(ground[0][4].right, 0, ground[0][4].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(-360, 40, -360);
		glVertex3f(ground[0][4].right, 0, ground[0][4].top);
		glVertex3f(ground[4][4].right, 0, ground[4][4].bottom);
		glEnd();
	}
	//오른쪽위
	{
		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(360, 40, -360);
		glVertex3f(ground[4][49].right, 0, ground[4][49].bottom);
		glVertex3f(ground[4][45].left, 0, ground[4][45].bottom);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(360, 40, -360);
		glVertex3f(ground[4][45].left, 0, ground[4][45].bottom);
		glVertex3f(ground[0][45].left, 0, ground[0][45].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(360, 40, -360);
		glVertex3f(ground[0][45].left, 0, ground[0][45].top);
		glVertex3f(ground[0][49].right, 0, ground[0][49].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(360, 40, -360);
		glVertex3f(ground[0][49].right, 0, ground[0][49].top);
		glVertex3f(ground[4][49].right, 0, ground[4][49].bottom);
		glEnd();
	}
	//왼쪽아래
	{
		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-360, 40, 360);
		glVertex3f(ground[49][4].right, 0, ground[49][4].bottom);
		glVertex3f(ground[49][0].left, 0, ground[49][0].bottom);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-360, 40, 360);
		glVertex3f(ground[49][0].left, 0, ground[49][0].bottom);
		glVertex3f(ground[45][0].left, 0, ground[45][0].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-360, 40, 360);
		glVertex3f(ground[45][0].left, 0, ground[45][0].top);
		glVertex3f(ground[45][4].right, 0, ground[45][4].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(-360, 40, 360);
		glVertex3f(ground[45][4].right, 0, ground[45][4].top);
		glVertex3f(ground[49][4].right, 0, ground[49][4].bottom);
		glEnd();
	}
	//오른쪽아래
	{
		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(360, 40, 360);
		glVertex3f(ground[49][49].right, 0, ground[49][49].bottom);
		glVertex3f(ground[49][45].left, 0, ground[49][45].bottom);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(360, 40, 360);
		glVertex3f(ground[49][45].left, 0, ground[49][45].bottom);
		glVertex3f(ground[45][45].left, 0, ground[45][45].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(360, 40, 360);
		glVertex3f(ground[45][45].left, 0, ground[45][45].top);
		glVertex3f(ground[45][49].right, 0, ground[45][49].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(360, 40, 360);
		glVertex3f(ground[45][49].right, 0, ground[45][49].top);
		glVertex3f(ground[49][49].right, 0, ground[49][49].bottom);
		glEnd();
	}
	//가운데
	{
		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(0, 200, 0);
		glVertex3f(ground[29][29].right, 0, ground[29][29].bottom);
		glVertex3f(ground[29][20].left, 0, ground[29][20].bottom);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(0, 200, 0);
		glVertex3f(ground[29][20].left, 0, ground[29][20].bottom);
		glVertex3f(ground[20][20].left, 0, ground[20][20].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(0, 200, 0);
		glVertex3f(ground[20][20].left, 0, ground[20][20].top);
		glVertex3f(ground[20][29].right, 0, ground[20][29].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(0, 200, 0);
		glVertex3f(ground[20][29].right, 0, ground[20][29].top);
		glVertex3f(ground[29][29].right, 0, ground[29][29].bottom);
		glEnd();
	}

	glPopMatrix();
}

GLvoid CRun_time_Framework::Draw_Particle() {

	Particle* t = particle;

	while (t != NULL) {
		glPushMatrix();
		for (int i = 0; i < 37; ++i) {
			glPushMatrix();
			glTranslatef(t->x, 0, t->z);
			glRotatef(i * 10, 0, 1, 0);
			for (int i = 0; i < 10; ++i) {
				glTranslatef(t->radius * cos(-i * 10 / 180.0*PI), t->radius * sin(-i * 10 / 180.0*PI), 0);
				glutSolidCube(20);
			}
			glPopMatrix();
		}
		glPopMatrix();
		t = t->next;
	}
}

GLvoid CRun_time_Framework::Make_Particle()
{
	if (particle == NULL) {
		particle = (Particle*)malloc(sizeof(Particle));
		particle->radius = 0;
		particle->x = Gridman.position[0];
		particle->z = Gridman.position[2];
		particle->next = NULL;
	}
	else {
		Particle* t;
		t = particle;
		while (t->next != NULL) {
			t = t->next;
		}
		t->next = (Particle*)malloc(sizeof(Particle));
		t = t->next;
		t->radius = 0;
		t->x = Gridman.position[0];
		t->z = Gridman.position[2];
		t->next = NULL;
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::UpdateParticle()
{
	Particle* t = particle;
	while (t != NULL) {
		t->radius += 0.2*(current_time - Prevtime);
		t = t->next;
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::Delete_Particle()
{
	Particle* t = particle;
	Particle* before = particle;

	while (t != NULL) {
		if (t->radius > 500 && t == particle) {
			particle = t->next;
			delete(t);
			t = particle;
			before = particle;
		}
		else if (t->radius > 500 && t != particle) {
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

GLvoid CRun_time_Framework::set_robots()
{
	Gridman.position[0] = 0;
	Gridman.position[1] = -200;
	Gridman.position[2] = 200;
	Gridman.dir = rand() % 4;
}

GLvoid CRun_time_Framework::update_bb()
{
	Gridman.bb.left = Gridman.position[0] - 40;
	Gridman.bb.right = Gridman.position[0] + 40;
	Gridman.bb.top = Gridman.position[2] + 40;
	Gridman.bb.bottom = Gridman.position[2] - 40;
}

GLvoid CRun_time_Framework::update_robots()
{
	// 애니메이션
	if (Gridman.animation_state) {
		Gridman.animation += 0.2 * (current_time - Prevtime);
		Gridman.cloak[2][0][1] += 0.15 * (current_time - Prevtime);
		Gridman.cloak[2][2][1] -= 0.15 * (current_time - Prevtime);
		if (Gridman.animation > 60) {
			Gridman.animation_state = false;
		}
	}
	else {
		Gridman.animation -= 0.2 * (current_time - Prevtime);
		Gridman.cloak[2][0][1] -= 0.15 * (current_time - Prevtime);
		Gridman.cloak[2][2][1] += 0.15 * (current_time - Prevtime);
		if (Gridman.animation < -60) {
			Gridman.animation_state = true;
		}
	}

	//방향조절
	switch (Gridman.dir) {
	case 0:
		if (Gridman.state_collide) {
			Gridman.position[2] -= 0.2 * (current_time - Prevtime);
			Make_Particle();
			Gridman.dir = rand() % 4;
		}
		else {
			Gridman.position[2] += 0.1 * (current_time - Prevtime);
		}
		if (Gridman.position[2] >= 360) {
			Gridman.position[2] = 360;
			Gridman.dir = rand() % 4;
		}
		break;
	case 1:
		if (Gridman.state_collide) {
			Gridman.position[0] -= 0.2 * (current_time - Prevtime);
			Make_Particle();
			Gridman.dir = rand() % 4;
		}
		else {
			Gridman.position[0] += 0.1 * (current_time - Prevtime);
		}
		if (Gridman.position[0] >= 360) {
			Gridman.position[0] = 360;
			Gridman.dir = rand() % 4;
		}
		break;
	case 2:
		if (Gridman.state_collide) {
			Gridman.position[2] += 0.2 * (current_time - Prevtime);
			Make_Particle();
			Gridman.dir = rand() % 4;
		}
		else {
			Gridman.position[2] -= 0.1 * (current_time - Prevtime);
		}
		if (Gridman.position[2] <= -360) {
			Gridman.position[2] = -360;
			Gridman.dir = rand() % 4;
		}
		break;
	case 3:
		if (Gridman.state_collide) {
			Gridman.position[0] += 0.2 * (current_time - Prevtime);
			Make_Particle();
			Gridman.dir = rand() % 4;
		}
		else {
			Gridman.position[0] -= 0.1 * (current_time - Prevtime);
		}
		if (Gridman.position[0] <= -360) {
			Gridman.position[0] = -360;
			Gridman.dir = rand() % 4;
		}
		break;
	}
}

GLvoid CRun_time_Framework::Robot()
{
	glPushMatrix();
	glTranslatef(Gridman.position[0], Gridman.position[1], Gridman.position[2]);

	glRotatef(Gridman.dir * 90, 0, 1, 0);
	// 머리
	glPushMatrix();
	glColor3f(0, 0, 0);

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
	glRotatef(-Gridman.animation, 1, 0, 0);
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
	glRotatef(Gridman.animation, 1, 0, 0);
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
	glRotatef(Gridman.animation, 1, 0, 0);
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
	glRotatef(-Gridman.animation, 1, 0, 0);
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
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &Gridman.cloak[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	// 그리드를 이용한 곡면 드로잉 
	glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);
	// 면을 이용하여 그리드 연결 
	glColor3f(0.0, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, 10, 0, 10);

	glPopMatrix();

	glPopMatrix();

}

GLvoid CRun_time_Framework::set_objectBB()
{
	objects[0].left = -400;
	objects[0].right = -320;
	objects[0].top = -320;
	objects[0].bottom = -400;

	objects[1].left = -400;
	objects[1].right = -320;
	objects[1].top = 400;
	objects[1].bottom = 320;

	objects[2].left = 320;
	objects[2].right = 400;
	objects[2].top = -320;
	objects[2].bottom = -400;

	objects[3].left = 320;
	objects[3].right = 400;
	objects[3].top = 400;
	objects[3].bottom = 320;

	objects[4].left = -80;
	objects[4].right = 80;
	objects[4].top = 80;
	objects[4].bottom = -80;
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