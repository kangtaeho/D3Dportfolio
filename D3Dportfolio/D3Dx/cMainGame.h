#pragma once

class cCamera;
class cCube;

class cMainGame
{
private:
	cCamera *	m_pCamera;
	cCube *		m_pCube;

public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

