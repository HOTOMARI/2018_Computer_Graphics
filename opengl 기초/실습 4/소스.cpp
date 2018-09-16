#include <GL/freeglut.h>
#include<time.h>
GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Timerfunction(int);

struct Shape {
	int size = 0;		// 1 ~ 10 변화
	bool bigger_size = true;	// 사각형 커지는지 작아지는지
	bool alive = false;			// 보이기 안보이기
	float R, G, B;				// 색깔
	RECT rect;
};

Shape shape[10];

int now_shape = 0;

void main(int argc, char** argv) // 윈도우 출력하고 출력함수 설정 
{
	// 초기화 함수들 
	glutInit(&argc, argv); // glut 초기화 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Tiles"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(DrawScene); // 출력 함수의 지정 
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정 
	glutTimerFunc(1000 / 60, Timerfunction, 1);	// 타이머 셋팅
	glutMouseFunc(Mouse);		// 마우스 버튼 입력 받기

	srand(time(NULL));

	glutMainLoop(); // 이벤트 처리 시작 
}

GLvoid DrawScene() // 출력 함수 
{
	glClearColor(0, 0, 0, 1); // 바탕색을 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 

	for (int i = 0; i < 10; ++i) {
		if (shape[i].alive) {
			glColor4f(shape[i].R, shape[i].G, shape[i].B, 1);
			glRectf(shape[i].rect.left - shape[i].size * 5, shape[i].rect.top + shape[i].size * 5,
				shape[i].rect.right + shape[i].size * 5, shape[i].rect.bottom - shape[i].size * 5);
		}
	}


	glFlush(); // 화면에 출력하기 
}

GLvoid Reshape(int w, int h) // 다시 그리기 함수 
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);
}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		shape[now_shape].alive = true;
		shape[now_shape].R = rand() % 255 / 255.0;
		shape[now_shape].G = rand() % 255 / 255.0;
		shape[now_shape].B = rand() % 255 / 255.0;
		shape[now_shape].size = rand() % 8 + 1;
		shape[now_shape].rect.left = x - 400;
		shape[now_shape].rect.right = shape[now_shape].rect.left + shape[now_shape].size * 5;
		shape[now_shape].rect.bottom = -1*y + 300;
		shape[now_shape].rect.top = shape[now_shape].rect.bottom + shape[now_shape].size * 5;
		now_shape++;
		if (now_shape > 9)
			now_shape = 0;
	}
	glutPostRedisplay();
}

GLvoid Timerfunction(int value) {
	switch (value) {
	case 1:
		for (int i = 0; i < 10; ++i) {
			shape[i].R = 1.0 - (rand() % 255 / 255.0);
			shape[i].G = 1.0 - (rand() % 255 / 255.0);
			shape[i].B = 1.0 - (rand() % 255 / 255.0);
			if (shape[i].alive) {
				if (shape[i].bigger_size) {
					shape[i].size++;
					if (shape[i].size >= 10) {
						shape[i].bigger_size = false;
					}
				}
				else {
					shape[i].size--;
					if (shape[i].size <= 1) {
						shape[i].bigger_size = true;
					}
				}
			}
		}
		glutPostRedisplay();
		glutTimerFunc(1000/60, Timerfunction, 1);
		break;
	}
}