#pragma once
#include "darts.h"
class Obj
{
	int noofvertex, noofsurface;
	Vertex* worldC;
	Surface* surface;

public:
	Obj(void);
	~Obj(void);
	Vertex tip;
	Obj(Vertex* wc, int numV,  Surface * s, int numS);
	//Obj(Vertex* wc, int numV,  Surface * s, int numS, Vertex c);
	//void setTip(float x, float y, float z);
	void Obj::rotateX(int deg);
	void Obj::rotateY(int deg);
	void Obj::rotateZ(int deg);
	void Obj::rotateZ(int deg, Vertex v);
	void Obj::scale(float fx, float fy, float fz);
	void Obj::translate(float x, float y, float z);

	//void Obj::scale(float fx, float fy, float fz);
	void set(Vertex* worldC, int noOfVertex, Surface* s, int numS);
	
	void display (HDC);

};

