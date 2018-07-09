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
	g_pSkillManager->AddSkill("원거리공격", MELEE_SKILL, 100, 100, 2.0f, 0, 0, 10, false);
}

void cPlayer::Release()
{

}

void cPlayer::Update()
{
	Check3DMousePointer();
	cCharacter::Update();
	g_pSkillManager->Update();
}

void cPlayer::Render()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);
	g_pFontManager->TextFont(ptMouse.x, ptMouse.y, "2D : %0.2f, %0.2f", (float)ptMouse.x, (float)ptMouse.y);
	g_pFontManager->TextFont(ptMouse.x, ptMouse.y + 20, "3D : %0.2f, %0.2f, %0.2f", (float)m_vNextPosition.x, (float)m_vNextPosition.y, (float)m_vNextPosition.z);
	
	g_pFontManager->TextFont(20, 300, "3D : %0.2f", m_fRotY);
	g_pFontManager->TextFont(20, 320, "3D : %0.2f, %0.2f, %0.2f", (float)m_vPosition.x, (float)m_vPosition.y, (float)m_vPosition.z);
	
	g_pSkillManager->Render();

	cCharacter::Render();
}

void cPlayer::Check3DMousePointer()
{
	if (!m_pMap) return;

	if (g_pKeyManager->IsOnceKeyDown('S'))
	{
		g_pSkillManager->Fire("원거리공격", m_vPosition, &m_vNextPosition, NULL);
	}

	if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
	{

	}

	if (g_pKeyManager->IsStayKeyDown(VK_LBUTTON))
	{
		D3DXVECTOR3 v = m_vPosition;
		cRayPicking ray;

		for (int i = 0; i < m_pMap->size(); i += 3)
		{
			if (ray.PickTri((*m_pMap)[i],
				(*m_pMap)[i + 1],
				(*m_pMap)[i + 2],
				g_pCameraManager->GetCameraEye(),
				m_vNextPosition))
			{
				m_fRotY = GetAngle(v.x, v.z, m_vNextPosition.x, m_vNextPosition.z);
				break;
			}
		}

	}

	if (g_pKeyManager->IsOnceKeyDown(VK_LEFT))
	{
		m_fRotY += 0.05f;
	}

}