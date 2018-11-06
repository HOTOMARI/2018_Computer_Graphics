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

	glMultMatrixf(identity);

	glRotatef(90, 1, 0, 0);
	Axis();
	Draw_Field();

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
	gluPerspective (60, (float)w / (float)h, 1, 1000);
	glTranslatef (0, 0, -520);

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
		if (top_viewmode == false) {
	case 'z':
		dir |= DIR_X_CCW;
		break;
	case 'Z':
		dir |= DIR_X_CW;
		break;
	case 'x':
		dir |= DIR_Y_CCW;
		break;
	case 'X':
		dir |= DIR_Y_CW;
		break;
	case 'c':
		dir |= DIR_Z_CCW;
		break;
	case 'C':
		dir |= DIR_Z_CW;
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
}

GLvoid CRun_time_Framework::KeyboardUp(unsigned char key, int x, int y) {
	switch (key) {
		if (top_viewmode == false) {
	case 'z':
		dir ^= DIR_X_CCW;
		break;
	case 'Z':
		dir ^= DIR_X_CW;
		break;
	case 'x':
		dir ^= DIR_Y_CCW;
		break;
	case 'X':
		dir ^= DIR_Y_CW;
		break;
	case 'c':
		dir ^= DIR_Z_CCW;
		break;
	case 'C':
		dir ^= DIR_Z_CW;
		break;
		}
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
		if (point_num < 8) {
			if (point_num % 2) {
				point[2][point_num / 2][0] = x - 400;
				point[2][point_num / 2][2] = y - 300;

				point[1][point_num / 2][0] = point[0][point_num / 2][0] + (point[2][point_num / 2][0] - point[0][point_num / 2][0]) / 2;
				point[1][point_num / 2][2] = point[0][point_num / 2][2] + (point[2][point_num / 2][2] - point[0][point_num / 2][2]) / 2;

				int random = rand() % 200 - 100;
				for (int i = 0; i < 3; ++i) {
					point[i][point_num / 2][1] = random;
				}

				point_num++;
			}
			else {
				point[0][point_num / 2][0] = x - 400;
				point[0][point_num / 2][2] = y - 300;
				point_num++;
			}
		}
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::Mouseaction(int button, int state, int x, int y) {
	if (myself != nullptr) {
		myself->Mouse(button, state, x, y);
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::Motion(int x, int y){
}

GLvoid CRun_time_Framework::Mousemotion(int x, int y)
{
	if (myself != nullptr) {
		myself->Motion(x, y);
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::Init() {
	point_num = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int k = 0; k < 3; ++k) {
				point[i][j][k] = 0;
			}
		}
	}

	top_viewmode = false;

	srand(time(NULL));

	memset(identity, 0, sizeof(identity));
	identity[0] = identity[5] = identity[10] = identity[15] = 1;

	camera_is_front = true;

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
	glutMotionFunc(Mousemotion);
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
		if (dir & DIR_Y_CCW) {
			glPushMatrix();
			{
				glRotatef(0.5f * (current_time - Prevtime), 0.f, 1.f, 0.f);
				glMultMatrixf(identity);
				glGetFloatv(GL_MODELVIEW_MATRIX, identity);
			}
			glPopMatrix();
		}
		if (dir & DIR_Y_CW) {
			glPushMatrix();
			{
				glRotatef(-0.5f * (current_time - Prevtime), 0.f, 1.f, 0.f);
				glMultMatrixf(identity);
				glGetFloatv(GL_MODELVIEW_MATRIX, identity);
			}
			glPopMatrix();
		}

		if (dir & DIR_Z_CCW) {
			glPushMatrix();
			{
				glRotatef(0.4f * (current_time - Prevtime), 0.f, 0.f, 1.f);
				glMultMatrixf(identity);
				glGetFloatv(GL_MODELVIEW_MATRIX, identity);
			}
			glPopMatrix();
		}
		if (dir & DIR_Z_CW) {
			glPushMatrix();
			{
				glRotatef(-0.4f * (current_time - Prevtime), 0.f, 0.f, 1.f);
				glMultMatrixf(identity);
				glGetFloatv(GL_MODELVIEW_MATRIX, identity);
			}
			glPopMatrix();
		}
		Prevtime = current_time;
		current_frame = 0;
		glutPostRedisplay();
	}
}


CRun_time_Framework::~CRun_time_Framework() {

}