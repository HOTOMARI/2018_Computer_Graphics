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

	// ����Ʈ ��ȯ ����: ��� ȭ�� ����
	glViewport(0, 0, w, h);

	// Ŭ���� ��ȯ ����: ����ϰ��� �ϴ� ���� ����
	// �Ʒ� 3���� ������ �����ϴ� �Լ� 
	glMatrixMode (GL_PROJECTION); 
	glLoadIdentity ();

	// ������ ���� ���� �Ǵ� ���� ���� �� �Ѱ��� �����Ѵ�.
	// ���� ������ ����ϴ� ���: 
	gluPerspective (60, (float)w / (float)h, 1, 1000);
	glTranslatef (0, 0, -520);

	// ���� �����ΰ��
	// glOrtho (0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

	// �𵨸� ��ȯ ����: ���÷��� �ݹ� �Լ����� �� ��ȯ �����ϱ� ���Ͽ� Matrix mode ����
	glMatrixMode (GL_MODELVIEW);

	// ���� ��ȯ: ī�޶��� ��ġ ���� (�ʿ��� ���, �ٸ� ���� ���� ����) 
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("15"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawscene); // ��� �Լ��� ����
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