#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <glut.h>

//#define max(x, y) ((x)<(y)?(y):(x))
//#define min(x, y) ((x)>(y)?(y):(x))

#define GL_PI 3.1415f

// they're variables, in which I recieve the two shapes that will be rotatating, where the 'moon' variable holds index of shape 
// that will rotate around shape whose index is stored in 'planet' variable
int planet, moon;

// array for storing shapes as a graph represented as an adjacency matrix
// initially, every shape rotates around itself
bool graph[][4] = { { 1,0,0,0 },
					{ 0,1,0,0 },
					{ 0,0,1,0 },
					{ 0,0,0,1 } };

// array for marking nodes(shapes) as visited, re-filled every render -included for applying graph algorithm-
bool vis[4] = { 0,0,0,0 };

/* void drawobject1(); */
/* void drawobject2(); */
void drawobject(bool s, int i);
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
float Scene[4][4] = { { 0,0,1,0 },
					{ 90,0,1,0 },
					{ 180,0,1,0 },
					{ 90,1,0,0 } };

// shapes' translations
float xTrans[4] = { 50 + width / 40,-50 - width / 40,-50 - width / 40,50 + width / 40 };
float yTrans[4] = { 50 + height / 40,50 + height / 40 + height / 40,-50 - height / 400,-50 - height / 40 };
float zTrans[4] = { 0,0,0,0 };

void screen() {

	float clr[3] = { 0.4, 0.4, 0.4 };

	// draw a frame around every camera
	float scr[][2] = {
		// top edge of frame
		{ width / 8, height / 8, },
		{ -width / 8, height / 8, },
		{ -width / 8, height / 8 - 5 },
		{ width / 8, height / 8 - 5 },

		// right edge of frame
		{ width / 8, height / 8 },
		{ width / 8, -height / 8 },
		{ width - 5, height / 8 },
		{ width - 5, -height / 8 },

		// bottom edge of frame
		{ width / 8, -height / 8 },
		{ -width / 8, -height / 8 },
		{ -width / 8, -height / 8 + 5 },
		{ width / 8, -height / 8 + 5 },

		// left edge of frame
		{ -width / 8, -height / 8 },
		{ -width / 8, height / 8 },
		{ -width - 5, -height / 8 + 5 },
		{ -width - 5, height / 8 },
	};

	for (int i = 0; i < 4; ++i) {
		glColor3f(1.0, 1.0, 1.0);
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

bool checkCyclicity(int n) {

	vis[n] = 1;

	for (int i = 0;i < 4;++i)
		if (i != n && graph[n][i])
			if (vis[i]) return true;
			else checkCyclicity(i);

			return false;
}

void rotate(int idxr) {
	
	// swap the loop and the 3-lines for rotation to get inversed effect .. that's how recursion really works


	if (idxr == 0)
		glTranslatef(-xTrans[idxr], -yTrans[idxr], zTrans[idxr]);
	else if (idxr == 1)
		glTranslatef(-xTrans[idxr], -yTrans[idxr], zTrans[idxr]);
	else if (idxr == 2)
		glTranslatef(-xTrans[idxr], -yTrans[idxr], zTrans[idxr]);
	else
		glTranslatef(-xTrans[idxr], -yTrans[idxr], zTrans[idxr]);

	for (int i = 0;i < 4;++i)
		if (i!=idxr && graph[idxr][i])
			rotate(i);

	if (idxr == 0)
		glTranslatef(xTrans[idxr], yTrans[idxr], zTrans[idxr]);
	else if (idxr == 1)
		glTranslatef(xTrans[idxr], yTrans[idxr], zTrans[idxr]);
	else if (idxr == 2)
		glTranslatef(xTrans[idxr], yTrans[idxr], zTrans[idxr]);
	else
		glTranslatef(xTrans[idxr], yTrans[idxr], zTrans[idxr]);

	glRotatef(xRot[idxr], 1.0f, 0.0f, 0.0f);
	glRotatef(yRot[idxr], 0.0f, 1.0f, 0.0f);
	glRotatef(zRot[idxr], 0.0f, 0.0f, 1.0f);

}

void RenderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	// an attempt to make a border around each camera, as a frame
	//screen();
	//  the following block is to create a separator in the middle of the screen
	{
		glViewport(0, 0, width, height);
		glColor3fv(new float[3]{ 135 / 256.0, 206 / 256.0, 250 / 256.0 });
		glBegin(GL_LINES);
		glVertex2d(-width, 0);
		glVertex2d(width, 0);
		glEnd();
		glBegin(GL_LINES);
		glVertex2d(0, -height);
		glVertex2d(0, height * 2);
		glEnd();
	}

	// initially, mark nodes as not visited .. then nodes are marked in the order they're visited
	for (int i = 0;i < 4;++i) vis[i] = 0;

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
			//if (j == 0) glTranslatef(xTra	ns[j] , yTrans[j] , zTrans[j]);
			//else if (j == 1) glTranslatef(xTrans[j] , yTrans[j] , zTrans[j]);
			//else if (j == 2) glTranslatef(xTrans[j] , yTrans[j] , zTrans[j]);
			//else glTranslatef(xTrans[j] , yTrans[j] , zTrans[j]);
			
			// here where the magic happens

			if (j == 0)
				glTranslatef(xTrans[j], yTrans[j], zTrans[j]);
			else if (j == 1)
				glTranslatef(xTrans[j], yTrans[j], zTrans[j]);
			else if (j == 2)
				glTranslatef(xTrans[j], yTrans[j], zTrans[j]);
			else
				glTranslatef(xTrans[j], yTrans[j], zTrans[j]);

			rotate(j);			

			//int iidxr, idxr = j;
			//do {

			//	glRotatef(xRot[idxr], 1.0f, 0.0f, 0.0f);
			//	glRotatef(yRot[idxr], 0.0f, 1.0f, 0.0f);
			//	glRotatef(zRot[idxr], 0.0f, 0.0f, 1.0f);

			//	if (idxr == 0)
			//		glTranslatef(xTrans[idxr] + width / 40, yTrans[idxr] + height / 40, zTrans[idxr]);
			//	else if (idxr == 1)
			//		glTranslatef(xTrans[idxr] - width / 40, yTrans[idxr] + height / 40, zTrans[idxr]);
			//	else if (idxr == 2)
			//		glTranslatef(xTrans[idxr] - width / 40, yTrans[idxr] - height / 40, zTrans[idxr]);
			//	else
			//		glTranslatef(xTrans[idxr] + width / 40, yTrans[idxr] - height / 40, zTrans[idxr]);

			//	for (iidxr = 0;iidxr < 4;++iidxr)
			//		if (iidxr != idxr && graph[idxr][iidxr]) {
			//			idxr = iidxr;
			//			break;
			//		}
			//	if (iidxr != 4) continue;
			//	if (idxr == 0)
			//		glTranslatef(-(xTrans[idxr] + width / 40), -(yTrans[idxr] + height / 40), -(zTrans[idxr]));
			//	else if (idxr == 1)
			//		glTranslatef(-(xTrans[idxr] - width / 40), -(yTrans[idxr] + height / 40), -(zTrans[idxr]));
			//	else if (idxr == 2)
			//		glTranslatef(-(xTrans[idxr] - width / 40), -(yTrans[idxr] - height / 40), -(zTrans[idxr]));
			//	else 
			//		glTranslatef(-(xTrans[idxr] + width / 40), -(yTrans[idxr] - height / 40), -(zTrans[idxr]));

			//} while (iidxr!=4);
			// ends here
			glScalef(.40, .40, .40);
			drawobject((j == selection), j);
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
			}
			else {
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

void read_input() {

	printf("Enter two indices, one of a shape and another for the shape "
		"around which the first will rotate\n\"x y ; means x around y\"\n");
	scanf("%d %d", &moon, &planet);

	if (moon < 1 || planet < 1 || moon>4 || planet>4) {
		printf("false input; x and y should be from 1 to 4\n");
		return;
	}
	moon--;
	planet--;

	int old = 0;
	for (int i = 0;i < 4;++i)
		if (graph[moon][i]) {
			old = i;
			graph[moon][i] = 0;
			break;
		}

	graph[moon][planet] = 1;

	for (int i = 0;i < 4;++i) {
		// remark vis[] array with 0 to check every node in its path, there might be conflicted paths ..
		// even though that might not happen because of the small number of nodes(shapes)
		for (int idxr = 0;idxr < 4;++idxr) vis[idxr] = 0;
		if (checkCyclicity(i)) {
			graph[moon][planet] = 0;
			graph[moon][old] = 1;
			printf("false input; it causes a cycle i.e., x is rotating around y which is either rotating around x \n"
				"\t\t\t\t\tor rotating around some other shape rotating around x");
			return;
		}
	}
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
	case 'r': 	case 'R':
		read_input();
	}

	animation = Oanimation;
	Zaxis = OZaxis;
}

void ChangeSize(int w, int h) {

	width = w;
	height = h;

	GLfloat nRange = 100.0f;

	if (h == 0) h = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	xPos = new float[4]{ width / 2, 0, 0, width / 2 };
	yPos = new float[4]{ height / 2, height / 2, 0, 0 };

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

void drawobject(bool s, int i) {

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