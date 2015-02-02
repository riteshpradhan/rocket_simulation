
#include "darts.h"
#include <math.h>

Vertex::Vertex(void)
{
}
Vertex::Vertex( float _x,float _y, float _z)
{ x = _x; y = _y; z = _z;
}
Vertex::Vertex( int _x,int _y, int _z)
{ x = float(_x); y = float(_y); z = float(_z);
}
Vertex::Vertex( double _x, double _y, double _z)
{ x = float(_x); y = float(_y); z = float(_z);
}
Vertex::~Vertex(void)
{
}



void Vertex::translateZ(int tz)
{
	z = z + tz;
}

void Vertex::translateY(int ty)
{
	y = y + ty;
}



void Vertex::rotateX()
{
	float costh = float(cos (angx));
	float sinth = float(sin (angx));
	
		y -= refy ; z -= refz;
		float yy = y * costh - z * sinth;
		float zz = y * sinth + z * costh;
		y = yy + refy;
		z = zz + refz;
	
}
void Vertex::rotateY()
{
	float costh = float(cos (angy));
	float sinth = float(sin (angy));
	
		x -= refx ; z -= refz;
		float zz= z * costh - x * sinth;
		float xx = z * sinth + x * costh;
		x = xx + refx;
		z = zz + refz;
	
}
void Vertex::rotateZ()
{
	float costh = float(cos (angz));
	float sinth = float(sin (angz));
	
		y -= refy ; x -= refx;
		float xx = x * costh - y * sinth;
		float yy = x * sinth + y * costh;
		y = yy + refy;
		x = xx + refx;
	
}
Vertex Vertex::operator - (Vertex b)
{
	Vertex t;
	t.x = x - b.x;
	t.y = y - b.y;
	t.z = z - b.z;
	return t;
}
Vertex Vertex::operator + (Vertex b)
{
	Vertex t;
	t.x = x + b.x;
	t.y = y + b.y;
	t.z = z + b.z;
	return t;
}
Vertex Vertex::operator * (float b)
{
	Vertex t;
	t.x = x * b;
	t.y = y * b;
	t.z = z * b;
	return t;
}
Vertex Vertex::operator / (int b)
{
	Vertex t;
	t.x = x / b;
	t.y = y / b;
	t.z = z / b;
	return t;
}
Vertex Vertex::findunit()
{
	float mag = sqrt(x*x + y*y + z*z);
	return Vertex(x/mag, y/mag, z/mag);
}
