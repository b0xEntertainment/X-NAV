
#include <string>
#include <Windows.h>
#include "Win32Mouse.h";


void Win32Mouse::LeftClick()
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, cursorPos.x, cursorPos.y, 0, 0); 
}

void Win32Mouse::RightClick()
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, cursorPos.x, cursorPos.y, 0, 0);
}

void Win32Mouse::LeftClickUp()
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	mouse_event(MOUSEEVENTF_LEFTUP, cursorPos.x, cursorPos.y, 0, 0);
}

void Win32Mouse::RightClickUp()
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	mouse_event(MOUSEEVENTF_RIGHTUP, cursorPos.x, cursorPos.y, 0, 0);
}

void Win32Mouse::LeftClickDown()
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	mouse_event(MOUSEEVENTF_LEFTDOWN, cursorPos.x, cursorPos.y, 0, 0);
}
void Win32Mouse::RightClickDown()
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	mouse_event(MOUSEEVENTF_RIGHTDOWN, cursorPos.x, cursorPos.y, 0, 0);
}

void Win32Mouse::SetPos(int x, int y)
{
	SetCursorPos(x, y); 
}

void Win32Mouse::AddPos(float x, float y)
{
	
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	SetCursorPos(cursorPos.x+ x,cursorPos.y+ y);
}

void Win32Mouse::AddPosX(float x)
{

	POINT cursorPos;
	GetCursorPos(&cursorPos);
	SetCursorPos(cursorPos.x + x, cursorPos.y);
}

void Win32Mouse::AddPosY(float y)
{

	POINT cursorPos;
	GetCursorPos(&cursorPos);
	SetCursorPos(cursorPos.x, cursorPos.y + y);
}

void Win32Mouse::SetDelta(DWORD amount)
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	mouse_event(MOUSEEVENTF_WHEEL, cursorPos.x, cursorPos.y, amount,0);
}

