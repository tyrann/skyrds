/*
 * callbacks.h
 *
 *  Created on: 5 avr. 2013
 *      Author: Aech
 */
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

static void DisplayGL();
static void IdleGL();
static void KeyboardGL(unsigned char c, int x, int y);
static void KeyboardGLRelease(unsigned char c, int x, int y);
static void MouseGL(int button, int state, int x, int y);
static void MotionGL(int x, int y);
static void ReshapeGL(int w, int h);
