#include <GL/freeglut.h>
#include<time.h>

struct Shape {
	bool alive = false;			// 보이기 안보이기
	float R, G, B;				// 색깔
	RECT rect;
};

GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Motion(int, int);
GLvoid Timerfunction(int);

bool collide_rec_rec(Shape, Shape);

Shape background_rect[100];
Shape eraser_rect;


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
	glutMotionFunc(Motion);		// 마우스 움직임 입력받기

	srand(time(NULL));

	// 배경 사각형 셋팅
	for (int i = 0; i < 100; ++i) {
		background_rect[i].alive = true;
		background_rect[i].R = rand()%255/255.0;
		background_rect[i].G = rand() % 255 / 255.0;
		background_rect[i].B = rand() % 255 / 255.0;
		background_rect[i].rect.left = rand() % 800 - 400;
		background_rect[i].rect.right = background_rect[i].rect.left + 20;
		background_rect[i].rect.top = -1 * (rand() % 600) + 300;
		background_rect[i].rect.bottom = background_rect[i].rect.top - 20;
	}

	glutMainLoop(); // 이벤트 처리 시작 
}

GLvoid DrawScene() // 출력 함수 
{
	glClearColor(0, 0, 0, 1); // 바탕색을 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 

	//배경사각형
	for (int i = 0; i < 100; ++i) {
		if (background_rect[i].alive) {
			glColor4f(background_rect[i].R, background_rect[i].G, background_rect[i].B, 1);
			glBegin(GL_POLYGON);
			glVertex2f(background_rect[i].rect.left, background_rect[i].rect.top);
			glVertex2f(background_rect[i].rect.left, background_rect[i].rect.bottom);
			glVertex2f(background_rect[i].rect.right, background_rect[i].rect.bottom);
			glVertex2f(background_rect[i].rect.right, background_rect[i].rect.top);
			glEnd();
		}
	}
	//지우개사각형
	if (eraser_rect.alive) {
		glColor4f(1, 1, 1, 1);
		glBegin(GL_POLYGON);
		glVertex2f(eraser_rect.rect.left, eraser_rect.rect.top);
		glVertex2f(eraser_rect.rect.left, eraser_rect.rect.bottom);
		glVertex2f(eraser_rect.rect.right, eraser_rect.rect.bottom);
		glVertex2f(eraser_rect.rect.right, eraser_rect.rect.top);
		glEnd();
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
		eraser_rect.alive = true;
		eraser_rect.rect.left = x - 20 - 400;
		eraser_rect.rect.right = eraser_rect.rect.left + 40;
		eraser_rect.rect.top = -1 * (y - 20) + 300;
		eraser_rect.rect.bottom = eraser_rect.rect.top - 40;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		eraser_rect.alive = false;
	}
	glutPostRedisplay();
}

GLvoid Motion(int x, int y) {
	if (eraser_rect.alive) {
		eraser_rect.rect.left = x - 20 - 400;
		eraser_rect.rect.right = eraser_rect.rect.left + 40;
		eraser_rect.rect.top = -1 * (y - 20) + 300;
		eraser_rect.rect.bottom = eraser_rect.rect.top - 40;
		for (int i = 0; i < 100; ++i) {
			if (background_rect[i].alive&&collide_rec_rec(background_rect[i], eraser_rect)) {
				background_rect[i].alive = false;
			}
		}
	}
}

GLvoid Timerfunction(int value) {
	switch (value) {
	case 1:
		glutPostRedisplay();
		glutTimerFunc(1000 / 60, Timerfunction, 1);
		break;
	}
}

bool collide_rec_rec(Shape background, Shape eraser) {
	if (background.rect.left<eraser.rect.right&&background.rect.right>eraser.rect.left
		&&background.rect.top>eraser.rect.bottom&&background.rect.bottom<eraser.rect.top)
		return true;
	else return false;
}