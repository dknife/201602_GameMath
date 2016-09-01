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
	n = new cvertex[nV];
	ComputeNormals();
}

void CMesh::ComputeNormals(void) {
	for (int i=0; i<nV; i++) {
		n[i].x = n[i].y = n[i].z = 1.0f;
	}
	
	for(int i=0;i<nF;i++) {
		// normal vector should be specified here
		cvertex p0, p1, p2;
		cvertex v0, v1;
		cvertex norm;
		p0 = v[f[i].v0];
		p1 = v[f[i].v1];
		p2 = v[f[i].v2];
		
		// v0 = p1 - p0
		v0.x = p1.x - p0.x;
		v0.y = p1.y - p0.y;
		v0.z = p1.z - p0.z;
		
		// v1 = p2 - p0
		v1.x = p2.x - p0.x;
		v1.y = p2.y - p0.y;
		v1.z = p2.z - p0.z;
		
		// norm =  v0 X v1 
		//     -------
		//     |v0 X v1|
		norm.x = v0.y*v1.z - v0.z*v1.y;
		norm.y = v0.z*v1.x - v0.x*v1.z;
		norm.z = v0.x*v1.y - v0.y*v1.x;
		float len = sqrt(norm.x*norm.x+norm.y*norm.y+norm.z*norm.z);
		norm.x /= len; norm.y /= len; norm.z /= len;
		
		n[f[i].v0].x += norm.x;
		n[f[i].v0].y += norm.y;
		n[f[i].v0].z += norm.z;
		
		n[f[i].v1].x += norm.x;
		n[f[i].v1].y += norm.y;
		n[f[i].v1].z += norm.z;
		
		n[f[i].v2].x += norm.x;
		n[f[i].v2].y += norm.y;
		n[f[i].v2].z += norm.z;
	}
	
	for (int i=0; i<nV; i++) {
		float len = sqrt(n[i].x*n[i].x+n[i].y*n[i].y+n[i].z*n[i].z);
		n[i].x /= len;
		n[i].y /= len;
		n[i].z /= len;
	}
}

void CMesh::DrawMesh(void) {
	if(!v || !f) return;
	
	
	
	glBegin(GL_TRIANGLES);
	for(int i=0;i<nF;i++) {
		// normal vector should be specified here
		cvertex p0, p1, p2;
		cvertex n0, n1, n2;
		n0 = n[f[i].v0];
		p0 = v[f[i].v0];
		n1 = n[f[i].v1];
		p1 = v[f[i].v1];
		n2 = n[f[i].v2];
		p2 = v[f[i].v2];
		
		glNormal3f( n0.x, n0.y, n0.z);
		glVertex3f( p0.x, p0.y, p0.z);
		glNormal3f( n1.x, n1.y, n1.z);
		glVertex3f( p1.x, p1.y, p1.z);
		glNormal3f( n2.x, n2.y, n2.z);
		glVertex3f( p2.x, p2.y, p2.z);
		
	}
	glEnd();
}
