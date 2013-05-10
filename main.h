#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#include "omp.h"
#endif
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "openglCamera.h"
using namespace std;

int draw_mode = 1;
OpenGLCamera render_camera(real3(0, 0, 0), real3(0, 0, 0), real3(0, 1, 0), 1);

void CallBackMouseFunc(int button, int state, int x, int y) {
	render_camera.SetPos(button, state, x, y);
}
void CallBackMotionFunc(int x, int y) {
	render_camera.Move2D(x, y);
}

void changeSize(int w, int h) {
	int width = w;
	int height = h;

	float ratio = 1.0 * w / h;
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, ratio, .01, 1000);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

void initScene() {

	GLfloat light_position[] = { 100.0, 100.0, 100.0, 0.0 };
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel (GL_SMOOTH);
	glEnable (GL_COLOR_MATERIAL);

	glEnable (GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);
	glPointSize(2);
	glEnable (GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable (GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	//glDepthFunc( GL_LEQUAL);
	//glClearDepth(1.0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);

}

void processNormalKeys(unsigned char key, int x, int y) {
	switch (key) {
	//spacebar
	case ' ':
		break;
	case 'w':
		render_camera.Forward();
		break;
	case 's':
		render_camera.Back();
		break;
	case 'd':
		render_camera.Right();
		break;
	case 'a':
		render_camera.Left();
		break;
	case 'q':
		render_camera.Up();
		break;
	case 'e':
		render_camera.Down();
		break;
	case '1':
		draw_mode = 1;
		break;
	case '2':
		draw_mode = 2;
		break;
	case '3':
		draw_mode = 3;
		break;
	}
}

real3 GetColour(double v, double vmin, double vmax) {
	real3 c = real3(0, 0, 0); // white
	double dv;

	if (v < vmin)
		v = vmin;
	if (v > vmax)
		v = vmax;
	dv = vmax - vmin;

	if (v < (vmin + 0.25 * dv)) {
		c.x = 0;
		c.y = 4 * (v - vmin) / dv;
	} else if (v < (vmin + 0.5 * dv)) {
		c.x = 0;
		c.z = 1 + 4 * (vmin + 0.25 * dv - v) / dv;
	} else if (v < (vmin + 0.75 * dv)) {
		c.x = 4 * (v - vmin - 0.5 * dv) / dv;
		c.z = 0;
	} else {
		c.y = 1 + 4 * (vmin + 0.75 * dv - v) / dv;
		c.z = 0;
	}
	return (c);
}
