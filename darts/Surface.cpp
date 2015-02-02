#include "darts.h"

Surface::Surface(void)
{
}
Surface::Surface( int a,int b, int c, int d)
{ v[0] = a, v[1] = b, v[2] = c, v[3]=d; //, color[v[0]].x;
	
}

// for diff color polygon
Surface::Surface( int a,int b, int c, int d, Vertex col)
{ //int i;
	v[0] = a, v[1] = b, v[2] = c, v[3]=d, 
color.x = col.x;
	color.y = col.y;
	color.z = col.z;
	
}

	Surface::~Surface(void)
{
}

void Surface::findNorm(Vertex* pv)
{
	float x1,y1,z1,x2,y2,z2,x3,y3,z3;

	x1 = pv[v[0]].x; y1 = pv[v[0]].y; z1 = pv[v[0]].z;
	x2 = pv[v[1]].x; y2 = pv[v[1]].y; z2 = pv[v[1]].z;
	x3 = pv[v[2]].x; y3 = pv[v[2]].y; z3 = pv[v[2]].z;

	norm.x = y1*(z2-z3) + y2*(z3-z1) + y3*(z1-z2);
	norm.y = z1*(x2-x3) + z2*(x3-x1) + z3*(x1-x2);
	norm.z = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
	//norm = norm.findunit();
	
	normD = -x1*(y2*z3-y3*z2) - x2*(y3*z1-y1*z3) - x3*(y1*z2-y2*z1);
}
void Surface::findNormZD(Vertex *pv)
{
	float x1,y1,z1,x2,y2,z2,x3,y3,z3;

	x1 = pv[v[0]].x; y1 = pv[v[0]].y; z1 = pv[v[0]].z;
	x2 = pv[v[1]].x; y2 = pv[v[1]].y; z2 = pv[v[1]].z;
	x3 = pv[v[2]].x; y3 = pv[v[2]].y; z3 = pv[v[2]].z;

	norm.z = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
	normD = -x1*(y2*z3-y3*z2) - x2*(y3*z1-y1*z3) - x3*(y1*z2-y2*z1);
	 
}
void Surface::findWorldNorm (Vertex* pv)
{
	float x1,y1,z1,x2,y2,z2,x3,y3,z3;

	x1 = pv[v[0]].x; y1 = pv[v[0]].y; z1 = pv[v[0]].z;
	x2 = pv[v[1]].x; y2 = pv[v[1]].y; z2 = pv[v[1]].z;
	x3 = pv[v[2]].x; y3 = pv[v[2]].y; z3 = pv[v[2]].z;

	worldN.x = y1*(z2-z3) + y2*(z3-z1) + y3*(z1-z2);
	worldN.y = z1*(x2-x3) + z2*(x3-x1) + z3*(x1-x2);
	worldN.z = x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2);
	worldN = worldN.findunit();
}