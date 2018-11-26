#include "Run_time_Framework.h"


GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // 바탕색을 'blue' 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
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
	// 앞
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0); // 텍스처 위치 설정 
	glVertex3f(100, 100 - front_rotate, 100 + front_rotate);
	glTexCoord2f(0, 0); // 텍스처 위치 설정 
	glVertex3f(-100, 100 - front_rotate, 100 + front_rotate);
	glTexCoord2f(0, 1); // 텍스처 위치 설정 
	glVertex3f(-100, -100, 100);
	glTexCoord2f(1, 1); // 텍스처 위치 설정 
	glVertex3f(100, -100, 100);
	glEnd();

	// 왼쪽
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

	// 뒤
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

	// 오른
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

	// 위
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

	// 아래
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

	// 바이너리 읽기 모드로 파일을 연다 
	if ( (fp = fopen (filename, "rb")) == NULL ) 
		return NULL;

	// 비트맵 파일 헤더를 읽는다. 
	if ( fread (&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1 ) { 
		fclose(fp); 
		return NULL; 
	}

	// 파일이 BMP 파일인지 확인한다. 
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	// BITMAPINFOHEADER 위치로 간다. 
	infosize = header.bfOffBits - sizeof (BITMAPFILEHEADER);

	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다. 
	if ( (*info = (BITMAPINFO *)malloc(infosize)) == NULL ) { 
		fclose(fp); 
		exit (0); 
		return NULL; 
	}

	// 비트맵 인포 헤더를 읽는다. 
	if ( fread (*info, 1, infosize, fp) < (unsigned int)infosize ) { 
		free (*info); 
		fclose(fp); 
		return NULL; 
	}

	// 비트맵의 크기 설정 
	if ( (bitsize = (*info)->bmiHeader.biSizeImage) == 0 ) 
		bitsize = (  (*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount+7) / 8.0 *  abs((*info)->bmiHeader.biHeight);

	// 비트맵의 크기만큼 메모리를 할당한다. 
	if ( (bits = (unsigned char *)malloc(bitsize) ) == NULL ) { 
		free (*info); 
		fclose(fp); 
		return NULL; 
	}

	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다. 
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
	// n개의 이미지 텍스처 매핑을 한다.
	glGenTextures(n, texture_object);

	//텍스처와 객체를 결합한다. --- (1) 
	glBindTexture (GL_TEXTURE_2D, texture_object[0]); 

	//이미지 로딩을 한다. --- (2) 
	pBytes = LoadDIBitmap("Map003.bmp", &info ); 

	//텍스처 설정 정의를 한다. --- (3) 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	//텍스처 파라미터 설정 --- (4) 
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 텍스처 모드 설정 
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// 나머지 n-1개의 텍스처에도 (1) ~ (4)까지의 과정을 진행하여 텍스처를 설정한다.
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


