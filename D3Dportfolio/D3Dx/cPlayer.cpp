#include "stdafx.h"
#include "cPlayer.h"
#include "cRayPicking.h"

cPlayer::cPlayer()
{
	
}

cPlayer::~cPlayer()
{
	
}

void cPlayer::Setup(const char* name)
{
	cCharacter::Setup(name);
}

void cPlayer::Release()
{

}

void cPlayer::Update()
{
	Check3DMousePointer();
	cCharacter::Update();
}

void cPlayer::Render()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);
	g_pFontManager->TextFont(ptMouse.x, ptMouse.y, "2D : %0.2f, %0.2f", (float)ptMouse.x, (float)ptMouse.y);
	g_pFontManager->TextFont(ptMouse.x, ptMouse.y + 20, "3D : %0.2f, %0.2f, %0.2f", (float)m_vNextPosition.x, (float)m_vNextPosition.y, (float)m_vNextPosition.z);
	
	cCharacter::Render();
}

void cPlayer::Check3DMousePointer()
{
	if (!m_pMap) return;

	if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
	{

	}

	if (g_pKeyManager->IsOnceKeyDown(VK_RBUTTON))
	{

		cRayPicking ray;

		for (int i = 0; i < m_pMap->size(); i += 3)
		{
			if (ray.PickTri((*m_pMap)[i],
				(*m_pMap)[i + 1],
				(*m_pMap)[i + 2],
				g_pCameraManager->GetCameraEye(),
				m_vNextPosition))
			{
				break;
			}
		}

	}



}