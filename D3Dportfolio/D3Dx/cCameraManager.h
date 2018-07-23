#pragma once

#define g_pCameraManager cCameraManager::GetInstance()

class cCameraManager
{
	SINGLETONE(cCameraManager);

private:
	SYNTHESIZE(D3DXVECTOR3, m_vEye, CameraEye);
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3 m_vLookAt;

	float m_fRotX;
	float m_fRotY;

	float m_fDistance;

	POINT m_ptPrevMouse;

	bool m_isRButtonDown;

	float m_fCameraPosX;
	float m_fCameraPosZ;

public:


	void Setup();
	void Update();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	
	void MoveWindow();		// 화면이동
};

