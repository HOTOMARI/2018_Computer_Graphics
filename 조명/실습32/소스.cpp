#include "Run_time_Framework.h"

void main(int argc, char *argv[]) {
	CRun_time_Framework framework;
	glutInit(&argc, argv);
	framework.Init();
	glutMainLoop();
}