// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw.h"
#include "vector"

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
//-----------------------
struct czlowiek
{
	int waga = 60;
	int cel;
	//int pozycja;//0-4 - pietra -1 lub cos innego - winda
	//alternatywnie utworzenie struktury pietro
};

struct pietro
{
	std::vector <czlowiek> ludzie;
};

const int lb_pieter = 5;
int h_pietra = 100;

pietro pietra_tab[lb_pieter];//tab pieter
							 //--------------

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
 
INT value;

uklad winda = {500, 400, 100, 200, /*cel*/2, 0, 8};

RECT drawArea = { 500, 0, 701, 500};
RECT drawArea0 = { 0, 401, 500, 499 };
RECT drawArea1 = { 701, 301, 1200, 399 };
RECT drawArea2 = { 0, 201, 500, 299 };
RECT drawArea3 = { 701, 101, 1200, 199 };
RECT drawArea4 = { 0, 1, 500, 99 };
//RECT drawArea2 = { winda.l_d_corner_x,winda.l_d_corner_y, winda.l_d_corner_x + winda.width, winda.l_d_corner_y + winda.height, };
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
	for (int i = 0; i <= lb_pieter; i++)
	{
		if (i == 0 || i == lb_pieter)
			graphics.DrawLine(&pen, 0, i * h_pietra, 2 * winda.l_d_corner_x + winda.width, i * h_pietra);
		else
		{
			graphics.DrawLine(&pen, winda.l_d_corner_x + winda.width, i * h_pietra, 2 * winda.l_d_corner_x + winda.width, i * h_pietra);
			graphics.DrawLine(&pen, 0, i * h_pietra, winda.l_d_corner_x, i * h_pietra);
		}
		if (i % 2 == 0)
			graphics.DrawLine(&pen, winda.l_d_corner_x + winda.width, i * h_pietra, winda.l_d_corner_x + winda.width, (i + 1) * h_pietra);
		else  if (i<lb_pieter)
			graphics.DrawLine(&pen, winda.l_d_corner_x, i * h_pietra, winda.l_d_corner_x, (i + 1) * h_pietra);
	}
	//------
	for (int j = 0 ;j <lb_pieter;j++)
	{
		for (int i = 0;i < pietra_tab[j].ludzie.size();i++)
		{
			if(j%2==0)
				graphics.DrawRectangle(&pen, 450-(i*21),(5-j)*h_pietra -60,20,50);
			else 
				graphics.DrawRectangle(&pen, 750 + (i * 21), (5-j)*h_pietra -60, 20,50);
		}
	}
	//winda
	if(value < winda.cel*h_pietra)
		value++;
	else if (value > winda.cel*h_pietra)
		value--;
	else
	{
		winda.cel--;
		graphics.DrawRectangle(&pen, winda.l_d_corner_x, winda.l_d_corner_y - value, winda.width, winda.height);
		Sleep(2500);//zatrzymanie windy na pietrze
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
       
   HWND hwndButton = CreateWindow(TEXT("button"),//pietro 4;  0
	   TEXT("0"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   20, 20,
	   20,20,
	   hWnd,
	   (HMENU)ID_BUTTON1,
	   hInstance,
	   NULL);
    hwndButton = CreateWindow(TEXT("button"),//pietro 4;  1
	   TEXT("1"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   40, 20,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON2,
	   hInstance,
	   NULL);
    hwndButton = CreateWindow(TEXT("button"),//pietro 4;  2
	   TEXT("2"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   60, 20,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON3,
	   hInstance,
	   NULL);
    hwndButton = CreateWindow(TEXT("button"),//pietro 4;  3
	   TEXT("3"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   80, 20,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON4,
	   hInstance,
	   NULL);

	 hwndButton = CreateWindow(TEXT("button"),//pietro 3
		TEXT("0"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1200-80,120,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON5,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),//pietro 3
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1200-60, 120,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON6,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),//pietro 3
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1200-40, 120,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON7,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),//pietro 3
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1200-20, 120,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON8,
		hInstance,
		NULL);

	 hwndButton = CreateWindow(TEXT("button"),//pietro 2
		TEXT("0"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 220,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON9,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),//pietro 2
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		40, 220,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON10,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),//pietro 2
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		60, 220,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON11,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),//pietro 2
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		80, 220,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON12,
		hInstance,
		NULL);

	 hwndButton = CreateWindow(TEXT("button"),//pietro 1
		TEXT("0"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1120, 320,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON13,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),//pietro 1
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1140, 320,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON14,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),//pietro 1
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1160, 320,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON15,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),//pietro 1
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1180, 320,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON16,
		hInstance,
		NULL);

	 hwndButton = CreateWindow(TEXT("button"),//pietro 0
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 420,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON17,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),//pietro 0
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		40, 420,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON18,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),//pietro 0
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		60, 420,
		20, 20,
		hWnd,
		(HMENU)ID_BUTTON19,
		hInstance,
		NULL);
	hwndButton = CreateWindow(TEXT("button"),//pietro 0
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
		//pietro 4
		case ID_BUTTON1:
			pietra_tab[4].ludzie.push_back({ 60, 0 });
			InvalidateRect(hWnd, &drawArea4, TRUE);
			break;
		case ID_BUTTON2:
			pietra_tab[4].ludzie.push_back({ 60, 1 });
			InvalidateRect(hWnd, &drawArea4, TRUE);
			break;
		case ID_BUTTON3:
			pietra_tab[4].ludzie.push_back({ 60, 2 });
			InvalidateRect(hWnd, &drawArea4, TRUE);
			break;
		case ID_BUTTON4:
			pietra_tab[4].ludzie.push_back({ 60, 3 });
			InvalidateRect(hWnd, &drawArea4, TRUE);
			break;

		case ID_BUTTON5:
			pietra_tab[3].ludzie.push_back({ 60, 0 });
			InvalidateRect(hWnd, &drawArea3, TRUE);
			break;
		case ID_BUTTON6:
			pietra_tab[3].ludzie.push_back({ 60, 1 });
			InvalidateRect(hWnd, &drawArea3, TRUE);
			break;
		case ID_BUTTON7:
			pietra_tab[3].ludzie.push_back({ 60, 2 });
			InvalidateRect(hWnd, &drawArea3, TRUE);
			break;
		case ID_BUTTON8:
			pietra_tab[3].ludzie.push_back({ 60, 4 });
			InvalidateRect(hWnd, &drawArea3, TRUE);
			break;

		case ID_BUTTON9:
			pietra_tab[2].ludzie.push_back({ 60, 0 });
			InvalidateRect(hWnd, &drawArea2, TRUE);
			break;
		case ID_BUTTON10:
			pietra_tab[2].ludzie.push_back({ 60, 1 });
			InvalidateRect(hWnd, &drawArea2, TRUE);
			break;
		case ID_BUTTON11:
			pietra_tab[2].ludzie.push_back({ 60, 3 });
			InvalidateRect(hWnd, &drawArea2, TRUE);
			break;
		case ID_BUTTON12:
			pietra_tab[2].ludzie.push_back({ 60, 4 });
			InvalidateRect(hWnd, &drawArea2, TRUE);
			break;

		case ID_BUTTON13:
			pietra_tab[1].ludzie.push_back({ 60, 0 });
			InvalidateRect(hWnd, &drawArea1, TRUE);
			break;
		case ID_BUTTON14:
			pietra_tab[1].ludzie.push_back({ 60, 2 });
			InvalidateRect(hWnd, &drawArea1, TRUE);
			break;
		case ID_BUTTON15:
			pietra_tab[1].ludzie.push_back({ 60, 3 });
			InvalidateRect(hWnd, &drawArea1, TRUE);
			break;
		case ID_BUTTON16:
			pietra_tab[1].ludzie.push_back({ 60, 4 });
			InvalidateRect(hWnd, &drawArea1, TRUE);
			break;

		case ID_BUTTON17:
			pietra_tab[0].ludzie.push_back({ 60, 1 });
			InvalidateRect(hWnd, &drawArea0, TRUE);
			break;
		case ID_BUTTON18:
			pietra_tab[0].ludzie.push_back({ 60, 2 });
			InvalidateRect(hWnd, &drawArea0, TRUE);
			break;
		case ID_BUTTON19:
			pietra_tab[0].ludzie.push_back({ 60, 3 });
			InvalidateRect(hWnd, &drawArea0, TRUE);
			break;
		case ID_BUTTON20:
			pietra_tab[0].ludzie.push_back({ 60, 4 });
			InvalidateRect(hWnd, &drawArea0, TRUE);
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
				InvalidateRect(hWnd, &drawArea2, TRUE);
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
