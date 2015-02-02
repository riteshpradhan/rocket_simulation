// darts.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "darts.h"
#include "Obj.h"
#include <stdio.h>
float Vertex::angx = 0; float Vertex::angy = 0; float Vertex::angz = 0;
float Vertex::refx = 0; float Vertex::refy = 0; float Vertex::refz = 0;
int keyUp = 0 , keyDown = 0, keyRight = 0, keyLeft = 0;
Obj Rock;
Obj cube;
Obj* sphere;
Vertex		pos = Vertex(200, 200,400);
	Vertex lookat = Vertex(200, 200,-100);
#define MAX_LOADSTRING 100
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

LRESULT				OnPaint(HWND hWnd);
HWND hWnd;

Obj* loadSphere();
void refresh(HWND hWnd)
{
	InvalidateRect(hWnd, NULL, false);
	//RECT rec = {0,35,width,height+35};
	//::InvalidateRect(hWnd, &rec, false);
	UpdateWindow(hWnd);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DARTS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DARTS));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//RECT r = {0,0, 1000,600 };		

		//InvalidateRect(msg.hwnd,0,false);		

	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DARTS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DARTS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }


   loadSphere();
   sphere->scale(80.0F,80.0F,80.0F);
   sphere->translate(-100.0F,-100.0F,0.0F);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;


		

		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_UP:
					keyUp = 1;
					//sphere->translate(10.0,10.0,10.0);
					//Rock.translate(10.0,10.0,10.0);
					break;
				
				case VK_LEFT:
					keyLeft = 1; break;
			case VK_RIGHT:
					keyRight = 1; break;
			case VK_DOWN:
					keyDown = 1;
					//sphere->translate(-10.0,10.0,10.0);
					break;

					case 'A':
						cube.translate(10,0,0); 
						break;
				case 'D':
					Rock.rotateY(-10); break;
				case 'S':
					Rock.rotateZ(-50); break;
				case 'W':
					Rock.rotateZ(50,Vertex(50,50,50)); break;
				/*case VK_A:
					keyA = 1; break;
				case VK_S:
					keyS = 1; break;
				case VK_D:
					keyD = 1; break;
				case VK_W:
					keyW = 1; break;
					*/

								default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
			refresh(hWnd);
		}

		break;

		case WM_KEYUP:
			
			switch(wParam)
			{
			case VK_UP:
					keyUp = 0; break;
			case VK_DOWN:
					keyDown = 0; break;
			case VK_LEFT:
					keyLeft = 0; break;
			case VK_RIGHT:
					keyRight = 0; break;
			default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
		break;

		case WM_CHAR:
			switch(wParam)
			{
			case 'a':
					keyUp = 0; break;
			case 'd':
					keyDown = 0; break;
			case 's':
					keyLeft = 0; break;
			case 'w':
					keyRight = 0; break;
			
			default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
		break;
	


	

	case WM_PAINT:
		

		return OnPaint(hWnd);
		// TODO: Add any drawing code here...
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	

}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}




float ll=70, hh=200, bb=-70;
	float sx= -35,sy=100,sz=35;
	const int n = 15;
	static int count = 0;
	Vertex tip;
	int tipx, tipy, tipz;
	
	
Vertex worldC[n]= { Vertex(sx,sy,sz),Vertex(sx + ll,sy,sz),Vertex(sx+ll,sy+hh,sz),Vertex(sx,sy+hh,sz),
							 Vertex(sx,sy,sz+bb),Vertex(sx+ ll,sy,sz+bb),Vertex(sx+ll,sy+hh,sz+bb),Vertex(sx,sy+hh,sz+bb),//body
							Vertex(0,450,0)   //tip
							,Vertex(0,100,0),Vertex(0,040,0),Vertex(35,10,-35),Vertex(35,20,35),Vertex(-35,20,35),Vertex(-35,20,-35)//fire
							};
Surface surf[] = {
		Surface(0,1,2,3,Vertex(float(160/255.0),float(2/255.0),float(190/255.0)))
		,Surface(1,5,6,2,Vertex(.61,.81,0.9)),
		Surface(5,4,7,6,Vertex(0,0,1)),
		Surface(3,7,4,0,Vertex(1,0,1)),
		Surface(6,7,3,2,Vertex(.77,.77,0.0)), 
		Surface(1,0,4,5,Vertex(0.44,.44,0.0))//body
			, Surface(2,6,8,8,Vertex(.1,0.2,0.3)), 
			Surface(6,7,8,8,Vertex(.31,0.44,0.511)), 
			Surface(8,7,3,8,Vertex(.21,0.98,0.54)), 
			Surface(8,3,2,8,Vertex(.31,0.5,0.1))//pyramid
				,Surface(9,10,11,9,Vertex(1,1,0)),
				Surface(9,10,12,9,Vertex(1,1,0)),
				Surface(10,9,13,10,Vertex(.8,0.8,0.0)),
				Surface(10,9,14,10,Vertex(.9,0.8,0.0))    //fire
				};

 
	 

	//,Vertex(1,0,0)

//Obj::tip = worldC[8];
void translate(int tz)
{
	for ( int i = 0; i < 15; i++)
	{
		worldC[i].translateZ(tz);
	}
	

}

void translatey(int ty)
{
	for ( int i = 0; i < 15; i++)
	{
		worldC[i].translateY(ty);
	}
	

}

void self_rotate() {
	Vertex::setRotationPoint(0,0,0);
	Vertex::setRotationAngle( 10,10,10);
	for ( int i = 0; i < 15; i++)
	{
		worldC[i].rotateY();
	}
}
Obj* loadSphere()
{
	float x,y,z;
	int xx,yy;
	FILE* fs = fopen("sphere.mod", "rb");
	if (fs == NULL)
	{	
		MessageBox(hWnd, _T("File not found: sphere.mod"), _T("Title"), MB_OK);
		return 0;
	}
	int numvertices,numtexcoord,numtriangles,numframes;
	int temp;
	fread(&temp, sizeof(int), 1,fs);
	fread(&temp, sizeof(int), 1,fs);

	fread(&numtexcoord, sizeof(int), 1,fs);
	fread(&numvertices, sizeof(int), 1,fs);
	fread(&numtriangles, sizeof(int), 1,fs);
	fread(&numframes, sizeof(int), 1,fs);

	//POINT* textureC = new POINT[numtexcoord];
	for (int i=0;i<numtexcoord;i++)
	{
		fread(&x, sizeof(float) ,1,fs);
		fread(&y, sizeof(float) ,1,fs);

		xx = int(x*648);
		yy = int(y*484);
		//textureC[i].x = xx;
		//textureC[i].y = yy;
	}

	short a,b,c,d,e,f;
	Surface* surf = new Surface[numtriangles];
	for (int i=0;i<numtriangles;i++)
    {
		fread(&a, sizeof(short), 1, fs);
		fread(&b, sizeof(short), 1, fs);
		fread(&c, sizeof(short), 1, fs);

		fread(&d, sizeof(short), 1, fs);
		fread(&e, sizeof(short), 1, fs);
		fread(&f, sizeof(short), 1, fs);

		//surf[i] = Surface(d,e,f,d,Vertex(0,1,0));
		surf[i] = Surface(c,b,a,c,Vertex(float(86/255.0),float(156/255.0),float(69/255.0)));
	}

	Vertex* worldC = new Vertex[numvertices];
	for (int i=0;i<numvertices;i++)
    {
		fread(&x, sizeof(float) , 1, fs);
		fread(&y, sizeof(float) , 1, fs);
		fread(&z, sizeof(float) , 1, fs);

		worldC[i] = Vertex(x,y,z);

		fread(&x, sizeof(float) , 1, fs);
		fread(&y, sizeof(float) , 1, fs);
		fread(&z, sizeof(float) , 1, fs);
	}

	::fclose(fs);

	sphere= new Obj(worldC, numvertices, surf, numtriangles);
	
	//sphere->setTextureCoord(textureC);
	return sphere;
}

LRESULT	OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HDC hdc1, hdc2;

	static int page = 0;

	/*hdc1 = GetDC(hWnd);
	hdc2 = GetDC(hWnd);

	if( page == 0 ) 
		{
			hdc1 = BeginPaint(hWnd,&ps);
			hdc = hdc1;
		}
	else
		{
			hdc2 = BeginPaint(hWnd,&ps);
			hdc = hdc2;
	}
*/

	hdc = BeginPaint(hWnd, &ps);

	HDC hdcmem = CreateCompatibleDC(hdc);
	HBITMAP bitmap = CreateCompatibleBitmap(hdc,1001,601); 
	SelectObject(hdcmem, bitmap);
	
	
	::SetBkColor(hdcmem, RGB(0,0,0));
	
	cube.set(worldC, 15, surf, 14); //creeate set funciton in obj
 
	if (keyUp == 1 )//&& count < 100 ) 
	{
	
		//translate(-6);
		//translatey(6);
		cube.rotateX(5);
		cube.translate(0,10,0);
		//count ++;
		
		   //traanlsate loop code
	}
		   //translat by 6 pixel;
	if ( keyDown == 1 )//&& count >= 0)
	{
		self_rotate();
			//translate(6);
			translatey(-6);
			//self_rotate();
			//count --;
			
	}

	/*for (int i=0;i<10;i++) {
		self_rotate();
		cube.display(hdc);
	}*/

	if (keyRight == 1 )//&& count < 100 ) 
	{
	
		translate(-5);
		//cube.display(hdc);

			for ( int i = 0; i < 15; i++)
	{
		Vertex::setRotationAngle(-1,0,0);
		worldC[i].rotateX();
		worldC[i].translateZ(6);
	}
			translate(-6);

			//cube.display(hdcmem);
		
		//translatey(6);
		//count ++;
		
		   //traanlsate loop code
	}
		   //translat by 6 pixel;
	if ( keyLeft == 1 )//&& count >= 0)
	{

			translate(5);
			//cube.display(hdcmem);
			//translate
			
			for ( int i = 0; i < 15; i++)
	{
		Vertex::setRotationAngle(1,0,0);
		worldC[i].rotateX();
		//worldC[i].translateZ(6);
	}
	
			//cube.display(hdc);
			//translatey(-6);
			//count --;
			
	}

	sphere->display(hdcmem);
	cube.display(hdcmem);
	//

	//BitBlt(hdc,0,0,ps.rcPaint.right,ps.rcPaint.bottom,hdcmem,0,0,SRCCOPY);
	BitBlt(hdc,0,0,1001,601,hdcmem,0,0,SRCCOPY);
	//BitBlt(hdc,0,startY,126,128,texture,0,0,SRCCOPY);
	
	DeleteDC(hdcmem);
	DeleteObject(bitmap);
	

	EndPaint(hWnd, &ps);

	page = !page;

	/*ReleaseDC(hWnd,hdc1);
	ReleaseDC(hWnd,hdc2);
*/
	//refresh(hWnd);

	//if(keypress && notfinish)  refresh(hWnd);
	return 0;
}


