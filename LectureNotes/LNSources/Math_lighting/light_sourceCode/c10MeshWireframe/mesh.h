#ifndef _2013MESH_H_
#define _2013MESH_H_ 

class cvertex {
public:
	float x;
	float y;
	float z;
};
class cface {
public:
	int v0; // vertex index 0
	int v1; // vertex index 1
	int v2; // vertex index 2
};  // face in a triangular mesh

class CMesh {
	int nV; // number of vertices
	int nF; // number of faces
	cvertex *v; // vertex array
	cface *f;   // face array
	
public:
	// aux data : bounding box
	float minx, miny, minz;
	float maxx, maxy, maxz;
	
public:
	// constructor
	CMesh();	
	
	// public methods
	void LoadMesh(char *meshFileName);
	void DrawMesh(void);
};

#endif