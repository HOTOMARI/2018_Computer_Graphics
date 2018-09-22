#pragma once
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>

class CRun_time_Framework {
private:
	static CRun_time_Framework* myself;
	int m_nWidth;
	int m_nHeight;
public:
	CRun_time_Framework();
	~CRun_time_Framework();
	GLvoid draw();
	GLvoid Reshape(int w, int h);
	GLvoid draw_centerline();
	static GLvoid Resize(int w, int h);
	static GLvoid drawscene();
};