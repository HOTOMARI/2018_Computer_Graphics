#include <GL/freeglut.h>
#include<time.h>
#include<math.h>
#define PI 3.141592
GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid Timerfunction(int);


struct Shape {
	double base, height, size, radius[2];
	int stacks, slices, sides, rings;

	int type = 0;		// 0 원뿔 1 육면체 2 구 3 도넛 4 주전자
	float R, G, B;
	int rotate_degree;
	int axis;			// 1 x축 2 y축 2 3축
	float x, y;
	float scale;

	bool rotate_left;
	bool dead = true;
};

Shape shapes[20];


void main(int argc, char** argv) // 윈도우 출력하고 출력함수 설정 
{
	// 초기화 함수들 
	glutInit(&argc, argv); // glut 초기화 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Tiles"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(DrawScene); // 출력 함수의 지정 
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정 
	glutTimerFunc(1000 / 60, Timerfunction, 1);	// 타이머 셋팅
	glutMouseFunc(Mouse);		// 마우스 버튼 입력 받기
	glutKeyboardFunc(Keyboard);	// 키보드 입력 받기

	srand(time(NULL));

	glutMainLoop(); // 이벤트 처리 시작 
}

GLvoid DrawScene() // 출력 함수 
{
	glClearColor(0, 0, 0, 1); // 바탕색을 지정 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 
	glEnable(GL_DEPTH_TEST);	//깊이테스트
	glDepthFunc(GL_LESS);		//Passes if the fragment's depth value is less than the stored depth value.
	glMatrixMode(GL_MODELVIEW);


	for (int i = 0; i < 20; ++i) {
		if (shapes[i].dead == false) {
			glPushMatrix();
			glColor3f(shapes[i].R, shapes[i].G, shapes[i].B);
			glTranslated(shapes[i].x, shapes[i].y, 0);
			glScaled(1.0+shapes[i].scale, 1.0 + shapes[i].scale, 1.0 + shapes[i].scale);
			//glRotatef(shapes[i].rotate_degree, 0, 1, 0);
			glRotatef(shapes[i].rotate_degree, shapes[i].axis / 1, shapes[i].axis / 2, shapes[i].axis / 3);

			switch (shapes[i].type) {
			case 0:
				glutWireCone(shapes[i].base, shapes[i].height, shapes[i].slices, shapes[i].stacks);
				break;
			case 1:
				glutWireCube(shapes[i].size);
				break;
			case 2:
				glutWireSphere(shapes[i].radius[0], shapes[i].slices, shapes[i].stacks);
				break;
			case 3:
				glutWireTorus(shapes[i].radius[0], shapes[i].radius[1], shapes[i].sides, shapes[i].rings);
				break;
			case 4:
				glutWireTeapot(shapes[i].size);
				break;
			}
			glPopMatrix();
		}
	}

	glutSwapBuffers(); // 화면에 출력하기 
}

GLvoid Reshape(int w, int h) // 다시 그리기 함수 
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);
}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = 0; i < 20; ++i) {
			if (shapes[i].dead) {
				shapes[i].type = rand() % 5;
				switch (shapes[i].type) {
				case 0:
					shapes[i].base = rand() % 200 + 50;
					shapes[i].height = rand() % 200 + 50;
					shapes[i].slices = rand() % 10 + 3;
					shapes[i].stacks = rand() % 10 + 3;
					break;
				case 1:
				case 4:
					shapes[i].size = rand() % 100 + 50;
					break;
				case 2:
					shapes[i].radius[0] = rand() % 100 + 50;
					shapes[i].slices = rand() % 10 + 3;
					shapes[i].stacks = rand() % 10 + 3;
					break;
				case 3:
					shapes[i].radius[0] = rand() % 30 + 50;
					shapes[i].radius[1] = rand() % 30 + 100;
					shapes[i].sides = rand() % 10 + 5;
					shapes[i].rings = rand() % 10 + 8;
					break;
				}
				shapes[i].x = x - 400;
				shapes[i].y = -1 * y + 300;
				shapes[i].rotate_degree = rand() % 360;
				shapes[i].R = rand() % 255 / 255.0;
				shapes[i].G = rand() % 255 / 255.0;
				shapes[i].B = rand() % 255 / 255.0;
				shapes[i].axis = rand() % 3 + 1;
				if (rand() % 2)
					shapes[i].rotate_left = true;
				else shapes[i].rotate_left = false;
				shapes[i].scale = 0;
				shapes[i].dead = false;
				break;
			}
		}
	}
	glutPostRedisplay();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
		glutLeaveMainLoop();
		break;
	case 'r':
	case 'R':
		for (int i = 0; i < 20; ++i) {
			if (shapes[i].dead == false) {
				if (shapes[i].rotate_left)
					shapes[i].rotate_left = false;
				else shapes[i].rotate_left = true;
			}
		}
		break;
	}

}

GLvoid Timerfunction(int value) {
	switch (value) {
	case 1:
		for (int i = 0; i < 20; ++i) {
			if (shapes[i].dead == false) {
				shapes[i].scale -= 0.003;
				if (shapes[i].scale <= -1.0)
					shapes[i].dead = true;
				if (shapes[i].rotate_left) {
					shapes[i].rotate_degree -= 5;
					if (shapes[i].rotate_degree < 0) {
						shapes[i].rotate_degree = 360 + shapes[i].rotate_degree;
					}
				}
				else {
					shapes[i].rotate_degree += 5;
					if (shapes[i].rotate_degree > 360) {
						shapes[i].rotate_degree = shapes[i].rotate_degree - 360;
					}
				}
			}
		}
		glutPostRedisplay();
		glutTimerFunc(1000/ 60, Timerfunction, 1);
		break;
	}
}