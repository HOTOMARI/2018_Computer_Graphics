#include "Run_time_Framework.h"

void main(int argc, char *argv[]) {
	CRun_time_Framework framework;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("7"); // ������ ���� (������ �̸�)
	glutDisplayFunc(framework.drawscene); // ��� �Լ��� ����
	glutReshapeFunc(framework.Resize);
	glutMainLoop();
}
