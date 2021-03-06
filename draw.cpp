// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw.h"
#include "vector"

#define MAX_LOADSTRING 100
#define TMR_1 1
//-------------------------------------------------------------struktury
struct czlowiek
{
	int waga ;
	int cel;
};

struct uklad
{
	const int l_d_corner_x;
	int l_d_corner_y;
	int height;
	int width;

	int cel;
	int lb_ludzi;
	int max_lb;

	bool open;//czy otwarta
	int cel_1;//do ktorego winda aktualnnie jedzie, cel po drodze
	std::vector <czlowiek> ludzie;
};

struct pietro
{
	std::vector <czlowiek> ludzie;
};
struct kolejnosc{
	int nr_pietra_p;
	int nr_pietra_d;
};
//----------------------------------------------------------zmienne
const int udzwig_windy = 600;
const int waga_os = 70;
const int lb_pieter = 5;
int h_pietra = 100;
std::vector<kolejnosc> dane;
int color;

pietro pietra_tab[lb_pieter];//tab pieter
							 //--------------

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
 
INT value;

uklad winda = {500, 400, 100, 200, /*cel*/0, 0, udzwig_windy/ waga_os, false, /*cel_1*/0};

RECT drawArea = { 500, 0, 701, 500 };
RECT drawArea0 = { 101, 401, 500, 499 };
RECT drawArea1 = { 701, 301, 1100, 399 };
RECT drawArea2 = { 101, 201, 500, 299 };
RECT drawArea3 = { 701, 101, 1100, 199 };
RECT drawArea4 = { 101, 1, 500, 99 };
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

 //------------------------------------------------------------------------funkcje
void postoj();
void poruszanie_w_gore();
void poruszanie_w_dol();

void MyOnPaint(HDC hdc)
{
	
	
	Graphics graphics(hdc);
	Pen pen(Color(255,0,0,255));
	SolidBrush Brush(Color(255, 0, 0, 0));
	
	//------------------------------------------------------------------rysowanie pi�ter
	for (int i = 0; i <= lb_pieter; i++)
	{
		if (i == 0 || i == lb_pieter)
			graphics.DrawLine(&pen, 0, i * h_pietra, 2 * winda.l_d_corner_x + winda.width, i * h_pietra);
		else
		{
			graphics.DrawLine(&pen, winda.l_d_corner_x + winda.width +1, i * h_pietra, 2 * winda.l_d_corner_x + winda.width, i * h_pietra);
			graphics.DrawLine(&pen, 0, i * h_pietra, winda.l_d_corner_x - 1, i * h_pietra);
		}
		if (i % 2 == 0)
			graphics.DrawLine(&pen, winda.l_d_corner_x + winda.width + 1, i * h_pietra, winda.l_d_corner_x + winda.width + 1, (i + 1) * h_pietra);
		else  if (i < lb_pieter)
			graphics.DrawLine(&pen, winda.l_d_corner_x - 1, i * h_pietra, winda.l_d_corner_x - 1, (i + 1) * h_pietra);
	}
	//------------------------------------------------------------------------------------rysowanie ludzi na pi�trach
	for (int j = 0; j <lb_pieter; j++)
	{
		for (int i = 0; i < pietra_tab[j].ludzie.size(); i++)
		{
			SolidBrush Brush(Color((pietra_tab[j].ludzie[i].cel+1) * 50, 0, 0, pietra_tab[j].ludzie[i].cel * 200));
			if (j % 2 == 0)
				graphics.FillRectangle(&Brush, 450 - (i * 21), (5 - j)*h_pietra - 60, 20, 50);
			else
				graphics.FillRectangle(&Brush, 750 + (i * 21), (5 - j)*h_pietra - 60, 20, 50);
		}
	}
	//-------------------------------------------------------------------------------------rysowanie ludzi w windzie
	for (int i = 0;i < winda.ludzie.size();i++)
	{
		SolidBrush Brush(Color((winda.ludzie[i].cel+1) * 50, 0, 0, winda.ludzie[i].cel*200));
		graphics.FillRectangle(&Brush, winda.l_d_corner_x + (i * 21) +20 , winda.l_d_corner_y - value+winda.height-50, 20, 50);
	}


	//-------------------------------------------------------------------------------------obs�uga windy 
	int lb_wsiadajacych = 0;

	if (value < winda.cel_1*h_pietra)
		poruszanie_w_gore();

	else if (value > winda.cel_1*h_pietra)
		poruszanie_w_dol();

	else //value == winda.cel_1*h_pietra
	{
		
		postoj();
		graphics.DrawRectangle(&pen, winda.l_d_corner_x, winda.l_d_corner_y - value, winda.width, winda.height);
		Sleep(500);//zatrzymanie windy na pietrze
	}
	graphics.DrawRectangle(&pen, winda.l_d_corner_x, winda.l_d_corner_y - value, winda.width, winda.height);
}

void poruszanie_w_gore()
{
	if (winda.ludzie.size() != winda.max_lb)
	{

		if (value / h_pietra + 1 < lb_pieter)//value/h_pietra+1
		{
			for (int i = 0; i < pietra_tab[value / h_pietra + 1].ludzie.size(); i++)
			{
				if (/*pietra_tab[value / h_pietra + 1].ludzie[i].cel <= winda.cel &&*/ pietra_tab[value / h_pietra + 1].ludzie[i].cel > value / h_pietra)
				{
					winda.cel_1 = value / h_pietra + 1;
				}
			}
		}
	}
	for (int i = 0; i < winda.ludzie.size(); i++)
	{
		if (winda.ludzie[i].cel == value / h_pietra + 1)
		{
			winda.cel_1 = value / h_pietra + 1;
		}
	}

	value++;
}

void poruszanie_w_dol()
{

	if (winda.ludzie.size() != winda.max_lb)
	{
		if (value / h_pietra > 0)//value/h_pietra+1
		{
			for (int i = 0; i < pietra_tab[value / h_pietra].ludzie.size(); i++)
			{
				if (/*pietra_tab[value / h_pietra].ludzie[i].cel >= winda.cel &&*/ pietra_tab[value / h_pietra].ludzie[i].cel < value / h_pietra)
				{
					winda.cel_1 = value / h_pietra;
				}
			}
		}
	}
	for (int i = 0; i < winda.ludzie.size(); i++)
	{
		if (winda.ludzie[i].cel == value / h_pietra)
		{
			winda.cel_1 = value / h_pietra;
		}
	}

	value--;
}

void postoj()
{

	int rozmiar = winda.ludzie.size();
	int lb_wsiadajacych = 0;
	//--------------------------------------------------------------------------------usuwanie ludzi z windy
	for (int i = 0; i < rozmiar; )
	{
		i++;
		if (winda.ludzie[i - 1].cel == winda.cel_1)
		{
			winda.ludzie.erase(winda.ludzie.begin() + i - 1);
			i = 0;
		}

		rozmiar = winda.ludzie.size();
	}

	int rozmiar_1 = pietra_tab[winda.cel_1].ludzie.size();
	bool czy_max = (winda.max_lb == winda.ludzie.size()) ? true : false;//czy osiagnieto max liczbe osob w windzie

	//-----------------------------  ----------------------------------------------nadawanie celu windy              
	if (rozmiar_1 != 0)
	{
		if (dane.size() == 0)
		{
			winda.cel = pietra_tab[winda.cel_1].ludzie[0].cel;
		}
		else if ((value == winda.cel*h_pietra && value == dane[0].nr_pietra_p*h_pietra))
		{
			winda.cel = pietra_tab[winda.cel_1].ludzie[0].cel;
		}
		else if (value == winda.cel*h_pietra && value != dane[0].nr_pietra_p*h_pietra/*chyba niepotrzebny "!= dane[0].nr_pietra_p*h_pietra" */)
		{
			winda.cel = dane[0].nr_pietra_p;
		}
		else if (value == winda.cel*h_pietra)
		{
			winda.cel = pietra_tab[winda.cel_1].ludzie[0].cel;
		}

	}

	//-----------------------------------------

	if (rozmiar != 0)//-------------------------------------
		winda.cel = winda.ludzie.front().cel;//odwolanie do celu pierwszego elementu// nie obsluguje przypadku, gdy najpierw ktos(czl_1) wezwie
											 //-------------------------------------------------------------------------------dodawanie ludzi do windy i usuwanie z pi�ter
	for (int i = 0; i < rozmiar_1 && !czy_max; i++)
	{
		if (!czy_max /*&& pietra_tab[winda.cel_1].ludzie[i].cel <= winda.cel */&& pietra_tab[winda.cel_1].ludzie[i].cel > winda.cel_1 && winda.cel >= winda.cel_1)
		{
			winda.ludzie.push_back(pietra_tab[winda.cel_1].ludzie[i]);
			pietra_tab[winda.cel_1].ludzie.erase(pietra_tab[winda.cel_1].ludzie.begin() + i);
			lb_wsiadajacych++;
			i--;
		}
		else if (!czy_max /*&& pietra_tab[winda.cel_1].ludzie[i].cel >= winda.cel */ && pietra_tab[winda.cel_1].ludzie[i].cel < winda.cel_1 && winda.cel <= winda.cel_1)
		{
			winda.ludzie.push_back(pietra_tab[winda.cel_1].ludzie[i]);
			pietra_tab[winda.cel_1].ludzie.erase(pietra_tab[winda.cel_1].ludzie.begin() + i);
			lb_wsiadajacych++;
			i--;
		}
		czy_max = (winda.max_lb == winda.ludzie.size()) ? true : false;
		rozmiar_1 = pietra_tab[winda.cel_1].ludzie.size();
	}


	int rozmiar_dane = dane.size();
	//---------------------------------------------------------------------usuwanie z kolejki
	for (int i = 0; i < rozmiar_dane && lb_wsiadajacych > 0; i++)
	{
		if (dane[i].nr_pietra_p == winda.cel_1)//natrafilismy na podroznika, ktory jest na rozpatrywanym pietrze
		{
			if (/*dane[i].nr_pietra_d <= winda.cel  &&*/ winda.cel >= winda.cel_1)
			{
				dane.erase(dane.begin() + i);
				lb_wsiadajacych--;
				i--;
			}
			else if (/*dane[i].nr_pietra_d >= winda.cel  &&*/ winda.cel <= winda.cel_1)
			{
				dane.erase(dane.begin() + i);
				lb_wsiadajacych--;
				i--;
			}
		}
		rozmiar_dane = dane.size();
	}

	if (value == winda.cel_1*h_pietra && winda.ludzie.size() == 0 && dane.size() != 0) //gdy jestesmy napietrze cel_1, w windzie nikogo nie ma, a w kolejce tak, to cel jest ustawiany na polozenie 1 w kolejce						
	{																					// winda.cel_1*h_pietra - aktualne polozenie windy
		winda.cel = dane[0].nr_pietra_p;
	}


	rozmiar = winda.ludzie.size();
	if (rozmiar != 0)//-------------------------------------
		winda.cel = winda.ludzie.front().cel;//odwolanie do celu pierwszego elementu// nie obsluguje przypadku, gdy najpierw ktos(czl_1) wezwie
											 // winde, a po drodze ktos(czl_2) wsiadzie i bedzie chcial jechac w innym kierunku
											 //zrobic najlepiej tak, ze jesli chce jechac w dol to winda sie nie zatrzyma
											 // co jesli czl_2 bedzie chcial jechac wyzej niz czl_1??

	winda.cel_1 = winda.cel;
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
       
   HWND hwndButton = CreateWindow(TEXT("button"),//pietro 4
	   TEXT("0"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   20, 20,
	   20,20,
	   hWnd,
	   (HMENU)ID_BUTTON1,
	   hInstance,
	   NULL);
    hwndButton = CreateWindow(TEXT("button"),//pietro 4
	   TEXT("1"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   40, 20,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON2,
	   hInstance,
	   NULL);
    hwndButton = CreateWindow(TEXT("button"),//pietro 4
	   TEXT("2"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   60, 20,
	   20, 20,
	   hWnd,
	   (HMENU)ID_BUTTON3,
	   hInstance,
	   NULL);
    hwndButton = CreateWindow(TEXT("button"),//pietro 4
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
			pietra_tab[4].ludzie.push_back({ waga_os, 0 });
			InvalidateRect(hWnd, &drawArea4, TRUE);
			dane.push_back({ 4,0 });
			break;
		case ID_BUTTON2:
			pietra_tab[4].ludzie.push_back({ waga_os, 1 });
			InvalidateRect(hWnd, &drawArea4, TRUE);
			dane.push_back({ 4,1 });
			break;
		case ID_BUTTON3:
			pietra_tab[4].ludzie.push_back({ waga_os, 2 });
			InvalidateRect(hWnd, &drawArea4, TRUE);
			dane.push_back({ 4,2 });
			break;
		case ID_BUTTON4:
			pietra_tab[4].ludzie.push_back({ waga_os, 3 });
			InvalidateRect(hWnd, &drawArea4, TRUE);
			dane.push_back({ 4,3 });
			break;
		//pietro 3
		case ID_BUTTON5:
			pietra_tab[3].ludzie.push_back({ waga_os, 0 });
			InvalidateRect(hWnd, &drawArea3, TRUE);
			dane.push_back({ 3,0 });
			break;
		case ID_BUTTON6:
			pietra_tab[3].ludzie.push_back({ waga_os, 1 });
			InvalidateRect(hWnd, &drawArea3, TRUE);
			dane.push_back({ 3,1 });
			break;
		case ID_BUTTON7:
			pietra_tab[3].ludzie.push_back({ waga_os, 2 });
			InvalidateRect(hWnd, &drawArea3, TRUE);
			dane.push_back({ 3,2 });
			break;
		case ID_BUTTON8:
			pietra_tab[3].ludzie.push_back({ waga_os, 4 });
			InvalidateRect(hWnd, &drawArea3, TRUE);
			dane.push_back({ 3,4 });
			break;
		//pietro 2
		case ID_BUTTON9:
			pietra_tab[2].ludzie.push_back({ waga_os, 0 });
			InvalidateRect(hWnd, &drawArea2, TRUE);
			dane.push_back({ 2,0 });
			break;
		case ID_BUTTON10:
			pietra_tab[2].ludzie.push_back({ waga_os, 1 });
			InvalidateRect(hWnd, &drawArea2, TRUE);
			dane.push_back({ 2,1 });
			break;
		case ID_BUTTON11:
			pietra_tab[2].ludzie.push_back({ waga_os, 3 });
			InvalidateRect(hWnd, &drawArea2, TRUE);
			dane.push_back({ 2,3 });
			break;
		case ID_BUTTON12:
			pietra_tab[2].ludzie.push_back({ waga_os, 4 });
			InvalidateRect(hWnd, &drawArea2, TRUE);
			dane.push_back({ 2,4 });
			break;
		//pietro 1
		case ID_BUTTON13:
			pietra_tab[1].ludzie.push_back({ waga_os, 0 });
			InvalidateRect(hWnd, &drawArea1, TRUE);
			dane.push_back({ 1,0 });
			break;
		case ID_BUTTON14:
			pietra_tab[1].ludzie.push_back({ waga_os, 2 });
			InvalidateRect(hWnd, &drawArea1, TRUE);
			dane.push_back({ 1,2 });
			break;
		case ID_BUTTON15:
			pietra_tab[1].ludzie.push_back({ waga_os, 3 });
			InvalidateRect(hWnd, &drawArea1, TRUE);
			dane.push_back({ 1,3 });
			break;
		case ID_BUTTON16:
			pietra_tab[1].ludzie.push_back({ waga_os, 4 });
			InvalidateRect(hWnd, &drawArea1, TRUE);
			dane.push_back({ 1,4 });
			break;
		//parter
		case ID_BUTTON17:
			pietra_tab[0].ludzie.push_back({ waga_os, 1 });
			InvalidateRect(hWnd, &drawArea0, TRUE);
			dane.push_back({ 0,1 });
			break;
		case ID_BUTTON18:
			pietra_tab[0].ludzie.push_back({ waga_os, 2 });
			InvalidateRect(hWnd, &drawArea0, TRUE);
			dane.push_back({ 0,2 });
			break;
		case ID_BUTTON19:
			pietra_tab[0].ludzie.push_back({ waga_os, 3 });
			InvalidateRect(hWnd, &drawArea0, TRUE);
			dane.push_back({ 0,3 });
			break;
		case ID_BUTTON20:
			pietra_tab[0].ludzie.push_back({ waga_os, 4 });
			InvalidateRect(hWnd, &drawArea0, TRUE);
			dane.push_back({ 0,4 });
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
				InvalidateRect(hWnd, &drawArea, TRUE);
					switch (value)
					{
					case 0: 
					case 1: InvalidateRect(hWnd, &drawArea0, TRUE); break;
					case 99:
					case 100:
					case 101:InvalidateRect(hWnd, &drawArea1, TRUE); break;
					case 199:
					case 200:
					case 201:InvalidateRect(hWnd, &drawArea2, TRUE); break;
					case 299:
					case 300:
					case 301:InvalidateRect(hWnd, &drawArea3, TRUE); break;
					case 399:
					case 400:InvalidateRect(hWnd, &drawArea4, TRUE); break;
					default: break;
					}
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
