#include "stdafx.h"
#include "cController.h"
#include "cCollisionMap.h"

cController::cController()
	: m_vOriginal(0, 0, 0)
	, m_vDirection(0, 0, 1.0f)
	, m_vControlPos(NULL)
	, m_pCM(NULL)
{
}


cController::~cController()
{
}

HRESULT cController::Setup()
{
	return E_NOTIMPL;
}

void cController::Release()
{
}

void cController::Update()
{
	Check2DMousePointer();
}

void cController::Render()
{
	// �׽�Ʈ��
	g_pFontManager->TextFont(m_ptMouse.x, m_ptMouse.y, "%0.2f, %0.2f", (float)m_ptMouse.x, (float)m_ptMouse.y);
}

void cController::Check2DMousePointer()
{
	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);
}

void cController::Check3DMousePointer()
{
	if (!m_pCM) return;
}

void cController::MouseAtWorldSpace()
{
	D3DVIEWPORT9 viewPort;
	g_pD3DDevice->GetViewport(&viewPort);	// ����Ʈ ������

	D3DXMATRIX matProjection;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);	// �������� ������

	D3DXVECTOR3 vDir(0, 0, 1);
	vDir.x = ((2.0f*m_ptMouse.x) / viewPort.Width - 1.0f) / matProjection._11;
	vDir.y = ((-2.0f*m_ptMouse.y) / viewPort.Height + 1.0f) / matProjection._22;

	D3DXMATRIX matInView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matInView);
	D3DXMatrixInverse(&matInView, 0, &matInView);

	D3DXVec3TransformCoord(&m_vOriginal, &m_vOriginal, &matInView);

	D3DXVec3TransformNormal(&vDir, &vDir, &matInView);
	D3DXVec3Normalize(&vDir, &vDir);
	m_vDirection = vDir;

}
