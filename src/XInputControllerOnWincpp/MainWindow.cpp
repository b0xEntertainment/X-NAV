#include <string>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <ctime>
#include "MainWindow.h"
#include "resource.h"

#define IDC_MAIN_BUTTON	101			
#define IDC_MAIN_EDIT	102




MainWindow* _wndInstance;



static LRESULT CALLBACK BtnMsgProc(int iCode, WPARAM wParam, LPARAM lParam)
{
	if ((iCode == HC_ACTION) && (wParam == PM_REMOVE))
	{


		MSG *msg = reinterpret_cast<MSG*>(lParam);

		if (reinterpret_cast<HWND>(msg->hwnd) == _wndInstance->GetBtnHWND() && msg->message == 514)
		{
		
           _wndInstance->ToggleLoop();
			return CallNextHookEx(_wndInstance->GetBtnHook(), iCode, wParam, lParam);
		}

	}
}



static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (_wndInstance->GetWndHWND() == hwnd)
		cout << "same surprise" << endl;

	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		exit(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	/*case WM_CREATE:
	{     
		
	}
		break;*/
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
const char mWindDescr[] = "BINDINGS:\r\n\r\nThumbstick Left: Move mouse\r\nRB + Thumbstick Left: Move mouse fast\r\nLB + Thumbstick Left: Move mouse slow\r\n\nThumbstick Right: Scroll mouse wheel\r\nRB + Thumbstick Right: Scroll fast\r\nLB + Thumbstick Right: Scroll slow\r\n\nRT: Left Click\r\nLT: Right Click\r\n\nY: Close current window\r\nX: Go to desktop (minimize all)\r\nA: Send ENTER (keyboard)\r\nB: Minimize current window\r\n\nStart: Open Manager Window (this window)\r\nBack: Exit program";





void MainWindow::Init(HINSTANCE &hinstance, int nCmdShow)
{
	_tRunning = false;
	_wndInstance = this;
	const char g_szClassName[] = "WindowClass";
	
    WNDCLASSEX wc;
	
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;

	// window title icon
	wc.hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	// task bar icon
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// Step 2: Creating the Window
	_wndHwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"X-NAV",
		WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX, // no maximize box
		CW_USEDEFAULT, CW_USEDEFAULT, 450, 500,
		NULL, NULL, hinstance, NULL);


	if (_wndHwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	ShowWindow(_wndHwnd, nCmdShow);
	UpdateWindow(_wndHwnd);

	
	_wndInstance->CreateWndContent();
	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{ 
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	
	/*return Msg.wParam;*/
}

void MainWindow::CreateWndContent()
{
	
	_btn = CreateWindowEx(NULL,
		"BUTTON",
		"Start",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
		130,
		400,
		150,
		50,
		_wndHwnd,
		(HMENU)IDC_MAIN_BUTTON,
		GetModuleHandle(NULL),
	NULL);

	

	HWND hWndLabel = CreateWindowEx(NULL,
		"STATIC",
		mWindDescr,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_EX_LEFT | BS_LEFTTEXT,
		50,
		50,
		300,
		330,
		_wndHwnd,
		(HMENU)IDC_MAIN_EDIT,
		GetModuleHandle(NULL),
		NULL);

	_btnHook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)BtnMsgProc, NULL, GetCurrentThreadId());
}

 const HWND MainWindow::GetWndHWND()
{
	return _wndHwnd;
}

const HWND MainWindow::GetBtnHWND()
{
	return _btn;
}

const HHOOK MainWindow::GetBtnHook()
{
	return _btnHook;
}

void MainWindow::ToggleLoop()
{
	

	if (_tRunning)
	{
		_execute->KillMe();
		SetWindowText(_btn, "Start");
	}
	else
	{
		_execute->Reset();
	    _tPtr = new thread(&Execute::Run, _execute);
        SetWindowText(_btn, "Stop");
	}

	_tRunning = !_tRunning;
}

MainWindow::~MainWindow()
{
	delete _execute;
}




