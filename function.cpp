/*
 * function.cpp
 *
 *  Created on: 4 avr. 2013
 *      Author: Aech
 */
#include "function.h"
#ifndef M_PI
#define M_PI=3.1415926535
#endif

void DrawTriangle(Vectorf2 p1, Vectorf2 p2, Vectorf2 p3) {
	glBegin(GL_TRIANGLES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glVertex2f(p3.x, p3.y);
	glEnd();
}

void DrawRectangle(float width, float height) {
	const float w = width / 2.0f;
	const float h = height / 2.0f;

	glBegin(GL_QUADS);
	glVertex2f(-w, h);   // Top-Left
	glVertex2f(w, h);   // Top-Right
	glVertex2f(w, -h);   // Bottom-Right
	glVertex2f(-w, -h);   // Bottom-Left
	glEnd();

}

void DrawCircle(float radius, int numSides /* = 8 */) {
	const float step = M_PI / numSides;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	for (float angle = 0.0f; angle < (2.0f * M_PI); angle += step) {
		glVertex2f(radius * sinf(angle), radius * cosf(angle));
	}
	glVertex2f(0.0f, radius); // One more vertex to close the circle
	glEnd();
}
void RenderScene1() {
	glMatrixMode(GL_MODELVIEW);               // Switch to modelview matrix mode
	glLoadIdentity();                                // Load the identity matrix

	glTranslatef(-1.5f, 1.0f, -6.0f); // Translate our view matrix back and a bit to the left.
	glColor3f(1.0f, 0.0f, 0.0f);                             // Set Color to red
	DrawTriangle(Vectorf2(0.0f, 1.0f), Vectorf2(-1.0f, -1.0f), Vectorf2(1.0f, -1.0f));

	glTranslatef(3.0f, 0.0f, 0.0f);           // Shift view 3 units to the right
	glColor3f(0.0f, 0.0f, 1.0f);                            // Set Color to blue
	DrawRectangle(2.0f, 2.0f);

	glTranslatef(-1.5f, -3.0f, 0.0f);         // Back to center and lower screen
	glColor3f(1.0f, 1.0f, 0.0f);                          // Set color to yellow
	DrawCircle(1.0f, 16);
}


void renderScene4(float pos_X, float pos_Y, float pos_Z) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	float difamb[] = { 1.0, 0.5, 0.3, 1.0 };

	glTranslatef(pos_X, pos_Y, pos_Z);         // Translate back and to the left
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, difamb);
	glNormal3f(0.0, 0.0, 1.0);

	glPushMatrix();     // Push the current modelview matrix on the matrix stack
	glBegin(GL_QUADS);
	// Top face
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(1.0f, 0.3f, -42.0f);                     // Top-right of top face
	glVertex3f(-1.0f, 0.3f, -42.0f);                     // Top-left of top face
	glVertex3f(-1.0f, 0.3f, 1.0f);                    // Bottom-left of top face
	glVertex3f(1.0f, 0.3f, 1.0f);                    // Bottom-right of top face

	// Bottom face
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(1.0f, -1.0f, -42.0f);                 // Top-right of bottom face
	glVertex3f(-1.0f, -1.0f, -42.0f);                 // Top-left of bottom face
	glVertex3f(-1.0f, -1.0f, 1.0f);                // Bottom-left of bottom face
	glVertex3f(1.0f, -1.0f, 1.0f);                // Bottom-right of bottom face

	// Front face
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(1.0f, 0.3f, 1.0f);                     // Top-Right of front face
	glVertex3f(-1.0f, 0.3f, 1.0f);                     // Top-left of front face
	glVertex3f(-1.0f, -1.0f, 1.0f);                 // Bottom-left of front face
	glVertex3f(1.0f, -1.0f, 1.0f);                 // Bottom-right of front face

	// Back face
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(1.0f, -1.0f, -1.0f);                  // Bottom-Left of back face
	glVertex3f(-1.0f, -1.0f, -1.0f);                // Bottom-Right of back face
	glVertex3f(-1.0f, 0.3f, -1.0f);                    // Top-Right of back face
	glVertex3f(1.0f, 0.3f, -1.0f);                      // Top-Left of back face

	// Left face
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-1.0f, 0.3f, 1.0f);                     // Top-Right of left face
	glVertex3f(-1.0f, 0.3f, -42.0f);                    // Top-Left of left face
	glVertex3f(-1.0f, -1.0f, -42.0f);                // Bottom-Left of left face
	glVertex3f(-1.0f, -1.0f, 1.0f);                 // Bottom-Right of left face

	// Right face
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(1.0f, 0.3f, 1.0f);                      // Top-Right of left face
	glVertex3f(1.0f, 0.3f, -42.0f);                     // Top-Left of left face
	glVertex3f(1.0f, -1.0f, -42.0f);                 // Bottom-Left of left face
	glVertex3f(1.0f, -1.0f, 1.0f);                  // Bottom-Right of left face
	glEnd();

	glPopMatrix();
}

void drawCube(float size) {

	float difamb[] = { 1.0, 0.5, 0.3, 1.0 };
	glBegin(GL_QUADS);
	//Front face
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, difamb);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(size / 2, size / 2, size / 2); //upper right corner
	glVertex3f(-size / 2, size / 2, size / 2); //upper left corner
	glVertex3f(-size / 2, -size / 2, size / 2); //lower left corner
	glVertex3f(size / 2, -size / 2, size / 2); //lower right corner

	//Back face
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);

	//Upper face
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);

	//Bottom face
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);

	//Left face
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);

	//Right face
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	glEnd();
}
