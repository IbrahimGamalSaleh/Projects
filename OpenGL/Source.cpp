#include <stdlib.h>
#include <iostream>
#include <glut.h>

/////
#define X 52.5731112119133606
#define Z 85.0650808352039932
static GLfloat vdata[12][3] = {
	{ -X, 0.0, Z },{ X, 0.0, Z },{ -X, 0.0, -Z },{ X, 0.0, -Z },
	{ 0.0, Z, X },{ 0.0, Z, -X },{ 0.0, -Z, X },{ 0.0, -Z, -X },
	{ Z, X, 0.0 },{ -Z, X, 0.0 },{ Z, -X, 0.0 },{ -Z, -X, 0.0 }
};
static GLint tindices[20][3] = {
	{ 0,4,1 },{ 0,9,4 },{ 9,5,4 },{ 4,5,8 },{ 4,8,1 },
	{ 8,10,1 },{ 8,3,10 },{ 5,3,8 },{ 5,2,3 },{ 2,7,3 },
	{ 7,10,3 },{ 7,6,10 },{ 7,11,6 },{ 11,0,6 },{ 0,1,6 },
	{ 6,1,10 },{ 9,0,11 },{ 9,11,2 },{ 9,2,5 },{ 7,2,11 } };
/////

#define max(x, y) (x<y?y:x)
#define min(x, y) (x>y?y:x)

#define GL_PI 3.1415f

bool movie[] = { 0, 0, 0, 0 };
bool movieX_selection[4] = { 2, 2, 2, 2 };
bool movieY_selection[4] = { 0, 0, 0, 0};
float movieX[][3] = { { -5.0, 0, 5.0 } ,{ -5.0, 0, 5.0 } ,{ -5.0, 0, 5.0 } ,{ -5.0, 0, 5.0 } };
float movieY[][3] = { { -5.0, 0, 5.0 } ,{ -5.0, 0, 5.0 } ,{ -5.0, 0, 5.0 } ,{ -5.0, 0, 5.0 } };

void drawobject1();
void drawobject2();
void drawobject3();
void drawobject4();
void(*drawobject[4])(void) = { drawobject1 , drawobject2 , drawobject3 , drawobject4 };

static int selection = 0;
static GLfloat width;
static GLfloat height;
static GLfloat xRot[] = { 0.0f, 0.0f, 0.0f, 0.0f };
static GLfloat yRot[] = { 0.0f, 0.0f, 0.0f, 0.0f };
float *xPos;
float *yPos;

void chess() {

	float Rclr[] = { 135/256.0, .2 };
	float Gclr[] = { 206/256.0, .2 };
	float Bclr[] = { 250/256.0, .2 };

	for (int i = 0; i < 4; ++i) {
		glColor3f(Rclr[i % 2], Gclr[i % 2], Bclr[i % 2]);
		glViewport(xPos[i], yPos[i], width / 2, height / 2);
		glBegin(GL_POLYGON);
			glVertex2f(width, height);
			glVertex2f(-width, height);
			glVertex2f(-width, -height);
			glVertex2f(width, -height);
		glEnd();
	}

}

void RenderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT);

	chess();

	float Rclr[] = { 135 / 256.0, .2 };
	float Gclr[] = { 206 / 256.0, .2 };
	float Bclr[] = { 250 / 256.0, .2 };

	for (int i = 0; i<4; ++i) {
		glPushMatrix();
		glRotatef(xRot[i], 1.0f, 0.0f, 0.0f);
		glRotatef(yRot[i], 0.0f, 1.0f, 0.0f);
		glViewport(xPos[i], yPos[i], width / 2, height / 2);
		glColor3f(Rclr[(1+i) % 2], Gclr[(1+i) % 2], Bclr[(1+i) % 2]);
		drawobject[i]();
		glPopMatrix();
	}

	glutSwapBuffers();
}

void SetupRC() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
}

//int max(int x, int y) { return (x < y ? y : x); }
//int min(int x, int y) { return (x > y ? y : x); }

void SpecialKeys(int key, int x, int y) {

	if (key == GLUT_KEY_F5) {
		movie[selection] = !movie[selection];
		return;
	}

	if (key == GLUT_KEY_F1) selection = 0;
	else if (key == GLUT_KEY_F2) selection = 1;
	else if (key == GLUT_KEY_F3) selection = 2;
	else if (key == GLUT_KEY_F4) selection = 3;

	if (movie[selection]) {
		if (key == GLUT_KEY_UP) movieX_selection[selection] = min(0, (movieX_selection[selection] - 1) % 3);
		if (key == GLUT_KEY_DOWN) movieX_selection[selection] = max(2, (movieX_selection[selection] + 1) % 3); 
		if (key == GLUT_KEY_LEFT) movieY_selection[selection] = min(0, (movieY_selection[selection] - 1) % 3);
		if (key == GLUT_KEY_RIGHT) movieY_selection[selection] = max(2, (movieY_selection[selection] + 1) % 3);
	}
	else {
		if (key == GLUT_KEY_UP) xRot[selection] -= 5.0f;
		if (key == GLUT_KEY_DOWN) xRot[selection] += 5.0f;
		if (key == GLUT_KEY_LEFT) yRot[selection] -= 5.0f;
		if (key == GLUT_KEY_RIGHT) yRot[selection] += 5.0f;
		if (xRot[selection] > 356.0f) xRot[selection] = 0.0f;
		if (xRot[selection] < -1.0f) xRot[selection] = 355.0f;
		if (yRot[selection] > 356.0f) yRot[selection] = 0.0f;
		if (yRot[selection] < -1.0f) yRot[selection] = 355.0f;
	}

	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) { } // didn't work, so used specialKeys function

void Mouse(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON)
		if (x > (int)width / 2 && y <= (int)height / 2) selection = 0;
		else if (x <= (int)width / 2 && y <= (int)height / 2) selection = 1;
		else if (x <= (int)width / 2 && y > (int)height / 2) selection = 2;
		else if (x > (int)width / 2 && y > (int)height / 2) selection = 3;
}

void ChangeSize(int w, int h) {

	GLfloat nRange = 100.0f;

	if (h == 0) h = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);

	width = w;
	height = h;

	xPos = new float[4] { width / 2, 0, 0, width / 2 };
	yPos = new float[4] { height / 2, height / 2, 0, 0 };

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}

void quarters(int x) {
	selection = x;
}

void Movie(int s) {

	for (int i = 0; i < 4; ++i) {
		if (!movie[i]) continue;
		yRot[i] += movieY[i][movieY_selection[i]];
		xRot[i] += movieX[i][movieX_selection[i]];
//		drawobject[i]();
	}
	glutPostRedisplay();
	glutTimerFunc(33, Movie, s);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Points Example");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(33, Movie, 0);
	glutMouseFunc(Mouse);
	glutCreateMenu(quarters);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutAddMenuEntry("You may use Left Click on a quarter", -1);
	glutAddMenuEntry("Or use F1 - F4, arranged as mentioned below", -1);
	glutAddMenuEntry("Upper Right", 0);
	glutAddMenuEntry("Upper Left", 1);
	glutAddMenuEntry("Bottom Left", 2);
	glutAddMenuEntry("Bottom Right", 3);
	SetupRC();
	glutMainLoop();
	return 0;
}

// Four objects ,, numbered realtively with quarters numbering
void drawobject1() {

	GLfloat x, y, z, angle;

	glBegin(GL_TRIANGLES);
	glVertex3f(1, 1, 1);
	glVertex3f(2, 2, 1);
	glVertex3f(3, 3, 1);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(1, 1, 0);
	glVertex3f(2, 2, 0);
	glVertex3f(4, 4, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(1, 1, 2);
	glVertex3f(3, 3, 2);
	glVertex3f(4, 4, 2);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(2, 2, 3);
	glVertex3f(3, 3, 3);
	glVertex3f(4, 4, 3);
	glEnd();

}

void drawobject2() {

	GLfloat x, y, z, angle;

	glBegin(GL_POINTS);
	z = -50.0f;
	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f) {

		x = 50.0f*sin(angle);
		y = 50.0f*cos(angle);

		glVertex3f(x, y, z);
		z += 0.5f;
	}
	glEnd();

}

int a[3] = { 50,50,50 };
int b[3] = { 50,-50,50 };
int c[3] = { -50,-50,50 };
int d[3] = { -50,50,50 };
int e[3] = { 50,50,-50 };
int f[3] = { 50,-50,-50 };
int g[3] = { -50,-50,-50 };
int h[3] = { -50,50,-50 };
float angle = 1.0;

void drawobject3() {

	GLfloat x, y, z, angle;

	glBegin(GL_LINE_LOOP);
	glVertex3iv(a);
	glVertex3iv(b);
	glVertex3iv(c);
	glVertex3iv(d);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3iv(a);
	glVertex3iv(e);
	glVertex3iv(f);
	glVertex3iv(b);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3iv(d);
	glVertex3iv(h);
	glVertex3iv(g);
	glVertex3iv(c);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3iv(e);
	glVertex3iv(f);
	glVertex3iv(g);
	glVertex3iv(h);
	glEnd();

}

void drawobject4() {

	float sin_theta, cos_theta, angle, r, x, y, z;

	glBegin(GL_LINE_STRIP);
	r = 50.0f;
	angle = 0.0f;
	for (z = -r; z <r; z += .1f) {
		//x = r cos(theta) cos(phi)
		//y = r cos(theta) sin(phi)
		//z = r sin(theta)
		sin_theta = z / r;
		cos_theta = sqrt(1 - sin_theta*sin_theta);
		//C runtime functions sin() and cos() accept angle values measured in radians
		x = r*sin(angle)*cos_theta;
		y = r*cos(angle)*cos_theta;
		angle += 0.1f;
		// Specify the point and move the Z value up a little
		glVertex3f(x, y, z);
	}
	// Done drawing points
	glEnd();

}