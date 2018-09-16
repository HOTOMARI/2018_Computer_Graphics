#include <GL/freeglut.h>
GLvoid DrawScene ();
GLvoid Reshape (int w, int h);

void main (int argc, char** argv) // 윈도우 출력하고 출력함수 설정 
{ 
// 초기화 함수들 
glutInit (&argc, argv); // glut 초기화 
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA); // 디스플레이 모드 설정 
glutInitWindowPosition ( 100, 100 ); // 윈도우의 위치 지정 
glutInitWindowSize ( 800, 600 ); // 윈도우의 크기 지정 
glutCreateWindow ( "Blue Window" ); // 윈도우 생성 (윈도우 이름) 
glutDisplayFunc ( DrawScene ); // 출력 함수의 지정 
glutReshapeFunc (Reshape); // 다시 그리기 함수 지정 
glutMainLoop (); // 이벤트 처리 시작 
} 

GLvoid DrawScene ( ) // 출력 함수 
{ 
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // 바탕색을 'blue' 로 지정 
	glClear( GL_COLOR_BUFFER_BIT ); // 설정된 색으로 전체를 칠하기 

	glColor4f(0, 1, 0, 1);		//사각형
	glRectf(-1, 0.8, -0.8, 1);
	glColor4f(1, 0, 1, 1);
	glRectf(0.8, 0.8, 1, 1);
	glColor4f(1, 1, 0, 1);
	glRectf(-1, -1, -0.8, -0.8);
	glColor4f(0, 1, 1, 1);
	glRectf(0.8, -0.8, 1, -1);

	glColor4f(1, 1, 1, 1); //직선
	glBegin(GL_LINES);
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(0, 1);
	glVertex2f(0, -1);
	glEnd();

	glColor4f(1, 0, 0, 1);		// 삼각형
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.2, -0.1);
	glVertex2f(0.2, -0.1);
	glVertex2f(0, 0.2);
	glEnd();
	glFlush(); // 화면에 출력하기 
}

GLvoid Reshape(int w, int h) // 다시 그리기 함수 
{ 
	glViewport (0, 0, w, h); 
}