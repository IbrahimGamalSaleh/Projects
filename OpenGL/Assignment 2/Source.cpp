#include <stdlib.h>
#include <iostream>
#include <glut.h>

#define max(x, y) (x<y?y:x)
#define min(x, y) (x>y?y:x)

#define GL_PI 3.1415f

/* void drawobject1(); */
/* void drawobject2(); */
void drawobject3(bool s, int i);
/* void drawobject4(); */
/* void(*drawobject[4])(void) = { drawobject1 , drawobject2 , drawobject3 , drawobject4 }; */

// selector upon which it's decided which shape will be affected by rotations or translations
// numbered as shapes mapped
int selection = 0;

// boolean array for the 4 shapes to automatically rotate them around the 3 axis
bool movie[] = { 0, 0, 0, 0 };

// By default, it should only move around X- axis only, changing ones to zero-es or two-es to makes it round by default for the corresponding shapes as mapped in manual
int movieX_selection[4] = { 2, 2, 2, 2 };
int movieY_selection[4] = { 1, 1, 1, 1 };
int movieZ_selection[4] = { 1, 1, 1, 1 };
float movieX[3] = { -5.0, 0, 5.0 };
float movieY[3] = { -5.0, 0, 5.0 };
float movieZ[3] = { -5.0, 0, 5.0 };

// boolean for rotation in z-axis , if true
bool Zaxis = 0;

// boolean for motion(moving shapes) , if true
bool animation;

// width and height for current size of window
float width;
float height;

// shapes' rotations
float xRot[] = { 0.0f,0.0f,0.0f,0.0f };
float yRot[] = { 0.0f,0.0f,0.0f,0.0f };
float zRot[] = { 0.0f,0.0f,0.0f,0.0f };

// points at which the viewport is portioned for 4 sections
float *xPos;
float *yPos;

// rotations to simulate the 4 cameras
float Scene[4][4] = { { 0,0,1,0 }
,{ 90,0,1,0 }
,{ 180,0,1,0 }
,{ 90,1,0,0 } };

// shapes' translations
float xTrans[4] = { 50,-50,-50,50 };
float yTrans[4] = { 50,50,-50,-50 };
float zTrans[4] = { 0,0,0,0 };

void screen() {

	float clr[3] = { 0.4, 0.4, 0.4 };

	// draw a frame around every camera
	float scr[][2] = {
		// top edge of frame
		{ width / 8, height / 8, },
		{ -width / 8, height / 8, },
		{ -width / 8, height / 8-5 },
		{ width / 8, height / 8-5 },

		// right edge of frame
		{ width / 8, height / 8 },
		{ width / 8, -height / 8 },
		{ width - 5, height / 8 },
		{ width - 5, -height / 8 },

		// bottom edge of frame
		{ width / 8, -height / 8 },
		{ -width / 8, -height / 8 },
		{ -width / 8, -height / 8+5 },
		{ width / 8, -height / 8+5 },

		// left edge of frame
		{ -width / 8, -height / 8 },
		{ -width / 8, height / 8 },
		{ -width - 5, -height / 8+5 },
		{ -width - 5, height / 8 },
	};

	for (int i = 0; i < 4; ++i) {
		glColor3f(1.0,1.0,1.0);
		glViewport(xPos[i], yPos[i], width / 2, height / 2);
		glPushMatrix();
		glBegin(GL_POLYGON);
		glVertex2fv(scr[0 + (i * 4)]);
		glVertex2fv(scr[1 + (i * 4)]);
		glVertex2fv(scr[2 + (i * 4)]);
		glVertex2fv(scr[3 + (i * 4)]);
		glEnd();
		glPopMatrix();
	}

}

void RenderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	// an attempt to make a border around each camera, as a frame
	//screen();
	glViewport(0,0,width, height);
	glBegin(GL_LINES);
	glVertex2d(-width,0);
	glVertex2d(width, 0);
	glEnd();
	
	glBegin(GL_LINES);
	glVertex2d(0, -height);
	glVertex2d(0, height * 2);
	glEnd();


	for (int i = 0; i < 4; ++i) {
		glPushMatrix();
		glViewport(xPos[i], yPos[i], width / 2, height / 2);
		//gluLookAt(Scene[i][0], Scene[i][1], Scene[i][2],
		//	Scene[i][3], Scene[i][4], Scene[i][5],
		//	Scene[i][6], Scene[i][7], Scene[i][8]);
		glRotatef(Scene[i][0], Scene[i][1], Scene[i][2], Scene[i][3]);
		for (int j = 0; j<4; ++j) {
			glPushMatrix();
			// the following 4 lines of code are meant to adjust initial position and further translations considering change windows size
			//if (j == 0) glTranslatef(xTrans[j] , yTrans[j] , zTrans[j]);
			//else if (j == 1) glTranslatef(xTrans[j] , yTrans[j] , zTrans[j]);
			//else if (j == 2) glTranslatef(xTrans[j] , yTrans[j] , zTrans[j]);
			//else glTranslatef(xTrans[j] , yTrans[j] , zTrans[j]);
			if (j == 0) glTranslatef(xTrans[j] + width / 40, yTrans[j] + height / 40, zTrans[j]);
			else if (j == 1) glTranslatef(xTrans[j] - width / 40, yTrans[j] + height / 40, zTrans[j]);
			else if (j == 2) glTranslatef(xTrans[j] - width / 40, yTrans[j] - height / 40, zTrans[j]);
			else glTranslatef(xTrans[j] + width / 40, yTrans[j] - height / 40, zTrans[j]);
			glRotatef(xRot[j], 1.0f, 0.0f, 0.0f);
			glRotatef(yRot[j], 0.0f, 1.0f, 0.0f);
			glRotatef(zRot[j], 0.0f, 0.0f, 1.0f);
			glScalef(.40, .40, .40);
			drawobject3((j == selection), j);
			//uncomment the next line to output rotations of shapes, this test to make sure that shapes doesn't oscillate and that they roatate full circle (360 deg) output is streamed to console (stdout)
			//printf("%lf %lf %lf\n%lf %lf %lf\n\n", xRot[selection], yRot[selection], zRot[selection], width / 40 + xTrans[selection], height / 30 + yTrans[selection], zTrans[selection]);
			
			glPopMatrix();
		}
		glPopMatrix();
	}

	glutSwapBuffers();
}

void SetupRC() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void SpecialKeys(int key, int x, int y) {
	
	
	if (key == GLUT_KEY_F5) {
		movie[selection] = !movie[selection];
		return;
	}

	if (key == GLUT_KEY_F6) { animation = !animation; return; }

	if (key == GLUT_KEY_HOME) { Zaxis = !Zaxis; return; }

	if (key == GLUT_KEY_F1) { selection = 0; return; }
	else if (key == GLUT_KEY_F2) { selection = 1; return; }
	else if (key == GLUT_KEY_F3) { selection = 2; return; }
	else if (key == GLUT_KEY_F4) { selection = 3; return; }

	if (movie[selection])
		if (!Zaxis) {
			if (key == GLUT_KEY_UP) if (1 <= movieX_selection[selection]) movieX_selection[selection]--;
			if (key == GLUT_KEY_DOWN) if (1 >= movieX_selection[selection]) movieX_selection[selection]++;
			if (key == GLUT_KEY_LEFT) if (1 <= movieY_selection[selection]) movieY_selection[selection]--;
			if (key == GLUT_KEY_RIGHT) if (1 >= movieY_selection[selection]) movieY_selection[selection]++;
		}
		else {
			if (key == GLUT_KEY_LEFT || key == GLUT_KEY_UP)
				if (1 <= movieZ_selection[selection]) movieZ_selection[selection]--;
			if (key == GLUT_KEY_RIGHT || key == GLUT_KEY_DOWN)
				if (1 >= movieZ_selection[selection]) movieZ_selection[selection]++;
		}
	
	if (animation) 
		if (!Zaxis) {
			if (key == GLUT_KEY_LEFT) { xTrans[selection] -= 10.0f; }
			if (key == GLUT_KEY_RIGHT) { xTrans[selection] += 10.0f; }
			if (key == GLUT_KEY_UP) { yTrans[selection] -= 10.0f; }
			if (key == GLUT_KEY_DOWN) { yTrans[selection] += 10.0f; }
		} else {
			if (key == GLUT_KEY_UP || key == GLUT_KEY_LEFT) { zTrans[selection] -= 10.0f; }
			if (key == GLUT_KEY_DOWN || key == GLUT_KEY_RIGHT) { zTrans[selection] += 10.0f; }
		}
	else 
		if (!Zaxis) {
			if (key == GLUT_KEY_UP) xRot[selection] -= 5.0f;
			if (key == GLUT_KEY_DOWN) xRot[selection] += 5.0f;
			if (key == GLUT_KEY_LEFT) yRot[selection] -= 5.0f;
			if (key == GLUT_KEY_RIGHT) yRot[selection] += 5.0f;
		}
		else {
			if (key == GLUT_KEY_UP || key == GLUT_KEY_LEFT) zRot[selection] -= 5.0f;
			if (key == GLUT_KEY_DOWN || key == GLUT_KEY_RIGHT) zRot[selection] += 5.0f;
		
		}

	if (xRot[selection] > 356.0f) xRot[selection] = 0.0f;
	if (xRot[selection] < -1.0f) xRot[selection] = 355.0f;
	if (yRot[selection] > 356.0f) yRot[selection] = 0.0f;
	if (yRot[selection] < -1.0f) yRot[selection] = 355.0f;
	if (zRot[selection] > 356.0f) zRot[selection] = 0.0f;
	if (zRot[selection] < -1.0f) zRot[selection] = 355.0f;

	//glutPostRedisplay();
}

void Keyboard(unsigned char c, int x, int y) {
	bool OZaxis = Zaxis;
	bool Oanimation = animation;
	
	switch (c) {
		case 'w': 	case 'W':
			Zaxis = 0;
			animation = 0;
			SpecialKeys(GLUT_KEY_UP, x, y);
			break;
		case 's': 	case 'S':
			Zaxis = 0;
			animation = 0;
			SpecialKeys(GLUT_KEY_DOWN, x, y);
			break;
		case 'd': 	case 'D':
			Zaxis = 0;
			animation = 0;
			SpecialKeys(GLUT_KEY_RIGHT, x, y);
			break;
		case 'a': 	case 'A':
			Zaxis = 0;
			animation = 0;
			SpecialKeys(GLUT_KEY_LEFT, x, y);
			break;
		case 'q': 	case 'Q':
			Zaxis = 1;
			animation = 0;
			SpecialKeys(GLUT_KEY_UP, x, y);
			break;
		case 'z': 	case 'Z':
			Zaxis = 1;
			animation = 0;
			SpecialKeys(GLUT_KEY_DOWN, x, y);
			break;
		case 'i': 	case 'I':
			animation = 1;
			SpecialKeys(GLUT_KEY_UP, x, y);
			break;
		case 'k': 	case 'K':
			animation = 1;
			SpecialKeys(GLUT_KEY_DOWN, x, y);
			break;
		case 'l': 	case 'L':
			animation = 1;
			SpecialKeys(GLUT_KEY_RIGHT, x, y);
			break;
		case 'j': 	case 'J':
			animation = 1;
			SpecialKeys(GLUT_KEY_LEFT, x, y);
			break;
		case 'u': 	case 'U':
			animation = 1;
			Zaxis = 1;
			SpecialKeys(GLUT_KEY_LEFT, x, y);
			break;
		case 'n': 	case 'N':
			animation = 1;
			Zaxis = 1;
			SpecialKeys(GLUT_KEY_RIGHT, x, y);
			break;

	}

	animation = Oanimation;
	Zaxis = OZaxis;
}

void ChangeSize(int w, int h) {

	//printf("%lf %lf\n", w, h);

	width = w;
	height = h;


	//printf("%lf %lf\n", width, height);

	GLfloat nRange = 100.0f;

	if (h == 0) h = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	xPos = new float[4]{ width / 2, 0, 0, width / 2 };
	yPos = new float[4] { height / 2, height / 2, 0, 0 };

	if (w <= h) 
		glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange* (h / w), nRange* (h / w));
	else
		glOrtho(-nRange*w / h, nRange*w / h, -nRange, nRange, -nRange, nRange);
		
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void shapes(int x) {
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);// | GLUT_DEPTH);
	//glEnable(GL_DEPTH_TEST);
	glutCreateWindow("Points Example");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(100, Movie, 0);
	glutCreateMenu(shapes);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutAddMenuEntry("use F1 - F4 to select a shape..", -1);
	glutAddMenuEntry(", arranged as mentioned below", -1);
	glutAddMenuEntry("Black Cube", 0);
	glutAddMenuEntry("Dark-Gray Cube", 1);
	glutAddMenuEntry("Gray Cube", 2);
	glutAddMenuEntry("White Cube", 3);
	SetupRC();
	glutMainLoop();
	return 0;
}

/*
// Four objects ,, numbered realtively with shapes numbering
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
*/

/*
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
	for (angle = 0; angle < 2 * GL_PI * 10.0f; angle += .1) {
		x = r*sin(angle);
		z = r*cos(angle);
		glVertex3f(x, y, z);
		y -= .1f;
		r -= res / (2 * GL_PI * 100.0);
	}
	glEnd();

}
*/

void drawobject3(bool s, int i) {

	float clr[][3] = { { 0.0,0.0,0.0 },{ .3,.3,.3 },{ .6,.6,.6 },{ 1.0,1.0,1.0 },{ 135 / 256.0, 206 / 256.0, 250 / 256.0 } };

	int a[3] = { 50,50,50 };
	int b[3] = { 50,-50,50 };
	int c[3] = { -50,-50,50 };
	int d[3] = { -50,50,50 };
	int e[3] = { 50,50,-50 };
	int f[3] = { 50,-50,-50 };
	int g[3] = { -50,-50,-50 };
	int h[3] = { -50,50,-50 };
	
	if (s) glColor3fv(clr[4]);
	else glColor3fv(clr[i]);

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

	if (s) glColor3fv(clr[1]);
	else  glColor3fv(clr[4]);

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

/*
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
*/



////#include <glut.h>
////#include <math.h>
////
////// Define a constant for the value of PI
////#define GL_PI 3.1415f
////
////// Rotation amounts
////static GLfloat  xRot[] = { 0.0f, 0.0f, 0.0f, 0.0f };
////static GLfloat  yRot[] = { 0.0f, 0.0f, 0.0f, 0.0f };
////static GLfloat hight = 600, width = 600;
////static GLint slactor;
////
////
////void drawobject2(GLfloat Xindex, GLfloat Yindex, GLfloat xangle, GLfloat yangle) {
////
////	glPushMatrix();
////	glRotatef(Xindex + xangle, 1.0f, 0.0f, 0.0f);
////	glRotatef(Yindex + yangle, 0.0f, 1.0f, 0.0f);
////
////	glColor3f(0.0f, 0.0f, 1.0f);
////	glBegin(GL_QUADS);
////	glVertex3f(50, -50, -50);
////	glVertex3f(50, 50, -50);
////	glVertex3f(-50, 50, -50);
////	glVertex3f(-50, -50, -50);
////	glEnd();
////
////	glColor3f(0.0f, 1.0f, 0.0f);
////	glBegin(GL_TRIANGLE_STRIP);
////	glVertex3f(0, 0, 100);
////	glVertex3f(50, 50, -50);
////	glVertex3f(50, -50, -50);
////
////	glColor3f(1.0f, 0.0f, 0.0f);
////	glVertex3f(0, 0, 100);
////	glVertex3f(50, -50, -50);
////	glVertex3f(-50, -50, -50);
////
////	glColor3f(1.0f, 0.0f, 1.0f);
////	glVertex3f(0, 0, 100);
////	glVertex3f(-50, -50, -50);
////	glVertex3f(-50, 50, -50);
////
////	glColor3f(0.0f, 1.0f, 1.0f);
////	glVertex3f(0, 0, 100);
////	glVertex3f(-50, 50, -50);
////	glVertex3f(50, 50, -50);
////	glEnd();
////
////	float clr[] = { 135 / 256.0, 206 / 256.0, 250 / 256.0 };
////	glColor3fv(clr);
////
////	glBegin(GL_LINES);
////	glVertex3f(0, 0, 100);
////	glVertex3f(50, 50, -50);
////
////	glVertex3f(0, 0, 100);
////	glVertex3f(50, -50, -50);
////
////	glVertex3f(0, 0, 100);
////	glVertex3f(-50, -50, -50);
////
////	glVertex3f(0, 0, 100);
////	glVertex3f(-50, 50, -50);
////
////	glVertex3f(50, 50, -50);
////	glVertex3f(50, -50, -50);
////
////	glVertex3f(50, -50, -50);
////	glVertex3f(-50, -50, -50);
////
////	glVertex3f(-50, -50, -50);
////	glVertex3f(-50, 50, -50);
////
////	glVertex3f(-50, 50, -50);
////	glVertex3f(50, 50, -50);
////	glEnd();
////	glPopMatrix();
////}
////int a[3] = { 50, 50, 50 };
////int b[3] = { 50, -50, 50 };
////int c[3] = { -50, -50, 50 };
////int d[3] = { -50, 50, 50 };
////int e[3] = { 50, 50, -50 };
////int f[3] = { 50, -50, -50 };
////int g[3] = { -50, -50, -50 };
////int h[3] = { -50, 50, -50 };
////float angle = 1.0;
////void drawobject3(GLfloat Xindex, GLfloat Yindex, GLfloat xangle, GLfloat yangle) {
////	glPushMatrix();
////	glRotatef(Xindex + xangle, 1.0f, 0.0f, 0.0f);
////	glRotatef(Yindex + yangle, 0.0f, 1.0f, 0.0f);
////	glColor3f(0.0f, 0.0f, 1.0f);
////	glBegin(GL_QUADS);
////	glVertex3iv(a);
////	glVertex3iv(b);
////	glVertex3iv(c);
////	glVertex3iv(d);
////	glColor3f(0.0f, 1.0f, 0.0f);
////	glVertex3iv(a);
////	glVertex3iv(e);
////	glVertex3iv(f);
////	glVertex3iv(b);
////	glColor3f(1.0f, 0.0f, 0.0f);
////	glVertex3iv(d);
////	glVertex3iv(h);
////	glVertex3iv(g);
////	glVertex3iv(c);
////	glColor3f(0.0f, 1.0f, 1.0f);
////	glVertex3iv(e);
////	glVertex3iv(f);
////	glVertex3iv(g);
////	glVertex3iv(h);
////	glColor3f(1.0f, 0.0f, 1.0f);
////	glVertex3iv(c);
////	glVertex3iv(f);
////	glVertex3iv(g);
////	glVertex3iv(b);
////	glColor3f(1.0f, 1.0f, 0.0f);
////	glVertex3iv(e);
////	glVertex3iv(a);
////	glVertex3iv(d);
////	glVertex3iv(h);
////	glEnd();
////
////	float clr[] = { 135 / 256.0, 206 / 256.0, 250 / 256.0 };
////	glColor3fv(clr);
////
////	glBegin(GL_LINE_LOOP);
////	glVertex3iv(a);
////	glVertex3iv(b);
////	glVertex3iv(c);
////	glVertex3iv(d);
////	glEnd();
////	glBegin(GL_LINE_LOOP);
////	glVertex3iv(a);
////	glVertex3iv(e);
////	glVertex3iv(f);
////	glVertex3iv(b);
////	glEnd();
////	glBegin(GL_LINE_LOOP);
////	glVertex3iv(d);
////	glVertex3iv(h);
////	glVertex3iv(g);
////	glVertex3iv(c);
////	glEnd();
////	glBegin(GL_LINE_LOOP);
////	glVertex3iv(e);
////	glVertex3iv(f);
////	glVertex3iv(g);
////	glVertex3iv(h);
////	glEnd();
////	glPopMatrix();
////}
////
////void drawobject4(GLfloat Xindex, GLfloat Yindex, GLfloat xangle, GLfloat yangle) {
////	glPushMatrix();
////	glRotatef(Xindex + xangle, 1.0f, 0.0f, 0.0f);
////	glRotatef(Yindex + yangle, 0.0f, 1.0f, 0.0f);
////	glColor3f(0.0f, 0.0f, 1.0f);
////	float sin_theta, cos_theta, angle, r, x, y, z;
////
////	glBegin(GL_LINE_STRIP);
////	r = 30.0f;
////	angle = 0.0f;
////	for (z = -r; z <r; z += .1) {
////		sin_theta = z / r;
////		cos_theta = sqrt(1 - sin_theta*sin_theta);
////
////		x = r*sin(angle)*cos_theta;
////		y = r*cos(angle)*cos_theta;
////		angle += 0.1f;
////
////		glVertex3f(x, y, z);
////	}
////	glEnd();
////	glColor3f(0.0f, 1.0f, 0.0f);
////	glBegin(GL_LINE_STRIP);
////	r = 20.0f;
////	angle = 0.0f;
////	for (z = -r; z <r; z += .1) {
////		sin_theta = z / r;
////		cos_theta = sqrt(1 - sin_theta*sin_theta);
////
////		x = r*sin(angle)*cos_theta;
////		y = r*cos(angle)*cos_theta;
////		angle += 0.1f;
////
////		glVertex3f(x - 60, y, z);
////	}
////	glEnd();
////	glColor3f(1.0f, 0.0f, 0.0f);
////	glBegin(GL_LINE_STRIP);
////	r = 10.0f;
////	angle = 0.0f;
////	for (z = -r; z <r; z += .1) {
////		sin_theta = z / r;
////		cos_theta = sqrt(1 - sin_theta*sin_theta);
////
////		x = r*sin(angle)*cos_theta;
////		y = r*cos(angle)*cos_theta;
////		angle += 0.1f;
////
////		glVertex3f(x - 100, y, z);
////	}
////	glEnd();
////	glPopMatrix();
////}
////void Coordinates()
////{
////	glColor3f(1.0f, 1.0f, 1.0f);
////	glPushMatrix();
////	glBegin(GL_LINE);
////	for (int i = 0; i < hight; i++)
////	{
////		glVertex3f(width / 2, i, 0);
////	}
////	glEnd();
////	glPopMatrix();
////}
////// Called to draw scene
////void RenderScene(void) {
////	GLfloat x, y, z, angle; // Storeage for coordinates and angles
////
////							// Clear the window with current clearing color
////	glClear(GL_COLOR_BUFFER_BIT);
////
////
////
////	glColor3f(0.0f, 1.0f, 0.0f);
////	// Save matrix state and do the rotation
////	glPushMatrix();
////	glRotatef(xRot[0], 1.0f, 0.0f, 0.0f);
////	glRotatef(yRot[0], 0.0f, 1.0f, 0.0f);
////
////	// Call only once for all remaining points
////
////	glViewport(0, 0, width / 4, hight / 4);
////	glBegin(GL_POINTS);
////
////	y = -50.0f;
////	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f)
////	{
////
////		//C runtime functions sin() and cos() accept angle values measured in radians 
////		x = 50.0f* sin(angle);
////		z = 50.0f*cos(angle);
////
////		// Specify the point and move the Z value up a little	
////		glVertex3f(x, y, z);
////		y += 0.5f;
////	}
////
////	// Done drawing points
////	glEnd();
////	glPopMatrix();
////
////
////	glColor3f(1.0f, 0.0f, 0.0f);
////
////	glPushMatrix();
////	glRotatef(xRot[0], 1.0f, 0.0f, 0.0f);
////	glRotatef(yRot[0], 0.0f, 1.0f, 0.0f);
////	glViewport(width / 2, 0, width / 4, hight / 4);
////	glBegin(GL_POINTS);
////
////	z = -50.0f;
////	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f)
////	{
////
////		//C runtime functions sin() and cos() accept angle values measured in radians
////		x = 50.0f* sin(angle);
////		y = 50.0f*cos(angle);
////
////		// Specify the point and move the Z value up a little	
////		glVertex3f(x, y, z);
////		z += 0.5f;
////	}
////
////	// Done drawing points
////	glEnd();
////	glPopMatrix();
////
////	glColor3f(0.0f, 0.0f, 1.0f);
////
////	glPushMatrix();
////	glRotatef(xRot[0], 1.0f, 0.0f, 0.0f);
////	glRotatef(yRot[0], 0.0f, 1.0f, 0.0f);
////	glViewport(0, hight / 2, width / 4, hight / 4);
////	glBegin(GL_POINTS);
////
////	x = -50.0f;
////	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f)
////	{
////
////		//C runtime functions sin() and cos() accept angle values measured in radians
////		z = 50.0f* sin(angle);
////		y = 50.0f*cos(angle);
////
////		// Specify the point and move the Z value up a little	
////		glVertex3f(x, y, z);
////		x += 0.5f;
////	}
////
////	// Done drawing points
////	glEnd();
////
////
////	glPopMatrix();
////
////
////	glColor3f(1.0f, 1.0f, 0.0f);
////	glPushMatrix();
////	glRotatef(xRot[0], 1.0f, 0.0f, 0.0f);
////	glRotatef(yRot[0], 0.0f, 1.0f, 0.0f);
////	glViewport(width / 2, hight / 2, width / 4, hight / 4);
////	glBegin(GL_POINTS);
////
////	z = 50.0f;
////	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f)
////	{
////
////		//C runtime functions sin() and cos() accept angle values measured in radians
////		x = 50.0f* sin(angle);
////		y = 50.0f*cos(angle);
////
////		// Specify the point and move the Z value up a little	
////		glVertex3f(x, y, z);
////		z -= 0.5f;
////	}
////
////	// Done drawing points
////	glEnd();
////	//////////////////////////////////////////////////////////////////////////////////////////////
////	//OBJECT2
////	//(150.0)
////	// Restore transformations
////
////	glPopMatrix();
////
////	glViewport(width / 4, 0, width / 4, hight / 4);
////	drawobject2(xRot[1], yRot[1], 0.0, 0.0);
////
////	// (450.0)
////
////	glViewport(3 * width / 4, 0, width / 4, hight / 4);
////	drawobject2(xRot[1], yRot[1], 90.0, 0.0);
////
////	// (150.300)
////
////	glViewport(width / 4, hight / 2, width / 4, hight / 4);
////	drawobject2(xRot[1], yRot[1], 180.0, 0.0);
////
////	// (450.300)
////
////	glViewport(3 * width / 4, hight / 2, width / 4, hight / 4);
////	drawobject2(xRot[1], yRot[1], 0.0, 270.0);
////
////
////
////	//////////////////////////////////////////////////////////
////	//OBJECT3
////	//(0,150)
////	glViewport(0, hight / 4, width / 4, hight / 4);
////	drawobject3(xRot[2], yRot[2], 0.0, 0.0);
////
////
////	//(300,150)
////	glViewport(width / 2, hight / 4, width / 4, hight / 4);
////	drawobject3(xRot[2], yRot[2], 0.0, 90.0);
////
////	//(0,450)
////	glViewport(0, 3 * hight / 4, width / 4, hight / 4);
////	drawobject3(xRot[2], yRot[2], 360.0, 180.0);
////
////	//(300,450)
////	glViewport(width / 2, 3 * hight / 4, width / 4, hight / 4);
////	drawobject3(xRot[2], yRot[2], 90.0, 360.0);
////
////	/////////////////////////////////////////////////////////
////	//OBJECT4
////
////	//(150,150)
////	glViewport(width / 4, hight / 4, width / 4, hight / 4);
////	drawobject4(xRot[3], yRot[3], 0.0, 0.0);
////
////	//(450,150)
////	glViewport(3 * width / 4, hight / 4, width / 4, hight / 4);
////	drawobject4(xRot[3], yRot[3], 0.0, 90.0);
////
////	//(150,450)
////	glViewport(width / 4, 3 * hight / 4, width / 4, hight / 4);
////	drawobject4(xRot[3], yRot[3], 90.0, 90.0);
////
////	//(450,450)
////	glViewport(3 * width / 4, 3 * hight / 4, width / 4, hight / 4);
////	drawobject4(xRot[3], yRot[3], 90.0, 0.0);
////
////	//glViewport(width / 2, 0, 2, 2);
////	//Coordinates();
////	// Flush drawing commands
////	glutSwapBuffers();
////
////}
////// This function does any needed initialization on the rendering
////// context. 
////void SetupRC() {
////	// Black background
////	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
////
////	// Set drawing color to green
////	glColor3f(0.0f, 1.0f, 0.0f);
////}
////
////void SpecialKeys(int key, int x, int y) {
////	if (key == GLUT_KEY_UP) xRot[slactor] -= 5.0f;
////	if (key == GLUT_KEY_DOWN)  xRot[slactor] += 5.0f;
////	if (key == GLUT_KEY_LEFT) yRot[slactor] -= 5.0f;
////	if (key == GLUT_KEY_RIGHT) yRot[slactor] += 5.0f;
////
////	if (xRot[slactor] > 356.0f) xRot[slactor] = 0.0f;
////	if (xRot[slactor] < -1.0f) xRot[slactor] = 355.0f;
////	if (yRot[slactor] > 356.0f) yRot[slactor] = 0.0f;
////	if (yRot[slactor] < -1.0f) yRot[slactor] = 355.0f;
////
////	// Refresh the Window
////	glutPostRedisplay();
////}
////void ChangeSize(int w, int h) {
////	GLfloat nRange = 100.0f;
////	GLfloat aspectRatio;
////	width = w;
////	hight = h;
////	// Prevent a divide by zero
////	if (h == 0)	h = 1;
////
////	// Set Viewport to window dimensions
////	glViewport(0, 0, w, h);
////
////	// Reset projection matrix stack
////	glMatrixMode(GL_PROJECTION);
////	glLoadIdentity();
////	aspectRatio = (GLfloat)w / (GLfloat)h;
////	// Establish clipping volume (left, right, bottom, top, near, far)
////	if (w <= h)
////		glOrtho(-nRange, nRange, -nRange / aspectRatio, nRange / aspectRatio, -nRange, nRange);
////	else
////		glOrtho(-nRange* aspectRatio, nRange* aspectRatio, -nRange, nRange, -nRange, nRange);
////
////	// Reset Model view matrix stack
////	glMatrixMode(GL_MODELVIEW);
////	glLoadIdentity();
////
////}
////
////void ProcessMenu(int value) {
////	slactor = value;
////	/*switch (value)	{
////
////	case 1: slactor = 0; break;
////	case 2: slactor = 1; break;
////
////	case 3: slactor = 2; break;
////
////	case 4: slactor = 3; break;
////
////
////	default: break;
////	}*/
////
////
////	glutPostRedisplay();
////}
////
////
////
////int main(int argc, char* argv[])
////{
////	glutInit(&argc, argv);
////	//glutInitWindowSize(600, 600);
////	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
////	glutCreateWindow("Points Example");
////	glutCreateMenu(ProcessMenu);
////	glutAddMenuEntry("Points", 0);
////	glutAddMenuEntry("Pyramid", 1);
////	glutAddMenuEntry("Cube", 2);
////	glutAddMenuEntry("ball", 3);
////	glutAttachMenu(GLUT_RIGHT_BUTTON);
////
////	glutReshapeFunc(ChangeSize);
////	glutSpecialFunc(SpecialKeys);
////	glutDisplayFunc(RenderScene);
////	SetupRC();
////	glutMainLoop();
////
////	return 0;
////}
////
////
//////
//////#include <glut.h>
//////#include <math.h>
//////using namespace std;
//////// Define a constant for the value of PI
//////#define GL_PI 3.1415f
//////
//////// Rotation amounts
//////static GLfloat  xRot[] = { 0.0f, 0.0f, 0.0f, 0.0f };
//////static GLfloat  yRot[] = { 0.0f, 0.0f, 0.0f, 0.0f };
//////static GLfloat  translatey[] = { 0.0f, 0.0f, 0.0f, 0.0f };
//////static GLfloat  translatex[] = { 0.0f, 0.0f, 0.0f, 0.0f };
//////static GLint i;
//////GLfloat W, H;
//////int X, Y;
//////void shape1() {
//////	GLfloat x, y, z, angle; // Storeage for coordinates and angles
//////
//////	glBegin(GL_POINTS);
//////	
//////	//if (translate[0] == 1)
//////	{
//////
//////		//	translate[0] = 0;
//////	}
//////	z = -50.0f;
//////	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f)
//////	{
//////
//////		//C runtime functions sin() and cos() accept angle values measured in radians
//////		x = 50.0f* sin(angle);
//////		y = 50.0f*cos(angle);
//////		if (angle > GL_PI*3.0f)
//////		{
//////			//
//////			glColor3f(1.0f, 0.0f, 0.0f);
//////			glVertex3f(x, y, z);
//////			z += 0.5f;
//////		}
//////		else
//////		{
//////			glColor3f(0.0f, 1.0f, 0.0f);
//////			glVertex3f(x, y, z);
//////			z += 0.5f;
//////		}
//////
//////		// Specify the point and move the Z value up a little
//////
//////	}
//////
//////	// Done drawing points
//////	glEnd();
//////
//////}
//////void shape2() {
//////	GLfloat x, y, z, angle; // Storeage for coordinates and angles
//////
//////	glBegin(GL_LINE_STRIP);   ////// see the second shape 
//////
//////	z = -50.0f;
//////	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f) {
//////		x = 50.0f*sin(angle);
//////		y = 50.0f*cos(angle);
//////		if (angle > GL_PI*3.0f)
//////		{
//////			//
//////			glColor3f(1.0f, 0.0f, 1.0f);
//////			glVertex3f(x, y, z);
//////			z += 0.5f;
//////		}
//////		else
//////		{
//////			glColor3f(0.0f, 1.0f, 0.0f);
//////			glVertex3f(x, y, z);
//////			z += 0.5f;
//////		}
//////	}
//////
//////	// Done drawing points
//////	glEnd();
//////
//////}
//////void shape3() {
//////	GLfloat x, y, z, angle; // Storeage for coordinates and angles
//////
//////	glBegin(GL_POINTS);
//////
//////	z = -50.0f;
//////	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f)
//////	{
//////
//////		//C runtime functions sin() and cos() accept angle values measured in radians
//////		x = 50.0f* sin(angle);
//////		y = 50.0f*cos(angle);
//////		if (angle > GL_PI*3.0f)
//////		{
//////			//
//////			glColor3f(0.0f, 0.0f, 1.0f);
//////			glVertex3f(x, y, z);
//////			z += 0.5f;
//////		}
//////		else
//////		{
//////			glColor3f(0.0f, 1.0f, 0.0f);
//////			glVertex3f(x, y, z);
//////			z += 0.5f;
//////		}
//////
//////		// Specify the point and move the Z value up a little
//////
//////	}
//////
//////	// Done drawing points
//////	glEnd();
//////
//////}
//////void shape4() {
//////	GLfloat x, y, z, angle; // Storeage for coordinates and angles
//////
//////	glBegin(GL_LINE_STRIP);   ////// see the second shape 
//////
//////	z = -50.0f;
//////	for (angle = 0.0f; angle <= (2.0f*GL_PI)*3.0f; angle += 0.1f) {
//////		x = 50.0f*sin(angle);
//////		y = 50.0f*cos(angle);
//////		// Specify the point and 
//////		//move the z value up a little
//////		if (angle > GL_PI*3.0f)
//////		{
//////			//
//////			glColor3f(1.0f, 1.0f, 0.0f);
//////			glVertex3f(x, y, z);
//////			z += 0.5f;
//////		}
//////		else
//////		{
//////			glColor3f(0.0f, 1.0f, 0.0f);
//////			glVertex3f(x, y, z);
//////			z += 0.5f;
//////		}
//////	}
//////
//////	// Done drawing points
//////	glEnd();
//////
//////}
//////// Called to draw scene
//////void RenderScene(void) {
//////	GLfloat x, y, z, angle; // Storeage for coordinates and angles
//////
//////							// Clear the window with current clearing color
//////	glClear(GL_COLOR_BUFFER_BIT);
//////
//////	// Save matrix state and do the rotation
//////
//////	/////shape 1
//////
//////	glPushMatrix();
//////	glTranslatef(translatex[0], translatey[0], 0.0f);
//////	glRotatef(xRot[0], 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[0], 0.0f, 1.0f, 0.0f);
//////	glViewport(0, 0, W, H);
//////	shape1();
//////	glPopMatrix();
//////
//////	glPushMatrix();
//////	glTranslatef(translatex[0], translatey[0], 0.0f);
//////	glRotatef(xRot[0] + 45, 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[0] + 45, 0.0f, 1.0f, 0.0f);
//////	glViewport(W + W, 0, W, H);
//////	shape1();
//////	glPopMatrix();
//////
//////	glPushMatrix();
//////	glTranslatef(translatex[0], translatey[0], 0.0f);
//////	glRotatef(xRot[0] + 90, 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[0] + 90, 0.0f, 1.0f, 0.0f);
//////	glViewport(0, H + H, W, H);
//////	shape1();
//////	glPopMatrix();
//////
//////	glPushMatrix();
//////	glTranslatef(translatex[0], translatey[0], 0.0f);
//////	glRotatef(xRot[0] + 135, 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[0] + 135, 0.0f, 1.0f, 0.0f);
//////	glViewport(W + W, H + H, W, H);
//////	shape1();
//////	glPopMatrix();
//////
//////	/////////shape 2
//////	glPushMatrix();
//////	glTranslatef(translatex[1], translatey[1], 0.0f);
//////	glRotatef(xRot[1], 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[1], 0.0f, 1.0f, 0.0f);
//////	glViewport(W, 0, W, H);
//////	shape2();
//////	glPopMatrix();
//////
//////	glPushMatrix();
//////	glTranslatef(translatex[1], translatey[1], 0.0f);
//////	glRotatef(xRot[1] + 45, 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[1] + 45, 0.0f, 1.0f, 0.0f);
//////	glViewport(3 * W, 0, W, H);
//////	shape2();
//////	glPopMatrix();
//////
//////	glPushMatrix();
//////	glTranslatef(translatex[1], translatey[1], 0.0f);
//////	glRotatef(xRot[1] + 90, 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[1] + 90, 0.0f, 1.0f, 0.0f);
//////	glViewport(W, 2 * H, W, H);
//////	shape2();
//////	glPopMatrix();
//////
//////	glPushMatrix();
//////	glTranslatef(translatex[1], translatey[1], 0.0f);
//////	glRotatef(xRot[1] + 135, 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[1] + 135, 0.0f, 1.0f, 0.0f);
//////	glViewport(3 * W, 2 * H, W, H);
//////	shape2();
//////	glPopMatrix();
//////
//////	//////////shape3
//////
//////	glPushMatrix();
//////	glTranslatef(translatex[2], translatey[2], 0.0f);
//////	glRotatef(xRot[2], 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[2], 0.0f, 1.0f, 0.0f);
//////	glViewport(0, H, W, H);
//////	shape3();
//////	glPopMatrix();
//////
//////	glPushMatrix();
//////	glTranslatef(translatex[2], translatey[2], 0.0f);
//////	glRotatef(xRot[2] + 45, 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[2] + 45, 0.0f, 1.0f, 0.0f);
//////	glViewport(2 * W, H, W, H);
//////	shape3();
//////	glPopMatrix();
//////
//////	glPushMatrix();
//////	glTranslatef(translatex[2], translatey[2], 0.0f);
//////	glRotatef(xRot[2] + 90, 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[2] + 90, 0.0f, 1.0f, 0.0f);
//////	glViewport(0, 3 * H, W, H);
//////	shape3();
//////	glPopMatrix();
//////
//////	glPushMatrix();
//////	glTranslatef(translatex[2], translatey[2], 0.0f);
//////	glRotatef(xRot[2] + 135, 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[2] + 135, 0.0f, 1.0f, 0.0f);
//////	glViewport(2 * W, 3 * H, W, H);
//////	shape3();
//////	glPopMatrix();
//////
//////	///////shape4
//////
//////	glPushMatrix();
//////	glTranslatef(translatex[3], translatey[3], 0.0f);
//////	glRotatef(xRot[3], 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[3], 0.0f, 1.0f, 0.0f);
//////	glViewport(W, H, W, H);
//////	shape4();
//////	glPopMatrix();
//////
//////	glPushMatrix();
//////	glTranslatef(translatex[3], translatey[3], 0.0f);
//////	glRotatef(xRot[3] + 45, 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[3] + 45, 0.0f, 1.0f, 0.0f);
//////	glViewport(3 * W, H, W, H);
//////	shape4();
//////	glPopMatrix();
//////
//////	glPushMatrix();
//////	glTranslatef(translatex[3], translatey[3], 0.0f);
//////	glRotatef(xRot[3] + 90, 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[3] + 90, 0.0f, 1.0f, 0.0f);
//////	glViewport(W, 3 * H, W, H);
//////	shape4();
//////	glPopMatrix();
//////
//////	glPushMatrix();
//////	glTranslatef(translatex[3], translatey[3], 0.0f);
//////	glRotatef(xRot[3] + 135, 1.0f, 0.0f, 0.0f);
//////	glRotatef(yRot[3] + 135, 0.0f, 1.0f, 0.0f);
//////	glViewport(3 * W, 3 * H, W, H);
//////	shape4();
//////	glPopMatrix();
//////
//////	// Flush drawing commands
//////	glutSwapBuffers();
//////}
//////// This function does any needed initialization on the rendering
//////// context.
//////void SetupRC() {
//////	// Black background
//////	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//////
//////	// Set drawing color to green
//////	glColor3f(0.0f, 1.0f, 0.0f);
//////}
//////void keyboard(unsigned char key, int x, int y) {
//////	
//////	switch (key) {
//////	case 'w':case 'W':
//////		
//////		translatey[i] += 10;
//////
//////		break;
//////	case 'S':case 's':
//////		
//////		translatey[i] -= 10;
//////
//////		break;
//////	case 'A':case 'a':
//////		
//////		translatex[i] -= 10;
//////
//////		break;
//////	case 'D':case 'd':
//////		
//////		translatex[i] += 10;
//////
//////		break;
//////	}
//////	glutPostRedisplay();
//////}
//////void SpecialKeys(int key, int x, int y) {
//////
//////
//////	if (key == GLUT_KEY_UP) xRot[i] -= 5.0f;
//////	if (key == GLUT_KEY_DOWN)  xRot[i] += 5.0f;
//////	if (key == GLUT_KEY_LEFT) yRot[i] -= 5.0f;
//////	if (key == GLUT_KEY_RIGHT) yRot[i] += 5.0f;
//////
//////	if (xRot[i] > 356.0f) xRot[i] = 0.0f;
//////	if (xRot[i] < -1.0f) xRot[i] = 355.0f;
//////	if (yRot[i] > 356.0f) yRot[i] = 0.0f;
//////	if (yRot[i] < -1.0f) yRot[i] = 355.0f;
//////
//////
//////
//////	// Refresh the Window
//////	glutPostRedisplay();
//////}
//////void ChangeSize(int w, int h) {
//////	W = w / 4; H = h / 4;
//////	// Prevent a divide by zero
//////	if (h == 0)	h = 1;
//////	// Reset projection matrix stack
//////	glMatrixMode(GL_PROJECTION);
//////	glLoadIdentity();
//////
//////	// Establish clipping volume (left, right, bottom, top, near, far)
//////	if (w <= h)
//////		glOrtho(-100, 100, -100 * h / w, 100 * h / w, -100, 100);
//////	else
//////		glOrtho(-100 * w / h, 100 * w / h, -100, 100, -100, 100);
//////
//////	// Reset Model view matrix stack
//////	glMatrixMode(GL_MODELVIEW);
//////	glLoadIdentity();
//////}
//////
//////void ProcessMenu(int value) {
//////
//////	i = value;
//////	glutPostRedisplay();
//////}
//////
//////
//////
//////int main(int argc, char* argv[])
//////{
//////	glutInit(&argc, argv);
//////	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//////	glutCreateWindow("Points Example");
//////	glutCreateMenu(ProcessMenu);
//////	glutAddMenuEntry("shape 1 ", 0);
//////	glutAddMenuEntry("shape 2", 1);
//////	glutAddMenuEntry("shape 3", 2);
//////	glutAddMenuEntry("shape 4", 3);
//////	glutAttachMenu(GLUT_RIGHT_BUTTON);
//////
//////	glutReshapeFunc(ChangeSize);
//////	glutSpecialFunc(SpecialKeys);
//////	glutKeyboardFunc(keyboard);
//////	glutDisplayFunc(RenderScene);
//////	SetupRC();
//////	glutMainLoop();
//////
//////	return 0;
//////}
