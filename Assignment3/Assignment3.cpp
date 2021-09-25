// Matthew Rogers

#include "framework.h"
#include "Assignment3.h"

#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst; // main window handle
WCHAR szTitle[ MAX_LOADSTRING ]; // The title bar text
WCHAR szWindowClass[ MAX_LOADSTRING ]; // the main window class name

// Forward declarations
ATOM my_register_class(HINSTANCE hInstance);
BOOL init_instance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPWSTR lpCmdLine,
                    int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_ASSIGNMENT3, szWindowClass, MAX_LOADSTRING);
	my_register_class(hInstance);

	// Perform application initialization:
	if (!init_instance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	const HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASSIGNMENT3));

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

	return static_cast<int>(msg.wParam);
}


ATOM my_register_class(const HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = WndProc;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hInstance     = hInstance;
	wcex.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASSIGNMENT3));
	wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>((COLOR_WINDOW + 1));
	wcex.lpszMenuName  = MAKEINTRESOURCEW(IDC_ASSIGNMENT3);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

// Create the window
BOOL init_instance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	const HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	                                100, 100, 800, 650, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	HWND hwndAmount = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("test"),
	                                 WS_CHILD | WS_VISIBLE | WS_BORDER, 100, 20, 140, 20, hWnd, NULL, NULL, NULL);

	// testing text input window
	std::string testInput;
	testInput.resize(GetWindowTextLength(hwndAmount) + 1, '\0');
	GetWindowText(hwndAmount, LPWSTR(testInput.c_str()), GetWindowTextLength(hwndAmount) + 1);

	// Testing labels
	HWND label = CreateWindow(TEXT("static"), LPCWSTR(testInput.c_str()), WS_VISIBLE | WS_CHILD, 60, 20, 25, 20, hWnd,
	                          NULL, NULL, NULL);

	// Testing buttons
	HWND testButton = CreateWindow(L"BUTTON", L"Test", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
	                               60, 40, 40, 20, hWnd, (HMENU)IDC_TEST_BUTTON,
	                               (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


// Process windows "messages"
LRESULT CALLBACK WndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
				// Testing button
			case IDC_TEST_BUTTON:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
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
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...
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
// Purely for testing purposes atm
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
