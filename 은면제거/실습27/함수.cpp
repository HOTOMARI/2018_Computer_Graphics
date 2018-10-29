#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // ¹ÙÅÁ»öÀ» 'blue' ·Î ÁöÁ¤
	glClear(GL_COLOR_BUFFER_BIT); // ¼³Á¤µÈ »öÀ¸·Î ÀüÃ¼¸¦ Ä¥ÇÏ±â
}

GLvoid CRun_time_Framework::crane()
{
	// ¸Ç ¾Æ·¡ ¸öÃ¼
	glTranslatef(shapes[0].position[0], -(100 * 0.3), shapes[0].position[1]);
	glMultMatrixf(shapes[0].identity);

	glPushMatrix();
	glScalef(1.5, 1.0, 0.7);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glColor3f(1, 0, 0);
	glutSolidCube(100);
	glPopMatrix();

	// 1Â÷ÆÈ
	glRotatef(shapes[1].rotate[1], 0.f, 1.f, 0.f);
	glMultMatrixf(shapes[1].identity);
	glTranslatef(0, 70, 0);

	glPushMatrix();
	glScalef(0.4, 1.0, 0.4);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glColor3f(0, 1, 0);
	glutSolidCube(100);
	glPopMatrix();

	// 2Â÷ÆÈ
	glTranslatef(0, 30, 0);
	glMultMatrixf(shapes[2].identity);
	glTranslatef(0, 70, 0);

	glPushMatrix();
	glScalef(0.2, 1.0, 0.2);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glColor3f(0, 0, 1);
	glutSolidCube(100);
	glPopMatrix();
}

GLvoid CRun_time_Framework::ball()
{
	glPushMatrix();
	glTranslatef(Ball.position[0], 0, Ball.position[1]);
	glMultMatrixf(Ball.identity);
	glColor3f(0, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glutWireSphere(50, 10, 10);
	glPopMatrix();
}

GLvoid CRun_time_Framework::ground()
{
	glColor3f(1, 1, 0);
	glTranslatef(0, -50, 0);
	glRotatef(-90, 1, 0, 0);
	glRectf(-400, -300, 400, 300);
	// »ï°¢Çü
	glColor3f(0, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex3f(-400, -300, 1);
	glVertex3f(-400, -100, 1);
	glVertex3f(-200, -300, 1);
	glEnd();
	glColor3f(1, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex3f(400, 300, 1);
	glVertex3f(400, 100, 1);
	glVertex3f(200, 300, 1);
	glEnd();
	glColor3f(1, 0.5, 0);
	glBegin(GL_TRIANGLES);
	glVertex3f(-400, 300, 1);
	glVertex3f(-400, 100, 1);
	glVertex3f(-200, 300, 1);
	glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex3f(400, -300, 1);
	glVertex3f(400, -100, 1);
	glVertex3f(200, -300, 1);
	glEnd();
	// Ãæµ¹¹Ù´Ú
	if (see_collide) {
		glColor3f(0, 1, 0);
		glBegin(GL_POLYGON);
		glVertex3f(Ball.bb.left, Ball.bb.bottom, 1);
		glVertex3f(Ball.bb.left, Ball.bb.top, 1);
		glVertex3f(Ball.bb.right, Ball.bb.top, 1);
		glVertex3f(Ball.bb.right, Ball.bb.bottom, 1);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(shapes[0].bb.left, shapes[0].bb.bottom, 80);
		glVertex3f(shapes[0].bb.left, shapes[0].bb.top, 80);
		glVertex3f(shapes[0].bb.right, shapes[0].bb.top, 80);
		glVertex3f(shapes[0].bb.right, shapes[0].bb.bottom, 80);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(object[0].left, object[0].bottom, 80);
		glVertex3f(object[0].left, object[0].top, 80);
		glVertex3f(object[0].right, object[0].top, 80);
		glVertex3f(object[0].right, object[0].bottom, 80);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(object[1].left, object[1].bottom, 80);
		glVertex3f(object[1].left, object[1].top, 80);
		glVertex3f(object[1].right, object[1].top, 80);
		glVertex3f(object[1].right, object[1].bottom, 80);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(object[2].left, object[2].bottom, 80);
		glVertex3f(object[2].left, object[2].top, 80);
		glVertex3f(object[2].right, object[2].top, 80);
		glVertex3f(object[2].right, object[2].bottom, 80);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(object[3].left, object[3].bottom, 80);
		glVertex3f(object[3].left, object[3].top, 80);
		glVertex3f(object[3].right, object[3].top, 80);
		glVertex3f(object[3].right, object[3].bottom, 80);
		glEnd();
	}
}

GLvoid CRun_time_Framework::tree()
{
	glTranslatef(-350, 0, 250);

	// ¸öÅë
	glPushMatrix();
	glScalef(0.2, 1.0, 0.2);
	glColor3f(1, 0.5, 0.5);
	glutSolidCube(100);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glPopMatrix();
	// ¸Ó¸®
	glPushMatrix();
	glTranslatef(0, 50, 0);
	glScalef(tree_size, tree_size, tree_size);
	glColor3f(0, 1, 0);
	glutWireSphere(70, 10, 10);
	glPopMatrix();
}

GLvoid CRun_time_Framework::metal_pole()
{
	glTranslatef(-350, 50, -250);

	// Ã¶ºÀ
	{
		glPushMatrix();
		glTranslatef(-40, -50, 0);
		glScalef(0.2, 1.0, 0.2);
		glColor3f(1, 0.5, 0.5);
		glutSolidCube(100);
		glColor3f(1, 1, 1);
		glutWireCube(100);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(40, -50, 0);
		glScalef(0.2, 1.0, 0.2);
		glColor3f(1, 0.5, 0.5);
		glutSolidCube(100);
		glColor3f(1, 1, 1);
		glutWireCube(100);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 50 - 50, 0);
		glScalef(1.0, 0.1, 0.1);
		glColor3f(0.5, 0.5, 1);
		glutSolidCube(100);
		glColor3f(1, 1, 1);
		glutWireCube(100);
		glPopMatrix();
	}
	// »ç¶÷
	{
		glPushMatrix();
		glRotatef(metal_pole_rotate, 1, 0, 0);
		glTranslatef(0, 25, 0);
		// ÆÈ
		glPushMatrix();
		glTranslatef(-25, -50, 0);
		glScalef(0.1, 0.4, 0.1);
		glColor3f(0.0, 0.0, 1);
		glutSolidCube(100);
		glColor3f(1, 1, 1);
		glutWireCube(100);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(25, -50, 0);
		glScalef(0.1, 0.4, 0.1);
		glColor3f(0.0, 0.0, 1);
		glutSolidCube(100);
		glColor3f(1, 1, 1);
		glutWireCube(100);
		glPopMatrix();
		// ¸öÅë
		glPushMatrix();
		glTranslatef(0, -30 - 50, 0);
		glScalef(0.5, 0.5, 0.5);
		glColor3f(0.0, 0.0, 1);
		glutSolidCube(100);
		glColor3f(1, 1, 1);
		glutWireCube(100);
		glPopMatrix();

		glPopMatrix();
	}
}

GLvoid CRun_time_Framework::bench_press()
{
	glTranslatef(350, 0, -250);

	// ´¯´Â°Å
	glPushMatrix();
	glTranslatef(0, -40, 0);
	glScalef(0.75, 0.2, 1);
	glColor3f(0.25, 0.75, 0.5);
	glutSolidCube(100);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glPopMatrix();

	// ¿ª±âºÀ
	glPushMatrix();
	glTranslatef(0, bench, 0);
	glScalef(1, 0.1, 0.1);
	glColor3f(0.75, 0.75, 0.5);
	glutSolidCube(100);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glPopMatrix();
	// ¿·¿¡´Ş¸°°Å
	glPushMatrix();
	glTranslatef(-50, bench, 0);
	glScalef(0.1, 0.5, 0.5);
	glColor3f(0.75, 0.75, 0.5);
	glutSolidCube(100);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(50, bench, 0);
	glScalef(0.1, 0.5, 0.5);
	glColor3f(0.75, 0.75, 0.5);
	glutSolidCube(100);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glPopMatrix();
}

GLvoid CRun_time_Framework::treadmill()
{
	glTranslatef(350, 0, 250);

	// ¹ßÆÇ
	glPushMatrix();
	glTranslatef(0, -37, 0);
	glScalef(1, 0.2, 4);
	glRotatef(-treadmill_rotate, 0, 0, 1);
	glColor3f(0.9, 0.6, 0.3);
	glutWireTorus(5,60,5,10);
	glPopMatrix();

	// ´Ù¸®
	glPushMatrix();
	glTranslatef(0, 50, 10);
	glRotatef(leg_rotate, 0, 0, 1);
	glTranslatef(0, -50, 0);
	glScalef(0.07, 0.5, 0.07);

	glColor3f(0.9, 0.75, 0.5);
	glutSolidCube(100);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 50, -10);
	glRotatef(-leg_rotate, 0, 0, 1);
	glTranslatef(0, -50, 0);
	glScalef(0.07, 0.5, 0.07);

	glColor3f(0.9, 0.75, 0.5);
	glutSolidCube(100);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glPopMatrix();
}

GLvoid CRun_time_Framework::airplane()
{
	//glTranslatef(200 * cos(airplane_rotate / 180 * PI), 0, 200 * sin(airplane_rotate / 180 * PI));
	glRotatef(airplane_rotate, 0, 1, 0);
	glTranslatef(0, 100, 200);
	if (airplane_dir)glRotatef(180, 0, 1, 0);
	else glRotatef(0, 0, 1, 0);
	glRotatef(airplane_spin, 1, 0, 0);

	// ¸öÃ¼
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(1, 0.4, 0.4);
	glColor3f(0.9, 0.6, 0.3);
	glutSolidCube(100);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glPopMatrix();

	// ¸öÃ¼
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glScalef(0.5, 0.1, 1);
	glColor3f(1, 0, 0);
	glutSolidCube(100);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glPopMatrix();

	// ÇÁ·ÎÆç·¯
	glPushMatrix();
	glTranslatef(-58, 0, 0);
	glRotatef(propeller_rotate, 1, 0, 0);
	glScalef(0.1, 0.5, 0.1);
	glColor3f(1, 1, 1);
	glutSolidCube(100);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glPopMatrix();

	// ²¿¸®
	glPushMatrix();
	glTranslatef(50, 30, 0);
	glScalef(0.1, 0.5, 0.5);
	glColor3f(1, 0, 0);
	glutSolidCube(100);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glPopMatrix();

	// ¿¬±â 1
	glPushMatrix();
	glTranslatef(80, 0, 0);
	glColor3f(0.5, 0.5, 0.5);
	glutSolidSphere(Smoke[0].size, 5, 5);
	glPopMatrix();

	// ¿¬±â 2
	glPushMatrix();
	glTranslatef(140, 0, 0);
	glColor3f(0.5, 0.5, 0.5);
	glutSolidSphere(Smoke[1].size, 5, 5);
	glPopMatrix();

	// ¿¬±â 1
	glPushMatrix();
	glTranslatef(200, 0, 0);
	glColor3f(0.5, 0.5, 0.5);
	glutSolidSphere(Smoke[2].size, 5, 5);
	glPopMatrix();
}

GLvoid CRun_time_Framework::update_bb()
{
	shapes[0].bb.left = shapes[0].position[0] - 75;
	shapes[0].bb.right = shapes[0].position[0] + 75;
	shapes[0].bb.top = -(shapes[0].position[1] - 35);
	shapes[0].bb.bottom = -(shapes[0].position[1] + 35);

	Ball.bb.left = Ball.position[0] - 50;
	Ball.bb.right = Ball.position[0] + 50;
	Ball.bb.top = -(Ball.position[1] - 50);
	Ball.bb.bottom = -(Ball.position[1] + 50);
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


