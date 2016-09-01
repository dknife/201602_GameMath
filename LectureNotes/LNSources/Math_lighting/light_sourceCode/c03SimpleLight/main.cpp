#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifdef WIN32
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // MAC OS X
#include <OpenGL/OpenGL.h> // OpenGL core and utility lib.
#include <GLUT/GLUT.h> // OpenGL utility toolkit lib.
#endif

#include "initWindow.h"

// 재질에 설정될 값
GLfloat mat_specular[] = { 1.0, 1.0f, 1.0f, 1.0f };
GLfloat mat_diffuse[] =  { 0.0, 1.0f, 1.0f, 1.0f };
GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 120.0 };

// 광원에 설정될 값
GLfloat lit_specular[] = { 1.0, 1.0f, 1.0f, 1.0f };
GLfloat lit_diffuse[] =  { 0.0, 1.0f, 1.0f, 1.0f };
GLfloat lit_ambient[] =  { 0.0, 0.0f, 0.0f, 1.0f };

GLfloat light_position[] = { 1.0, 1.0f, 1.0f, 0.0f };

void LightSet(void) {
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	glLightfv(GL_LIGHT0, GL_SPECULAR, lit_specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lit_ambient);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void LightPositioning(void) {
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void init(int argc, char **argv) {
	initWindow(&argc, argv);
	
	glClearColor(1.0, 1.0, 1.0, 1.0);
	
	LightSet();
	glEnable(GL_DEPTH_TEST);
	
}
void reshape(int w, int h) {
	// CAMERA 렌즈의 설정
	glViewport(0, 0, w, h);
	float aspRatio = float(w)/h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, aspRatio, 0.1, 1000.0);
	
}

void display() {
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	
	gluLookAt(0,1,2,0,0,0,0,1,0);
	LightPositioning();
	
	glutSolidTeapot(0.5);
	
	// Double Buffer
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	init(argc, argv);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
}