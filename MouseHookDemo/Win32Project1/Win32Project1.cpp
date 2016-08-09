// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"
#include <windowsx.h>
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HINSTANCE hDLL;
HWND hWndMain;

POINT curPos;

static const GUID myGUID =
{ 0xf0e079db, 0xdab3, 0x4a49,{ 0x97, 0x51, 0x95, 0x14, 0xc7, 0x61, 0x84, 0x98 } };
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
VOID getPosProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


VOID AddNotificationIcon();

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
	LoadStringW(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32PROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	hWndMain = hWnd;
	if (!hWnd)
	{
		return FALSE;
	}

	AddNotificationIcon();
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code that uses hdc here...
	getPosProc(hWnd, message, wParam, lParam);
	

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
		case ID_INSTALLHOOK_MOUSE:
		{
			hDLL = LoadLibrary(_T("MouseHookDemo.dll"));
			typedef  int(*proc1) (HWND);
			if (hDLL != NULL)
			{
				proc1 installHookproc = (proc1)GetProcAddress(hDLL, "InitMouseHook");
				if (installHookproc != NULL)
				{
					int rs = installHookproc(hWnd);
					if (rs == 1)
					{
						MessageBox(hWnd, _T("Install hook success"), _T("Info"), MB_OK);
					}
					else
					{
						MessageBox(hWnd, _T("Install hook failed"), _T("Error"), MB_OK);
					}
				}
				else
				{
					MessageBox(hWnd, _T("Get proc failed"), _T("eError"), MB_OK);
				}
			}
			else
			{
				MessageBox(hWnd, _T("Load DLL failed"), _T("Error"), MB_OK);
			}
		}
		break;
		case ID_INSTALLHOOK_KEY:
		{
			hDLL = LoadLibrary(_T("MouseHookDemo.dll"));
			typedef  int(*proc1) (HWND);
			if (hDLL != NULL)
			{
				proc1 installHookproc = (proc1)GetProcAddress(hDLL, "InitKeyHook");
				if (installHookproc != NULL)
				{
					int rs = installHookproc(hWnd);
					if (rs == 1)
					{
						MessageBox(hWnd, _T("Install hook success"), _T("Info"), MB_OK);
					}
					else
					{
						MessageBox(hWnd, _T("Install hook failed"), _T("Error"), MB_OK);
					}
				}
				else
				{
					MessageBox(hWnd, _T("Get proc failed"), _T("eError"), MB_OK);
				}
			}
			else
			{
				MessageBox(hWnd, _T("Load DLL failed"), _T("Error"), MB_OK);
			}
		}
		break;
		case ID_HOOK_UNINSTALLHOOK:
		{
			if (hDLL != NULL)
			{
				typedef void(*proc)();
				proc uninstallHook = (proc)GetProcAddress(hDLL, "UninstallHook");
				if (uninstallHook != NULL)
				{
					uninstallHook();
				}
				FreeLibrary(hDLL);
				MessageBox(hWnd, _T("Hook uninstalled"), _T("Info"), MB_OK);
			}
		}
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		/*WCHAR buffer[20];
		int len = swprintf_s(buffer, 20, L"x: %d\ty: %d", curPos.x, curPos.y);*/
		//TextOut(hdc, 10, 10, buffer, len);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		NOTIFYICONDATA notifyIconData;
		notifyIconData.cbSize = sizeof(notifyIconData);
		notifyIconData.hWnd = hWndMain;
		notifyIconData.uFlags = NIF_GUID;
		notifyIconData.guidItem = myGUID;
		Shell_NotifyIcon(NIM_DELETE, &notifyIconData) ? S_OK : E_FAIL;
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

VOID AddNotificationIcon()
{
	NOTIFYICONDATA notifyIconData;
	notifyIconData.cbSize = sizeof(notifyIconData);
	notifyIconData.hWnd = hWndMain;
	notifyIconData.uFlags = NIF_ICON | NIF_TIP | NIF_GUID;

	notifyIconData.guidItem = myGUID;

	// This text will be shown as the icon's tooltip.
	StringCchCopy(notifyIconData.szTip, ARRAYSIZE(notifyIconData.szTip), L"Test application");

	// Load the icon for high DPI.

	LoadIconMetric(hInst, MAKEINTRESOURCE(IDI_SMALL), LIM_SMALL, &(notifyIconData.hIcon));

	// Show the notification.
	Shell_NotifyIcon(NIM_ADD, &notifyIconData) ? S_OK : E_FAIL;

}

VOID getPosProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = GetDC(hWnd);
	WCHAR buffer[20];
	int len=0;
	switch (message)
	{
	case WM_MOUSEMOVE:
		
		GetCursorPos(&curPos);
		
		len = swprintf_s(buffer, 20, L"x: %d\ty: %d", curPos.x, curPos.y);
		TextOut(hdc, 10, 10, buffer, len);
		UpdateWindow(hWnd);
		break;
	case WM_LBUTTONDOWN:

		TextOut(hdc, 10, 30, _T("Left mouse clicked"), 20);
		UpdateWindow(hWnd);
		break;
	case WM_RBUTTONDOWN:

		TextOut(hdc, 10, 30, _T("Right mouse clicked"), 20);
		UpdateWindow(hWnd);
		break;
	default: 
		break;
	}
}
