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
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WhiteLight);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 80.0f);
	glutSolidSphere(200, 30, 30);
	glPopMatrix();
}

GLvoid CRun_time_Framework::Draw_Cone()
{
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(light[0].position[0], light[0].position[1], light[0].position[2]);
	glRotatef(180 - light[0].degree, 0, 1, 0);
	gluCylinder(qobj, 60, 0.0, 60, 20, 8);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(light[1].position[0], light[1].position[1], light[1].position[2]);
	glRotatef(180 - light[1].degree, 0, 1, 0);
	gluCylinder(qobj, 60, 0.0, 60, 20, 8);
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
	return GLvoid();
}

GLvoid CRun_time_Framework::UpdateLight()
{
	light[0].position[0] = 600.0*sin(light[0].degree / 180.0*PI);
	light[0].position[2] = -600.0*cos(light[0].degree / 180.0*PI);
	light[1].position[0] = 600.0*sin(light[1].degree / 180.0*PI);
	light[1].position[2] = -600.0*cos(light[1].degree / 180.0*PI);
	return GLvoid();
}
