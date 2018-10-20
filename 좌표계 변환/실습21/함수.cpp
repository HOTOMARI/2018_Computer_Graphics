#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // ¹ÙÅÁ»öÀ» 'blue' ·Î ÁöÁ¤
	glClear(GL_COLOR_BUFFER_BIT); // ¼³Á¤µÈ »öÀ¸·Î ÀüÃ¼¸¦ Ä¥ÇÏ±â
}

GLvoid CRun_time_Framework::crane()
{
	// ¸Ç ¾Æ·¡ ¸öÃ¼
	glTranslatef(shapes[0].position[0], -(100 * 0.3), 0);
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

GLvoid CRun_time_Framework::ground()
{
	glColor3f(1, 1, 0);
	glTranslatef(0, -50, 0);
	glRotatef(-90, 1, 0, 0);
	glRectf(-400, -300, 400, 300);

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
	// ¿·¿¡´Þ¸°°Å
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


