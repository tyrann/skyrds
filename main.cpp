/*
 * main.cpp
 *
 *  Created on: 31 mars 2013
 *      Author: Aech
 */

#include <math.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "function.h"
#include "callbacks.h"

//WINDOW
int g_iWindowWidth = 1024;
int g_iWindowHeight = 768;

int g_hWindowHandle = 0;

//MOVEMENT
bool forward = false;
bool backwards = false;
bool left = false;
bool right = false;
float pos_X = 0.0f;
float pos_Y = -1.4f;
float pos_Z = -6.0f;
float movement_speed = 2;

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

//vertex buffer object
GLuint VBO;

static void initGlut(int argc, char* argv[]);

static void InitializeGlutCallbacks() {

	//Register the callback functions
	glutDisplayFunc(DisplayGL);
	glutIdleFunc(IdleGL);
	glutKeyboardUpFunc(KeyboardGLRelease);
	glutKeyboardFunc(KeyboardGL);
	glutMouseFunc(MouseGL);
	glutMotionFunc(MotionGL);
	glutReshapeFunc(ReshapeGL);

}

int main(int argc, char **argv) {
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	g_PreviousTicks = std::clock();
	initGlut(argc, argv);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutMainLoop();
	return 0;
}

static void initGlut(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	int iScreenWidth = glutGet(GLUT_SCREEN_WIDTH);
	int iScreenHeight = glutGet(GLUT_SCREEN_HEIGHT);

	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition((iScreenWidth - g_iWindowWidth) / 2,
			(iScreenHeight - g_iWindowHeight) / 2);
	glutInitWindowSize(g_iWindowWidth, g_iWindowHeight);

	g_hWindowHandle = glutCreateWindow("OpenGL Template");

	InitializeGlutCallbacks();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
}
static void DisplayGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	renderScene4(pos_X,pos_Y,pos_Z);
	glutSwapBuffers();
}

static void IdleGL() {
	g_CurrentTick = std::clock();
	float deltaTicks = (float) (g_CurrentTick - g_PreviousTicks);
	g_PreviousTicks = g_CurrentTick;

	float deltaTtime = deltaTicks / (float) CLOCKS_PER_SEC;
	g_fRotate1 += (g_fRotationRate * deltaTtime);
	g_fRotate1 = fmodf(g_fRotate1, 360.0f);

	glutPostRedisplay();
	if (forward) {
		pos_Z += movement_speed * deltaTtime;
	}
	if (backwards) {
		pos_Z -= movement_speed * deltaTtime;
	}
	if (right) {
		pos_X -= movement_speed * deltaTtime;
	}
	if (left) {
		pos_X += movement_speed * deltaTtime;
	}
}
static void KeyboardGL(unsigned char c, int x, int y) {
	printf("Key pressed is : %d\n ", (int) c);
	switch (c) {
	case 1:
		break;
	case 2:
		break;
	case 97:
		left = true;
		break;
	case 100:
		right = true;
		break;
	case 115:
		backwards = true;
		break;
	case 119:
		forward = true;
		break;
	case 27:
		break;
	}

}

static void KeyboardGLRelease(unsigned char c, int x, int y) {
	printf("Key pressed is : %d\n ", (int) c);
	switch (c) {
	case 1:
		break;
	case 2:
		break;
	case 97:
		left = false;
		break;
	case 100:
		right = false;
		break;
	case 115:
		backwards = false;
		break;
	case 119:
		forward = false;
		break;
	case 27:
		glutLeaveMainLoop();
		break;
	}

}

static void MouseGL(int button, int state, int x, int y) {

}

static void MotionGL(int x, int y) {

}

static void ReshapeGL(int w, int h) {

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

