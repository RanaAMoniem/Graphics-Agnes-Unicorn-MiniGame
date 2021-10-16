#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glut.h>
#include <time.h>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

//screen
double windowSizeX = 1000;
double windowSizeY = 800;

//gameover checker
bool gameover = false;

//camera
double eye_x = 0;
double eye_y = 7;
double eye_z = 25;
//front view pos
double front_x = 0.0;
double front_y = 8.0;
double front_z = 35;
//top view pos
double top_x = 0.0;
double top_y = 50.0;
double top_z = 0.1;
//side view pos
double side_x = 35;
double side_y = 15.0;
double side_z = 0;

//player movements
double speX = 0;
double speZ = 0;

//goal initial random position
double goalX;
double goalZ;
double goalY;
double unicornXright;
double unicornXleft;
double unicornZback;
double unicornZfront;

//player initial/current position
double agnesX = 0;
double agnesZ = 9;

//animations controls
//grass: grows -> the y value increases
bool grassOn = false;
bool grassBack = false;
double yGrassAnim = 0;
//fence
double red = 1;
double green = 1;
double blue = 1;
bool fenceOn = false;
bool fenceOnBack = false;
double xFenceAnim = 0;
//swing
bool swingOn = false;
double swingRotAngle = 0;
bool swingright = false;
//trees
bool treesOn = false;
double treeRotAngle = 0;
bool treesRight = false;
double depthHeight = 6;
double yLeafFall = 0;
//pergola
bool pergolaOn = false;
bool pergolaBack = false;
double pergolaRotAngle;
//swimming pool wave
bool waveOn = false;
bool waveBack = false;
double zWave = 0;



double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}



void collisionChecker() {
	if (agnesX >= unicornXleft && agnesX <= unicornXright && agnesZ >= unicornZback && agnesZ <= unicornZfront) {
		gameover = true;
		PlaySound(TEXT("unicorn_life.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	if (agnesX >= 9.5 + xFenceAnim) {
		speX -= 1;
		agnesX -= 1;
		PlaySound(TEXT("Agnes_scream.wav"), NULL, SND_ASYNC | SND_FILENAME);
		
	}
	if (agnesX <= -9.5 + xFenceAnim) {
		speX += 1;
		agnesX += 1;
		PlaySound(TEXT("Agnes_scream.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	if (agnesZ >= 9.5 + xFenceAnim) {
		speZ -= 1;
		agnesZ -= 1;
		PlaySound(TEXT("Agnes_scream.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	if (agnesZ <= -9.5 + xFenceAnim) {
		speZ += 1;
		agnesZ += 1;
		PlaySound(TEXT("Agnes_scream.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
}
void spe(int k, int x, int y)
{
	if (k == GLUT_KEY_RIGHT) {
		speX += 1;
		agnesX += 1;
	}
	if (k == GLUT_KEY_LEFT) {
		speX -= 1;
		agnesX -= 1;
	}
	if (k == GLUT_KEY_UP) {
		speZ -= 1;
		agnesZ -= 1;
	}
	if (k == GLUT_KEY_DOWN) {
		speZ += 1;
		agnesZ += 1;
	}
	collisionChecker();
	glutPostRedisplay();
}



void key(unsigned char k, int x, int y) {
	// camera movements
	if (k == 'q')
		eye_x += 1;
	if (k == 'w')
		eye_x -= 1;
	if (k == 'a')
		eye_y += 1;
	if (k == 's')
		eye_y -= 1;
	if (k == 'z')
		eye_z += 1;
	if (k == 'x')
		eye_z -= 1;
	if (k == 'e') {
		eye_x = front_x;
		eye_y = front_y;
		eye_z = front_z;
	}
	if (k == 'd') {
		eye_x = top_x;
		eye_y = top_y;
		eye_z = top_z;
	}
	if (k == 'c') {
		eye_x = side_x;
		eye_y = side_y;
		eye_z = side_z;
	}

	//grass animation keys
	if (k == 'r') {
		PlaySound(TEXT("Animation.wav"), NULL, SND_ASYNC | SND_FILENAME);
		grassOn = true;
	}
	if (k == 't')
		grassOn = false;
	if (k == 'y')
		grassBack = true;

	//fence animation keys
	if (k == 'f'){
		fenceOn = true;
	}
	if (k == 'g')
		fenceOn = false;
	if (k == 'h')
		fenceOnBack = true;

	//swing animation keys
	if (k == 'v') {
		swingOn = true;
		swingright = true;
		PlaySound(TEXT("Animation.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	if (k == 'b')
		swingOn = false;
	if (k == 'n')
		swingRotAngle = 0;

	//trees animation keys
	if (k == 'u') {
		PlaySound(TEXT("Animation.wav"), NULL, SND_ASYNC | SND_FILENAME);
		treesOn = true;
		treesRight = true;
	}
	if (k == 'i')
		treesOn = false;
	if (k == 'o') {
		treeRotAngle = 0;
		yLeafFall = 0;
	}

	//pergola
	if (k == 'j') {
		PlaySound(TEXT("Animation.wav"), NULL, SND_ASYNC | SND_FILENAME);
		pergolaOn = true;
	}
	if (k == 'k')
		pergolaOn = false;
	if (k == 'l')
		pergolaBack = true;

	//wave controls
	if (k == 'm') {
		waveOn = true;
		PlaySound(TEXT("Animation.wav"), NULL, SND_ASYNC | SND_FILENAME);
	}
	if (k == 'p')
		waveOn = false;

	glutPostRedisplay();
}



void createGrassGroup(double xin, double yin, double zin) {
	double y = yin;
	double z = zin;
	double x = xin;
	glColor3f(0.5, 0.5, 0);

	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x + 0.05, y, z);
	glVertex3f(x + 0.05, y + 0.6 + yGrassAnim, z);
	glVertex3f(x + 0.025, y + 0.8 + yGrassAnim, z);
	glVertex3f(x, y + 0.6 + yGrassAnim, z);
	glEnd();

	x += 0.09;

	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x + 0.05, y, z);
	glVertex3f(x + 0.05, y + 0.6 + yGrassAnim, z);
	glVertex3f(x, y + 0.6 + yGrassAnim, z);
	glEnd();

	z += 0.1;
	x -= 0.09;

	glBegin(GL_POLYGON);
	glVertex3f(x, y, z);
	glVertex3f(x + 0.05, y, z);
	glVertex3f(x + 0.05, y + 0.6 + yGrassAnim, z);
	glVertex3f(x, y + 0.6 + yGrassAnim, z);
	glEnd();

	x += 0.09;

	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x + 0.05, y, z);
	glVertex3f(x + 0.05, y + 0.6 + yGrassAnim, z);
	glVertex3f(x + 0.025, y + 0.8 + yGrassAnim, z);
	glVertex3f(x, y + 0.6 + yGrassAnim, z);
	glEnd();

	z -= 0.1;
}
void createGrass(double xin, double yin, double zin) {
	for (double z = -zin; z <= zin; z += 0.05) {
		for (double x = -xin; x <= xin; x += 0.15) {
			createGrassGroup(x, yin, z);
			x += 0.09;
		}
	}
}



void createFencePiece(double x, double y, double z) {
	//left fence
	glColor3f(red, green, blue);
	glPushMatrix();
	glTranslated(-x + xFenceAnim, y, z);
	glScaled(0.1, 2, 0.5);
	glutSolidCube(1);
	glPopMatrix();
	glColor3f(red, green, blue);
	glPushMatrix();
	glTranslated(-x - 0.05 + xFenceAnim, y, z - 0.75);
	glScaled(0.1, 0.5, 1);
	glutSolidCube(1);
	glPopMatrix();

	//right fence
	glColor3f(red, green, blue);
	glPushMatrix();
	glTranslated(x + xFenceAnim, y, z);
	glScaled(0.1, 2, 0.5);
	glutSolidCube(1);
	glPopMatrix();
	glColor3f(red, green, blue);
	glPushMatrix();
	glTranslated(x + 0.05 + xFenceAnim, y, z - 0.75);
	glScaled(0.1, 0.5, 1);
	glutSolidCube(1);
	glPopMatrix();

	//back fence
	glColor3f(red, green, blue);
	glPushMatrix();
	glTranslated(z + xFenceAnim, y, -x);
	glScaled(0.5, 2, 0.1);
	glutSolidCube(1);
	glPopMatrix();
	glColor3f(red, green, blue);
	glPushMatrix();
	glTranslated(z - 0.75 + xFenceAnim, y, -x - 0.05);
	glScaled(1, 0.5, 0.1);
	glutSolidCube(1);
	glPopMatrix();

}
void createFence(double x, double y) {
	double z = x - 0.25;
	double zStop = -1 * z;
	for (int p = 1; p < 14; p++) {
		if (z >= zStop) {
			createFencePiece(x, y, z);
			z -= 1.5;
		}
	}
	glColor3f(red, green, blue);
	glPushMatrix();
	glTranslated(-x + xFenceAnim, y, zStop);
	glScaled(0.1, 2, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(x + xFenceAnim, y, zStop);
	glScaled(0.1, 2, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(zStop + xFenceAnim, 1, -x);
	glScaled(0.5, 2, 0.1);
	glutSolidCube(1);
	glPopMatrix();

}



void createLeaves(double x, double y) {
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(x + 0.0, y + 0.0, 0.0);
	glVertex3f(x + 0.2, y + 0.1, 0.0);
	glVertex3f(x + 0.1, y + 0.2, 0.0);
	glVertex3f(x + 0.4, y + 0.3, 0.0);
	glVertex3f(x + 0.1, y + 0.4, 0.0);
	glVertex3f(x + 0.3, y + 0.5, 0.0);
	glVertex3f(x + 0.0, y + 0.4, 0.0);
	glVertex3f(x - 0.3, y + 0.5, 0.0);
	glVertex3f(x - 0.1, y + 0.4, 0.0);
	glVertex3f(x - 0.4, y + 0.3, 0.0);
	glVertex3f(x - 0.1, y + 0.2, 0.0);
	glVertex3f(x - 0.2, y + 0.1, 0.0);
	glEnd();
	glPopMatrix();
}
void treeCylinder(double height, double r) {
	glPushMatrix();
	glTranslated(0, height, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* q;
	q = gluNewQuadric();
	gluQuadricNormals(q, GLU_SMOOTH);
	gluCylinder(q, r - 0.1, r - 0.2, height, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qbase;
	qbase = gluNewQuadric();
	gluQuadricNormals(qbase, GLU_SMOOTH);
	gluCylinder(qbase, r, r - 0.1, height, 16, 4);
	glPopMatrix();
}
void treeBranch(int depth, double height, double r) {
	height *= 0.8;
	double angle = 30;
	r *= 0.6;
	//stem:
	glColor3f(0.518, 0.23, 0.0);
	treeCylinder(height, r);

	//leaves:
	if (depth == 0) {
		double angle = 60;
		glPushMatrix();
		glTranslatef(0.0, height, 0.0);
		glRotatef(30, 0.0, 1.0, 0.0);

		glColor3f(0.1, 0.6, 0.1);
		for (int i = 0; i < 10; i++) {
			createLeaves(0.5, 0.5);
			glRotatef(angle, 1.0, 0.0, 0.0);
			glRotatef(-angle, 1.0, 0.0, 0.0);
			glRotatef(60, 0.0, 1.0, 0.0);
		}
		glPopMatrix();
	}
	else {
		glColor3f(0.518, 0.23, 0.0);
		glPushMatrix();
		glTranslatef(0.0, height * 0.95, 0.0);
		//left branch
		glRotatef(30, 0.0, 1.0, 0.0);
		glRotatef(angle, 0.0, 0.0, 1.0);
		treeBranch(depth - 1, height, r);
		// back branch
		glRotatef(-angle, 0.0, 0.0, 1.0);
		glRotatef(120, 0.0, 1.0, 0.0);
		glRotatef(angle, 0.0, 0.0, 1.0);
		treeBranch(depth - 1, height, r);
		//right branch
		glRotatef(-angle, 0.0, 0.0, 1.0);
		glRotatef(120, 0.0, 1.0, 0.0);
		glRotatef(angle, 0.0, 0.0, 1.0);
		treeBranch(depth - 1, height, r);
		glPopMatrix();
		if (depth == 1) {
			double angle = 60;
			glPushMatrix();
			glTranslatef(0.0, height, 0.0);
			glRotatef(30, 0.0, 1.0, 0.0);

			glColor3f(0.1, 0.6, 0.1);
			for (int i = 0; i < 50; i++) {
				createLeaves(0.5, 0);
				glRotatef(angle, 1.0, 0.0, 0.0);
				glRotatef(-angle, 1.0, 0.0, 0.0);
				glRotatef(60, 0.0, 1.0, 0.0);
			}
			glPopMatrix();
		}
	}
}



void createPergola(double x, double y, double z) {

	//    glColor3f(0.6, 0.3, 0.1);
	glColor3f(0.79, 0.64, 0.44);
	// legs
	glPushMatrix();
	glTranslated(-x + 6, y / 2, z);
	glScaled(0.5, 7, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x + 6, y / 2, -z);
	glScaled(0.5, 7, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x, y / 2, -z);
	glScaled(0.5, 7, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x, y / 2, z);
	glScaled(0.5, 7, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	//    glColor3f(0.6, 0.2, 0.2);
	glColor3f(0.6, 0.3, 0.1);
	glPushMatrix();
	glTranslated(-x + 6, 1, z);
	glScaled(0.7, 2, 0.7);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x + 6, 1, -z);
	glScaled(0.7, 2, 0.7);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x, 1, -z);
	glScaled(0.7, 2, 0.7);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x, 1, z);
	glScaled(0.7, 2, 0.7);
	glutSolidCube(1);
	glPopMatrix();

	//roof base:
	glPushMatrix();
	glTranslated(-x + 6, 7, 0);
	glScaled(0.5, 0.5, 9.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x, 7, 0);
	glScaled(0.5, 0.5, 9.5);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.79, 0.64, 0.44);
	// roof logs:
	glPushMatrix();
	glTranslated(-x + 3, 7, 0);
	glScaled(7, 0.5, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x + 3, 7, 1.5);
	glScaled(7, 0.5, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x + 3, 7, -1.5);
	glScaled(7, 0.5, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x + 3, 7, 3);
	glScaled(7, 0.5, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x + 3, 7, -3);
	glScaled(7, 0.5, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x + 3, 7, 4.5);
	glScaled(7, 0.5, 0.5);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x + 3, 7, -4.5);
	glScaled(7, 0.5, 0.5);
	glutSolidCube(1);
	glPopMatrix();
}



void createSwing() {
	glPushMatrix();
	glTranslated(-5.5, (4.1 + 2.6), 0);
	glRotated(swingRotAngle, 0, 0, 1);
	glTranslated(5.5, -1 * (4.1 + 2.6), 0);

	glColor3f(0.6, 0.7, 0.6);
	//bars:
	glPushMatrix();
	glTranslated(-5.5, 2.6 + 1.5, -1.5);
	glRotated(30, 1, 0, 0);
	glTranslated(0, -3, 0);
	glRotated(-90, 1, 0, 0);
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	gluCylinder(qobj, 0.1, 0.1, 6, 16, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-5.5, 2.6 + 1.5, 1.5);
	glRotated(-30, 1, 0, 0);
	glTranslated(0, -3, 0);
	glRotated(-90, 1, 0, 0);
	GLUquadricObj* q1;
	q1 = gluNewQuadric();
	gluQuadricDrawStyle(q1, GLU_LINE);
	gluCylinder(q1, 0.1, 0.1, 6, 16, 100);
	glPopMatrix();

	//seat:
	glColor3f(0.79, 0.64, 0.44);
	glPushMatrix();
	glTranslated(-5.5, 1.5, 0);
	glScaled(2, 0.15, 6);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-7, 1.5 + 0.76, 0);
	glRotated(-50, 0, 0, 1);
	glScaled(2, 0.15, 6);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.6, 0.3, 0.1);
	glPushMatrix();
	glTranslated(-5.5, 1.5, 0);
	glScaled(1, 0.17, 6);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-7, 1.5 + 0.76, 0);
	glRotated(-50, 0, 0, 1);
	glScaled(1, 0.17, 6);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}



void createUnicorn() {
	//pink legs
	glColor3f(1, 0.49, 0.87);
	glPushMatrix();
	glTranslated(1, 0, 2);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qlegdr;
	qlegdr = gluNewQuadric();
	gluQuadricNormals(qlegdr, GLU_SMOOTH);
	gluCylinder(qlegdr, 0.5, 0.5, 1, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1, 0, 2);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qlegdl;
	qlegdl = gluNewQuadric();
	gluQuadricNormals(qlegdl, GLU_SMOOTH);
	gluCylinder(qlegdl, 0.5, 0.5, 1, 16, 4);
	glPopMatrix();

	glColor3f(1, 0.49, 0.87);
	glPushMatrix();
	glTranslated(1, 0, -2);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qlegur;
	qlegur = gluNewQuadric();
	gluQuadricNormals(qlegur, GLU_SMOOTH);
	gluCylinder(qlegur, 0.5, 0.5, 1, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1, 0, -2);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qlegul;
	qlegul = gluNewQuadric();
	gluQuadricNormals(qlegul, GLU_SMOOTH);
	gluCylinder(qlegul, 0.5, 0.5, 1, 16, 4);
	glPopMatrix();
	//white legs
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslated(1, 1, 2);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qlegdr2;
	qlegdr2 = gluNewQuadric();
	gluQuadricNormals(qlegdr2, GLU_SMOOTH);
	gluCylinder(qlegdr2, 0.5, 0.5, 1, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1, 1, 2);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qlegdl2;
	qlegdl2 = gluNewQuadric();
	gluQuadricNormals(qlegdl2, GLU_SMOOTH);
	gluCylinder(qlegdl2, 0.5, 0.5, 1, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1, 1, -2);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qlegur2;
	qlegur2 = gluNewQuadric();
	gluQuadricNormals(qlegur2, GLU_SMOOTH);
	gluCylinder(qlegur2, 0.5, 0.5, 1, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1, 1, -2);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qlegul2;
	qlegul2 = gluNewQuadric();
	gluQuadricNormals(qlegul2, GLU_SMOOTH);
	gluCylinder(qlegul2, 0.5, 0.5, 1, 16, 4);
	glPopMatrix();
	//body
	glPushMatrix();
	glTranslated(0, 2, 0);
	glScaled(2, 2, 3);
	glutSolidSphere(1, 16, 16);
	glPopMatrix();
	//neck
	glPushMatrix();
	glTranslated(0, 1 + 2.7, 2.5);
	glRotated(40, 1, 0, 0);
	glTranslated(0, -1, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qneck2;
	qneck2 = gluNewQuadric();
	gluQuadricNormals(qneck2, GLU_SMOOTH);
	gluCylinder(qneck2, 1, 0.7, 2, 16, 4);
	glPopMatrix();
	//head
	glPushMatrix();
	glTranslated(0, 4, 3.5);
	glRotated(25, 1, 0, 0);
	glScaled(1, 1, 2);
	glutSolidSphere(1, 16, 16);
	glPopMatrix();
	//eyes
	glPushMatrix();
	glTranslated(0.5, 5, 3.9);
	glScaled(1.5, 1.5, 1.75);
	glutSolidSphere(0.1, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.5, 5, 3.9);
	glScaled(1.5, 1.5, 1.75);
	glutSolidSphere(0.1, 15, 15);
	glPopMatrix();

	//horn
	glColor3f(0.8, 0.6, 0.1);
	glPushMatrix();
	glTranslated(0, 4.5, 3.2);
	glScaled(1, 2, 1);
	glRotated(-60, 1, 0, 0);
	glutSolidCone(0.3, 1, 16, 4);
	glPopMatrix();

	//pink tail
	glColor3f(1, 0.49, 0.87);
	glPushMatrix();
	glTranslated(0, 4.5, -3.5);
	glScaled(1, 2, 1);
	glRotated(45, 1, 0, 0);
	glutSolidCone(0.5, 1.5, 16, 4);
	glPopMatrix();
}



void createAgnes() {
	//head : sphere - hair: another sphere gowaha with w bit of it barra lonha eswed - hair elastic: donut - rest of hair : cylinder with diff r
	// hair over elastic
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0, 3, 8.7);
	glRotated(-32, 1, 0, 0);
	glRotated(-90, 1, 0, 0);
	GLUquadricObj* q1;
	q1 = gluNewQuadric();
	gluQuadricNormals(q1, GLU_SMOOTH);
	gluCylinder(q1, 0.07, 0.18, 0.75, 16, 100);
	glPopMatrix();
	//elastic
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0, 3.1, 8.7);
	glRotated(65, 1, 0, 0);
	glutSolidTorus(0.07, 0.17, 15, 15);
	glPopMatrix();
	//hair over head
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0, 2.6, 8.9);
	glutSolidSphere(0.5, 15, 15);
	glPopMatrix();
	//head
	glPushMatrix();
	glColor3f(1.0, 0.87, 0.76);
	glTranslated(0, 2.5, 9);
	glutSolidSphere(0.5, 15, 15);
	glPopMatrix();

	//eyes: lessa
	glColor3f(1.0, 1, 1);

	glPushMatrix();
	glTranslated(0.15, 2.625, 9.40);
	glScaled(1.5, 1.5, 1.75);
	glutSolidSphere(0.07, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.15, 2.625, 9.40);
	glScaled(1.5, 1.5, 1.75);
	glutSolidSphere(0.07, 15, 15);
	glPopMatrix();
	//iris
	glColor3f(0.65, 0.33, 0.0);
	glPushMatrix();
	glTranslated(0.15, 2.625, 9.47);
	glScaled(1, 1, 1);
	glutSolidSphere(0.07, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.15, 2.625, 9.47);
	glScaled(1, 1, 1);
	glutSolidSphere(0.07, 15, 15);
	glPopMatrix();

	//neck: extremely short cylinder
	glPushMatrix();
	glColor3f(1.0, 0.87, 0.76);
	glTranslated(0, 1.95, 9);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qneck;
	qneck = gluNewQuadric();
	gluQuadricNormals(qneck, GLU_SMOOTH);
	gluCylinder(qneck, 0.15, 0.15, 0.1, 16, 4);
	glPopMatrix();

	//arm: 2 cubes(sleeve & arm)- hands: small sphere
	glPushMatrix();
	glColor3f(0.96, 0.87, 0.31);
	glTranslated(0.29, 1.65, 9);
	glTranslated(0, 0.125, 0);
	glRotated(45, 0, 0, 1);
	glTranslated(0, -0.125, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qarmr;
	qarmr = gluNewQuadric();
	gluQuadricNormals(qarmr, GLU_SMOOTH);
	gluCylinder(qarmr, 0.09, 0.1, 0.25, 4, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.96, 0.87, 0.31);
	glTranslated(-0.29, 1.65, 9);
	glTranslated(0, 0.125, 0);
	glRotated(-45, 0, 0, 1);
	glTranslated(0, -0.125, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qarml;
	qarml = gluNewQuadric();
	gluQuadricNormals(qarml, GLU_SMOOTH);
	gluCylinder(qarml, 0.09, 0.1, 0.25, 4, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.87, 0.76);
	glTranslated(0.45, 1.5, 9);
	glTranslated(0, 0.125, 0);
	glRotated(45, 0, 0, 1);
	glTranslated(0, -0.125, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qarmr2;
	qarmr2 = gluNewQuadric();
	gluQuadricNormals(qarmr2, GLU_SMOOTH);
	gluCylinder(qarmr2, 0.09, 0.1, 0.25, 5, 4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.45, 1.50, 9);
	glTranslated(0, 0.125, 0);
	glRotated(-45, 0, 0, 1);
	glTranslated(0, -0.125, 0);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qarml2;
	qarml2 = gluNewQuadric();
	gluQuadricNormals(qarml2, GLU_SMOOTH);
	gluCylinder(qarml2, 0.09, 0.1, 0.25, 5, 4);
	glPopMatrix();

	//torso : yellow cube/cylinder (paint blue jumpsuit over it using 2D polygon) - rest of torso:  cube color blue
	glPushMatrix();
	glColor3f(0.96, 0.87, 0.31);
	glTranslated(0, 1.70, 9);
	glScaled(0.5, 0.5, 0.35);
	glutSolidCube(1);
	glPopMatrix();

	glTranslated(0, 0.25, 0);
	glPushMatrix();
	glColor3f(0.2, 0.6, 0.7);
	glTranslated(0, 1.20, 9);
	glScaled(0.5, 0.5, 0.35);
	glutSolidCube(1);
	glPopMatrix();

	//legs: cylinder(jeans)- cube(jeans folded) - cylinger (yellow socks)
	glPushMatrix();
	glColor3f(0.2, 0.6, 0.7);
	glTranslated(0.15, 0.70, 9);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* quplegr;
	quplegr = gluNewQuadric();
	gluQuadricNormals(quplegr, GLU_SMOOTH);
	gluCylinder(quplegr, 0.09, 0.1, 0.25, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2, 0.6, 0.7);
	glTranslated(-0.15, 0.7, 9);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* quplegl;
	quplegl = gluNewQuadric();
	gluQuadricNormals(quplegl, GLU_SMOOTH);
	gluCylinder(quplegl, 0.09, 0.1, 0.25, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2, 0.6, 0.7);
	glTranslated(0.15, 0.65, 9);
	glScaled(0.2, 0.1, 0.35);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.2, 0.6, 0.7);
	glTranslated(-0.15, 0.65, 9);
	glScaled(0.2, 0.1, 0.35);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.96, 0.87, 0.31);
	glTranslated(0.15, 0.35, 9);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qdownlegr;
	qdownlegr = gluNewQuadric();
	gluQuadricNormals(qdownlegr, GLU_SMOOTH);
	gluCylinder(qdownlegr, 0.09, 0.1, 0.25, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.15, 0.35, 9);
	glRotatef(-90, 1.0, 0.0, 0.0);
	GLUquadricObj* qdownlegl;
	qdownlegl = gluNewQuadric();
	gluQuadricNormals(qdownlegl, GLU_SMOOTH);
	gluCylinder(qdownlegl, 0.09, 0.1, 0.25, 16, 4);
	glPopMatrix();

	//shoes: white cube (base) + white sphere (inside the cube)
	glColor3f(1, 1, 1);

	glPushMatrix();
	glTranslated(-0.15, 0.15, 9);
	glScaled(0.2, 0.2, 0.35);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.15, 0.15, 9);
	glScaled(0.2, 0.2, 0.35);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.15, 0.3, 9);
	glScaled(1, 1.5, 1);
	glutSolidSphere(0.1, 15, 15);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0.15, 0.3, 9);
	glScaled(1, 1, 1);
	glutSolidSphere(0.1, 15, 15);
	glPopMatrix();
}



void randomGoal() {
	goalY = fRand(0, 0);
	goalZ = fRand(-9, 9);
	goalX = fRand(-9, 9);
	unicornXright = goalX + 1;
	unicornXleft = goalX - 1;
	unicornZback = goalZ - 1.5;
	unicornZfront = goalZ + 1.5;
}



void randomFenceColor() {
	goalY = fRand(0, 0);
	red = fRand(0, 1);
	green = fRand(0, 1);
	blue = fRand(0, 1);
}



void fenceColorTimer(int value) {
	randomFenceColor();
	glutTimerFunc(3 * 1000, fenceColorTimer, 0);
}



void Timer(int value) { // game over timer
	gameover = true;
	glutPostRedisplay();
}



void Anim() {

	//grass animation
	if (grassOn)
		yGrassAnim += 0.1;
	if (yGrassAnim <= 0)
		grassBack = false;
	if (grassBack) {
		if (yGrassAnim > 0)
			yGrassAnim -= 0.1;
	}

	//fence animation
	if (fenceOn)
		xFenceAnim += 0.1;
	if (fenceOnBack) {
		if (xFenceAnim > 0)
			xFenceAnim -= 0.1;
	}
	if (xFenceAnim <= 0)
		fenceOnBack = false;

	//swing animation
	if (swingOn) {
		if (swingRotAngle == 45)
			swingright = false;
		if (swingRotAngle == -45)
			swingright = true;
		if (swingright)
			swingRotAngle += 1;
		if (!swingright)
			swingRotAngle -= 1;
	}
	//trees animation
	if (treesOn) {
		if (yLeafFall < depthHeight)
			yLeafFall += 0.1;
		if (treeRotAngle == 10)
			treesRight = false;
		if (treeRotAngle == -10)
			treesRight = true;
		if (treesRight)
			treeRotAngle += 1;
		if (!treesRight)
			treeRotAngle -= 1;
	}

	//pergola
	if (pergolaOn)
		pergolaRotAngle += 1; //lessa -> birds flying high?
	if (pergolaRotAngle == 0)
		pergolaBack = false;
	if (pergolaBack) {
		if (pergolaRotAngle > 0)
			pergolaRotAngle -= 1;
	}

	//wave
	if (waveOn) {
		if (zWave <= -3)
			waveBack = true;
		if (zWave >= 0)
			waveBack = false;
		if (waveBack)
			zWave += 0.1;
		if (!waveBack)
			zWave -= 0.1;
	}

	glutPostRedisplay();
}



void Display() {
	//camera settings:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, windowSizeX / windowSizeY, 0.01f, 100.0f);//FOV - aspect ratio - near - far
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye_x, eye_y, eye_z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // where camera is x-y-z - where i am looking (center x-y-z) - up7aga betetsab as is

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!gameover) {
		glPushMatrix();

		//swimming pool
		glPushMatrix();

		//pool body
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslated(6, 0.5, -1.5);
		glScaled(5, 1, 5);
		glutSolidCube(1);
		glPopMatrix();
		//water
		glPushMatrix();
		glColor3f(0.29, 0.8, 1);
		glTranslated(6, 0.75, -1.5);
		glScaled(4, 1, 4);
		glutSolidCube(1);
		glPopMatrix();
		if (waveOn) {
			//wave
			glPushMatrix();
			glColor3f(0.29, 0.9, 1);
			glTranslated(6, 1.2, zWave);
			glScaled(4, 1, 1.2);
			glutSolidSphere(0.5, 16, 16);
			glPopMatrix();
		}
		//pool stairs bars
		glPushMatrix();
		glColor3f(0.8, 0.8, 0.8);
		glTranslated(6.5, 0.5, -3.75);
		glRotatef(-90, 1.0, 0.0, 0.0);
		GLUquadricObj* qbarr;
		qbarr = gluNewQuadric();
		gluQuadricNormals(qbarr, GLU_SMOOTH);
		gluCylinder(qbarr, 0.1, 0.1, 1.5, 16, 4);
		glPopMatrix();
		glPushMatrix();
		glColor3f(0.8, 0.8, 0.8);
		glTranslated(5.5, 0.5, -3.75);
		glRotatef(-90, 1.0, 0.0, 0.0);
		GLUquadricObj* qbarl;
		qbarl = gluNewQuadric();
		gluQuadricNormals(qbarl, GLU_SMOOTH);
		gluCylinder(qbarl, 0.1, 0.1, 1.5, 16, 4);
		glPopMatrix();

		glPopMatrix();

		//goal: Agnes' unicorn
		glPushMatrix();
		glTranslated(goalX, 0, goalZ);
		glScaled(0.5, 0.5, 0.5);
		createUnicorn();
		glPopMatrix();

		//character: Agnes
		glPushMatrix();
		glTranslated(speX, 0, speZ);
		createAgnes();
		glPopMatrix();

		//Swing:
		createSwing();

		//Pergola:
		glPushMatrix();
		glTranslated(-5.5, 3.5, 0);
		glRotated(pergolaRotAngle, 0, 1, 0);
		glTranslated(5.5, -3.5, 0);
		createPergola(8.5, 7, 4);
		glPopMatrix();

		//trees:
		//left-front tree
		glPushMatrix();
		glTranslated(-8.5, 0, 8.5);
		glRotated(treeRotAngle, 0, 0, 1);
		glTranslated(8.5, 0, -8.5);
		glTranslated(-8.5, 0, 8.5);
		treeBranch(3, 3, 0.7);
		glPopMatrix();
		glPushMatrix();
		glColor3f(1, 0.6, 0.2);
		if (treesOn) {
			for (int i = 0; i < 17; i++) {
				createLeaves(-8.5 + (i + 2), 6 - yLeafFall);
				glRotatef(120, 1.0, 0.0, 0.0);
				glRotatef(-120, 1.0, 0.0, 0.0);
				glRotatef(60, 0.0, 1.0, 0.0);
			}
			glColor3f(0.56, 0.18, 0.25);
			for (int i = 0; i < 13; i++) {
				createLeaves(-8.5 + (i + 3), 5 - yLeafFall);
				glRotatef(130, 1.0, 0.0, 0.0);
				glRotatef(-130, 1.0, 0.0, 0.0);
				glRotatef(50, 0.0, 1.0, 0.0);
			}
		}
		glPopMatrix();
		//right-front tree
		glPushMatrix();
		glTranslated(8.5, 0, 8.5);
		glRotated(treeRotAngle, 0, 0, 1);
		glTranslated(-8.5, 0, -8.5);
		glTranslated(8.5, 0, 8.5);
		treeBranch(3, 3, 0.7);
		glPopMatrix();
		glPushMatrix();
		glColor3f(1, 0.6, 0.2);
		if (treesOn) {
			for (int i = 0; i < 17; i++) {
				createLeaves(-8.5 + (i + 2), 6 - yLeafFall);
				glRotatef(120, 1.0, 0.0, 0.0);
				glRotatef(-120, 1.0, 0.0, 0.0);
				glRotatef(60, 0.0, 1.0, 0.0);
			}
			glColor3f(0.56, 0.18, 0.25);
			for (int i = 0; i < 13; i++) {
				createLeaves(-8.5 + (i + 3), 5 - yLeafFall);
				glRotatef(130, 1.0, 0.0, 0.0);
				glRotatef(-130, 1.0, 0.0, 0.0);
				glRotatef(50, 0.0, 1.0, 0.0);
			}
		}
		glPopMatrix();
		//left-back tree
		glPushMatrix();
		glTranslated(-8.5, 0, -8.5);
		glRotated(treeRotAngle, 0, 0, 1);
		glTranslated(8.5, 0, 8.5);
		glTranslated(-8.5, 0, -8.5);
		treeBranch(3, 3, 0.7);
		glPopMatrix();
		glPushMatrix();
		glColor3f(1, 0.6, 0.2);
		if (treesOn) {
			for (int i = 0; i < 17; i++) {
				createLeaves(8.5 + (i + 2), 6 - yLeafFall);
				glRotatef(120, 1.0, 0.0, 0.0);
				glRotatef(-120, 1.0, 0.0, 0.0);
				glRotatef(60, 0.0, 1.0, 0.0);
			}
			glColor3f(0.56, 0.18, 0.25);
			for (int i = 0; i < 13; i++) {
				createLeaves(-8.5 + (i + 3), 5 - yLeafFall);
				glRotatef(130, 1.0, 0.0, 0.0);
				glRotatef(-130, 1.0, 0.0, 0.0);
				glRotatef(50, 0.0, 1.0, 0.0);
			}
		}
		glPopMatrix();
		//right-back tree
		glPushMatrix();
		glTranslated(8.5, 0, -8.5);
		glRotated(treeRotAngle, 0, 0, 1);
		glTranslated(-8.5, 0, 8.5);
		glTranslated(8.5, 0, -8.5);
		treeBranch(3, 3, 0.7);
		glPopMatrix();
		glPushMatrix();
		glColor3f(1, 0.6, 0.2);
		if (treesOn) {
			for (int i = 0; i < 17; i++) {
				createLeaves(8.5 + (i + 2), 6 - yLeafFall);
				glRotatef(120, 1.0, 0.0, 0.0);
				glRotatef(-120, 1.0, 0.0, 0.0);
				glRotatef(60, 0.0, 1.0, 0.0);
			}
			glColor3f(0.56, 0.18, 0.25);
			for (int i = 0; i < 13; i++) {
				createLeaves(-8.5 + (i + 3), 5 - yLeafFall);
				glRotatef(130, 1.0, 0.0, 0.0);
				glRotatef(-130, 1.0, 0.0, 0.0);
				glRotatef(50, 0.0, 1.0, 0.0);
			}
		}
		glPopMatrix();
		//fence
		createFence(10, 1);

		//grass
		createGrass(9.5, 0, 9.5);

		//ground
		glPushMatrix();
		glColor3f(0.4, 0.3, 0.2);
		glScaled(20, 0.1, 20);
		glutSolidCube(1);
		glPopMatrix();

		glPopMatrix();
	}
	else {
		glPushMatrix();

		glPushMatrix();
		//glTranslated(5, 5, 0);
		glRotated(90, 0, 1, 0);
		createUnicorn();
		glPopMatrix();

		glColor3f(0.5f, 0.8f, 0.9f);
		glBegin(GL_QUADS);
		glVertex3f(0, 0, 0);
		glVertex3f(windowSizeX, 0, 0);
		glVertex3f(windowSizeX, windowSizeY, 0);
		glVertex3f(0, windowSizeY, 0);
		glEnd();

		glPopMatrix();
	}
	glFlush();
}

int main(int argc, char** argr) {
	srand(unsigned(time(0)));
	randomGoal();
	glutInit(&argc, argr);
	glutInitWindowSize(windowSizeX, windowSizeY);
	glutInitWindowPosition(150, 150);
	glutCreateWindow("Garden");

	glutDisplayFunc(Display);
	glutSpecialFunc(spe);
	glutKeyboardFunc(key);
	glutIdleFunc(Anim);
	glutTimerFunc(60 * 1000, Timer, 0);
	glutTimerFunc(3 * 1000, fenceColorTimer, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	PlaySound(TEXT("Happy.wav"), NULL, SND_ASYNC | SND_FILENAME);
	glClearColor(0.5f, 0.8f, 0.9f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();

	return 0;
}
