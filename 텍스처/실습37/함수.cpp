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

	// 자동 매핑 설정 
	glEnable (GL_TEXTURE_GEN_S); 
	glEnable (GL_TEXTURE_GEN_T);

	glTranslatef(100 * sin(moon_degree / 180.0*PI), 0, -100 * cos(moon_degree / 180.0*PI));

	// 구 매핑 
	glTexGeni (GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); 
	glTexGeni (GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); 
	glBindTexture (GL_TEXTURE_2D, texture[1]); 

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, a);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, d);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WhiteLight);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 80.0f);
	glutSolidSphere(50, 30, 30);

	// 자동 매핑 해제 
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
	//왼쪽위
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
	//오른쪽위
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
	//왼쪽아래
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
	//오른쪽아래
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
	//가운데
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
	glGenTextures(3, texture);

	//텍스처와 객체를 결합한다. --- (1) 
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	//이미지 로딩을 한다. --- (2) 
	pBytes = LoadDIBitmap("ground.bmp", &info);

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
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTranslatef(-200, -100, 0);
	// 앞
	glBegin(GL_QUADS);
	glTexCoord2f(Scroll[4], 0); // 텍스처 위치 설정 
	glVertex3f(50, 200, 50);
	glTexCoord2f(Scroll[3], 0); // 텍스처 위치 설정 
	glVertex3f(-50, 200, 50);
	glTexCoord2f(Scroll[3], 1); // 텍스처 위치 설정 
	glVertex3f(-50, -200, 50);
	glTexCoord2f(Scroll[4], 1); // 텍스처 위치 설정 
	glVertex3f(50, -200, 50);
	glEnd();

	// 왼쪽
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

	// 뒤
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

	// 오른
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

	// 위
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

	// 아래
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
