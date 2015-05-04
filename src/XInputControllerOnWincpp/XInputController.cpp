#include "stdafx.h"


	

bool  XInputController::Init(DWORD index)
{
	_lastState = _currentState;
	/*memcpy(&_lastState, &_currentState, sizeof(_currentState));*/
	DWORD dwResult;
	ZeroMemory(&_currentState, sizeof(XINPUT_STATE));
	dwResult = XInputGetState(index, &_currentState);

	return dwResult == ERROR_SUCCESS;
}


	bool XInputController::ButtonDown(WORD btnMask)
	{
		return (_currentState.Gamepad.wButtons & btnMask) == btnMask && (_lastState.Gamepad.wButtons & btnMask) != btnMask;
	
	}

	bool XInputController::ButtonUp(WORD btnMask)
	{
		return (_currentState.Gamepad.wButtons & btnMask) != btnMask && (_lastState.Gamepad.wButtons & btnMask) == btnMask;

	}

	bool XInputController::Button(WORD btnMask)
	{
		return (_currentState.Gamepad.wButtons & btnMask) == btnMask;

	}

	bool XInputController::LeftTriggerDown()
	{
		float t1, t2;
		LeftTrigger(t1,_currentState);
		LeftTrigger(t2, _lastState);
		return t1 != -2 && t2 == -2;
	}

	bool XInputController::RightTriggerDown()
	{
		float t1, t2;
		RightTrigger(t1, _currentState);
		RightTrigger(t2, _lastState);
		return t1 != -2 && t2 == -2;
	}

	bool XInputController::LeftTriggerUp()
	{
		float t1, t2;
		LeftTrigger(t1, _currentState);
		LeftTrigger(t2, _lastState);
		return t1 == -2 && t2 != -2;
	}

	bool XInputController::RightTriggerUp()
	{
		float t1, t2;
		RightTrigger(t1, _currentState);
		RightTrigger(t2, _lastState);
		return t1 == -2 && t2 != -2;
	}

	bool XInputController::LeftTrigger()
	{
		float t = 0;
		LeftTrigger(t);
		return t != -2;
	}

	bool XInputController::RightTrigger()
	{
		float t = 0;
		RightTrigger(t);
		return t != -2;
	}

	void XInputController::LeftTrigger(float &t)
	{
		LeftTrigger(t, _currentState);
	}

	void XInputController::RightTrigger(float &t)
	{
		RightTrigger(t, _currentState);
	}

	void XInputController::LeftTrigger(float &t, XINPUT_STATE state)
	{
		if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			t = state.Gamepad.bLeftTrigger;
		}
		else
			t = -2; // Since -1 is a valid value, -2 means false
	}

	void XInputController::RightTrigger(float &t, XINPUT_STATE state)
	{
		if (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			t = state.Gamepad.bRightTrigger;
		}
		else
			t = -2;
	}

	void XInputController::ThumbStickLeft(float &x, float &y)
	{
	
		ThumbStick(_currentState.Gamepad.sThumbLX, _currentState.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, x, y);
	
	}

	void XInputController::ThumbStickRight(float &x, float &y)
	{
		
		 ThumbStick(_currentState.Gamepad.sThumbRX, _currentState.Gamepad.sThumbRY, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE,x,y);
	
	
	}


	void XInputController::ThumbStick(SHORT lx, SHORT ly, SHORT ld, float &x, float &y)
	{
	

	
	
		//determine the direction the controller is pushed
		float normalizedLX = (1 / (float)32767) * lx;
		float normalizedLY = (1 / (float)32767) * ly;
		float normalizedLD = (1 / (float)32767) * ld;
		

		//cout << normalizedLY << endl;

		if (normalizedLX > 0 && normalizedLX < normalizedLD
			|| normalizedLX < 0 && normalizedLX > -normalizedLD)
			
		{
			// Since -2 isnt a legit value, this means its inside deadzone.
			x = -2;
		
		}
		else x = normalizedLX;

		if (normalizedLY > 0 && normalizedLY < normalizedLD
			|| normalizedLY < 0 && normalizedLY > -normalizedLD)

		{
		
			y = -2;
		
		}
		else
		{
			y = normalizedLY;
			//cout << y << endl;
		}


	
	
	}
