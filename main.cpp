#include "main.h"
vector<float> x, y, z;
int num_particles = 1000;
int frame = 0;

/// SCENE UPDATE FUNCTION
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1);
	glEnable (GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	//glDepthRange(0.1, 1.0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_BACK, GL_LINE);
	glLoadIdentity();
	render_camera.Update();
	glColor3f(0, 0, 0);

	/// Randomly perturb spheres
	for (int i = 0; i < num_particles; i++) {
		x[i] += (rand() % 1000 / 100000.0 - .005) * sin(frame / 1000.0);
		y[i] += (rand() % 1000 / 100000.0 - .005) * cos(frame / 1000.0);
		z[i] += (rand() % 1000 / 100000.0 - .005) * sin(frame / 1000.0) * cos(frame / 1000.0);

	}

	/// Different Draw Modes
	if (draw_mode == 1) {
		glBegin (GL_POINTS);
		for (int i = 0; i < num_particles; i++) {
			glVertex3f(x[i], y[i], z[i]);
		}
		glEnd();
	}
	if (draw_mode == 2) {
		glBegin (GL_LINE_LOOP);
		for (int i = 0; i < num_particles; i++) {
			glVertex3f(x[i], y[i], z[i]);
		}
		glEnd();
	}
	if (draw_mode == 3) {
		for (int i = 0; i < num_particles; i++) {
			glPushMatrix();
			glTranslatef(x[i], y[i], z[i]);
			glutWireCube(.5);
			glutWireSphere(.1, 10, 10);
			//glutSolidCube(.5);
			//glutSolidSphere(.1, 10, 10);

			glPopMatrix();
		}
	}
//#if defined( _WINDOWS )
//	Sleep( 40 );
//#else
//	usleep(40 * 1000);
//#endif

	glutSwapBuffers();
	frame++;
}
///Main
int main(int argc, char* argv[]) {

	for (int i = 0; i < num_particles; i++) {
		x.push_back((rand() % 1000 / 1000.0 - .5) * 10);
		y.push_back((rand() % 1000 / 1000.0 - .5) * 10);
		z.push_back((rand() % 1000 / 1000.0 - .5) * 10);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL test");
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutReshapeFunc(changeSize);
	glutIgnoreKeyRepeat(0);
	glutKeyboardFunc(processNormalKeys);
	glutMouseFunc(CallBackMouseFunc);
	glutMotionFunc(CallBackMotionFunc);
	initScene();
	glutMainLoop();

}
