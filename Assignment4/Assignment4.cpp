// Matthew Rogers
// 10/03/2021
// Assignment 4 - coin conversion
// Spiced up with the Win32 API to add a GUI
// Given that the options are selected via radio buttons, there
// is no way to select an "invalid option" I hope that's okay

#include "framework.h"
#include "Assignment4.h"
#include "MoneyCalculator.h"

#include <string>

// Maximum buffer of characters for win32 resource strings
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst; // main window handle
WCHAR szTitle[ MAX_LOADSTRING ]; // The title bar text
WCHAR szWindowClass[ MAX_LOADSTRING ]; // the main window class name

HWND gTextBoxCents; // text box to enter the amount of cents

// radio buttons
HWND gRadioButtonNickels;
HWND gRadioButtonDimes;
HWND gRadioButtonQuarters;

// The button to make the magic happen
HWND gButtonCalc;

// Forward declarations
ATOM my_register_class(HINSTANCE hInstance);
BOOL init_instance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

// Main function for a win32 app with my current project set up
int WINAPI wWinMain(HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPWSTR lpCmdLine,
                    int nCmdShow)
{
	// normally I'd just use [[maybe_unused]] but I am currently using c++14 instead of 17 or 20,
	// as I'm not sure which you actually prefer students using
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_ASSIGNMENT4, szWindowClass, MAX_LOADSTRING);
	my_register_class(hInstance);

	// Perform application initialization:
	if (!init_instance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	// Enables keyboard short cuts defined in the resources file.
	// In this case, Alt+? brings up the little about window
	// Alt+c is the short cut for the calculate button
	const HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASSIGNMENT4));

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


// sets up window flags and registers its class
ATOM my_register_class(const HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = WndProc;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hInstance     = hInstance;
	wcex.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASSIGNMENT4));
	wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>((COLOR_WINDOW));
	wcex.lpszMenuName  = MAKEINTRESOURCEW(IDC_ASSIGNMENT4);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

// Create the window
BOOL init_instance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	const HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	                                800, 400, 400, 350, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	// Create gui elements

	// Testing labels
	HWND label = CreateWindow(TEXT("static"), L"Enter Cents:", WS_VISIBLE | WS_CHILD, 10, 20, 100, 20, hWnd,
	                          NULL, hInstance, NULL);

	gTextBoxCents = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), TEXT("100"),
	                               WS_CHILD | WS_VISIBLE | WS_BORDER,
	                               100, 20, 140, 20,
	                               hWnd, NULL, hInstance, NULL);

	UINT radioX = 30;
	UINT radioY = 80;

	gRadioButtonNickels = CreateWindowEx(0, TEXT("BUTTON"), TEXT("Nickels"),
	                                     WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
	                                     radioX, radioY, 150, 30,
	                                     hWnd, (HMENU) IDC_RADIO_NICKELS, hInstance, NULL);

	gRadioButtonDimes = CreateWindowEx(0, TEXT("BUTTON"), TEXT("Dimes"),
	                                   WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
	                                   radioX, radioY + 40, 150, 30,
	                                   hWnd, (HMENU) IDC_RADIO_DIMES, hInstance, NULL);

	gRadioButtonQuarters = CreateWindowEx(0, TEXT("BUTTON"), TEXT("Quarters"),
	                                      WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
	                                      radioX, radioY + 80, 150, 30,
	                                      hWnd, (HMENU) IDC_RADIO_QUARTERS, hInstance, NULL);

	// makes the nickels button be enabled by default
	SendDlgItemMessage(hWnd, IDC_RADIO_NICKELS, BM_SETCHECK, 1, 0); // enables


	gButtonCalc = CreateWindowEx(0, TEXT("BUTTON"), TEXT("Calculate"),
	                             WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
	                             60, 40, 80, 30, hWnd, (HMENU) IDC_CALCULATOR_BUTTON,
	                             hInstance, NULL);

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
			case IDC_CALCULATOR_BUTTON:
				{
					std::wstring testInput;
					testInput.resize(GetWindowTextLength(gTextBoxCents) + 1, '\0');
					GetWindowText(gTextBoxCents, LPWSTR(testInput.c_str()), GetWindowTextLength(gTextBoxCents) + 1);
					
					// TODO: Convert textInput to float and convert to selected option
					// Actually on second thought, you can't have a fraction of a coin

					const int numCents = std::stoi(testInput); // should go ahead and just convert inputted floats to ints
					const MoneyCalculator calc(numCents);
					std::string stringified;
					if (SendDlgItemMessage(hWnd, IDC_RADIO_NICKELS, BM_GETCHECK, 0, 0))
					{
						stringified = std::to_string(calc.getNickels()) + " Nickels";
					}else if (SendDlgItemMessage(hWnd, IDC_RADIO_DIMES, BM_GETCHECK, 0, 0))
					{
						stringified = std::to_string(calc.getDimes()) + " Dimes";
					}else if (SendDlgItemMessage(hWnd, IDC_RADIO_QUARTERS, BM_GETCHECK, 0, 0))
					{
						stringified = std::to_string(calc.getQuarters()) + " Quarters";
					}

					std::wstring wideStr = std::wstring(stringified.begin(), stringified.end());
					const wchar_t* showableText = wideStr.c_str();
					
					MessageBox(nullptr, showableText, L"Results", MB_OK | MB_ICONINFORMATION);
				}
				break;

				// Radio buttons. When one is clicked, disable the others and enable that one
			case IDC_RADIO_NICKELS:
				{
					switch (HIWORD(wParam))
					{
					case BN_CLICKED:
						if (SendDlgItemMessage(hWnd, IDC_RADIO_NICKELS, BM_GETCHECK, 0, 0) == 0)
						{
							SendDlgItemMessage(hWnd, IDC_RADIO_NICKELS, BM_SETCHECK, 1, 0); // enables
							SendDlgItemMessage(hWnd, IDC_RADIO_DIMES, BM_SETCHECK, 0, 0); // disables
							SendDlgItemMessage(hWnd, IDC_RADIO_QUARTERS, BM_SETCHECK, 0, 0);
						}
						break;
					}
				}
				break;
			case IDC_RADIO_DIMES:
				{
					switch (HIWORD(wParam))
					{
					case BN_CLICKED:
						if (SendDlgItemMessage(hWnd, IDC_RADIO_DIMES, BM_GETCHECK, 0, 0) == 0)
						{
							SendDlgItemMessage(hWnd, IDC_RADIO_NICKELS, BM_SETCHECK, 0, 0);
							SendDlgItemMessage(hWnd, IDC_RADIO_DIMES, BM_SETCHECK, 1, 0);
							SendDlgItemMessage(hWnd, IDC_RADIO_QUARTERS, BM_SETCHECK, 0, 0);
						}
						break;
					}
				}
				break;
			case IDC_RADIO_QUARTERS:
				{
					switch (HIWORD(wParam))
					{
					case BN_CLICKED:
						if (SendDlgItemMessage(hWnd, IDC_RADIO_QUARTERS, BM_GETCHECK, 0, 0) == 0)
						{
							SendDlgItemMessage(hWnd, IDC_RADIO_NICKELS, BM_SETCHECK, 0, 0);
							SendDlgItemMessage(hWnd, IDC_RADIO_DIMES, BM_SETCHECK, 0, 0);
							SendDlgItemMessage(hWnd, IDC_RADIO_QUARTERS, BM_SETCHECK, 1, 0);
						}
						break;
					}
				}
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
// Might leave in, because why not?
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
