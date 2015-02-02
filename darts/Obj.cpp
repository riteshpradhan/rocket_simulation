#include "StdAfx.h"
#include "Obj.h"
#include "darts.h"
#include <math.h>
Obj::Obj(void)
{
}
Obj::Obj(Vertex* wc, int numV,  Surface * s, int numS)
{
	worldC = wc; surface = s; 
	noofvertex = numV; noofsurface = numS;
}

Obj::~Obj(void)
{
}
void Obj::rotateX(int deg)
{	
	if(!deg) return;
	Vertex::setRotationPoint (0, 0, 0);
	Vertex::setRotationAngle (deg,0, 0);
	for (int i = 0; i< noofvertex; i++)
	{
		worldC[i].rotateX();
	}
	//changed = true;
}
void Obj::rotateY(int deg)
{	
	if(!deg) return;
	
	Vertex::setRotationAngle (0, deg, 0);
	for (int i = 0; i< noofvertex; i++)
			worldC[i].rotateY();
	
}
void Obj::rotateZ(int deg)
{	
	if(!deg) return;
	//Vertex::setRotationPoint (centroid.x, centroid.y, centroid.z);
	Vertex::setRotationAngle (0,0, deg);
	for (int i = 0; i< noofvertex; i++)
	{
		worldC[i].rotateZ();
	}
	//changed = true;
}
void Obj::rotateZ(int deg, Vertex v)
{	
	if(!deg) return;
	Vertex::setRotationPoint (v.x, v.y, v.z);
	Vertex::setRotationAngle (0,0, deg);
	for (int i = 0; i< noofvertex; i++)
	{
		worldC[i].rotateZ();
	}
	//centroid.rotateZ();
	//changed = true;
}
/*void Obj::scale(float fx, float fy, float fz)
{
	for (int i = 0; i< noofvertex; i++)
	{
		worldC[i].x = ((worldC[i].x - centroid.x) * fx) + centroid.x;
		worldC[i].y = ((worldC[i].y - centroid.y) * fy) + centroid.y;
		worldC[i].z = ((worldC[i].z - centroid.z) * fz) + centroid.z;
	}
	changed = true;
}
*/
void Obj::translate(float x, float y, float z)
{
	if(x ==0 && y==0 && z==0) return;
	Vertex v = Vertex(x,y,z);
	for (int i = 0; i< noofvertex; i++)
	{
		worldC[i] = worldC[i] + v;
	}
	//centroid = centroid + v;
	//changed = true;
}

//Obj.tip = Vertex(5,5,5);
void Obj::scale(float fx, float fy, float fz)
{
	for (int i = 0; i< noofvertex; i++)
	{
		worldC[i].x = ((worldC[i].x - 0/*centroid.x*/) * fx) ;//+ centroid.x;
		worldC[i].y = ((worldC[i].y -  0/*centroid.y*/) * fy) ;//+ centroid.y;
		worldC[i].z = ((worldC[i].z -  0/*centroid.z*/) * fz) ;//+ centroid.z;
	}
	
}
void Obj::display(HDC hdc)
{
	Vertex a,t,tt[4];
	float temp, zprp=400;
	temp = (zprp - 0);
	int devx=600,devy=150;
	POINT p[4];
	int light = 220;
	int r=45,g=43,b=0;
	float dot;
	int amb = 35;

			

	Vertex		pos = Vertex(200, 200,400);
	Vertex lookat = Vertex(200, 200,-100);

	Vertex dirN = pos - lookat;
	Vertex dirV = Vertex (0,1,0);
	
	float magN = sqrt(dirN.x*dirN.x + dirN.y*dirN.y +dirN.z*dirN.z);
	dirN = Vertex ( dirN.x/magN , dirN.y/magN, dirN.z/magN );
	Vertex dirU = Vertex ( dirV.y*dirN.z - dirV.z*dirN.y, dirV.z*dirN.x-dirV.x*dirN.z, dirV.x*dirN.y-dirV.y*dirN.x );  // u = v X n;
	dirV = Vertex ( dirN.y*dirU.z - dirN.z*dirU.y , dirN.z*dirU.x- dirN.x*dirU.z , dirV.z =	dirN.x*dirU.y- dirN.y*dirU.x ); //v= n X u

	Vertex lightDir = Vertex(0,0,1);
	for (int i=0; i< noofsurface; i++)
	{
		
		
		for(int j=0; j< 4; j++)
		{
			a = worldC[surface[i].v[j]];
			
			//translation
			a.x -= pos.x ;
			a.y -= pos.y ;
			a.z -= pos.z;

			//rotation
			t.x = dirU.x * a.x + dirU.y * a.y + dirU.z * a.z ;
			t.y = dirV.x * a.x + dirV.y * a.y + dirV.z * a.z ;
			t.z = dirN.x * a.x + dirN.y * a.y + dirN.z * a.z ;

			tt[j]= t;

			p[j].x = int (t.x /(zprp - t.z)*temp) + devx;
			p[j].y = -(int (t.y / (zprp - t.z)*temp)) + devy;
			
		}
			
		//lightDir = lightDir.findunit();
		surface[i].findWorldNorm(worldC);
		dot = surface[i].worldN.x * lightDir.x +surface[i].worldN.y * lightDir.y + surface[i].worldN.z * lightDir.z; 
		
			r = surface[i].color.x *( (light*dot) + amb);
			g = surface[i].color.y * ( (light*dot) + amb);
			b = surface[i].color.z * ( (light*dot) + amb);

			SetDCPenColor(hdc, RGB(r,g,b));
			SetDCBrushColor(hdc, RGB(r,g,b));
			SelectObject(hdc, GetStockObject(DC_PEN) );
			SelectObject(hdc, GetStockObject(DC_BRUSH) );
		Surface s(0,1,2,3);
		s.findNormZD(tt);

		if ((s.norm.z * zprp+s.normD) < 0) continue;
		
		Polygon (hdc,p,4);


	}

	


}

void Obj::set(Vertex* wC, int numV , Surface* s, int numS)
	{
		worldC = wC; surface = s; 
	noofvertex = numV; noofsurface = numS;
		

	}
