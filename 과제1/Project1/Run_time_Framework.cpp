#include "Run_time_Framework.h"

extern int kind;

CRun_time_Framework* CRun_time_Framework::myself = nullptr;

CRun_time_Framework::CRun_time_Framework() {

}

GLvoid CRun_time_Framework::draw() {
	glClearColor(0, 0, 0, 1); // 바탕색을 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 
	glMatrixMode(GL_MODELVIEW);

	Draw_Tri();
	Draw_Rect();
	if (line.see) {
		Draw_Line();
	}
	Draw_Fragments();
	Draw_Trash();

	glutSwapBuffers();
}

GLvoid CRun_time_Framework::Reshape(int w, int h) {
	if (w > 0)
		m_nWidth = w;
	if (h > 0)
		m_nHeight = h;

	glViewport(0, 0, w, h);
	glOrtho (-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);

}

GLvoid CRun_time_Framework::KeyboardDown(unsigned char key, int x, int y) {
	switch (key) {
	
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
		if (line_finished == false) {
			line.see = true;
			line.x1 = line.x2 = x - 400;
			line.y1 = line.y2 = -1 * (y - 300);
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		line.see = false;
		line_finished = true;
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::Motion(int x, int y)
{
	if (line.see) {
		line.x2 = x - 400;
		line.y2 = -1 * (y - 300);
	}
	return GLvoid();
}

GLvoid CRun_time_Framework::Mouseaction(int button, int state, int x, int y) {
	if (myself != nullptr) {
		myself->Mouse(button, state, x, y);
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
	triangle = NULL;
	rectangle = NULL;
	Make_Tri();
	Make_Rect();
	make_timer[0] = 0;
	make_timer[1] = 0;
	trash_count = 0;

	trash[1][0].fill = true;

	line_finished = false;

	srand(time(NULL));
	myself = this;
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
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

		Update_Tri();
		Delete_ScreenOut_Tri();

		Update_Rect();
		Delete_ScreenOut_Rect();

		make_timer[0]++;
		make_timer[1]++;
		if (make_timer[0] > 120) {
			Make_Tri();
			make_timer[0] = 0;
		}
		if (make_timer[1] > 200) {
			Make_Rect();
			make_timer[1] = 0;
		}

		if (line_finished && line.see==false) {
			Rect* t = rectangle;
			int index = 0;
			while (t != NULL) {
				if ((collide_Line_and_Line(line.x1, line.x2, t->p[0].x, t->p[1].x, line.y1, line.y2, t->p[0].y, t->p[1].y)||
					collide_Line_and_Line(line.x1, line.x2, t->p[1].x, t->p[2].x, line.y1, line.y2, t->p[1].y, t->p[2].y)||
					collide_Line_and_Line(line.x1, line.x2, t->p[2].x, t->p[3].x, line.y1, line.y2, t->p[2].y, t->p[3].y)||
					collide_Line_and_Line(line.x1, line.x2, t->p[3].x, t->p[0].x, line.y1, line.y2, t->p[3].y, t->p[0].y)) && t->live &&
					fragments[0].live == false && fragments[1].live == false &&
					(t->p[2].y > -190 && t->p[2].y < 190)) {
					t->live = false;
					printf("collide RECT%d!\n", index);
					Make_Fragments(t);
					break;
				}
				index++;
				t = t->next;
			}
			line_finished = false;
		}

		Update_Fragments();
		Update_Trash();

		Prevtime = current_time;
		current_frame = 0;
		glutPostRedisplay();
	}
}


CRun_time_Framework::~CRun_time_Framework() {

}