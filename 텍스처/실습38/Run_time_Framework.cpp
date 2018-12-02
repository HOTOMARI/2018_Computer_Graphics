#include "Run_time_Framework.h"

extern int kind;

CRun_time_Framework* CRun_time_Framework::myself = nullptr;

CRun_time_Framework::CRun_time_Framework() {

}

GLvoid CRun_time_Framework::draw() {
	glClearColor(0, 0, 0, 1); // �������� ���� 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

	glEnable(GL_DEPTH_TEST);	//�����׽�Ʈ
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

	// ����Ʈ ��ȯ ����: ��� ȭ�� ����
	glViewport(0, 0, w, h);

	// Ŭ���� ��ȯ ����: ����ϰ��� �ϴ� ���� ����
	// �Ʒ� 3���� ������ �����ϴ� �Լ� 
	glMatrixMode (GL_PROJECTION); 
	glLoadIdentity ();

	// ������ ���� ���� �Ǵ� ���� ���� �� �Ѱ��� �����Ѵ�.
	// ���� ������ ����ϴ� ���: 
	//gluPerspective (60, (float)w / (float)h, 1, 5000);
	//glTranslatef (0, 0, -400);

	// ���� �����ΰ��
	glOrtho (-450.0, 450.0, -450.0, 450.0, -400, 400);

	// �𵨸� ��ȯ ����: ���÷��� �ݹ� �Լ����� �� ��ȯ �����ϱ� ���Ͽ� Matrix mode ����
	glMatrixMode (GL_MODELVIEW);

	// ���� ��ȯ: ī�޶��� ��ġ ���� (�ʿ��� ���, �ٸ� ���� ���� ����) 
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(900, 900); // �������� ũ�� ����
	glutCreateWindow("15"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawscene); // ��� �Լ��� ����
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