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


int shape_mode = 0;	// 0 사인곡선 1 스프링 2 리본 3 사각형

int animation_speed = 1000;
bool animation_switch[2] = { false, };	// 왼쪽, 오른쪽 이동

float moveX = 0, moveY = 0;
float transformSize = 1;

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

	srand(time(NULL));

	glutMainLoop(); // 이벤트 처리 시작 
}

GLvoid DrawScene() // 출력 함수 
{
	glClearColor(0, 0, 0, 1); // 바탕색을 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 

	glPointSize(3.0);
	
	// 중심선
	glBegin(GL_LINES);
	glVertex3f(0, 300 ,0);
	glVertex3f(0, -300, 0);
	glVertex3f(400, 0, 0);
	glVertex3f(-400, 0, 0);
	glEnd();

	switch (shape_mode) {
	case 0:
		for (int i = -400 ; i < 400; ++i) {
			glBegin(GL_LINES);
			glVertex3f(i, cos(((i*transformSize) + moveX) / 180.0 * PI) * 200 + moveY, 0);
			glVertex3f(i + 1, cos(((i + 1)*transformSize + moveX) / 180.0 * PI) * 200 + moveY, 0);
			glEnd();
		}
		break;
	case 1:
		for (int i = -800; i < 800; ++i) {
			glBegin(GL_LINES);
			glVertex3f(200 * sin(((i*transformSize) + moveX) / 180.0 * PI) + i, cos(((i*transformSize)+ moveX) / 180.0 * PI) * 200 + moveY, 0);
			glVertex3f(200*sin(((i + 1)*transformSize + moveX) / 180.0 * PI) + i+1, cos(((i + 1)*transformSize + moveX) / 180.0 * PI) * 200 + moveY, 0);
			glEnd();
		}
		break;
	case 2:
		// 왼쪽부분
		glBegin(GL_POLYGON);
		glVertex3f(-0.5 * 400 + moveX - ((transformSize - 1) * 100), 0.5 * 300 + moveY, 0);
		glVertex3f(-0.5 * 400 + moveX - ((transformSize - 1) * 100), -0.5 * 300 + moveY, 0);
		glVertex3f(0 + moveX, 0 + moveY, 0);
		glEnd();
		// 오른쪽부분
		glBegin(GL_POLYGON);
		glVertex3f(0 + moveX, 0, 0);
		glVertex3f(0.5 * 400 + moveX + ((transformSize - 1) * 100), 0.5 * 300 + moveY, 0);
		glVertex3f(0.5 * 400 + moveX + ((transformSize - 1) * 100), -0.5 * 300 + moveY, 0);
		glEnd();
		break;
	case 3:
		glBegin(GL_POLYGON);
		glVertex3f(-0.5 * 400 + moveX - ((transformSize - 1) * 100), 0.5 * 300 + moveY, 0);
		glVertex3f(-0.5 * 400 + moveX - ((transformSize - 1) * 100), -0.5 * 300 + moveY, 0);
		glVertex3f(0.5 * 400 + moveX + ((transformSize - 1) * 100), -0.5 * 300 + moveY, 0);
		glVertex3f(0.5 * 400 + moveX + ((transformSize - 1) * 100), 0.5 * 300 + moveY, 0);
		glEnd();
		break;
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
	case 'x':
		moveX++;
		break;
	case 'X':
		moveX--;
		break;
	case 'y':
		moveY++;
		break;
	case 'Y':
		moveY--;
		break;
	case 's':
		transformSize += 0.05;
		break;
	case 'S':
		//if (transformSize > 0.05) {
			transformSize -= 0.05;
		//}
		break;
	case 'r':
		moveX += 20;
		break;
	case 'R':
		moveX += 20;
		break;
	case 'a':
		animation_switch[0] = true;
		animation_switch[1] = false;
		break;
	case 'A':
		animation_switch[0] = false;
		animation_switch[1] = true;
		break;
	case 't':
	case 'T':
		animation_switch[0] = false;
		animation_switch[1] = false;
		break;
	case '1':
		shape_mode = 0;
		moveX = 0, moveY = 0;
		animation_switch[0] = false, animation_switch[1] = false;
		transformSize = 1;
		break;
	case '2':
		shape_mode = 1;
		moveX = 0, moveY = 0;
		animation_switch[0] = false, animation_switch[1] = false;
		transformSize = 1;
		break;
	case '3':
		shape_mode = 2;
		moveX = 0, moveY = 0;
		animation_switch[0] = false, animation_switch[1] = false;
		transformSize = 1;
		break;
	case '4':
		shape_mode = 3;
		moveX = 0, moveY = 0;
		animation_switch[0] = false, animation_switch[1] = false;
		transformSize = 1;
		break;
	}
	glutPostRedisplay();
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
		if (animation_switch[0]) {
			moveX++;
		}
		else if (animation_switch[1]) {
			moveX--;
		}
		glutPostRedisplay();
		glutTimerFunc(animation_speed / 60, Timerfunction, 1);
		break;
	}
}