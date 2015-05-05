#include <thread>
#include <Windows.h>
#include "MainWindow.h";


using frame_period = std::chrono::duration<long long, std::ratio<1, 30>>;


void InitWind(HINSTANCE hInstance, int nCmdShow)
{
	MainWindow w;
	w.Init(hInstance, nCmdShow);
}

int  WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	
	
	InitWind(hInstance, nCmdShow);
	

	
	
	
	
	

}
