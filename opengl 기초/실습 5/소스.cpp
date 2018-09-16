#include <GL/freeglut.h>
#include<time.h>
GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid SpecialKeyboard(int, int, int);
GLvoid Timerfunction(int);

struct Shape {
	int size = 0;		// 1 ~ 10 변화
	int type = 0;		// 0 사각형 1 삼각형
	bool bigger_size = true;	// 사각형 커지는지 작아지는지
	bool alive = false;			// 보이기 안보이기
	float R, G, B;				// 색깔
	int move_dirrection;	// 좌상 좌하 우하 우상
	RECT rect;
};

Shape shape[10];

int shape_cursor = 0;
int shape_make_mode = 0;	// 0 사각형 1 삼각형
int animation_speed = 1000;

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
	glutTimerFunc(animation_speed / 60, Timerfunction, 2);
	glutMouseFunc(Mouse);		// 마우스 버튼 입력 받기
	glutKeyboardFunc(Keyboard);	// 키보드 입력 받기
	glutSpecialFunc(SpecialKeyboard);	// 키보드 특수버튼 입력 받기

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
			switch (shape[i].type) {
			case 0:
				glBegin(GL_POLYGON);
				glVertex2f(shape[i].rect.left - shape[i].size * 5, shape[i].rect.top + shape[i].size * 5);
				glVertex2f(shape[i].rect.left - shape[i].size * 5, shape[i].rect.bottom - shape[i].size * 5);
				glVertex2f(shape[i].rect.right + shape[i].size * 5, shape[i].rect.bottom - shape[i].size * 5);
				glVertex2f(shape[i].rect.right + shape[i].size * 5, shape[i].rect.top + shape[i].size * 5);
				glEnd();
				break;
			case 1:
				glBegin(GL_POLYGON);
				glVertex2f(((shape[i].rect.right + shape[i].size * 5)-(shape[i].rect.left - shape[i].size * 5))/2+ shape[i].rect.left - shape[i].size * 5, shape[i].rect.top + shape[i].size * 5);
				glVertex2f(shape[i].rect.left - shape[i].size * 5, shape[i].rect.bottom - shape[i].size * 5);
				glVertex2f(shape[i].rect.right + shape[i].size * 5, shape[i].rect.bottom - shape[i].size * 5);
				
				glEnd();
				break;
			}
			
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
	//사각형 생성
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		shape[shape_cursor].alive = true;
		shape[shape_cursor].R = rand() % 255 / 255.0;
		shape[shape_cursor].G = rand() % 255 / 255.0;
		shape[shape_cursor].B = rand() % 255 / 255.0;

		shape[shape_cursor].size = rand() % 8 + 1;
		shape[shape_cursor].rect.left = x - 400;
		shape[shape_cursor].rect.right = shape[shape_cursor].rect.left + shape[shape_cursor].size * 5;
		shape[shape_cursor].rect.bottom = -1 * y + 300;
		shape[shape_cursor].rect.top = shape[shape_cursor].rect.bottom + shape[shape_cursor].size * 5;

		shape[shape_cursor].move_dirrection = rand() % 4;
		shape[shape_cursor].type = shape_make_mode;

		shape_cursor++;
		if (shape_cursor > 9)
			shape_cursor = 0;
	}
	glutPostRedisplay();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'r':
	case 'R':
		shape_make_mode = 0;
		break;
	case 't':
	case 'T':
		shape_make_mode = 1;
		break;
	}
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		if (animation_speed > 100)
			animation_speed -= 100;
		break;
	case GLUT_KEY_DOWN:
		animation_speed += 100;
		break;
	}
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
					if (shape[i].size >= 5) {
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
		glutTimerFunc(1000 / 60, Timerfunction, 1);
		break;
	case 2:
		for (int i = 0; i < 10; ++i) {
			if (shape[i].alive) {
				switch (shape[i].move_dirrection) {
				case 0:
					shape[i].rect.left -= 3;
					shape[i].rect.right -= 3;
					shape[i].rect.top += 3;
					shape[i].rect.bottom += 3;
					if (shape[i].rect.top >= 300|| shape[i].rect.left <= -400) {
						shape[i].move_dirrection = 1;
					}
					break;
				case 1:
					shape[i].rect.left -= 3;
					shape[i].rect.right -= 3;
					shape[i].rect.top -= 3;
					shape[i].rect.bottom -= 3;
					if (shape[i].rect.left <= -400|| shape[i].rect.bottom <= -300) {
						shape[i].move_dirrection = 2;
					}
					break;
				case 2:
					shape[i].rect.left += 3;
					shape[i].rect.right += 3;
					shape[i].rect.top -= 3;
					shape[i].rect.bottom -= 3;
					if (shape[i].rect.bottom <= -300|| shape[i].rect.right >= 400) {
						shape[i].move_dirrection = 3;
					}
					break;
				case 3:
					shape[i].rect.left += 3;
					shape[i].rect.right += 3;
					shape[i].rect.top += 3;
					shape[i].rect.bottom += 3;
					if (shape[i].rect.right >= 400|| shape[i].rect.top >= 300) {
						shape[i].move_dirrection = 0;
					}
					break;
				}
				
			}
		}
		glutPostRedisplay();
		glutTimerFunc(animation_speed / 60, Timerfunction, 2);
		break;
	}
}