#include <GL/freeglut.h>
#include<time.h>
GLvoid DrawScene();
GLvoid Reshape(int w, int h);

struct Shape {
	int type;	// 0 선 1 삼각형 2 사각형 3 오각형
};

Shape shape[3][3];

bool type_set_mode = false;	//false 순방향  true 역방향
int type_set_num = 0;

void main(int argc, char** argv) // 윈도우 출력하고 출력함수 설정 
{
	// 초기화 함수들 
	glutInit(&argc, argv); // glut 초기화 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치 지정 
	glutInitWindowSize(900, 600); // 윈도우의 크기 지정 
	glutCreateWindow("Tiles"); // 윈도우 생성 (윈도우 이름) 
	glutDisplayFunc(DrawScene); // 출력 함수의 지정 
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정 

	srand(time(NULL));

	type_set_num = rand() % 4;
	shape[0][0].type = type_set_num;	//처음 도형 세팅
	if (shape[0][0].type == 3) {
		type_set_mode = true;
	}

	for (int i = 0; i < 3; ++i)		// 나머지 도형 세팅
		for (int j = 0; j < 3; ++j) 
			if (!(i == 0 && j == 0)) {		// 처음거 제외
				if (type_set_mode) {		// 역방향
					shape[i][j].type = --type_set_num;
					if (type_set_num == 0)
						type_set_mode = false;
				}
				else {						// 순방향
					shape[i][j].type = ++type_set_num;
					if (type_set_num == 3) 
						type_set_mode = true;
				}
			}

	glutMainLoop(); // 이벤트 처리 시작 
}

GLvoid DrawScene() // 출력 함수 
{
	glClearColor(0, 0, 0, 1); // 바탕색을 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 

	glColor4f(1, 1, 1, 1); //직선
	for (int i = 1; i <= 2; ++i) {
		glBegin(GL_LINES);				// 가로
		glVertex2f(-450 + i * 300, -300);
		glVertex2f(-450 + i * 300, 300);
		glEnd();
		glBegin(GL_LINES);				// 세로
		glVertex2f(-450, -300 + 200 * i);
		glVertex2f(450, -300 + 200 * i);
		glEnd();
	}

	glPointSize(5);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			switch (shape[i][j].type) {
			case 0:
				glBegin(GL_LINES);
				glVertex2f(-450 + j * 300 + 50, 300 - i * 200 - 100);
				glVertex2f(-450 + j * 300 + 250, 300 - i * 200 - 100);
				glEnd();
				break;
			case 1:
				glBegin(GL_TRIANGLES);
				glVertex2f(-450 + j * 300 + 300 / 3, 300 - i * 200 - 150);
				glVertex2f(-450 + j * 300 + 300 / 3 * 2, 300 - i * 200 - 150);
				glVertex2f(-450 + j * 300 + 300 / 2, 300 - i * 200 - 50);
				glEnd();
				break;
			case 2:
				glBegin(GL_POLYGON);
				glVertex2f(-450 + j * 300 + 300 / 3, 300 - i * 200 - 150);
				glVertex2f(-450 + j * 300 + 300 / 3 * 2, 300 - i * 200 - 150);
				glVertex2f(-450 + j * 300 + 300 / 3 * 2, 300 - i * 200 - 50);
				glVertex2f(-450 + j * 300 + 300 / 3, 300 - i * 200 - 50);
				glEnd();
				break;
			case 3:
				glBegin(GL_POLYGON);
				glVertex2f(-450 + j * 300 + 300 / 5*2, 300 - i * 200 - 150);
				glVertex2f(-450 + j * 300 + 300 / 5*3, 300 - i * 200 - 150);
				glVertex2f(-450 + j * 300 + 300 / 3 * 2, 300 - i * 200 - 100);
				glVertex2f(-450 + j * 300 + 300 / 2, 300 - i * 200 - 50);
				glVertex2f(-450 + j * 300 + 300 / 3, 300 - i * 200 - 100);
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
	glOrtho(-450.0, 450.0, -300.0, 300.0, -1.0, 1.0);
}