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
	
	// �ؽ�ó ���� Ȱ��ȭ 
	glEnable(GL_TEXTURE_2D);
	//skybox
	Skybox();

	glEnable(GL_LIGHTING);		//���� Ȱ��ȭ

	glLightfv(GL_LIGHT0, GL_AMBIENT, light[0].AmbientColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light[0].DiffuseColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light[0].SpecularColor);
	glLightfv(GL_LIGHT0, GL_POSITION, light[0].position);
	if (light[0].on)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light[1].AmbientColor);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light[1].DiffuseColor);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light[1].SpecularColor);
	glLightfv(GL_LIGHT1, GL_POSITION, light[1].position);
	glEnable(GL_LIGHT1);
	if (light[1].on)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);

	GLfloat pos[4] = { 0,100,1,0 };
	GLfloat a[] = { 0.2,0.2,0.2,1.0 };
	GLfloat d[] = { 0.8,0.8,0.8,1.0 };

	glLightfv(GL_LIGHT7, GL_AMBIENT, a);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, d);
	glLightfv(GL_LIGHT7, GL_SPECULAR, WhiteLight);
	glLightfv(GL_LIGHT7, GL_POSITION, pos);
	if (uplighton)
		glEnable(GL_LIGHT7);
	else
		glDisable(GL_LIGHT7);

	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);


	glEnable(GL_FOG);
	if (fogmmode == 0)
		glFogf(GL_FOG_MODE, GL_LINEAR);
	else if (fogmmode == 1)
		glFogf(GL_FOG_MODE, GL_EXP);
	else if (fogmmode == 2)
		glFogf(GL_FOG_MODE, GL_EXP2);

	glFogfv(GL_FOG_COLOR, fog_color);
	glFogf(GL_FOG_START, start);
	glFogf(GL_FOG_END, end);

	glFogf(GL_FOG_DENSITY, density);

	// �ٴ�
	Draw_Ground();
	//�Ƕ�̵�
	Draw_Piramid();
	//��
	Draw_Ball();
	//����
	Draw_Cone();
	// ���
	Pilar();
	// ��
	Draw_Snow();

	glDisable(GL_TEXTURE_2D);
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
	gluPerspective (60, (float)w / (float)h, 1, 5000);
	glTranslatef (0, 0, -400);

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
	case 'h':
		density += 0.005;
		if (density > 1.0)
			density = 1.0;
		break;
	case 'H':
		density -= 0.005;
		if (density < 0.0)
			density = 0.0;
		break;
	case 'j':
		start += 50;
		break;
	case 'J':
		start -= 50;
		break;
	case 'k':
		end += 50;
		break;
	case 'K':
		end -= 50;
		break;
	case'l':
		fogmmode = (fogmmode + 1) % 3;
		break;
	case';':
		snowon = (snowon + 1) % 2;
		break;
	


	case '1':
		light[0].on = (light[0].on + 1) % 2;
		break;
	case '2':
		light[1].on = (light[1].on + 1) % 2;
		break;
	case '3':
		uplighton = (uplighton + 1) % 2;
		break;
	case 'b':
	case 'B':
		normal = (normal + 1) % 2;
		break;
	case 'z':
	case 'Z':
		move_light = (move_light + 1) % 2;
		break;
	case 'x':
		if (light[0].AmbientColor[1] < 1.0) {
			light[0].AmbientColor[1] += 0.1;
			if (light[0].AmbientColor[1] > 1.0) {
				light[0].AmbientColor[1] = 1.0;
			}
		}
		if (light[1].AmbientColor[0] < 1.0) {
			light[1].AmbientColor[0] += 0.1;
			if (light[1].AmbientColor[0] > 1.0) {
				light[1].AmbientColor[0] = 1.0;
			}
		}
		break;
	case 'X':
		if (light[0].AmbientColor[1] > 0.0) {
			light[0].AmbientColor[1] -= 0.1;
			if (light[0].AmbientColor[1] < 0.0) {
				light[0].AmbientColor[1] = 0.0;
			}
		}
		if (light[1].AmbientColor[0] > 0.0) {
			light[1].AmbientColor[0] -= 0.1;
			if (light[1].AmbientColor[0] < 0.0) {
				light[1].AmbientColor[0] = 0.0;
			}
		}
		break;
	case 'c':
		if (light[0].DiffuseColor[1] < 1.0) {
			light[0].DiffuseColor[1] += 0.1;
			if (light[0].DiffuseColor[1] > 1.0) {
				light[0].DiffuseColor[1] = 1.0;
			}
		}
		if (light[1].DiffuseColor[0] < 1.0) {
			light[1].DiffuseColor[0] += 0.1;
			if (light[1].DiffuseColor[0] > 1.0) {
				light[1].DiffuseColor[0] = 1.0;
			}
		}
			break;
	case 'C':
		if (light[0].DiffuseColor[1] > 0.0) {
			light[0].DiffuseColor[1] -= 0.1;
			if (light[0].DiffuseColor[1] < 0.0) {
				light[0].DiffuseColor[1] = 0.0;
			}
		}
		if (light[1].DiffuseColor[0] > 0.0) {
			light[1].DiffuseColor[0] -= 0.1;
			if (light[1].DiffuseColor[0] < 0.0) {
				light[1].DiffuseColor[0] = 0.0;
			}
		}
		break;
	case 'v':
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (light[i].SpecularColor[j] < 1.0) {
					light[i].SpecularColor[j] += 0.1;
					if (light[i].SpecularColor[j] > 1.0) {
						light[i].SpecularColor[j] = 1.0;
					}
				}
			}
		}
		break;
	case 'V':
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 3; ++j) {
				if (light[i].SpecularColor[j] > 0.0) {
					light[i].SpecularColor[j] -= 0.1;
					if (light[i].SpecularColor[j] < 0.0) {
						light[i].SpecularColor[j] = 0.0;
					}
				}
			}
		}
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

	camera.zoom = 500;
	camera.x = 0;
	camera.y = 0;
	Init_Light();
	move_light = false;
	normal = true;
	moon_degree = 0;
	for (int i = 0; i < 5; ++i)
		Scroll[i] = i * 0.25;

	for (int i = 0; i < 50; ++i) {
		for (int j = 0; j < 50; ++j) {
			ground[i][j].left = -400 + 16 * j;
			ground[i][j].right = -400 + 16 * (j + 1);
			ground[i][j].top = -400 + 16 * i;
			ground[i][j].bottom = -400 + 16 * (i + 1);		
		}
	}
	snowon = true;
	fog_color[0] = 0.7;
	fog_color[1] = 0.7; 
	fog_color[2] = 0.7; 
	fog_color[3] = 1.0; 
	density = 0.001;
	start = 100;
	end = 400;
	fogmmode = 0;
	uplighton = true;
	sier = 0;
	snow = NULL;
	snowstack = 0;

	srand(time(NULL));
	myself = this;
	//glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("15"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawscene); // ��� �Լ��� ����
	glutReshapeFunc(Resize);
	glutKeyboardFunc(KeyDowninput);
	glutKeyboardUpFunc(KeyUpinput);
	glutMouseFunc(Mouseaction);
	glutIdleFunc(Updatecallback);
	set_texture();
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
		if (move_light) {
			light[0].degree += 0.3*(current_time - Prevtime);
			light[1].degree += 0.3*(current_time - Prevtime);
		}
		UpdateLight();

		for (int i = 0; i < 5; ++i) {
			Scroll[i] -= 0.0002*(current_time - Prevtime);
			
		}

		sier += 0.003*(current_time - Prevtime);
		if (sier > 5)
			sier = 0;

		moon_degree += 0.2*(current_time - Prevtime);

		if (snowon)
			snowstack += 0.2*(current_time - Prevtime);
		if (snowstack > 3) {
			Make_Snow();
			snowstack = 0;
		}
		UpdateSnow();
		Delete_Snow();

		Prevtime = current_time;
		current_frame = 0;
		glutPostRedisplay();

	}
}


CRun_time_Framework::~CRun_time_Framework() {

}