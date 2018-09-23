#include <GL/freeglut.h>
#include<time.h>
#include<math.h>
#define PI 3.141592

GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid SpecialKeyboard(int, int, int);
GLvoid Timerfunction(int);
void InitialShape();

struct Shape {
	bool is_triangle = true;
	bool is_now_morp = false;
	bool morp_bigger = true;
	float size = 20;
	int rotate_shape = 0;
	int position_shape = 0;
};


int shape_mode = 0;	// 0 원 1 사인 2 회오리 3 지그재그 4 경로그리기

int animation_speed = 1000;

float moveX = 0, moveY = 0;
float global_rotate = 0;

Shape shape;

void main(int argc, char** argv) // 윈도우 출력하고 출력함수 설정 
{
	// 초기화 함수들 
	glutInit(&argc, argv); // glut 초기화 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정 
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

	//shape.cx = 0;
	//shape.cy = 200;

	glutMainLoop(); // 이벤트 처리 시작 
}

GLvoid DrawScene() // 출력 함수 
{
	glClearColor(0, 0, 0, 1); // 바탕색을 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 
	glMatrixMode(GL_MODELVIEW);

	glPointSize(3.0);

	glPushMatrix();
	// 중심선
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0, 300, 0);
	glVertex3f(0, -300, 0);
	glVertex3f(400, 0, 0);
	glVertex3f(-400, 0, 0);
	glEnd();

	glRotatef(global_rotate, 0, 1.0, 0);
	switch (shape_mode)
	{
	case 0:
		for (int i = 0; i < 360; ++i) {
			glBegin(GL_LINES);
			glVertex3f(200 * cos(i / 180.0 * PI), 200 * sin(i / 180.0 * PI), 0);
			glVertex3f(200 * cos((i + 1) / 180.0 * PI), 200 * sin((i + 1) / 180.0 * PI), 0);
			glEnd();
		}
		glTranslated(200 * cos(shape.position_shape / 180.0 * PI),
			200 * sin(shape.position_shape / 180.0 * PI), 0);
		glRotatef(shape.rotate_shape, 0, 0, 1.0);
		break;
	case 1:
		for (int i = -400; i < 400; ++i) {
			glBegin(GL_LINES);
			glVertex3f(i, 200 * sin(i / 180.0 * PI), 0);
			glVertex3f(i + 1, 200 * sin((i + 1) / 180.0 * PI), 0);
			glEnd();
		}
		if (shape.position_shape > 400 + shape.size) {
			shape.position_shape = -400;
		}
		else if (shape.position_shape < -400 - shape.size) {
			shape.position_shape = 400;
		}
		glTranslated(shape.position_shape, 200 * sin(shape.position_shape / 180.0 * PI), 0);
		break;
	case 2:
		glRotatef(90, 0, 0, 1.0);
		for (int i = -800; i < 800; ++i) {
			glBegin(GL_LINES);
			glVertex3f(200 * cos(i / 180.0 * PI) + i, 200 * sin(i / 180.0 * PI), 0);
			glVertex3f(200 * cos((i + 1) / 180.0 * PI) + i + 1, 200 * sin((i + 1) / 180.0 * PI), 0);
			glEnd();
		}
		glRotatef(-90, 0, 0, 1.0);
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
	if (shape.is_triangle) {
		glColor3f(1.0, 1.0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(shape.size * cos(90.0 / 180.0 * PI), shape.size * sin(90.0 / 180.0 * PI), 0);
		glVertex3f(shape.size * cos(210.0 / 180.0 * PI), shape.size * sin(210.0 / 180.0 * PI), 0);
		glVertex3f(shape.size * cos(330.0 / 180.0 * PI), shape.size * sin(330.0 / 180.0 * PI), 0);
		glEnd();
	}
	else {
		glColor3f(1.0, 1.0, 0);
		glBegin(GL_POLYGON);
		glVertex3f(shape.size * -1.0, shape.size * 1.0, 0);
		glVertex3f(shape.size * -1.0, shape.size * -1.0, 0);
		glVertex3f(shape.size * 1.0, shape.size * -1.0, 0);
		glVertex3f(shape.size * 1.0, shape.size * 1.0, 0);
		glEnd();
	}

	glPopMatrix();
	glutSwapBuffers(); // 화면에 출력하기 
}

GLvoid Reshape(int w, int h) // 다시 그리기 함수 
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);
}

GLvoid Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
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
	case 't':
		if (shape.is_triangle) {
			shape.is_triangle = false;
		}
		else {
			shape.is_triangle = true;
		}
		break;
	case 'r':
		if (shape_mode == 0) {
			shape.rotate_shape += 5;
			shape.position_shape += 5;
		}
		break;
	case 'R':
		if (shape_mode == 0) {
			shape.rotate_shape -= 5;
			shape.position_shape -= 5;
		}
		break;
	case 'e':
		shape.position_shape += 5;
		break;
	case 'E':
		shape.position_shape -= 5;
		break;
	case 's':
		if (shape.is_now_morp) {
			shape.is_now_morp = false;
		}
		else {
			shape.is_now_morp = true;
		}
		break;
	case 'y':
		global_rotate += 5;
		break;
	case 'Y':
		global_rotate -= 5;
		break;
	case '0':
		shape_mode = 0;
		InitialShape();
		break;
	case '1':
		shape_mode = 1;
		InitialShape();
		break;
	case '2':
		shape_mode = 2;
		InitialShape();
		break;
	case '3':
		shape_mode = 3;
		InitialShape();
		break;
	case '4':
		shape_mode = 4;
		InitialShape();
		break;
	}
	glutPostRedisplay();
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	switch (key) {
	}
}

GLvoid Timerfunction(int value) {
	switch (value) {
	case 1:
		if (shape.is_now_morp) {
			if (shape.morp_bigger) {
				shape.size++;
				if (shape.size > 40) {
					shape.morp_bigger = false;
				}
			}
			else {
				shape.size--;
				if (shape.size < 10) {
					shape.morp_bigger = true;
				}
			}
		}
		glutPostRedisplay();
		glutTimerFunc(animation_speed / 60, Timerfunction, 1);
		break;
	}
}

void InitialShape()
{
	shape.is_triangle = true;
	shape.is_now_morp = false;
	shape.morp_bigger = true;
	shape.size = 20;
	shape.rotate_shape = 0;
	shape.position_shape = 0;
	global_rotate = 0;
}
