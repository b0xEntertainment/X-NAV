#ifndef Execute_H
#define Execute_H



typedef enum {
	UNKNOWN = 0,
	CONNECTED = 1,
	DISCONNECTED = 2
} ConnectionState;

class MainWindow; // double reference, cant add both in header..so just let execute know it's there
class Execute
{


private:
	MainWindow* _mWnd;
	ConnectionState _conState;
	XInputController _controller;
	Win32Mouse _mouse;

	

public:
	Execute(MainWindow* mWnd);
	void KillMe();
	void Run();
	void Reset();
	void GetDesktopResolution(int& horizontal, int& vertical);
	~Execute();
};

#endif