#include <stdlib.h>
#include <iostream>
#include <glut.h>

#define max(x, y) (x<y?y:x)
#define min(x, y) (x>y?y:x)

#define GL_PI 3.1415f

void drawobject1();
void drawobject2();
void drawobject3();
void drawobject4();
void(*drawobject[4])(void) = { drawobject1 , drawobject2 , drawobject3 , drawobject4 };


int selection = 0;

bool movie[] = { 0, 0, 0, 0 };
// By default, it should only move around X- axis only, change ones to zero-es or two-es to make it around by default for the corresponding shapes
int movieX_selection[4] = { 2, 2, 2, 2 }; 
int movieY_selection[4] = { 1, 1, 1, 1 };
int movieZ_selection[4] = { 1, 1, 1, 1 };
float movieX[3] = { -5.0, 0, 5.0 };
float movieY[3] = { -5.0, 0, 5.0 };
float movieZ[3] = { -5.0, 0, 5.0 };

bool Zaxis = 0;

float width;
float height;
float xRot[] = { 0.0f,0.0f,0.0f,0.0f };
float yRot[] = { 0.0f,0.0f,0.0f,0.0f };
float zRot[] = { 0.0f,0.0f,0.0f,0.0f };
float *xPos;
float *yPos;

void chess() {

	float clr[][3] = { { 135 / 256.0, 206 / 256.0, 250 / 256.0 },{ .2, .2, .2 } };

	for (int i = 0; i < 4; ++i) {
		glColor3fv(clr[i % 2]);
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

	float clr[][3] = { { .2, .2, .2 } , { 135 / 256.0, 206 / 256.0, 250 / 256.0 }};

	for (int i = 0; i<4; ++i) {
		glPushMatrix();
		glRotatef(xRot[i], 1.0f, 0.0f, 0.0f);
		glRotatef(yRot[i], 0.0f, 1.0f, 0.0f);
		glRotatef(zRot[i], 0.0f, 0.0f, 1.0f);
		glViewport(xPos[i], yPos[i], width / 2, height / 2);
		glColor3fv(clr[i%2]);
		//uncomment the next line to output rotations of shapes, this test to make sure that shapes doesn't oscillate and that they roatate full circle (360 deg) output is streamed to console (stdout)
		//printf("%lf %lf %lf\n", xRot[selection], yRot[selection], zRot[selection]);
		drawobject[i]();
		glPopMatrix();
	}

	glutSwapBuffers();
}

void SetupRC() {
	glClearColor(0.0f,0.0f,0.0f, 1.0f);
}

void SpecialKeys(int key, int x, int y) {

	if (key == GLUT_KEY_F5) {
		movie[selection] = !movie[selection];
		return;
	}

	if (key == GLUT_KEY_HOME) { Zaxis = !Zaxis; return; }

	if (key == GLUT_KEY_F1) { selection = 0; return; }
	else if (key == GLUT_KEY_F2) { selection = 1; return; }
	else if (key == GLUT_KEY_F3) { selection = 2; return; }
	else if (key == GLUT_KEY_F4) { selection = 3; return; }

	if (movie[selection]) {
		if (!Zaxis) {
			if (key == GLUT_KEY_UP) if (1 <= movieX_selection[selection]) movieX_selection[selection]--;
			if (key == GLUT_KEY_DOWN) if (1 >= movieX_selection[selection]) movieX_selection[selection]++;
			if (key == GLUT_KEY_LEFT) if (1 <= movieY_selection[selection]) movieY_selection[selection]--;
			if (key == GLUT_KEY_RIGHT) if (1 >= movieY_selection[selection]) movieY_selection[selection]++;
		}else {
			if (key == GLUT_KEY_LEFT || key == GLUT_KEY_UP)
									if (1 <= movieZ_selection[selection]) movieZ_selection[selection]--;
			if (key == GLUT_KEY_RIGHT || key == GLUT_KEY_DOWN)
									if (1 >= movieZ_selection[selection]) movieZ_selection[selection]++;
		} 
	} else {
		if (!Zaxis) {
			if (key == GLUT_KEY_UP) xRot[selection] -= 5.0f;
			if (key == GLUT_KEY_DOWN) xRot[selection] += 5.0f;
			if (key == GLUT_KEY_LEFT) yRot[selection] -= 5.0f;
			if (key == GLUT_KEY_RIGHT) yRot[selection] += 5.0f;
		}else {
			if (key == GLUT_KEY_UP || key == GLUT_KEY_LEFT) zRot[selection] -= 5.0f;
			if (key == GLUT_KEY_DOWN || key == GLUT_KEY_RIGHT) zRot[selection] += 5.0f;
		}
		if (xRot[selection] > 356.0f) xRot[selection] =0.0f;
		if (xRot[selection] < -1.0f) xRot[selection] = 355.0f;
		if (yRot[selection] > 356.0f) yRot[selection] = 0.0f;
		if (yRot[selection] < -1.0f) yRot[selection] = 355.0f;
		if (zRot[selection] > 356.0f) zRot[selection] = 0.0f;
		if (zRot[selection] < -1.0f) zRot[selection] = 355.0f;
	}

	//glutPostRedisplay();
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
		xRot[i] += movieX[movieX_selection[i]];
		yRot[i] += movieY[movieY_selection[i]];
		zRot[i] += movieZ[movieZ_selection[i]];
		if (xRot[selection] > 356.0f) xRot[selection] = 0.0f;
		if (xRot[selection] < -1.0f) xRot[selection] = 355.0f;
		if (yRot[selection] > 356.0f) yRot[selection] = 0.0f;
		if (yRot[selection] < -1.0f) yRot[selection] = 355.0f;
		if (zRot[selection] > 356.0f) zRot[selection] = 0.0f;
		if (zRot[selection] < -1.0f) zRot[selection] = 355.0f;
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
	glutTimerFunc(100, Movie, 0);
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

	glBegin(GL_QUADS);
		glVertex3f(50, -50, -50);
		glVertex3f(50, 50, -50);
		glVertex3f(-50, 50, -50);
		glVertex3f(-50, -50, -50);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(0, 0, 100);
		glVertex3f(50, 50, -50);
		glVertex3f(50, -50, -50);
	
		glVertex3f(0, 0, 100);
		glVertex3f(50, -50, -50);
		glVertex3f(-50, -50, -50);

		glVertex3f(0, 0, 100);
		glVertex3f(-50, -50, -50);
		glVertex3f(-50, 50, -50);

		glVertex3f(0, 0, 100);
		glVertex3f(-50, 50, -50);
		glVertex3f(50, 50, -50);
	glEnd();
	
	float clr[] = { 135 / 256.0, 206 / 256.0, 250 / 256.0 };
	glColor3fv(clr);

	glBegin(GL_LINES);
		glVertex3f(0, 0, 100);
		glVertex3f(50, 50, -50);
	
		glVertex3f(0, 0, 100);
		glVertex3f(50, -50, -50);
	
		glVertex3f(0, 0, 100);
		glVertex3f(-50, -50, -50);	

		glVertex3f(0, 0, 100);
		glVertex3f(-50, 50, -50);
	
		glVertex3f(50, 50, -50);
		glVertex3f(50, -50, -50);

		glVertex3f(50, -50, -50);
		glVertex3f(-50, -50, -50);

		glVertex3f(-50, -50, -50);
		glVertex3f(-50, 50, -50);

		glVertex3f(-50, 50, -50);
		glVertex3f(50, 50, -50);
	glEnd();

}

void drawobject2() {

	float sin_theta, cos_theta, angle, r, x, y, z;

	glBegin(GL_LINE_STRIP);
	r = 20.0f;
	angle = 0.0f;
	float res = 0;
	for (z = -r; z <r; z += .1) {
		sin_theta = z / r;
		cos_theta = sqrt(1 - sin_theta*sin_theta);

		x = r*sin(angle)*cos_theta;
		res = max(res, x);
		y = r*cos(angle)*cos_theta;
		angle += 0.1f;

		glVertex3f(x, y + 50, z);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	r = res;
	y = 40.0f;
	for (angle = 0 ; angle < 2 * GL_PI * 10.0f; angle += .1) {
		x = r*sin(angle);
		z = r*cos(angle);
		glVertex3f(x, y, z);
		y -= .1f;
		r -= res / (2 * GL_PI * 100.0);
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

	glBegin(GL_QUADS);
		glVertex3iv(a);
		glVertex3iv(b);
		glVertex3iv(c);
		glVertex3iv(d);
	
		glVertex3iv(a);
		glVertex3iv(e);
		glVertex3iv(f);
		glVertex3iv(b);
	
		glVertex3iv(d);
		glVertex3iv(h);
		glVertex3iv(g);
		glVertex3iv(c);
	
		glVertex3iv(e);
		glVertex3iv(f);
		glVertex3iv(g);
		glVertex3iv(h);
	
		glVertex3iv(c);
		glVertex3iv(f);
		glVertex3iv(g);
		glVertex3iv(b);
	
		glVertex3iv(e);
		glVertex3iv(a);
		glVertex3iv(d);
		glVertex3iv(h);
	glEnd();

	float clr[] = { 135 / 256.0, 206 / 256.0, 250 / 256.0 };
	glColor3fv(clr);

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
	r = 30.0f;
	angle = 0.0f;
	for (z = -r; z <r; z += .1) {
		sin_theta = z / r;
		cos_theta = sqrt(1 - sin_theta*sin_theta);
		
		x = r*sin(angle)*cos_theta;
		y = r*cos(angle)*cos_theta;
		angle += 0.1f;
	
		glVertex3f(x, y, z);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	r = 20.0f;
	angle = 0.0f;
	for (z = -r; z <r; z += .1) {
		sin_theta = z / r;
		cos_theta = sqrt(1 - sin_theta*sin_theta);

		x = r*sin(angle)*cos_theta;
		y = r*cos(angle)*cos_theta;
		angle += 0.1f;

		glVertex3f(x - 60, y, z);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	r = 10.0f;
	angle = 0.0f;
	for (z = -r; z <r; z += .1) {
		sin_theta = z / r;
		cos_theta = sqrt(1 - sin_theta*sin_theta);

		x = r*sin(angle)*cos_theta;
		y = r*cos(angle)*cos_theta;
		angle += 0.1f;

		glVertex3f(x - 100, y, z);
	}
	glEnd();

}