#include "Run_time_Framework.h"

void main(int argc, char *argv[]) {
	CRun_time_Framework framework;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("7"); // 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(framework.drawscene); // 출력 함수의 지정
	glutReshapeFunc(framework.Resize);
	glutMainLoop();
}
