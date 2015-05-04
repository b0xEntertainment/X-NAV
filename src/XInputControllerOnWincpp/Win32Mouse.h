#ifndef Win32Mouse_H
#define Win32Mouse_H


class Win32Mouse
{


private:
	float _posSaveX;
	float _posSaveY;

public:
	void LeftClick();
	void RightClick();
	void LeftClickUp();
	void RightClickUp();
	void LeftClickDown();
	void RightClickDown();


	void SetPos(int x, int y);
	void AddPos(float x, float y);
	void AddPosX(float x);
	void AddPosY(float y);
	void SetDelta(DWORD amount);

};

#endif