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

	Draw_fonts();

	glEnable(GL_LIGHTING);

	GLfloat pos[] = { -500, 500, 400, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	Draw_Shapes();

	glDisable(GL_LIGHTING);
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
	//gluPerspective (60, (float)w / (float)h, 1, 5000);
	//glTranslatef (0, 0, -400);

	// 직각 투영인경우
	glOrtho (-450.0, 450.0, -450.0, 450.0, -400, 400);

	// 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장
	glMatrixMode (GL_MODELVIEW);

	// 관측 변환: 카메라의 위치 설정 (필요한 경우, 다른 곳에 설정 가능) 
	//gluLookAt(0.0, 0.0, camera_zoom, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);

	return GLvoid();
}

GLvoid CRun_time_Framework::KeyboardDown(unsigned char key, int x, int y) {
	switch (key) {
	case '0':
		sel = 0;
		break;
	case '1':
		sel = 1;
		break;
	case '2':
		sel = 2;
		break;
	case '3':
		sel = 3;
		break;
	case '4':
		sel = 4;
		break;
	case '5':
		sel = 5;
		break;
	case '6':
		sel = 6;
		break;
	case '7':
		sel = 7;
		break;
	case '8':
		sel = 8;
		break;

	case 'z':
		shape[sel].alpha[0] += 0.1;
		if (shape[sel].alpha[0] > 1)
			shape[sel].alpha[0] = 1;
		break;
	case 'Z':
		shape[sel].alpha[0] -= 0.1;
		if (shape[sel].alpha[0] < 0)
			shape[sel].alpha[0] = 0;
		break;
	case 'x':
		shape[sel].alpha[1] += 0.1;
		if (shape[sel].alpha[1] > 1)
			shape[sel].alpha[1] = 1;
		break;
	case 'X':
		shape[sel].alpha[1] -= 0.1;
		if (shape[sel].alpha[1] < 0)
			shape[sel].alpha[1] = 0;
		break;
	case 'c':
		shape[sel].alpha[2] += 0.1;
		if (shape[sel].alpha[2] > 1)
			shape[sel].alpha[2] = 1;
		break;
	case 'C':
		shape[sel].alpha[2] -= 0.1;
		if (shape[sel].alpha[2] < 0)
			shape[sel].alpha[2] = 0;
		break;
	
	}
}

GLvoid CRun_time_Framework::KeyboardUp(unsigned char key, int x, int y) {
	switch (key) {

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
	srand(time(NULL));

	camera.zoom = 500;
	camera.x = 0;
	camera.y = 0;

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 3; ++j) {
			shape[i].alpha[j] = rand() % 100;
			shape[i].alpha[j] = shape[i].alpha[j] / 100.0;
		}
	}

	sel = 0;

	myself = this;
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(900, 900); // 윈도우의 크기 지정
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


		Prevtime = current_time;
		current_frame = 0;
		glutPostRedisplay();

	}
}


CRun_time_Framework::~CRun_time_Framework() {

}