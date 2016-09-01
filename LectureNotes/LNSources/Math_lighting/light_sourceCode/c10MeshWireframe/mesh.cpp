#include "Mesh.h"

#ifdef WIN32
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // MAC OS X
#include <OpenGL/OpenGL.h> // OpenGL core and utility lib.
#include <GLUT/GLUT.h> // OpenGL utility toolkit lib.
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BIGNUMBER 10000000000000000.0

CMesh::CMesh(): nV(0), nF(0), v(NULL), f(NULL),
minx(BIGNUMBER), miny(BIGNUMBER), minz(BIGNUMBER),
maxx(-BIGNUMBER),maxy(-BIGNUMBER),maxz(-BIGNUMBER)
{ }


// public methods

void CMesh::LoadMesh(char *meshFileName) {
	FILE *fptr = fopen(meshFileName,"r") ;
	if(!meshFileName || !fptr ) return;
	
	// When the file was successfully opened
	fscanf(fptr, "%d", &nV);
	v = new cvertex[nV];
	for(int i=0;i<nV;i++) {
		fscanf(fptr, "%f", &v[i].x);
		fscanf(fptr, "%f", &v[i].y);
		fscanf(fptr, "%f", &v[i].z);
		if (v[i].x<minx) minx = v[i].x;
		if (v[i].y<miny) miny = v[i].y;
		if (v[i].z<minz) minz = v[i].z;
		if (v[i].x>maxx) maxx = v[i].x;
		if (v[i].y>maxy) maxy = v[i].y;
		if (v[i].z>maxz) maxz = v[i].z;
	}
	fscanf(fptr, "%d", &nF); 
	f = new cface[nF];
	for(int i=0;i<nF;i++) {
		fscanf(fptr, "%d", &f[i].v0);
		fscanf(fptr, "%d", &f[i].v1);
		fscanf(fptr, "%d", &f[i].v2);
	}
}

void CMesh::DrawMesh(void) {
	if(!v || !f) return;
	
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<nF;i++) {
		
		glVertex3f( v[f[i].v0].x, v[f[i].v0].y, v[f[i].v0].z);
		glVertex3f( v[f[i].v1].x, v[f[i].v1].y, v[f[i].v1].z);
		glVertex3f( v[f[i].v2].x, v[f[i].v2].y, v[f[i].v2].z);
		glEnd();
	}
}
