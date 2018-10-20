#include "Run_time_Framework.h"

extern int kind;

CRun_time_Framework* CRun_time_Framework::myself = nullptr;

CRun_time_Framework::CRun_time_Framework() {

}

GLvoid CRun_time_Framework::draw() {
	glClearColor(0, 0, 0, 1); // 바탕색을 지정 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 
	glEnable(GL_DEPTH_TEST);	//깊이테스트
	glDepthFunc(GL_LESS);		//Passes if the fragment's depth value is less than the stored depth value.

	glPushMatrix();
	gluLookAt(0, 0, camera.zoom, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	gluLookAt(camera.x, camera.y, 0, 0.0, 0.0, -100.0, cos(camera.degree[2] / 180 * PI), sin(camera.degree[2] / 180 * PI), 0.0);
	//gluLookAt(0 , 0, 0, 0.0, 0.0, -100.0, cos(camera.degree[2] / 180 * PI), sin(camera.degree[2] / 180 * PI), 0.0);
	gluLookAt(cos(camera.degree[1] / 180 * PI) * 200, 0, sin(camera.degree[1] / 180 * PI) * 200, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	if ((fabs((int)camera.degree[0]%360) <= 120 && fabs((int)camera.degree[0] % 360) >= 0)||
		(fabs((int)camera.degree[0] % 360) <= 360 && fabs((int)camera.degree[0] % 360) > 240))
		gluLookAt(0, sin(camera.degree[0] / 180 * PI) * 200, cos(camera.degree[0] / 180 * PI) * 200, 0.0, 0.0, -100.0, 0.0, -1.0, 0.0);
	else
	gluLookAt(0, sin(camera.degree[0] / 180 * PI) * 200, cos(camera.degree[0] / 180 * PI) * 200, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	//glMultMatrixf(identity);
	/*
	{
		glLineWidth(5);
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(50, 0, 0);
		glEnd();

		glColor3f(0, 1, 0);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 50, 0);
		glEnd();

		glColor3f(0, 0, 1);
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 50);
		glEnd();
		glLineWidth(1);
	}
	*/

	// 바닥
	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(0, -50, 0);
	glRotatef(-90, 1, 0, 0);
	glRectf(-400, -300, 400, 300);
	glPopMatrix();

	// 맨 아래 몸체
	glPushMatrix();
	glTranslatef(shapes[0].position[0], -(100*0.3), 0);
	glMultMatrixf(shapes[0].identity);

	glPushMatrix();
	glScalef(1.5, 1.0, 0.7);
	glColor3f(1, 1, 1);
	glutWireCube(100);
	glColor3f(1, 0, 0);
	glutSolidCube(100);
	glPopMatrix();

	// 1차팔
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

	// 2차팔
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

	glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
	return GLvoid();
}

GLvoid CRun_time_Framework::Reshape(int w, int h) {
	if (w > 0)
		m_nWidth = w;
	if (h > 0)
		m_nHeight = h;

	// 뷰포트 변환 설정: 출력 화면 결정
	glViewport(0, 0, w, h);

	// 클리핑 변환 설정: 출력하고자 하는 공간 결정
	// 아래 3줄은 투영을 설정하는 함수 
	glMatrixMode (GL_PROJECTION); 
	glLoadIdentity ();

	// 투영은 직각 투영 또는 원근 투영 중 한개를 설정한다.
	// 원근 투영을 사용하는 경우: 
	gluPerspective (60, (float)w / (float)h, 1, 2000);
	glTranslatef (0, 0, -400);

	// 직각 투영인경우
	// glOrtho (0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

	// 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장
	glMatrixMode (GL_MODELVIEW);

	// 관측 변환: 카메라의 위치 설정 (필요한 경우, 다른 곳에 설정 가능) 
	//gluLookAt(0.0, 0.0, camera_zoom, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);

	return GLvoid();
}

GLvoid CRun_time_Framework::KeyboardDown(unsigned char key, int x, int y) {
	switch (key) {
	case 'z':
		shapes[0].dir |= DIR_Y_CCW;
		break;
	case 'Z':
		shapes[0].dir |= DIR_Y_CW;
		break;
	case 'x':
		shapes[1].dir |= DIR_X_CCW;
		break;
	case 'X':
		shapes[1].dir |= DIR_X_CW;
		break;
	case 'c':
		shapes[1].dir |= DIR_Y_CCW;
		break;
	case 'C':
		shapes[1].dir |= DIR_Y_CW;
		break;
	case 'v':
		shapes[2].dir |= DIR_X_CCW;
		break;
	case 'V':
		shapes[2].dir |= DIR_X_CW;
		break;
	case 'b':
		shapes[2].dir |= DIR_Z_CCW;
		break;
	case 'B':
		shapes[2].dir |= DIR_Z_CW;
		break;



	case '-':
		camera.zoom += 30.0;
		break;
	case '+':
		camera.zoom += -30.0;
		break;

	case 'w':
		camera.y += 10;
		break;
	case 's':
		camera.y -= 10;
		break;
	case 'a':
		camera.x -= 10;
		break;
	case 'd':
		camera.x += 10;
		break;

	case 'n':
		camera.degree[0] += 10.0;
		break;
	case 'N':
		camera.degree[0] -= 10.0;
		break;
	case 'm':
		camera.degree[1] += 10.0;
		break;
	case 'M':
		camera.degree[1] -= 10.0;
		break;
	case ',':
		camera.degree[2] += 10.0;
		break;
	case '<':
		camera.degree[2] -= 10.0;
		break;

	case 'i':
		shapes[0].position[0] = 0;
		shapes[0].position[1] = 0;
		camera.degree[0] = -180;
		camera.degree[1] = -90;
		camera.degree[2] = 90;
		camera.zoom = 0;
		camera.x = 0;
		camera.y = 0;
		memset(identity, 0, sizeof(identity));
		identity[0] = identity[5] = identity[10] = identity[15] = 1;
		break;
	}
}

GLvoid CRun_time_Framework::KeyboardUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'z':
		shapes[0].dir ^= DIR_Y_CCW;
		break;
	case 'Z':
		shapes[0].dir ^= DIR_Y_CW;
		break;
	case 'x':
		shapes[1].dir ^= DIR_X_CCW;
		break;
	case 'X':
		shapes[1].dir ^= DIR_X_CW;
		break;
	case 'c':
		shapes[1].dir ^= DIR_Y_CCW;
		break;
	case 'C':
		shapes[1].dir ^= DIR_Y_CW;
		break;
	case 'v':
		shapes[2].dir ^= DIR_X_CCW;
		break;
	case 'V':
		shapes[2].dir ^= DIR_X_CW;
		break;
	case 'b':
		shapes[2].dir ^= DIR_Z_CCW;
		break;
	case 'B':
		shapes[2].dir ^= DIR_Z_CW;
		break;
	}
}

GLvoid CRun_time_Framework::Resize(int w, int h) {
	if (!myself)
		return GLvoid();
	myself->Reshape(w, h);
}

GLvoid CRun_time_Framework::drawscene() {
	if (myself != nullptr) {
		myself->draw();
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::KeyDowninput(unsigned char key, int x, int y) {
	if (myself != nullptr) {
		myself->KeyboardDown(key, x, y);
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::KeyUpinput(unsigned char key, int x, int y) {
	if (myself != nullptr) {
		myself->KeyboardUp(key, x, y);
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

	}
	return GLvoid();
}

GLvoid CRun_time_Framework::Mouseaction(int button, int state, int x, int y) {
	if (myself != nullptr) {
		myself->Mouse(button, state, x, y);
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::Init() {
	for (int i = 0; i < 3; ++i) {
		memset(shapes[i].identity, 0, sizeof(shapes[i].identity));
		shapes[i].identity[0] = shapes[i].identity[5] = shapes[i].identity[10] = shapes[i].identity[15] = 1;
	}
	srand(time(NULL));
	myself = this;
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("15"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawscene); // 출력 함수의 지정
	glutReshapeFunc(Resize);
	glutKeyboardFunc(KeyDowninput);
	glutKeyboardUpFunc(KeyUpinput);
	glutMouseFunc(Mouseaction);
	glutIdleFunc(Updatecallback);
}

GLvoid CRun_time_Framework::Updatecallback() {
	if (myself != nullptr) {
		myself->Update();
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::Update() {
	current_time = glutGet(GLUT_ELAPSED_TIME);
	current_frame++;

	if (current_time - Prevtime > 1000 / FPS_TIME) {
		if (crane_right) {
			shapes[0].position[0] += 0.1 * (current_time - Prevtime);
			if (shapes[0].position[0] > 300)
				crane_right = false;
		}
		else {
			shapes[0].position[0] -= 0.1 * (current_time - Prevtime);
			if (shapes[0].position[0] < -300)
				crane_right = true;
		}

		if (shapes[0].dir & DIR_Y_CCW) {
			glPushMatrix();
			{
				shapes[0].rotate[1] += 0.5 * (current_time - Prevtime);
				glRotatef(0.5f * (current_time - Prevtime), 0.f, 1.f, 0.f);
				glMultMatrixf(shapes[0].identity);
				glGetFloatv(GL_MODELVIEW_MATRIX, shapes[0].identity);
			}
			glPopMatrix();
		}
		if (shapes[0].dir & DIR_Y_CW) {
			glPushMatrix();
			{
				shapes[0].rotate[1] -= 0.5 * (current_time - Prevtime);
				glRotatef(-0.5f * (current_time - Prevtime), 0.f, 1.f, 0.f);
				glMultMatrixf(shapes[0].identity);
				glGetFloatv(GL_MODELVIEW_MATRIX, shapes[0].identity);
			}
			glPopMatrix();
		}

		if (shapes[1].dir & DIR_X_CCW) {
			if (shapes[1].rotate[0] < 90.0) {
				glPushMatrix();
				{
					shapes[1].rotate[0] += 0.5 * (current_time - Prevtime);
					glRotatef(0.5f * (current_time - Prevtime), 1, 0.f, 0);
					glMultMatrixf(shapes[1].identity);
					glGetFloatv(GL_MODELVIEW_MATRIX, shapes[1].identity);
				}
				glPopMatrix();
			}
		}
		if (shapes[1].dir & DIR_X_CW) {
			if (shapes[1].rotate[0] > -90.0) {
				glPushMatrix();
				{
					shapes[1].rotate[0] -= 0.5 * (current_time - Prevtime);
					glRotatef(-0.5f * (current_time - Prevtime), 1, 0.f, 0);
					glMultMatrixf(shapes[1].identity);
					glGetFloatv(GL_MODELVIEW_MATRIX, shapes[1].identity);
				}
				glPopMatrix();
			}
		}
		if (shapes[1].dir & DIR_Y_CCW) {
			glPushMatrix();
			{
				shapes[1].rotate[1] += 0.5 * (current_time - Prevtime);
				//glRotatef(0.5f * (current_time - Prevtime), 0.f, 1.f, 0.f);
				glMultMatrixf(shapes[1].identity);
				glGetFloatv(GL_MODELVIEW_MATRIX, shapes[1].identity);
			}
			glPopMatrix();
		}
		if (shapes[1].dir & DIR_Y_CW) {
			glPushMatrix();
			{
				shapes[1].rotate[1] -= 0.5 * (current_time - Prevtime);
				//glRotatef(-0.5f * (current_time - Prevtime), 0.f, 1.f, 0.f);
				glMultMatrixf(shapes[1].identity);
				glGetFloatv(GL_MODELVIEW_MATRIX, shapes[1].identity);
			}
			glPopMatrix();
		}

		if (shapes[2].dir & DIR_X_CCW) {
			if (shapes[2].rotate[0] < 90.0) {
				glPushMatrix();
				{
					shapes[2].rotate[0] += 0.5 * (current_time - Prevtime);
					glRotatef(0.5f * (current_time - Prevtime), 1, 0.f, 0);
					glMultMatrixf(shapes[2].identity);
					glGetFloatv(GL_MODELVIEW_MATRIX, shapes[2].identity);
				}
				glPopMatrix();
			}
		}
		if (shapes[2].dir & DIR_X_CW) {
			if (shapes[2].rotate[0] > -90.0) {
				glPushMatrix();
				{
					shapes[2].rotate[0] -= 0.5 * (current_time - Prevtime);
					glRotatef(-0.5f * (current_time - Prevtime), 1, 0.f, 0);
					glMultMatrixf(shapes[2].identity);
					glGetFloatv(GL_MODELVIEW_MATRIX, shapes[2].identity);
				}
				glPopMatrix();
			}
		}

		if (shapes[2].dir & DIR_Z_CCW) {
			if (shapes[2].rotate[2] < 90.0) {
				glPushMatrix();
				{
					shapes[2].rotate[2] += 0.5 * (current_time - Prevtime);
					glRotatef(0.5f * (current_time - Prevtime), 0.f, 0.f, 1.f);
					glMultMatrixf(shapes[2].identity);
					glGetFloatv(GL_MODELVIEW_MATRIX, shapes[2].identity);
				}
				glPopMatrix();
			}
		}
		if (shapes[2].dir & DIR_Z_CW) {
			if (shapes[2].rotate[2] > -90.0) {
				glPushMatrix();
				{
					shapes[2].rotate[2] -= 0.5 * (current_time - Prevtime);
					glRotatef(-0.5f * (current_time - Prevtime), 0.f, 0.f, 1.f);
					glMultMatrixf(shapes[2].identity);
					glGetFloatv(GL_MODELVIEW_MATRIX, shapes[2].identity);
				}
				glPopMatrix();
			}
		}
		

		Prevtime = current_time;
		current_frame = 0;
		glutPostRedisplay();

	}
}


CRun_time_Framework::~CRun_time_Framework() {

}