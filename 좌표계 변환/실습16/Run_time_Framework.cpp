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
	glRotatef(rotatey, 0, 1, 0);


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

	glTranslatef(0, 0, 0);

	//glutWireSphere(80, 10, 10);

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
	gluPerspective (60.0, w/h, 1.0, 1.0); 
	glTranslatef (0.0, 0.0, -1.0);

	// ���� �����ΰ��
	// glOrtho (0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

	// �𵨸� ��ȯ ����: ���÷��� �ݹ� �Լ����� �� ��ȯ �����ϱ� ���Ͽ� Matrix mode ����
	glMatrixMode (GL_MODELVIEW);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);

	// ���� ��ȯ: ī�޶��� ��ġ ���� (�ʿ��� ���, �ٸ� ���� ���� ����) 
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);

	return GLvoid();
}

GLvoid CRun_time_Framework::Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'y':
		rotatey += 5;
		break;
	case 'Y':
		rotatey -= 5;
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

GLvoid CRun_time_Framework::Keyinput(unsigned char key, int x, int y) {
	if (myself != nullptr) {
		myself->Keyboard(key, x, y);
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
	myself = this;
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("15"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawscene); // ��� �Լ��� ����
	glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyinput);
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