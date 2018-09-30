#include <GL/freeglut.h>
#include<time.h>
#include<math.h>
#define PI 3.141592
GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid Timerfunction(int);

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
	glutKeyboardFunc(Keyboard);	// 키보드 입력 받기

	glutMainLoop(); // 이벤트 처리 시작 
}

GLvoid DrawScene() // 출력 함수 
{
	glClearColor(0, 0, 0, 1); // 바탕색을 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glScaled(0.6, 0.6, 1.0);
	glTranslated(-460, 0, 0);

	for (int j = 0; j < 6; ++j) {

		if (j != 0) {
			glTranslated(170, 0, 0);
			if (j % 2 == 0)
				glTranslated(40, 0, 0);
		}
		glPushMatrix();
		glTranslated(0, 125, 0);
		for (int i = 0; i < 3; ++i) {
			if (i)
				glTranslated(0, -125, 0);
			glPushMatrix();
			glScaled(1.0, 0.25, 1.0);
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(100);
			glPopMatrix();
		}
		glTranslated(-63, 187, 0);
		for (int i = 0; i < 2; ++i) {
			if (i)
				glTranslated(125, 0, 0);
			glPushMatrix();
			glScaled(0.25, 1.0, 1.0);
			glColor3f(1.0, 1.0, 1.0);
			glutWireCube(100);
			glTranslated(0, -125, 0);
			glutWireCube(100);
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glutSwapBuffers(); // 화면에 출력하기 
}

GLvoid Reshape(int w, int h) // 다시 그리기 함수 
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -400.0, 400.0);
}


GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
		glutLeaveMainLoop();
		break;
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