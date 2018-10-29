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
	//벽
	glPushMatrix();
	wall();
	glPopMatrix();
	//나무
	glPushMatrix();
	tree();
	glPopMatrix();
	//철봉
	glPushMatrix();
	metal_pole();
	glPopMatrix();
	//벤치프레스
	glPushMatrix();
	bench_press();
	glPopMatrix();
	//러닝머신
	glPushMatrix();
	treadmill();
	glPopMatrix();
	//비행기
	glPushMatrix();
	airplane();
	glPopMatrix();
	// 로봇
	glPushMatrix();
	robot();
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

	case 'o':
	case 'O':
		front_up = (front_up + 1) % 2;
		break;

	case '1':
		depth = (depth + 1) % 2;
		break;
	case '2':
		culling = (culling + 1) % 2;
		break;
	case '3':
		Gridman.dir = 0;
		break;
	case '4':
		Gridman.dir = 1;
		break;
	case '5':
		Gridman.dir = 2;
		break;
	case '6':
		Gridman.dir = 3;
		break;
	case '0':
		see_collide = (see_collide + 1) % 2;


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
	Gridman.position[1] = 40;
	Gridman.bb.left = -40;
	Gridman.bb.right = 40;
	Gridman.bb.top = 40;
	Gridman.bb.bottom = -40;

	object[0].left = -380;
	object[0].right = -320;
	object[0].top = -220;
	object[0].bottom = -280;

	object[1].left = -400;
	object[1].right = -280;
	object[1].top = 280;
	object[1].bottom = 200;

	object[2].left = 270;
	object[2].right = 400;
	object[2].top = 350;
	object[2].bottom = 150;

	object[3].left = 260;
	object[3].right = 400;
	object[3].top = -200;
	object[3].bottom = -300;

	Smoke[0].size = 50;
	Smoke[1].size = 30;
	Smoke[2].size = 10;

	crane_dir = 0;
	ball_dir = 2;
	airplane_dir = 0;

	tree_size = 0.2;
	metal_pole_rotate = 0;
	treadmill_rotate = 0;
	leg_rotate = 0;
	propeller_rotate = 0;
	airplane_rotate = 0;
	airplane_spin = 0;
	bench = 0;
	front_ani = 0;

	camera_is_front = true;
	crane_right = true;
	tree_bigger = true;
	bench_up = true;
	leg_up = true;
	see_collide = false;
	front_up = false;

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

		if (front_up) {
			if (front_ani < 400) {
				front_ani += 1 * (current_time - Prevtime);
			}
			else {
				front_ani = 400;
			}
		}
		else {
			if (front_ani > 0) {
				front_ani -= 1 * (current_time - Prevtime);
			}
			else {
				front_ani = 0;
			}
		}

		if (tree_bigger) {
			tree_size += 0.001 * (current_time - Prevtime);
			if (tree_size > 1.0)
				tree_bigger = false;
		}
		else {
			tree_size -= 0.001 * (current_time - Prevtime);
			if (tree_size < 0.2)
				tree_bigger = true;
		}

		metal_pole_rotate += 0.1*(current_time - Prevtime);

		if (bench_up) {
			bench += 0.1 * (current_time - Prevtime);
			if (bench > 10)
				bench_up = false;
		}
		else {
			bench -= 0.1 * (current_time - Prevtime);
			if (bench < -20)
				bench_up = true;
		}

		treadmill_rotate += 0.1*(current_time - Prevtime);

		if (leg_up) {
			leg_rotate += 0.1 * (current_time - Prevtime);
			if (leg_rotate > 30)
				leg_up = false;
		}
		else {
			leg_rotate -= 0.1 * (current_time - Prevtime);
			if (leg_rotate < -30)
				leg_up = true;
		}

		propeller_rotate += 2 * (current_time - Prevtime);

		if (airplane_dir)
			airplane_rotate += 0.1 * (current_time - Prevtime);
		else
			airplane_rotate -= 0.1 * (current_time - Prevtime);
	
		update_bb();

		for (int i = 0; i < 3; ++i) {
			Smoke[i].size -= 0.1 * (current_time - Prevtime);
		}
		if (Smoke[2].size <= 0) {
			Smoke[2].size = Smoke[1].size + 10;
			Smoke[1].size = Smoke[0].size + 5;
			Smoke[0].size = rand() % 40 + 20;
		}

		switch (Gridman.dir) {
		case 0:
			//Gridman.position[2] += 0.1 * (current_time - Prevtime);

			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		}

		if (Gridman.animation_state) {
			Gridman.animation += 0.2 * (current_time - Prevtime);
			if (Gridman.animation > 60) {
				Gridman.animation_state = false;
			}
		}
		else {
			Gridman.animation -= 0.2 * (current_time - Prevtime);
			if (Gridman.animation < -60) {
				Gridman.animation_state = true;
			}
		}

		Prevtime = current_time;
		current_frame = 0;
		glutPostRedisplay();

	}
}


CRun_time_Framework::~CRun_time_Framework() {

}