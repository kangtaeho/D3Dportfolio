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
	g_pSkillManager->AddSkill("ÆòÅ¸", RANGE_SKILL, 100, m_fRange, 20.0f, 0.3f, 3.0f, 20, true);
	g_pSkillManager->AddSkill("¹ö¼¸", OBJECT_SKILL, 100, 400, 10.0f, 0.5f, 3.0f, 20, true, "BantamTrap");

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
		setAnimation("Attack1");
	}
	else if(D3DXVec3Length(&(m_vPosition - m_vNextPosition)) < m_fSpeed)
	{
		setAnimation();
	}
	else
	{
		setAnimation("Run");
	}


}

void cPlayer::Render()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);
	g_pFontManager->TextFont(ptMouse.x, ptMouse.y, "2D : %0.2f, %0.2f", (float)ptMouse.x, (float)ptMouse.y);
	g_pFontManager->TextFont(ptMouse.x, ptMouse.y + 20, "3D : %0.2f, %0.2f, %0.2f", (float)m_vNextPosition.x, (float)m_vNextPosition.y, (float)m_vNextPosition.z);
	
	g_pSkillManager->Render();

	if(m_pSphere)
	m_pSphere->Render();

	cCharacter::Render();
}

void cPlayer::Check3DMousePointer()
{
	if (!m_pMap) return;		// Ãæµ¹ ÆÇÁ¤ ¸ÊÀÌ ¾ø´Ù¸é,

	cRayPicking ray;

	if (g_pKeyManager->IsOnceKeyDown('W'))
	{
		g_pSkillManager->IsReady("¹ö¼¸");
	}

	if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
	{
		if (!g_pSkillManager->CheckReady()) return;

		for (int i = 0; i < m_pMap->size(); i += 3)
		{
			if (ray.PickTri((*m_pMap)[i],
				(*m_pMap)[i + 1],
				(*m_pMap)[i + 2],
				g_pCameraManager->GetCameraEye(),
				m_vNextPosition)) break;
		}

		m_vClickPos = m_vNextPosition;

		g_pSkillManager->Fire("¹ö¼¸", &m_vPosition, &m_vClickPos, false);

	}

	if (g_pKeyManager->IsOnceKeyDown(VK_RBUTTON))
	{

		for (int i = 0; i < m_pMap->size(); i += 3)
		{
			if (ray.PickTri((*m_pMap)[i],
				(*m_pMap)[i + 1],
				(*m_pMap)[i + 2],
				g_pCameraManager->GetCameraEye(),
				m_vNextPosition)) break;
		}

		if (ray.PickSphere(m_pSphere->GetPos(), 100))
		{
			if (D3DXVec3Length(&(m_vPosition - m_pSphere->GetPos())) < m_fRange)
			{
				m_fRotY = GetAngle(m_vPosition, m_pSphere->GetPos());
				m_vNextPosition = m_vPosition;
			}
			g_pSkillManager->Fire("ÆòÅ¸", &m_vPosition, &m_pSphere->GetPos());
		}

	}

}
