#include "stdafx.h"
#include "cPlayer.h"
#include "cRayPicking.h"
#include "cSphere.h"

cPlayer::cPlayer()
	:m_bIsTarget(false)
	,m_fRange(400)
{
	
}

cPlayer::~cPlayer()
{
	
}

void cPlayer::Setup(const char* name)
{
	cCharacter::Setup(name);
	g_pSkillManager->AddSkill("평타", RANGE_SKILL, 100, m_fRange, 10.0f, 3.0f, 20, true);

	m_pSphere = new cSphere;
	m_pSphere->Setup(D3DXVECTOR3(200, 5172, 200), 100);

}

void cPlayer::Release()
{
	delete m_pSphere;
	g_pSkillManager->Release();
}

void cPlayer::Update()
{
	Check3DMousePointer();

	cCharacter::Update();

	g_pSkillManager->Update();

	if (g_pSkillManager->IsCasting())
	{
		m_vNextPosition = m_vPosition;

	}

}

void cPlayer::Render()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);
	g_pFontManager->TextFont(ptMouse.x, ptMouse.y, "2D : %0.2f, %0.2f", (float)ptMouse.x, (float)ptMouse.y);
	g_pFontManager->TextFont(ptMouse.x, ptMouse.y + 20, "3D : %0.2f, %0.2f, %0.2f", (float)m_vNextPosition.x, (float)m_vNextPosition.y, (float)m_vNextPosition.z);
	g_pFontManager->TextFont(10, 250, "테스트 :%d", m_bIsTarget);
	
	g_pSkillManager->Render();

	if(m_pSphere)
	m_pSphere->Render();

	cCharacter::Render();
}

void cPlayer::Check3DMousePointer()
{
	if (!m_pMap) return;

	if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
	{

	}

	if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
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
				break;
			}
		}

		if (ray.PickSphere(m_pSphere->GetPos(), 100))
		{
			D3DXVECTOR3	v = m_vPosition - m_pSphere->GetPos();
			float s = D3DXVec3Length(&v);
			if (D3DXVec3Length(&(m_vPosition - m_pSphere->GetPos())) < m_fRange)
			{
				m_fRotY = GetAngle(m_vPosition, m_pSphere->GetPos());
				m_vNextPosition = m_vPosition;
			}
			g_pSkillManager->Fire("평타", &m_vPosition, &m_pSphere->GetPos(), NULL);
		}

	}

}
