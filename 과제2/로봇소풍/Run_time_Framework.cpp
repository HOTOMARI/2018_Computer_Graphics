#include "Run_time_Framework.h"

extern int kind;

CRun_time_Framework* CRun_time_Framework::myself = nullptr;

CRun_time_Framework::CRun_time_Framework() {

}

GLvoid CRun_time_Framework::draw() {
	glClearColor(0, 0, 0, 1); // 바탕색을 지정 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 
	glEnable(GL_DEPTH_TEST);	//깊이테스
	glDepthFunc(GL_LESS);		//Passes if the fragment's depth value is less than the stored depth value.


	glPushMatrix();

	if (play_mode == 2) {
		if (nowCamera == 0) {
			gluLookAt(0, 0, camera.zoom, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
			gluLookAt(camera.x, camera.y, 0, camera.x, camera.y, -100.0, cos(camera.degree[2] / 180 * PI), sin(camera.degree[2] / 180 * PI), 0.0);
			gluLookAt(cos(camera.degree[1] / 180 * PI) * 200, 0, sin(camera.degree[1] / 180 * PI) * 200, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
			if ((fabs((int)camera.degree[0] % 360) <= 120 && fabs((int)camera.degree[0] % 360) >= 0) ||
				(fabs((int)camera.degree[0] % 360) <= 360 && fabs((int)camera.degree[0] % 360) > 240))
				gluLookAt(0, sin(camera.degree[0] / 180 * PI) * 200, cos(camera.degree[0] / 180 * PI) * 200, 0.0, 0.0, -100.0, 0.0, -1.0, 0.0);
			else
				gluLookAt(0, sin(camera.degree[0] / 180 * PI) * 200, cos(camera.degree[0] / 180 * PI) * 200, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
		}
		else if (nowCamera == 1) {
			gluLookAt((Gridman[0].position[0] + sin(Gridman[0].dir*90.0 / 180.0*PI) * 400), Gridman[0].position[1], Gridman[0].position[2] + cos(Gridman[0].dir*90.0 / 180.0*PI) * 400,
				(Gridman[0].position[0] + sin(Gridman[0].dir*90.0 / 180.0*PI) * 400) + sin(Gridman[0].dir*90.0 / 180.0*PI)*2000.0, Gridman[0].position[1], (Gridman[0].position[2] + cos(Gridman[0].dir*90.0 / 180.0*PI) * 400) + cos(Gridman[0].dir*90.0 / 180.0*PI)*2000.0,
				0, 1.0, 0);
		}
	}
	else {
		if (play_mode == 0)
			glRotatef(90, 1, 0, 0);
		else
			glRotatef(90, 0, 1, 0);
	}
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
	ground();
	// 나무
	Tree();
	//컨트롤포인트
	draw_points();
	// 경로
	draw_rails();

	if (play_mode == 2) {
		// 로봇
		Robot();
		// 총알
		draw_bullets();
	}

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
	if (play_mode == 2) {
		gluPerspective(60, (float)w / (float)h, 1, 2000);
		glTranslatef(0, 0, -400);
	}

	// 직각 투영인경우
	else glOrtho (-400.0, 400.0, -400.0, 400.0, -400.0, 400.0);

	// 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장
	glMatrixMode (GL_MODELVIEW);

	// 관측 변환: 카메라의 위치 설정 (필요한 경우, 다른 곳에 설정 가능) 
	//gluLookAt(0.0, 0.0, camera_zoom, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);

	return GLvoid();
}

GLvoid CRun_time_Framework::KeyboardDown(unsigned char key, int x, int y) {
	if (play_mode == 2) {
		switch (key) {
		case 't':
			play_mode = 0;
			Reshape(800, 800);
			break;

		case '1':
			nowCamera = 0;
			break;
		case '2':
			nowCamera = 1;
			break;
		case '3':
			nowCamera = 2;
			break;

		case 's':
			Gridman[0].dir = 0;
			break;
		case 'd':
			Gridman[0].dir = 1;
			break;
		case 'w':
			Gridman[0].dir = 2;
			break;
		case 'a':
			Gridman[0].dir = 3;
			break;

		case 'q':
			make_bullet(0);
			make_bullet(1);
			break;

		case 'z':
			camera.zoom += 30.0;
			break;
		case 'Z':
			camera.zoom += -30.0;
			break;

		case 'u':
			camera.y += 10;
			break;
		case 'U':
			camera.y -= 10;
			break;
		case 'c':
			camera.x -= 10;
			break;
		case 'C':
			camera.x += 10;
			break;

		case 'x':
			camera.degree[0] += 10.0;
			break;
		case 'X':
			camera.degree[0] -= 10.0;
			break;
		case 'y':
			camera.degree[1] += 10.0;
			break;
		case 'Y':
			camera.degree[1] -= 10.0;
			break;

		case 'i':
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
	else {
		switch (key) {
		case 't':
			play_mode = (play_mode + 1) % 2;
			break;
		case 'q':
			if (set_pointsnum >= 2) {
				play_mode = 2;
				Reshape(800,800);
			}
			break;
		}
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
	if (play_mode == 0) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (grounds[y / 80][x / 80].type == 0 && set_pointsnum < 10) {
				point[set_pointsnum][0] = (x / 80) * 80 - 360;
				point[set_pointsnum][1] = -100 + (rand() % 100);
				point[set_pointsnum][2] = (y / 80) * 80 - 360;
				set_pointsnum++;
			}
		}
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			for (int i = 0; i < 10; ++i) {
				if (pow(point[i][0] - (x - 400), 2) + pow(point[i][2] - (y - 400), 2) < 400 && i < set_pointsnum) {
					picked[i] = true;
					pick_tmp[0] = point[i][0];
					pick_tmp[2] = point[i][2];
					break;
				}
			}
		}
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
			for (int i = 0; i < 10; ++i) {
				if (picked[i]) {
					picked[i] = false;
					for (int j = 0; j < 10; ++j) {
						if (pow(point[i][0] - (object[j].left + 10), 2) + pow(point[i][2] - (object[j].top + 10), 2) <= 3600) {
							point[i][0] = pick_tmp[0];
							point[i][2] = pick_tmp[2];
							break;
						}
					}
				}
			}
		}
	}
	else if (play_mode == 1) {
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			for (int i = 0; i < 10; ++i) {
				if (pow(point[i][2] - (x - 400), 2) + pow(point[i][1] - (400 - y), 2) < 400 && i < set_pointsnum) {
					picked[i] = true;
					pick_tmp[1] = point[i][1];
					break;
				}
			}
		}
		else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
			for (int i = 0; i < 10; ++i) {
				if (picked[i]) {
					picked[i] = false;
					if (point[i][1] < -100) {
						point[i][1] = pick_tmp[1];
						break;
					}
				}
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

GLvoid CRun_time_Framework::Motion(int x, int y)
{
	if (play_mode == 0) {
		for (int i = 0; i < 10; ++i) {
			if (picked[i]) {
				point[i][0] = x - 400;
				point[i][2] = y - 400;
			}
		}
	}
	else if (play_mode == 1) {
		for (int i = 0; i < 10; ++i) {
			if (picked[i]) {
				point[i][1] = 400 - y;
			}
		}
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::Mousemotion(int x, int y)
{
	if (myself != nullptr) {
		myself->Motion(x, y);
	}
	return GLvoid();
}


GLvoid CRun_time_Framework::Init() {
	srand(time(NULL));
	set_trees();
	set_robots();

	set_pointsnum = 0;
	play_mode = 0;
	for (int i = 0; i < 10; ++i)
		picked[i] = false;

	bullets = NULL;
	combined = false;
	comb_t = 0;

	camera.zoom = 500;
	camera.x = 0;
	camera.y = 50;
	nowCamera = 0;

	myself = this;
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 800); // 윈도우의 크기 지정
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

		if (play_mode == 2) {
			update_bb();
			// 로봇 & 나무
			for (int j = 0; j < 2; ++j) {
				for (int i = 0; i < 10; ++i) {
					if (collide(Gridman[j].bb, object[i])) {
						Gridman[j].state_collide = true;
						break;
					}
					else {
						Gridman[j].state_collide = false;
					}
				}
			}
			// 로봇 & 로봇
			if (collide(Gridman[0].bb, Gridman[1].bb)) {
				combined = true;
				Gridman[1].dir = Gridman[0].dir;
			}
			Bullet* t = bullets;
			while (t != NULL) {
				//총알 & 로봇
				for (int i = 0; i < 2; ++i) {
					if (collide(Gridman[i].bb, t->bb) && t->owner != i && !combined) {
						t->hit = true;
						break;
					}
				}
				//총알 & 나무
				for (int i = 0; i < 10; ++i) {
					if (collide(object[i], t->bb)) {
						t->hit = true;
						break;
					}
				}
				t = t->next;
			}
			update_robots();
			go_comb();
			update_bullets();
			delete_bullets();
		}

		Prevtime = current_time;
		current_frame = 0;
		glutPostRedisplay();

	}
}


CRun_time_Framework::~CRun_time_Framework() {

}