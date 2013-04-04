/*
 * track1.cpp
 *
 *  Created on: 31 mars 2013
 *      Author: Aech
 */
/*
 * forms.cpp
 *
 *  Created on: 31 mars 2013
 *      Author: Aech
 */
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "function.h"
#include "camera.h"

//WINDOW
int g_iWindowWidth = 800;
int g_iWindowHeight = 600;

int g_hWindowHandle = 0;

//MOVEMENT
float movement_speed = 2;

//CAMERA
Camera* pGameCamera = NULL;

std::clock_t g_PreviousTicks;
std::clock_t g_CurrentTick;

//ROTATION
float g_fRotationRate = 50.0;
float g_fRotate1 = 0.0f;

//GL_LIGHTING
float pos[] = { -2.0, 2.0, -3.0, 1.0 };
float dif[] = { 1.0, 1.0, 1.0, 1.0 };
float amb[] = { 0.2, 0.2, 0.2, 1.0 };

float difamb[] = { 1.0, 0.5, 0.3, 1.0 };

void initGlut(int argc, char* argv[]);

void DisplayGL();
void IdleGL();
void KeyboardGL(unsigned char c, int x, int y);
void KeyboardGLRelease(unsigned char c, int x, int y);
void MouseGL(int button, int state, int x, int y);
void MotionGL(int x, int y);
void ReshapeGL(int w, int h);


int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	g_PreviousTicks = std::clock();
	initGlut(argc, argv);
	glutMainLoop();
	return 0;
}

void initGlut(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	int iScreenWidth = glutGet(GLUT_SCREEN_WIDTH);
	int iScreenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition((iScreenWidth - g_iWindowWidth) / 2,
			(iScreenHeight - g_iWindowHeight) / 2);
	glutInitWindowSize(g_iWindowWidth, g_iWindowHeight);

	g_hWindowHandle = glutCreateWindow("OpenGL Template");

	//Register the callback functions
	glutDisplayFunc(DisplayGL);
	glutIdleFunc(IdleGL);
	glutKeyboardUpFunc(KeyboardGLRelease);
	glutKeyboardFunc(KeyboardGL);
	glutMouseFunc(MouseGL);
	glutMotionFunc(MotionGL);
	glutReshapeFunc(ReshapeGL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
}
void DisplayGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	renderScene4();
	glutSwapBuffers();
}

void IdleGL() {
	g_CurrentTick = std::clock();
	float deltaTicks = (float) (g_CurrentTick - g_PreviousTicks);
	g_PreviousTicks = g_CurrentTick;

	float deltaTtime = deltaTicks / (float) CLOCKS_PER_SEC;
	g_fRotate1 += (g_fRotationRate * deltaTtime);
	g_fRotate1 = fmodf(g_fRotate1, 360.0f);

	glutPostRedisplay();
}
void KeyboardGL(unsigned char c, int x, int y) {

}

void KeyboardGLRelease(unsigned char c, int x, int y) {

}

void MouseGL(int button, int state, int x, int y) {

}

void MotionGL(int x, int y) {

}

void ReshapeGL(int w, int h) {

	if (h == 0) {
		h = 1;
	}
	g_iWindowWidth = w;
	g_iWindowHeight = h;

	glViewport(0, 0, g_iWindowWidth, g_iWindowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, g_iWindowWidth / (GLdouble) g_iWindowHeight, 0.1,
			400.0);
	glutPostRedisplay();

}


