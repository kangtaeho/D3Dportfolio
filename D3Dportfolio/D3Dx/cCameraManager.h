#pragma once

#define g_pCameraManager cCameraManager::GetInstance()

class cCameraManager
{
	SINGLETONE(cCameraManager);

private:
	D3DXVECTOR3 m_vEye;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3 m_vLookAt;

	float m_fRotX;
	float m_fRotY;

	float m_fDistance;

	POINT m_ptPrevMouse;

	bool m_isRButtonDown;

public:

	void Setup();
	void Update();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
};

