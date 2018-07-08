#include "stdafx.h"
#include "cController.h"
#include "cCollisionMap.h"
#include "cRayPicking.h"

cController::cController()
	: m_vMousePos(0,0,0)
	, m_vControlPos(NULL)
	, m_pCM(NULL)
{
}


cController::~cController()
{
}

HRESULT cController::Setup()
{
	return S_OK;
}

void cController::Release()
{
}

void cController::Update()
{
	Check2DMousePointer();
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

	cRayPicking ray;

	for (int i = 0; i < m_pCM->getMap()->size(); i += 3)
	{
		if (ray.PickTri((*m_pCM->getMap())[i],
			(*m_pCM->getMap())[i + 1],
			(*m_pCM->getMap())[i + 2],
			g_pCameraManager->GetCameraEye(),
			m_vMousePos))
		{
			break;
		}
	}
}