#include "Run_time_Framework.h"

CRun_time_Framework* CRun_time_Framework::myself = nullptr;

CRun_time_Framework::CRun_time_Framework() {
	myself = this;
}

CRun_time_Framework::~CRun_time_Framework() {

}

GLvoid CRun_time_Framework::draw() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
	return GLvoid();
}

GLvoid CRun_time_Framework::Reshape(int w, int h) {
	if (w > 0)
		m_nWidth = w;
	if (h > 0)
		m_nHeight = h;
	glOrtho(0.0, 800.0, 0.0, 600.0, -300, 300);
	return GLvoid();
}

GLvoid CRun_time_Framework::Resize(int w, int h) {
	if(!myself)
		return GLvoid();
	myself->Reshape(w, h);
}

GLvoid CRun_time_Framework::drawscene() {
	if (myself != nullptr) {
		myself->draw();
	}
	return GLvoid();
}