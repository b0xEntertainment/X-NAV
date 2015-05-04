#include <string>
#include <Windows.h>
#include <Xinput.h>
#include <chrono>
#include <mutex>
#include "MainWindow.h"
#include "Execute.h"
#define UPDATE_LOOP_FPS 60

mutex mu;
bool kill;
Execute::Execute(MainWindow* mWnd)
	: _mWnd(mWnd)
{
	_conState = UNKNOWN; // Before run is running for the first time, we dont know it.
	 kill = false;
}

void Execute::KillMe()
{
	mu.lock();
	kill = true;
	mu.unlock();
}

void Execute::Reset()
{
	mu.lock();
	kill = false;
	_conState = UNKNOWN;
	mu.unlock();
}

void Execute::Run()
{
	
	

	
     while (!kill)
	{
		 clock_t begin = clock();
		bool newConnected = _controller.Init(0);

		if (!newConnected && _conState == UNKNOWN)
		{
			MessageBox(NULL, "There is no XInput compatible controller connected.", NULL, MB_OK | MB_ICONERROR);
			_mWnd->ToggleLoop();
			return;
		}

	   if (!newConnected && _conState == CONNECTED)
		{  // Controller just got disconnected..stop execution.
		   _mWnd->ToggleLoop();
		
		}
		_conState = newConnected ? CONNECTED : DISCONNECTED;
		

		float x, y;
		_controller.ThumbStickLeft(x, y);

		if (x != 2 || y != 2)
		{
			int mouseSpeed = 15;
			if (_controller.Button(XINPUT_GAMEPAD_RIGHT_SHOULDER))
				mouseSpeed = 50;
			else if (_controller.Button(XINPUT_GAMEPAD_LEFT_SHOULDER))
				mouseSpeed = 6;

			// Mouse speed should be pixel independed. Otherwise its faster when less than 1080p.
			int nX = 1920, nY = 1080;
			int val = 1920 + 1080;

			int rX, rY;
			GetDesktopResolution(rX, rY);
			int rVal = rX + rY;

			mouseSpeed *= (rVal / val);

			if (x != -2)
				_mouse.AddPosX(x * mouseSpeed);

			if (y != -2)
				_mouse.AddPosY(-y * mouseSpeed);
		}
		// LEFT CLICK

		
		if (_controller.RightTriggerDown())
			_mouse.LeftClickDown();
		else if (_controller.RightTriggerUp()) // We also need to handle when its up otherwise it stays pressed..
			_mouse.LeftClickUp();

		// RIGHT CLICK

		if (_controller.LeftTriggerDown())
			_mouse.RightClickDown();
		else if (_controller.LeftTriggerUp()) 
			_mouse.RightClickUp();

		// SCROLL WHEEL

		_controller.ThumbStickRight(x, y);

        if (y != -2)
		{

			int delta = 40;
			float deltaMulp = 1;

			if (_controller.Button(XINPUT_GAMEPAD_RIGHT_SHOULDER))
				deltaMulp = 3;
			else if (_controller.Button(XINPUT_GAMEPAD_LEFT_SHOULDER))
				deltaMulp = 0.33;
		

			_mouse.SetDelta(y*( delta * deltaMulp));
		}

		// BUTTONS
		if (_controller.ButtonDown(XINPUT_GAMEPAD_Y))
		{
			// CLOSE CURRENT WINDOW

			const HWND   hwnd = GetForegroundWindow();
			PostMessage(hwnd, WM_CLOSE, 0, 0);
		}

		else if (_controller.ButtonDown(XINPUT_GAMEPAD_X))
		{
			// GO TO DESKTOP

			const HWND hwnd = FindWindow("Shell_TrayWnd", NULL);

			// 419 == minimize all code!
			SendMessage(hwnd, WM_COMMAND, 419, 0); // Minimize all windows


		}
		else if (_controller.ButtonDown(XINPUT_GAMEPAD_B))
		{
			// Minimize
		
			ShowWindow(_mWnd->GetWndHWND(), SW_MINIMIZE);
		}

		else if (_controller.ButtonDown(XINPUT_GAMEPAD_A))
		{
			// Minimize

			keybd_event(VK_RETURN, 0x9C, 0, 0);
		}

		//else if (_controller.ButtonDown(XINPUT_GAMEPAD_DPAD_RIGHT))
		//{
		//	

		//	keybd_event(VK_TAB, 0x09, 0, 0);
		//}

		//else if (_controller.ButtonDown(XINPUT_GAMEPAD_DPAD_LEFT))
		//{
		//	keybd_event(VK_SHIFT, 0x10, 0, 0);
		//	keybd_event(VK_TAB , 0x09, 0, 0);
		//	/*keybd_event(VK_TAB | VK_SHIFT, 0x09 | 0x10, 0, 0);*/
		//}
		else if (_controller.ButtonDown(XINPUT_GAMEPAD_DPAD_UP))
		{
			
			////ShellExecute(NULL, "open", "C:\\Windows\System32\\osk.exe", NULL, NULL, SW_SHOWDEFAULT);

			//STARTUPINFO si;
			//PROCESS_INFORMATION pi;

			//// set the size of the structures
			//ZeroMemory(&si, sizeof(si));
			//si.cb = sizeof(si);
			//ZeroMemory(&pi, sizeof(pi));

			//// start the program up
			//CreateProcess("osk.exe",   // the path
			//	NULL,        // Command line
			//	NULL,           // Process handle not inheritable
			//	NULL,           // Thread handle not inheritable
			//	FALSE,          // Set handle inheritance to FALSE
			//	0,              // No creation flags
			//	NULL,           // Use parent's environment block
			//	NULL,           // Use parent's starting directory 
			//	&si,            // Pointer to STARTUPINFO structure
			//	&pi);         // Pointer to PROCESS_INFORMATION structure

			////	// Close process and thread handles. 
			////	CloseHandle(pi.hProcess);
			////CloseHandle(pi.hThread);
		}

		else if (_controller.ButtonDown(XINPUT_GAMEPAD_START))
		{
			SetForegroundWindow(_mWnd->GetWndHWND());
		}

		else if (_controller.ButtonDown(XINPUT_GAMEPAD_BACK))
		{
			exit(0);
		}
		clock_t end = clock();
		// 32.333 - "the time the code needed" to have a stable loop.
	    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

		double targetFPS = ((double)1000 / UPDATE_LOOP_FPS);
		Sleep(targetFPS - (elapsed_secs > targetFPS ? 0 : elapsed_secs));
	/*	Sleep(targetFPS);*/
	
	}

	
	
	 // thread runs to end and ends itself
}

void Execute::GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;

	const HWND hDesktop = GetDesktopWindow();

	GetWindowRect(hDesktop, &desktop);

	horizontal = desktop.right;
	vertical = desktop.bottom;
}


Execute::~Execute()
{
	delete _mWnd;
};




