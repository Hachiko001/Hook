// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
HWND hWnd;
HHOOK hMyHook;
HINSTANCE hInstance;

bool winPressed = false;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	hInstance = hModule;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyProc(int nCode, WPARAM wParam, LPARAM lParam);

INT InitMouseHook(HWND hwndYourWindow)
{
	hWnd = hwndYourWindow;
	hMyHook = SetWindowsHookEx(WH_MOUSE, MouseProc, hInstance, 0);
	if (hMyHook != NULL)
	{
		return 1;
	}
	return 0;
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		switch (wParam)
		{
		case WM_RBUTTONDOWN:
			if (IsIconic(hWnd))
			{
				ShowWindow(hWnd, SW_RESTORE);
			}
			else
			{
				ShowWindow(hWnd, SW_MINIMIZE);
			}

			break;
		default:
			break;
		}
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
}

INT InitKeyHook(HWND hwndYourWindow)
{
	hWnd = hwndYourWindow;
	hMyHook = SetWindowsHookEx(WH_KEYBOARD, KeyProc, hInstance, 0);
	if (hMyHook != NULL)
	{
		return 1;
	}
	return 0;
}

LRESULT CALLBACK KeyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION)
	{
		switch (wParam)
		{
		case VK_LWIN:
			winPressed = true;
			break;
		case (VK_F2):
			if (IsIconic(hWnd))
			{
				ShowWindow(hWnd, SW_RESTORE);
			}
			break;
		case (VK_F3):
			if (!IsIconic(hWnd))
			{
				ShowWindow(hWnd, SW_MINIMIZE);
			}
			break;
		/*case (VK_F2&VK_LWIN):
			if (IsIconic(hWnd))
			{
				ShowWindow(hWnd, SW_RESTORE);
			}
			else
			{
				ShowWindow(hWnd, SW_MINIMIZE);
			}
			break;*/
		default:
			break;
		}
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
}

INT UninstallHook()
{
	if (hMyHook != NULL)
	{
		UnhookWindowsHookEx(hMyHook);
		return 1;
	}
	return 0;
}
