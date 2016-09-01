#ifdef WIN32
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // MAC OS X
#include <OpenGL/OpenGL.h> // OpenGL core and utility lib.
#include <GLUT/GLUT.h> // OpenGL utility toolkit lib.
#endif

#include "initWindow.h"

void initWindow(int *pArg, char **argv) {
	// 윈도우 설정 및 프레임 버퍼 설정
	glutInit(pArg, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(512,512);
	glutCreateWindow("Dr. Kang's Graphics Lecture");	
	
}