#include "Run_time_Framework.h"

extern int kind;

CRun_time_Framework* CRun_time_Framework::myself = nullptr;

CRun_time_Framework::CRun_time_Framework() {

}

GLvoid CRun_time_Framework::draw() {
	glClearColor(0, 0, 0, 1); // 바탕색을 지정 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 
	glEnable(GL_DEPTH_TEST);	//깊이테스트
	if (depth)
		glDepthFunc(GL_LESS);		//Passes if the fragment's depth value is less than the stored depth value.
	else
		glDepthFunc(GL_ALWAYS);

	if (culling) {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}
	else
		glDisable(GL_CULL_FACE);

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
	ground();
	glPopMatrix();
	// 피라미드
	glPushMatrix();
	Piramid();
	glPopMatrix();
	// 공
	glPushMatrix();
	Ball();
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
	case '1':
		if (ani_step == 0)
			ani_step++;
		break;
	case '2':
		if (ani_step >= 6) {
			ani_step = 0;
			ball.rotate = 0;
			ball.position[0] = 0;
			ball.position[1] = 350;
			ball.position[2] = 0;
			ball.line = 4;
			ball.t = 0;
			ball_rotate = 0;
			ball_radius = 200;
		}
		break;
	case '3':
		ground_line = (ground_line + 1) % 2;
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
		depth = true;
		culling = false;
		camera.degree[0] = -180;
		camera.degree[1] = -90;
		camera.degree[2] = 90;
		camera.zoom = 500;
		camera.x = 0;
		camera.y = 50;
		memset(identity, 0, sizeof(identity));
		identity[0] = identity[5] = identity[10] = identity[15] = 1;
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
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			point[i][j][0] = -400 + j * 90;
			point[i][j][2] = -400 + i * 90;
			point[i][j][1] = 0;
		}
	}
	point[4][4][1] = 1000;
	point[4][5][1] = 1000;
	point[5][5][1] = 1000;
	point[5][4][1] = 1000;

	ani_step = 0;
	ball_rotate = 0;
	ball_radius = 200;

	camera.zoom = 500;
	camera.x = 0;
	camera.y = 50;

	depth = true;
	culling = false;

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

		switch (ani_step) {
		case 0:
			ball.position[0] = ball_radius * cos(ball_rotate / 180.0*PI);
			ball.position[2] = ball_radius * sin(ball_rotate / 180.0*PI);
			ball_rotate += 0.2f*(current_time - Prevtime);
			break;
		case 1:
			ball.position[0] = ball_radius * cos(ball_rotate / 180.0*PI);
			ball.position[2] = ball_radius * sin(ball_rotate / 180.0*PI);
			ball_radius -= 0.2f*(current_time - Prevtime);
			ball_rotate += 0.2f*(current_time - Prevtime);
			if (ball_radius <= 0)
				ani_step++;
			break;
		case 2:
			ball.position[1] -= 0.2f*(current_time - Prevtime);
			if (ball.position[1] < 300)
				ani_step++;
			break;
		case 3:
			ball.position[1] -= 0.1f*(current_time - Prevtime);
			point[4][4][1] -= 1*(current_time - Prevtime);
			point[4][5][1] -= 1*(current_time - Prevtime);
			point[5][5][1] -= 1*(current_time - Prevtime);
			point[5][4][1] -= 1*(current_time - Prevtime);
			for (int i = 2; i < 8; ++i) {
				for (int j = 2; j < 8; ++j) {
					if ((i != 4 && j != 4) && (i != 5 && j != 5) && (i != 5 && j != 4) && (i != 4 && j != 5)) {
						point[i][j][1] += 0.5*(current_time - Prevtime);
					}
				}
			}

			if (ball.position[1] < 200)
				ani_step++;
			break;
		case 4:
			ball.position[1] += 0.1f*(current_time - Prevtime);
			point[4][4][1] += 1 * (current_time - Prevtime);
			point[4][5][1] += 1 * (current_time - Prevtime);
			point[5][5][1] += 1 * (current_time - Prevtime);
			point[5][4][1] += 1 * (current_time - Prevtime);
			for (int i = 2; i < 8; ++i) {
				for (int j = 2; j < 8; ++j) {
					if ((i != 4 && j != 4) && (i != 5 && j != 5) && (i != 5 && j != 4) && (i != 4 && j != 5)) {
						point[i][j][1] -= 0.5*(current_time - Prevtime);
					}
				}
			}

			if (ball.position[1] > 300)
				ani_step++;
			break;
		case 5:
			ball.rotate += 0.5*(current_time - Prevtime);
			ball.position[2] = ball.t * (point[int(ball.line) + 1][4][2]+45.0) + (1 - ball.t)*(point[int(ball.line)][4][2] + 45.0);
			ball.position[1] -= 0.5*(current_time - Prevtime);;
			ball.t += 0.01*(current_time - Prevtime);
			if (ball.t >= 1.0) {
				ball.line++;
				ball.t = 0;
			}
			if (ball.line >= 9)
				ani_step++;
			break;
		}

		Prevtime = current_time;
		current_frame = 0;
		glutPostRedisplay();

	}
}


CRun_time_Framework::~CRun_time_Framework() {

}