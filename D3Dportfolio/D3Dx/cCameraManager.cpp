#include "stdafx.h"
#include "cCameraManager.h"


cCameraManager::cCameraManager()
	: m_vEye(0, 0, -3000)
	, m_vUp(0, 1, 0)
	, m_vLookAt(0, 5100, 0)
	, m_fRotX(0)
	, m_fRotY(0)
	, m_fDistance(3000)
	, m_isRButtonDown(false)
	, m_bIsMoveWindow(false)
	, m_fCameraPosX(0)
	, m_fCameraPosZ(0)
{
}


cCameraManager::~cCameraManager()
{
}

void cCameraManager::Setup()
{
	// 컴포넌트오브젝트를 생성할라면 디바이쓰를 서야한다고 말함.

	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH(&matProj,
		D3DX_PI / 8.0f,
		rc.right / (float)rc.bottom,
		1.0f,
		100000.0f);//1. 받아올것 2.시야각

	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

}

void cCameraManager::Update()
{
	MoveWindow();

	m_fRotX = D3DX_PI / 4;

	D3DXMATRIX matRotX;
	D3DXMatrixRotationX(&matRotX, m_fRotX);

	D3DXMATRIX matRotY;
	D3DXMatrixRotationY(&matRotY, m_fRotY);

	m_vEye = D3DXVECTOR3(0, 0, -m_fDistance);

	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &(matRotX*matRotY));

	m_vLookAt = D3DXVECTOR3(m_fCameraPosX, 5100, m_fCameraPosZ);
	m_vEye = m_vLookAt + m_vEye;

	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

}

void cCameraManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	// case WM_RBUTTONDOWN:
	// {
	// 	m_ptPrevMouse.x = LOWORD(lParam);
	// 	m_ptPrevMouse.y = HIWORD(lParam);
	// 	m_isRButtonDown = true;
	// }
	// break;
	// case WM_RBUTTONUP:
	// {
	// 	m_isRButtonDown = false;
	// }
	// break;
	// case WM_MOUSEMOVE:
	// {
	// 	if (m_isRButtonDown)
	// 	{
	// 		POINT ptCurrMouse;
	// 		ptCurrMouse.x = LOWORD(lParam);
	// 		ptCurrMouse.y = HIWORD(lParam);
	// 
	// 		m_fRotY += (ptCurrMouse.x - m_ptPrevMouse.x) / 100.0f;
	// 		m_fRotX += (ptCurrMouse.y - m_ptPrevMouse.y) / 100.0f;
	// 
	// 		// X축 회전은 위아래 90도 제한한다.
	// 		if (m_fRotX <= -D3DX_PI * 0.5f + FLT_EPSILON)
	// 			m_fRotX = -D3DX_PI * 0.5f + FLT_EPSILON;
	// 		else if (m_fRotX >= D3DX_PI * 0.5f + FLT_EPSILON)
	// 			m_fRotX = D3DX_PI * 0.5f + FLT_EPSILON;
	// 
	// 		m_ptPrevMouse = ptCurrMouse;
	// 	}
	// }
	// break;
	case WM_MOUSEWHEEL:
	{
		m_fDistance -= GET_WHEEL_DELTA_WPARAM(wParam) * 2.0f;
	}
	break;
	}

}

void cCameraManager::MoveWindow()
{
	if (!m_bIsMoveWindow) return;

	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	if (ptMouse.x <= 20)
	{
		m_fCameraPosX -= 20.0f;
	}
	else if(ptMouse.x>=WINSIZEX-20)
	{
		m_fCameraPosX += 20.0f;
	}


	if (ptMouse.y <= 20)
	{
		m_fCameraPosZ += 20.0f;
	}
	else if (ptMouse.y>=WINSIZEY-20)
	{
		m_fCameraPosZ -= 20.0f;
	}
}
