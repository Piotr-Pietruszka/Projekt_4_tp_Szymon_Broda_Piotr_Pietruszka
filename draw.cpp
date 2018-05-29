// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw.h"

#define MAX_LOADSTRING 100
#define TMR_1 1
//struktury
struct uklad
{
	const int l_d_corner_x;
	int l_d_corner_y;
	int height;
	int width;

	int cel;
	int lb_ludzi;
	int max_lb;
};
int pietro = 100;

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
 
INT value;

uklad winda = {500, 300, 100, 200, /*cel*/0, 0, 8};

RECT drawArea2 = { 500, 0, 700, 400 };
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


void MyOnPaint(HDC hdc)
{
	

	Graphics graphics(hdc);
	Pen pen(Color(255,0,0,255));
	
	//pietra-----
	graphics.DrawLine(&pen,0,5*pietro, 2 * winda.l_d_corner_x + winda.width,5*pietro);
	graphics.DrawLine(&pen, 0, 4*pietro, winda.l_d_corner_x, 4 * pietro);
	graphics.DrawLine(&pen, winda.l_d_corner_x + winda.width, 3 * pietro, 2*winda.l_d_corner_x + winda.width , 3 * pietro);
	graphics.DrawLine(&pen, 0, 2 * pietro, winda.l_d_corner_x, 2 * pietro);
	graphics.DrawLine(&pen, winda.l_d_corner_x + winda.width, 1 * pietro,2* winda.l_d_corner_x + winda.width, 1 * pietro);
	graphics.DrawLine(&pen, 0,  0 * pietro,2* winda.l_d_corner_x + winda.width, 0*pietro);
	graphics.DrawLine(&pen, winda.l_d_corner_x + winda.width, 4 * pietro,2* winda.l_d_corner_x + winda.width, 4 * pietro);
	graphics.DrawLine(&pen, 0, 3 * pietro, winda.l_d_corner_x, 3 * pietro);
	graphics.DrawLine(&pen, winda.l_d_corner_x + winda.width, 2 * pietro,2* winda.l_d_corner_x + winda.width, 2 * pietro);
	graphics.DrawLine(&pen, 0, 1 * pietro, winda.l_d_corner_x, 1 * pietro);

	graphics.DrawLine(&pen, winda.l_d_corner_x + winda.width, 0 * pietro, winda.l_d_corner_x + winda.width, 1 * pietro);
	graphics.DrawLine(&pen, winda.l_d_corner_x + winda.width, 2 * pietro, winda.l_d_corner_x + winda.width, 3 * pietro);
	graphics.DrawLine(&pen, winda.l_d_corner_x + winda.width, 4 * pietro, winda.l_d_corner_x + winda.width, 5 * pietro);
	graphics.DrawLine(&pen, winda.l_d_corner_x, 1 * pietro, winda.l_d_corner_x, 2 * pietro);
	graphics.DrawLine(&pen, winda.l_d_corner_x, 3 * pietro, winda.l_d_corner_x, 4 * pietro);
	//------

	//winda
	if(value < winda.cel*pietro)
		value++;
	else if (value > winda.cel*pietro)
		value--;
	else
	{
		//zatrzymanie i zmiana celu windy
	}
	graphics.DrawRectangle(&pen,winda.l_d_corner_x, winda.l_d_corner_y - value,winda.width, winda.height);
}


int OnCreate(HWND window)
{
   SetTimer(window, TMR_1, 25, 0);
   return 0;
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

	value= 0;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DRAW);
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
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
       HWND hwndButton = CreateWindow(TEXT("button"),
	   TEXT("1"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   20, 20,
	   20,20,
	   hWnd,
	   (HMENU)ID_BUTTON1,
	   hInstance,
	   NULL);
    hwndButton = CreateWindow(TEXT("button"),
	   TEXT("2"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   40, 20,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON2,
	   hInstance,
	   NULL);
    hwndButton = CreateWindow(TEXT("button"),
	   TEXT("3"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   60, 20,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON3,
	   hInstance,
	   NULL);
    hwndButton = CreateWindow(TEXT("button"),
	   TEXT("4"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   80, 20,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON4,
	   hInstance,
	   NULL);
	 hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1200-80,120,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON5,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1200-60, 120,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON6,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1200-40, 120,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON7,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1200-20, 120,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON8,
		hInstance,
		NULL);
	 hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 220,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON9,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		40, 220,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON10,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		60, 220,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON11,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		80, 220,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON12,
		hInstance,
		NULL);
	 hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1120, 320,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON13,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1140, 320,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON14,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1160, 320,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON15,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1180, 320,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON16,
		hInstance,
		NULL);
	 hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 420,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON17,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		40, 420,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON18,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		60, 420,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON19,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		80, 420,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON20,
		hInstance,
		NULL);
   OnCreate(hWnd);

   if (!hWnd)
   {
      return FALSE;
   }

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
	PAINTSTRUCT ps;
	HDC hdc;
	//OnCreate(hWnd,wParam,lParam);
	//OnTimer(hWnd,wParam,lParam);

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
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		MyOnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
			case TMR_1:
				//force window to repaint
				InvalidateRect(hWnd, NULL, TRUE);
				hdc = BeginPaint(hWnd, &ps);
				MyOnPaint(hdc);
				EndPaint(hWnd, &ps);
			break;
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
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