#ifndef XInputController_H
#define XInputController_H



class XInputController
{


private:
	XINPUT_STATE _currentState;
	XINPUT_STATE _lastState;
	void ThumbStick(SHORT lx, SHORT ly, SHORT ld,float &x, float &y);
	void LeftTrigger(float &t, XINPUT_STATE state);
	void RightTrigger(float &t, XINPUT_STATE state);

public:
     bool Init(DWORD index);
	 bool ButtonDown(WORD btnMask);
	 bool ButtonUp(WORD btnMask);
	 bool Button(WORD btnMask);

	 
	 bool LeftTrigger();
	 bool RightTrigger();
	 bool LeftTriggerDown();
	 bool RightTriggerDown();
	 bool LeftTriggerUp();
	 bool RightTriggerUp();
	 void LeftTrigger(float &t);
	 void RightTrigger(float &r);
	

	 void ThumbStickLeft(float &x, float &y);
	 void ThumbStickRight(float &x, float &y);
};

#endif