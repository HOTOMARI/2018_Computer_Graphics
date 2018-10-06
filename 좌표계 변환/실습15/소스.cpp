#include <GL/freeglut.h>
#include<time.h>
#include<math.h>
#define PI 3.141592
GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid Timerfunction(int);

time_t	now;
struct tm curr_time;

int nums[6];
int rotate_degree = 0;

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
	glutKeyboardFunc(Keyboard);	// 키보드 입력 받기

	glutMainLoop(); // 이벤트 처리 시작 
}

GLvoid DrawScene() // 출력 함수 
{
	glClearColor(0, 0, 0, 1); // 바탕색을 지정 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 
	glEnable(GL_DEPTH_TEST);	//깊이테스트
	glDepthFunc(GL_LESS);		//Passes if the fragment's depth value is less than the stored depth value.
	glMatrixMode(GL_MODELVIEW);
	glLineWidth(2);
	glPushMatrix();
	glRotated(rotate_degree, 0, 1.0, 0);
	glRotated(30, 1.0, 1.0, 0);
	//glRotated(90, 0, 1.0, 0);
	
	glScaled(0.6, 0.6, 1.0);
	glTranslated(-460, 0, 0);

		for (int j = 0; j < 6; ++j) {
			if (j != 0) {
				glTranslated(170, 0, 0);
				if (j % 2 == 0) {
					glTranslated(40, 0, 0);
				}
			}

			glPushMatrix();
			glTranslated(0, 125, 0);
			for (int i = 0; i < 3; ++i) {
				if (i)
					glTranslated(0, -125, 0);
				glPushMatrix();
				glScaled(1.0, 0.25, 1.0);
				switch (i) {
				case 0:
					if (nums[j] == 2 || nums[j] == 3 || nums[j] == 5 || nums[j] == 6 || nums[j] == 7 || nums[j] == 8 || nums[j] == 9 || nums[j] == 0) {
						glColor3f(0, 1.0, 0);
						glutSolidCube(100);
					}
					break;
				case 1:
					if (nums[j] == 2 || nums[j] == 3 || nums[j] == 4 || nums[j] == 5 || nums[j] == 6 || nums[j] == 8 || nums[j] == 9) {
						glColor3f(0, 1.0, 0);
						glutSolidCube(100);
					}
					break;
				case 2:
					if (nums[j] == 2 || nums[j] == 3 || nums[j] == 5 || nums[j] == 6 || nums[j] == 8 || nums[j] == 0) {
						glColor3f(0, 1.0, 0);
						glutSolidCube(100);
					}
					break;
				}
				glColor3f(0, 0, 0);
				glutWireCube(100);
				glPopMatrix();
			}
			glTranslated(-63, 187, 0);
			for (int i = 0; i < 2; ++i) {
				if (i)
					glTranslated(125, 0, 0);
				glPushMatrix();
				glScaled(0.25, 1.0, 1.0);
				switch (i) {
				case 0:
					if (nums[j] == 4 || nums[j] == 5 || nums[j] == 6 || nums[j] == 8 || nums[j] == 9 || nums[j] == 0) {
						glColor3f(0, 1.0, 0);
						glutSolidCube(100);
					}
					break;
				case 1:
					if (nums[j] == 1 || nums[j] == 2 || nums[j] == 3 || nums[j] == 4 || nums[j] == 7 || nums[j] == 8 || nums[j] == 9 || nums[j] == 0) {
						glColor3f(0, 1.0, 0);
						glutSolidCube(100);
					}
				}
				glColor3f(0, 0, 0);
				glutWireCube(100);
				glTranslated(0, -125, 0);
				switch (i) {
				case 0:
					if (nums[j] == 2 || nums[j] == 6 || nums[j] == 8 || nums[j] == 0) {
						glColor3f(0, 1.0, 0);
						glutSolidCube(100);
					}
					break;
				case 1:
					if (nums[j] == 1 || nums[j] == 3 || nums[j] == 4 || nums[j] == 5 || nums[j] == 6 || nums[j] == 7 || nums[j] == 8 || nums[j] == 9 || nums[j] == 0) {
						glColor3f(0, 1.0, 0);
						glutSolidCube(100);
					}
				}
				glColor3f(0, 0, 0);
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
	case 'r':
		rotate_degree += 5;
		//if (rotate_degree >= 360)
			//rotate_degree = 0;
		break;
	case 'R':
		rotate_degree -= 5;
		if (rotate_degree <= 0)
			rotate_degree = 360;
		break;
	}

}

GLvoid Timerfunction(int value) {
	switch (value) {
	case 1:
		now = time(0);
		localtime_s(&curr_time, &now);
		nums[0] = curr_time.tm_hour / 10;
		nums[1] = curr_time.tm_hour % 10;
		nums[2] = curr_time.tm_min / 10;
		nums[3] = curr_time.tm_min % 10;
		nums[4] = curr_time.tm_sec / 10;
		nums[5] = curr_time.tm_sec % 10;
		glutPostRedisplay();
		glutTimerFunc(1000 / 60, Timerfunction, 1);
		break;
	}
}