// 421_Fractals.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "421_Fractals.h"
#include "DrawBuffer.h"
#include <thread>
#include <mutex>
#include <vector>

#define MAX_LOADSTRING 100

using namespace std;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
std::vector<int> buf1;
std::vector<int> buf2;
std::vector<int> buf3;
std::vector<int> buf4;
bool buf1done = false;
bool buf2done = false;
bool buf3done = false;
bool buf4done = false;
mutex HDCMutex;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY421FRACTALS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY421FRACTALS));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY421FRACTALS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY421FRACTALS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, 1000, 900, nullptr, nullptr, hInstance, nullptr);

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
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
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
        }
        break;
    case WM_PAINT:
        {
			std::vector<int> buffer;
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			HPEN hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			SelectObject(hdc, hpen);
            // TODO: Add any drawing code that uses hdc here...
			drawFractalParallelized(&hdc, 200, 8, 500, 400, 3);
			DeleteObject(hpen);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
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

void drawFractal(HDC* hdc, int len, int depth, int x, int y, DrawBuffer* dbuf)
{
	dbuf->mutex->lock();

	std::vector<int>* buf = &dbuf->buf;

	buf->push_back(x);
	buf->push_back(y);
	buf->push_back(x);
	buf->push_back(y + len);
	buf->push_back(x);
	buf->push_back(y);
	buf->push_back(x + len);
	buf->push_back(y);
	buf->push_back(x);
	buf->push_back(y);
	buf->push_back(x);
	buf->push_back(y - len);
	buf->push_back(x);
	buf->push_back(y);
	buf->push_back(x - len);
	buf->push_back(y);

	dbuf->mutex->unlock();

	len = len / 2;
	if (depth > 0)
	{
		drawFractal(hdc, len, depth - 1, x + len, y, dbuf);
		drawFractal(hdc, len, depth - 1, x - len, y, dbuf);
		drawFractal(hdc, len, depth - 1, x, y + len, dbuf);
		drawFractal(hdc, len, depth - 1, x, y - len, dbuf);
	}
}

void fractalThread(HDC* hdc, int len, int depth, int x, int y, DrawBuffer* dbuf, int pDepth) {
	if(pDepth > 0)
		drawFractalParallelized(hdc, len, depth, x, y, pDepth);
	else
		drawFractal(hdc, len, depth, x, y, dbuf);
	dbuf->done = true;
}

void drawFractalParallelized(HDC* hdc, int len, int depth, int x, int y, int pDepth)
{
	std::vector<DrawBuffer> bufList;
	std::mutex mut1;
	DrawBuffer dbuf1(&mut1);
	bufList.push_back(dbuf1);
	std::mutex mut2;
	DrawBuffer dbuf2(&mut2);
	bufList.push_back(dbuf2);
	std::mutex mut3;
	DrawBuffer dbuf3(&mut3);
	bufList.push_back(dbuf3);
	std::mutex mut4;
	DrawBuffer dbuf4(&mut4);
	bufList.push_back(dbuf4);
	drawFractal(hdc, len, 0, x, y, &bufList[0]);

	pDepth--;
	len = len / 2;
	if (depth > 0)
	{
		std::thread rightBranch(fractalThread, hdc, len, depth - 1, x + len, y, &bufList[0], pDepth);
		std::thread leftBranch(fractalThread, hdc, len, depth - 1, x - len, y, &bufList[1], pDepth);
		std::thread downBranch(fractalThread, hdc, len, depth - 1, x, y + len, &bufList[2], pDepth);
		std::thread upBranch(fractalThread, hdc, len, depth - 1, x, y - len, &bufList[3], pDepth);
		
		drawFromBuffers(hdc, &bufList);
		rightBranch.join();
		leftBranch.join();
		downBranch.join();
		upBranch.join();
	}
}

void drawFromBuffers(HDC* hdc, std::vector<DrawBuffer>* bufList) {
	bool allDone = false;
	while (!allDone)
	{
		allDone = true;
		for (int j = 0; j < bufList->size(); j++)
		{
			DrawBuffer& dbuf = bufList->at(j);

			dbuf.mutex->lock();
			while (dbuf.cursor + 3 < (dbuf.buf.size()))
			{
				HDCMutex.lock();
				MoveToEx(*hdc, dbuf.buf[dbuf.cursor], dbuf.buf[dbuf.cursor + 1], NULL);
				LineTo(*hdc, dbuf.buf[dbuf.cursor + 2], dbuf.buf[dbuf.cursor + 3]);
				dbuf.cursor += 4;
				HDCMutex.unlock();
			}
			if (!dbuf.done)
				allDone = false;
			dbuf.mutex->unlock();
		}
	}
}

/*void drawLeft(HDC* hdc, int len, int depth, int x, int y)
{
	HDCMutex.lock();
	MoveToEx(*hdc, x, y, NULL);
	LineTo(*hdc, x, y + len);
	//MoveToEx(*hdc, x, y, NULL);
	//LineTo(*hdc, x + len, y);
	MoveToEx(*hdc, x, y, NULL);
	LineTo(*hdc, x, y - len);
	MoveToEx(*hdc, x, y, NULL);
	LineTo(*hdc, x - len, y);
	HDCMutex.unlock();

	len = len / 2;
	if (depth > 0)
	{
		//drawRight(hdc, len, depth - 1, x + len, y);
		drawLeft(hdc, len, depth - 1, x - len, y);
		drawUp(hdc, len, depth - 1, x, y + len);
		drawDown(hdc, len, depth - 1, x, y - len);
	}
}

void drawRight(HDC* hdc, int len, int depth, int x, int y)
{
	HDCMutex.lock();
	MoveToEx(*hdc, x, y, NULL);
	LineTo(*hdc, x, y + len);
	MoveToEx(*hdc, x, y, NULL);
	LineTo(*hdc, x + len, y);
	MoveToEx(*hdc, x, y, NULL);
	LineTo(*hdc, x, y - len);
	//MoveToEx(*hdc, x, y, NULL);
	//LineTo(*hdc, x - len, y);
	HDCMutex.unlock();

	len = len / 2;
	if (depth > 0)
	{
		drawRight(hdc, len, depth - 1, x + len, y);
		//drawLeft(hdc, len, depth - 1, x - len, y);
		drawUp(hdc, len, depth - 1, x, y + len);
		drawDown(hdc, len, depth - 1, x, y - len);
	}
}

void drawUp(HDC* hdc, int len, int depth, int x, int y)
{
	HDCMutex.lock();
	MoveToEx(*hdc, x, y, NULL);
	LineTo(*hdc, x, y + len);
	MoveToEx(*hdc, x, y, NULL);
	LineTo(*hdc, x + len, y);
	//MoveToEx(*hdc, x, y, NULL);
	//LineTo(*hdc, x, y - len);
	MoveToEx(*hdc, x, y, NULL);
	LineTo(*hdc, x - len, y);
	HDCMutex.unlock();

	len = len / 2;
	if (depth > 0)
	{
		drawRight(hdc, len, depth - 1, x + len, y);
		drawLeft(hdc, len, depth - 1, x - len, y);
		drawUp(hdc, len, depth - 1, x, y + len);
		//drawDown(hdc, len, depth - 1, x, y - len);
	}
}

void drawDown(HDC* hdc, int len, int depth, int x, int y)
{
	HDCMutex.lock();
	//MoveToEx(*hdc, x, y, NULL);
	//LineTo(*hdc, x, y + len);
	MoveToEx(*hdc, x, y, NULL);
	LineTo(*hdc, x + len, y);
	MoveToEx(*hdc, x, y, NULL);
	LineTo(*hdc, x, y - len);
	MoveToEx(*hdc, x, y, NULL);
	LineTo(*hdc, x - len, y);
	HDCMutex.unlock();

	len = len / 2;
	if (depth > 0)
	{
		drawRight(hdc, len, depth - 1, x + len, y);
		drawLeft(hdc, len, depth - 1, x - len, y);
		//drawUp(hdc, len, depth - 1, x, y + len);
		drawDown(hdc, len, depth - 1, x, y - len);
	}
}
*/
