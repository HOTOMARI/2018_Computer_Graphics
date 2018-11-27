#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
}

GLvoid CRun_time_Framework::Draw_Ball()
{
	GLfloat a[] = { 0.2,0.2,0.2,1.0 };
	GLfloat d[] = { 0.8,0.8,0.8,1.0 };
	glPushMatrix();

	// �ڵ� ���� ���� 
	glEnable (GL_TEXTURE_GEN_S); 
	glEnable (GL_TEXTURE_GEN_T);

	glTranslatef(100 * sin(moon_degree / 180.0*PI), 0, -100 * cos(moon_degree / 180.0*PI));

	// �� ���� 
	glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); 
	glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); 
	glBindTexture (GL_TEXTURE_2D, texture[1]); 

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WhiteLight);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 80.0f);
	glutSolidSphere(50, 30, 30);

	// �ڵ� ���� ���� 
	glDisable (GL_TEXTURE_GEN_S); 
	glDisable (GL_TEXTURE_GEN_T);
	glPopMatrix();
}

GLvoid CRun_time_Framework::Draw_Cone()
{
	//glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(light[0].position[0], light[0].position[1], light[0].position[2]);
	glRotatef(180 - light[0].degree, 0, 1, 0);
	gluCylinder(qobj, 20, 0.0, 20, 20, 8);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslatef(light[1].position[0], light[1].position[1], light[1].position[2]);
	glRotatef(180 - light[1].degree, 0, 1, 0);
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
	return GLvoid();
}

GLvoid CRun_time_Framework::UpdateLight()
{
	light[0].position[0] = 300.0*sin(light[0].degree / 180.0*PI);
	light[0].position[2] = -300.0*cos(light[0].degree / 180.0*PI);
	light[1].position[0] = 300.0*sin(light[1].degree / 180.0*PI);
	light[1].position[2] = -300.0*cos(light[1].degree / 180.0*PI);
	return GLvoid();
}

GLvoid CRun_time_Framework::Draw_Ground()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTranslatef(0, -300, 0);
	for (int i = 0; i < 50; ++i) {
		for (int j = 0; j < 50; ++j) {
			if (normal)
				glNormal3f(0.0, 1.0, 0.0);
			glBegin(GL_QUADS);
			glTexCoord2f(j*(1.0 / 50.0), i*(1.0 / 50.0));
			glVertex3f(ground[i][j].left, 0, ground[i][j].top);
			glTexCoord2f((j + 1)*(1.0 / 50.0), i*(1.0 / 50.0));
			glVertex3f(ground[i][j].right, 0, ground[i][j].top);
			glTexCoord2f((j + 1)*(1.0 / 50.0), (i + 1)*(1.0 / 50.0));
			glVertex3f(ground[i][j].right, 0, ground[i][j].bottom);
			glTexCoord2f(j*(1.0 / 50.0), (i + 1)*(1.0 / 50.0));
			glVertex3f(ground[i][j].left, 0, ground[i][j].bottom);
			glEnd();
		}
	}
	glPopMatrix();
}

GLvoid CRun_time_Framework::Draw_Piramid()
{
	GLfloat a[] = { 0.2,0.2,0.2,1.0 };
	GLfloat d[] = { 0.8,0.8,0.8,1.0 };

	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glMaterialfv(GL_FRONT, GL_AMBIENT, a);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
	glMaterialfv(GL_FRONT, GL_SPECULAR, WhiteLight);

	glTranslatef(0, -300, 0);
	glColor3f(1, 1, 1);
	//������
	{
		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(-360, 40, -360);
		glTexCoord2f(0, 1);
		glVertex3f(ground[4][4].right, 0, ground[4][4].bottom);
		glTexCoord2f(1, 1);
		glVertex3f(ground[4][0].left, 0, ground[4][0].bottom);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(-360, 40, -360);
		glTexCoord2f(0, 1);
		glVertex3f(ground[4][0].left, 0, ground[4][0].bottom);
		glTexCoord2f(1, 1);
		glVertex3f(ground[0][0].left, 0, ground[0][0].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(-360, 40, -360);
		glTexCoord2f(0, 1);
		glVertex3f(ground[0][0].left, 0, ground[0][0].top);
		glTexCoord2f(1, 1);
		glVertex3f(ground[0][4].right, 0, ground[0][4].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(1.0, 0.0, 0.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(-360, 40, -360);
		glTexCoord2f(0, 1);
		glVertex3f(ground[0][4].right, 0, ground[0][4].top);
		glTexCoord2f(1, 1);
		glVertex3f(ground[4][4].right, 0, ground[4][4].bottom);
		glEnd();
	}
	//��������
	{
		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(360, 40, -360);
		glTexCoord2f(0, 1);
		glVertex3f(ground[4][49].right, 0, ground[4][49].bottom);
		glTexCoord2f(1, 1);
		glVertex3f(ground[4][45].left, 0, ground[4][45].bottom);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(360, 40, -360);
		glTexCoord2f(0, 1);
		glVertex3f(ground[4][45].left, 0, ground[4][45].bottom);
		glTexCoord2f(1, 1);
		glVertex3f(ground[0][45].left, 0, ground[0][45].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(360, 40, -360);
		glTexCoord2f(0, 1);
		glVertex3f(ground[0][45].left, 0, ground[0][45].top);
		glTexCoord2f(1, 1);
		glVertex3f(ground[0][49].right, 0, ground[0][49].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(1.0, 0.0, 0.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(360, 40, -360);
		glTexCoord2f(0, 1);
		glVertex3f(ground[0][49].right, 0, ground[0][49].top);
		glTexCoord2f(1, 1);
		glVertex3f(ground[4][49].right, 0, ground[4][49].bottom);
		glEnd();
	}
	//���ʾƷ�
	{
		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(-360, 40, 360);
		glTexCoord2f(0, 1);
		glVertex3f(ground[49][4].right, 0, ground[49][4].bottom);
		glTexCoord2f(1, 1);
		glVertex3f(ground[49][0].left, 0, ground[49][0].bottom);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(-360, 40, 360);
		glTexCoord2f(0, 1);
		glVertex3f(ground[49][0].left, 0, ground[49][0].bottom);
		glTexCoord2f(1, 1);
		glVertex3f(ground[45][0].left, 0, ground[45][0].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(-360, 40, 360);
		glTexCoord2f(0, 1);
		glVertex3f(ground[45][0].left, 0, ground[45][0].top);
		glTexCoord2f(1, 1);
		glVertex3f(ground[45][4].right, 0, ground[45][4].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(1.0, 0.0, 0.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(-360, 40, 360); 
		glTexCoord2f(0, 1);
		glVertex3f(ground[45][4].right, 0, ground[45][4].top);
		glTexCoord2f(1, 1);
		glVertex3f(ground[49][4].right, 0, ground[49][4].bottom);
		glEnd();
	}
	//�����ʾƷ�
	{
		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(360, 40, 360);
		glTexCoord2f(0, 1);
		glVertex3f(ground[49][49].right, 0, ground[49][49].bottom);
		glTexCoord2f(1, 1);
		glVertex3f(ground[49][45].left, 0, ground[49][45].bottom);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(360, 40, 360);
		glTexCoord2f(0, 1);
		glVertex3f(ground[49][45].left, 0, ground[49][45].bottom);
		glTexCoord2f(1, 1);
		glVertex3f(ground[45][45].left, 0, ground[45][45].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(360, 40, 360);
		glTexCoord2f(0, 1);
		glVertex3f(ground[45][45].left, 0, ground[45][45].top);
		glTexCoord2f(1, 1);
		glVertex3f(ground[45][49].right, 0, ground[45][49].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(1.0, 0.0, 0.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(360, 40, 360);
		glTexCoord2f(0, 1);
		glVertex3f(ground[45][49].right, 0, ground[45][49].top);
		glTexCoord2f(1, 1);
		glVertex3f(ground[49][49].right, 0, ground[49][49].bottom);
		glEnd();
	}
	//���
	{
		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, 1.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(0, 200, 0);
		glTexCoord2f(0, 1);
		glVertex3f(ground[29][29].right, 0, ground[29][29].bottom);
		glTexCoord2f(1, 1);
		glVertex3f(ground[29][20].left, 0, ground[29][20].bottom);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(-1.0, 0.0, 0.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(0, 200, 0);
		glTexCoord2f(0, 1);
		glVertex3f(ground[29][20].left, 0, ground[29][20].bottom);
		glTexCoord2f(1, 1);
		glVertex3f(ground[20][20].left, 0, ground[20][20].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(0.0, 0.0, -1.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(0, 200, 0);
		glTexCoord2f(0, 1);
		glVertex3f(ground[20][20].left, 0, ground[20][20].top);
		glTexCoord2f(1, 1);
		glVertex3f(ground[20][29].right, 0, ground[20][29].top);
		glEnd();

		glBegin(GL_POLYGON);
		if (normal)
			glNormal3f(1.0, 0.0, 0.0);
		glTexCoord2f(0.5, 0);
		glVertex3f(0, 200, 0);
		glTexCoord2f(0, 1);
		glVertex3f(ground[20][29].right, 0, ground[20][29].top);
		glTexCoord2f(1, 1);
		glVertex3f(ground[29][29].right, 0, ground[29][29].bottom);
		glEnd();
	}

	glPopMatrix();
}

GLubyte * CRun_time_Framework::LoadDIBitmap(const char *filename, BITMAPINFO ** info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	// ���̳ʸ� �б� ���� ������ ���� 
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;

	// ��Ʈ�� ���� ����� �д´�. 
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}

	// ������ BMP �������� Ȯ���Ѵ�. 
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	// BITMAPINFOHEADER ��ġ�� ����. 
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�. 
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}

	// ��Ʈ�� ���� ����� �д´�. 
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// ��Ʈ���� ũ�� ���� 
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 *  abs((*info)->bmiHeader.biHeight);

	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�. 
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�. 
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
	// n���� �̹��� �ؽ�ó ������ �Ѵ�.
	glGenTextures(3, texture);

	//�ؽ�ó�� ��ü�� �����Ѵ�. --- (1) 
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	//�̹��� �ε��� �Ѵ�. --- (2) 
	pBytes = LoadDIBitmap("ground.bmp", &info);

	//�ؽ�ó ���� ���Ǹ� �Ѵ�. --- (3) 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	//�ؽ�ó �Ķ���� ���� --- (4) 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �ؽ�ó ��� ���� 
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// ������ n-1���� �ؽ�ó���� (1) ~ (4)������ ������ �����Ͽ� �ؽ�ó�� �����Ѵ�.
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	pBytes = LoadDIBitmap("piramid.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	pBytes = LoadDIBitmap("Skybox.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	pBytes = LoadDIBitmap("Pilar.bmp", &info);
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
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	// ��
	glBegin(GL_QUADS);
	glTexCoord2f(4.0 / 4.0, 1.0 / 3.0); // �ؽ�ó ��ġ ���� 
	glVertex3f(2000, 2000, 2000);
	glTexCoord2f(3.0 / 4.0, 1.0 / 3.0); // �ؽ�ó ��ġ ���� 
	glVertex3f(-2000, 2000, 2000);
	glTexCoord2f(3.0 / 4.0, 2.0 / 3.0); // �ؽ�ó ��ġ ���� 
	glVertex3f(-2000, -2000, 2000);
	glTexCoord2f(4.0 / 4.0, 2.0 / 3.0); // �ؽ�ó ��ġ ���� 
	glVertex3f(2000, -2000, 2000);
	glEnd();
	
	// ����
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

	// ��
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

	// ����
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

	// ��
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

	// �Ʒ�
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
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTranslatef(-200, -100, 0);
	// ��
	glBegin(GL_QUADS);
	glTexCoord2f(Scroll[4], 0); // �ؽ�ó ��ġ ���� 
	glVertex3f(50, 200, 50);
	glTexCoord2f(Scroll[3], 0); // �ؽ�ó ��ġ ���� 
	glVertex3f(-50, 200, 50);
	glTexCoord2f(Scroll[3], 1); // �ؽ�ó ��ġ ���� 
	glVertex3f(-50, -200, 50);
	glTexCoord2f(Scroll[4], 1); // �ؽ�ó ��ġ ���� 
	glVertex3f(50, -200, 50);
	glEnd();

	// ����
	glBegin(GL_QUADS);
	glTexCoord2f(Scroll[3], 0);
	glVertex3f(-50, 200, 50);
	glTexCoord2f(Scroll[2], 0);
	glVertex3f(-50, 200, -50);
	glTexCoord2f(Scroll[2], 1);
	glVertex3f(-50, -200, -50);
	glTexCoord2f(Scroll[3], 1);
	glVertex3f(-50, -200, 50);
	glEnd();

	// ��
	glBegin(GL_QUADS);
	glTexCoord2f(Scroll[2], 0);
	glVertex3f(-50, 200, -50);
	glTexCoord2f(Scroll[1], 0);
	glVertex3f(50, 200, -50);
	glTexCoord2f(Scroll[1], 1);
	glVertex3f(50, -200, -50);
	glTexCoord2f(Scroll[2], 1);
	glVertex3f(-50, -200, -50);
	glEnd();

	// ����
	glBegin(GL_QUADS);
	glTexCoord2f(Scroll[1], 0);
	glVertex3f(50, 200, -50);
	glTexCoord2f(Scroll[0], 0);
	glVertex3f(50, 200, 50);
	glTexCoord2f(Scroll[0], 1);
	glVertex3f(50, -200, 50);
	glTexCoord2f(Scroll[1], 1);
	glVertex3f(50, -200, -50);
	glEnd();

	// ��
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(50, 200, -50);
	glTexCoord2f(0.05, 0);
	glVertex3f(-50, 200, -50);
	glTexCoord2f(0.05, 0.1);
	glVertex3f(-50, 200, 50);
	glTexCoord2f(0, 0.1);
	glVertex3f(50, 200, 50);
	glEnd();

	// �Ʒ�
	glBegin(GL_QUADS);
	glTexCoord2f(0.05, 0);
	glVertex3f(-50, -200, -50);
	glTexCoord2f(0, 0);
	glVertex3f(50, -200, -50);
	glTexCoord2f(0, 0.1);
	glVertex3f(50, -200, 50);
	glTexCoord2f(0.05, 0.1);
	glVertex3f(-50, -200, 50);
	glEnd();
	glPopMatrix();
	return GLvoid();
}
