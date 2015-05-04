#ifndef MainWindow_H
#define MainWindow_H

#include "stdafx.h"
#include <thread>


class MainWindow

{

private:
	bool _tRunning;
	thread* _tPtr;
	HWND _btn;
    HHOOK _btnHook;
	HWND _wndHwnd;
	Execute* _execute = new Execute(this);
	
	//HINSTANCE _hInstance;
	
	public:
	
	void Init(HINSTANCE &hinstance,int ncmdShow);

	const HWND GetWndHWND();
	const HWND GetBtnHWND();
	const HHOOK GetBtnHook();
	//const HINSTANCE GetHInstance();

	void CreateWndContent();
	void ToggleLoop();
	~MainWindow();
};



#endif