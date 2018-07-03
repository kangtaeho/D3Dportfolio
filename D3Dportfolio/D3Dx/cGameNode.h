#pragma once

class cGameNode
{
private:

public:
	cGameNode();
	virtual ~cGameNode();

	virtual HRESULT Setup();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

