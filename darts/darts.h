#pragma once

#include "resource.h"
#include "stdafx.h"
#define M_PI       3.14159265358979323846

class Vertex
{
	static float refx, refy, refz;
	static float angx, angy, angz;
public:
	float x, y, z;
	

	Vertex(void);
	~Vertex(void);
	Vertex( int _x,int _y, int _z);
	Vertex( float _x,float _y, float _z);
	Vertex( double _x,double _y, double _z);

	static void Vertex::setRotationPoint(float xx, float yy, float zz)
	{	refx = xx; refy = yy; refz = zz;
	}
	static void Vertex::setRotationAngle(int degx, int degy, int degz)
	{	
		angx = float(degx * M_PI / 180);
		angy = float(degy * M_PI / 180);
		angz = float(degz * M_PI / 180);
	}

	void translateZ(int tz);
	void translateY(int ty);
	void rotateX();
	void rotateY();
	void rotateZ();

	Vertex operator - (Vertex b);
	Vertex operator + (Vertex b);
	Vertex operator * (float b);
	Vertex operator / (int b);
	Vertex findunit ();
};

class Surface
{
public:
	unsigned int v[4];
	Vertex color;
	Vertex worldN;
	Vertex norm;
	float normD;


	Surface(void);
	~Surface(void);
	Surface( int a,int b, int c,int d);
	Surface( int a,int b, int c,int d, Vertex color);
	void findWorldNorm (Vertex* worldC);
	void findNorm (Vertex* viewC);
	void findNormZD (Vertex* viewC);
};
