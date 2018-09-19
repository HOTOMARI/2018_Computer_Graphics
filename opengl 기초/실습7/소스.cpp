#include <GL/freeglut.h>
#include<time.h>
#include<math.h>
#define PI 3.141592
GLvoid DrawScene();
GLvoid Reshape(int, int);
GLvoid Mouse(int, int, int, int);
GLvoid Timerfunction(int);


struct Shape {
	int x, y;
	float r = 0;
	int type = 0;
	Shape* next;
};

Shape* head = NULL;


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
	Shape* t = head;

	glPointSize(3.0);
	glLineWidth(3.0);
	while (t != NULL) {
		for (int i = 0; i < 360; ++i) {
			if (t->type == 0) {
				glColor3f(1, 1, 1);
				glBegin(GL_LINES);
				glVertex2f(t->r*cos(i*PI / 180) + t->x, t->r*sin(i*PI / 180) + t->y);
				glVertex2f(t->r*cos((i + 1)*PI / 180) + t->x, t->r*sin((i + 1)*PI / 180) + t->y);
				glEnd();
			}
			else {
				if (i % 4==0) {
					glColor3f(rand()%255/255.0, rand() % 255 / 255.0, rand() % 255 / 255.0);
					glBegin(GL_POINTS);
					glVertex2f(t->r*cos(i*PI / 180) + t->x, t->r*sin(i*PI / 180) + t->y);
					glEnd();
				}
			}
		}
		t = t->next;
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
		Shape* t = head;
		if (head == NULL) {
			head = (Shape*)malloc(sizeof(Shape));
			head->next = NULL;
			head->x = x - 400;
			head->y = -1 * y + 300;
			head->r = 0;
			head->type = rand() % 2;
		}
		else {
			while (t->next != NULL) {
				t = t->next;
			}
			t->next = (Shape*)malloc(sizeof(Shape));
			t = t->next;
			t->next = NULL;
			t->x = x - 400;
			t->y = -1 * y + 300;
			t->r = 0;
			t->type = rand() % 2;
		}
	}
	glutPostRedisplay();
}

GLvoid Timerfunction(int value) {
	switch (value) {
	case 1:
		Shape* t = head;
		while (t != NULL) {
			t->r = t->r + 1;
			if (t->type == 0 && t->r > 20) {
				t->r = 0;
			}
			t = t->next;
		}
		glutPostRedisplay();
		glutTimerFunc(1000 / 60, Timerfunction, 1);
		break;
	}
}