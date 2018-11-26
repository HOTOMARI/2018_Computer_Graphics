#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
}

GLvoid CRun_time_Framework::ground()
{
	glColor3f(1, 1, 0);
	glTranslatef(0, -50, 0);
	glRotatef(-90, 1, 0, 0);
	glRectf(-400, -300, 400, 300);

}


GLvoid CRun_time_Framework::QBEY()
{
	// ��
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0); // �ؽ�ó ��ġ ���� 
	glVertex3f(100, 100 - front_rotate, 100 + front_rotate);
	glTexCoord2f(0, 0); // �ؽ�ó ��ġ ���� 
	glVertex3f(-100, 100 - front_rotate, 100 + front_rotate);
	glTexCoord2f(0, 1); // �ؽ�ó ��ġ ���� 
	glVertex3f(-100, -100, 100);
	glTexCoord2f(1, 1); // �ؽ�ó ��ġ ���� 
	glVertex3f(100, -100, 100);
	glEnd();

	// ����
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(-100, 100, 100);
	glTexCoord2f(0, 0);
	glVertex3f(-100, 100, -100);
	glTexCoord2f(0, 1);
	glVertex3f(-100, -100, -100);
	glTexCoord2f(1, 1);
	glVertex3f(-100, -100, 100);
	glEnd();

	// ��
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(-100, 100, -100);
	glTexCoord2f(0, 0);
	glVertex3f(100, 100, -100);
	glTexCoord2f(0, 1);
	glVertex3f(100, -100, -100);
	glTexCoord2f(1, 1);
	glVertex3f(-100, -100, -100);
	glEnd();

	// ����
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(100, 100, -100);
	glTexCoord2f(0, 0);
	glVertex3f(100, 100, 100);
	glTexCoord2f(0, 1);
	glVertex3f(100, -100, 100);
	glTexCoord2f(1, 1);
	glVertex3f(100, -100, -100);
	glEnd();

	// ��
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(100, 100, -100);
	glTexCoord2f(0, 0);
	glVertex3f(-100, 100, -100);
	glTexCoord2f(0, 1);
	glVertex3f(-100, 100 + top_rotate, 100 - top_rotate);
	glTexCoord2f(1, 1);
	glVertex3f(100, 100+top_rotate, 100-top_rotate);
	glEnd();

	// �Ʒ�
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(-100, -100, -100);
	glTexCoord2f(0, 0);
	glVertex3f(100, -100, -100);
	glTexCoord2f(0, 1);
	glVertex3f(100, -100, 100);
	glTexCoord2f(1, 1);
	glVertex3f(-100, -100, 100);
	glEnd();
	
}

GLvoid CRun_time_Framework::spring()
{
	glColor3f(1, 1, 1);
	for (float i = 0; i < 1800; ++i) {
		glBegin(GL_LINES);
		glVertex3f(50 * sin(i / 180 * PI), i*spring_stretch, 50 * cos(i / 180 * PI));
		glVertex3f(50 * sin((i+1) / 180 * PI), (i+1)*spring_stretch, 50 * cos((i + 1) / 180 * PI));
		glEnd();
	}
	glPushMatrix();
	glTranslatef(50 * sin(spring_ball / 180 * PI), spring_ball*spring_stretch, 50 * cos(spring_ball / 180 * PI));
	glColor3f(1, 0, 0);
	glutWireSphere(10, 10, 10);
	glPopMatrix();
}

GLvoid CRun_time_Framework::ball()
{
	glTranslatef(0, -50, ball_move);
	glRotatef(ball_move, 1, 0, 0);
	glColor3f(1, 1, 1);
	glutWireSphere(50, 10, 10);
}

GLubyte * CRun_time_Framework::LoadDIBitmap(const char *filename, BITMAPINFO ** info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize; 
	BITMAPFILEHEADER header;

	// ���̳ʸ� �б� ���� ������ ���� 
	if ( (fp = fopen (filename, "rb")) == NULL ) 
		return NULL;

	// ��Ʈ�� ���� ����� �д´�. 
	if ( fread (&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1 ) { 
		fclose(fp); 
		return NULL; 
	}

	// ������ BMP �������� Ȯ���Ѵ�. 
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	// BITMAPINFOHEADER ��ġ�� ����. 
	infosize = header.bfOffBits - sizeof (BITMAPFILEHEADER);

	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�. 
	if ( (*info = (BITMAPINFO *)malloc(infosize)) == NULL ) { 
		fclose(fp); 
		exit (0); 
		return NULL; 
	}

	// ��Ʈ�� ���� ����� �д´�. 
	if ( fread (*info, 1, infosize, fp) < (unsigned int)infosize ) { 
		free (*info); 
		fclose(fp); 
		return NULL; 
	}

	// ��Ʈ���� ũ�� ���� 
	if ( (bitsize = (*info)->bmiHeader.biSizeImage) == 0 ) 
		bitsize = (  (*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount+7) / 8.0 *  abs((*info)->bmiHeader.biHeight);

	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�. 
	if ( (bits = (unsigned char *)malloc(bitsize) ) == NULL ) { 
		free (*info); 
		fclose(fp); 
		return NULL; 
	}

	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�. 
	if ( fread(bits, 1, bitsize, fp) < (unsigned int)bitsize ) { 
		free (*info); 
		free (bits); 
		fclose(fp); 
		return NULL; 
	}
	fclose(fp); 
	return bits;
}

GLvoid CRun_time_Framework::set_texture(int n)
{
	// n���� �̹��� �ؽ�ó ������ �Ѵ�.
	glGenTextures(n, texture_object);

	//�ؽ�ó�� ��ü�� �����Ѵ�. --- (1) 
	glBindTexture (GL_TEXTURE_2D, texture_object[0]); 

	//�̹��� �ε��� �Ѵ�. --- (2) 
	pBytes = LoadDIBitmap("Map003.bmp", &info ); 

	//�ؽ�ó ���� ���Ǹ� �Ѵ�. --- (3) 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	//�ؽ�ó �Ķ���� ���� --- (4) 
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �ؽ�ó ��� ���� 
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// ������ n-1���� �ؽ�ó���� (1) ~ (4)������ ������ �����Ͽ� �ؽ�ó�� �����Ѵ�.
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	pBytes = LoadDIBitmap("Map004.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 512, 512, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

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


