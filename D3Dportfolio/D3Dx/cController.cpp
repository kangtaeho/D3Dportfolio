#include "stdafx.h"
#include "cController.h"
#include "cCollisionMap.h"

cController::cController()
	: m_vOriginal(0, 0, 0)
	, m_vDirection(0, 0, 1.0f)
	, m_vMousePos(0,0,0)
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
	MouseAtWorldSpace();
	Check3DMousePointer();
}

void cController::Render()
{
	// 테스트용
	g_pFontManager->TextFont(m_ptMouse.x, m_ptMouse.y, "2D : %0.2f, %0.2f", (float)m_ptMouse.x, (float)m_ptMouse.y);
	g_pFontManager->TextFont(m_ptMouse.x, m_ptMouse.y+20, "3D : %0.2f, %0.2f, %0.2f", (float)m_vMousePos.x, (float)m_vMousePos.y, (float)m_vMousePos.z);
}

void cController::Check2DMousePointer()
{
	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);
}

void cController::Check3DMousePointer()
{
	if (!m_pCM) return;

	float pU = 0;
	float pV = 0;

	int a = m_pCM->getMap()->size();

	for (int i = 0; i < m_pCM->getMap()->size(); i+=3)
	{
		D3DXVECTOR3 d = (*m_pCM->getMap())[i];
		if (D3DXIntersectTri(&(*m_pCM->getMap())[i],
			&(*m_pCM->getMap())[i + 1],
			&(*m_pCM->getMap())[i + 2],
			&m_vOriginal,
			&m_vDirection,
			&pU,
			&pV,
			NULL))
		{
			m_vMousePos = pU*((*m_pCM->getMap())[i + 1] - (*m_pCM->getMap())[i])
				+ pV*((*m_pCM->getMap())[i + 2] - (*m_pCM->getMap())[i]);
			break;
		}

	}
	
}

void cController::MouseAtWorldSpace()
{
	D3DVIEWPORT9 viewPort;
	g_pD3DDevice->GetViewport(&viewPort);	// 뷰포트 가져옴

	D3DXMATRIX matProjection;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);	// 프로젝션 갖고옴

	D3DXVECTOR3 vDir(0, 0, 1);
	vDir.x = ((2.0f*m_ptMouse.x) / viewPort.Width - 1.0f) / matProjection._11;
	vDir.y = ((-2.0f*m_ptMouse.y) / viewPort.Height + 1.0f) / matProjection._22;

	D3DXMATRIX	matView, matInView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInView, 0, &matView);

	D3DXVec3TransformCoord(&m_vOriginal, &m_vOriginal, &matInView);

	D3DXVec3TransformNormal(&vDir, &vDir, &matInView);
	D3DXVec3Normalize(&vDir, &vDir);
	m_vDirection = vDir;


}
