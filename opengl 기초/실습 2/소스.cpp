#include <GL/freeglut.h>
#include<time.h>
GLvoid DrawScene();
GLvoid Reshape(int w, int h);

float R, G, B;
float garo, sero;

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

	srand(time(NULL));

	glutMainLoop(); // 이벤트 처리 시작 
}

GLvoid DrawScene() // 출력 함수 
{
	R = rand() % 100;		//초기색 지정
	G = rand() % 100;
	B = rand() % 100;

	R = R / 255.0;
	G = G / 255.0;
	B = B / 255.0;

	garo = rand() % 10 + 5;	// 초기 칸 지정
	sero = rand() % 10 + 5;

	glClearColor(R, G, B, 1); // 바탕색을 'blue' 로 지정 
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기 


	for (int i = 0; i < sero; ++i) {
		for (int j = 0; j < garo; ++j) {
			glColor4f(R+0.05*j, G + 0.02*i, B + 0.02*i+0.05*j, 1);		//사각형
			glRectf(-400.0 + ((800.0 / garo)*j), 300.0 - ((600.0 / sero)*i),
				(-400.0 + ((800.0 / garo)*(j + 1))), 300.0 - ((600.0 / sero)*(i + 1)));
		}
	}
	

	glFlush(); // 화면에 출력하기 
}

GLvoid Reshape(int w, int h) // 다시 그리기 함수 
{
	glViewport(0, 0, w, h);
	glOrtho(-400.0, 400.0, -300.0, 300.0, -1.0, 1.0);
}