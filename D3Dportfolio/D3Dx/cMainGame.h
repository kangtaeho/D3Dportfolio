#pragma once
#include "cGameNode.h"

class cCamera;
class cCube;

class cMainGame  :public cGameNode
{
private:
	cCamera *	m_pCamera;
	cCube *		m_pCube;

public:
	cMainGame();
	virtual ~cMainGame();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

