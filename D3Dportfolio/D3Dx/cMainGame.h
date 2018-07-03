#pragma once
#include "cGameNode.h"
#include "cShop.h"
class cCamera;
class cCube;

class cMainGame  :public cGameNode
{
private:
	cCamera *	m_pCamera;
	cCube *		m_pCube;

	cShop* m_pshop;
public:
	cMainGame();
	virtual ~cMainGame();

	virtual HRESULT Setup();
	virtual void Update();
	virtual void Render();

	void addSprite();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

