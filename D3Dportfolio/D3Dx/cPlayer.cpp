#include "stdafx.h"
#include "cPlayer.h"
#include "cCube.h"

cPlayer::cPlayer()
	: m_pCube(NULL)
	, m_fRotY(0)
	, m_vPos(0,0,0)
	, m_vEnemyPos(0,0,0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cPlayer::~cPlayer()
{
	delete m_pCube;
}

HRESULT cPlayer::Setup()
{
	m_pCube = new cCube;
	m_pCube->Setup(D3DXVECTOR3(2,2,2),NULL);

	g_pSkillManager->AddSkill("근거리공격", MELEE_SKILL, 100, 100, 0, 0, 0, 0,false);
	g_pSkillManager->AddSkill("원거리공격", RANGE_SKILL, 100, 100, 0.05f, 10.0f, NULL, 5.0, false);
	return S_OK;
}

void cPlayer::Release()
{
}

void cPlayer::Update()
{
	D3DXVECTOR3 dir(0, 0, 1);
	D3DXMATRIX	matR, matT;

	if (g_pKeyManager->IsStayKeyDown(VK_LEFT))
	{
		m_fRotY -= 0.05f;
	}

	if (g_pKeyManager->IsStayKeyDown(VK_RIGHT))
	{
		m_fRotY += 0.05f;
	}

	if (m_fRotY > D3DX_PI*2.0) m_fRotY -= D3DX_PI*2.0;
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXVec3TransformNormal(&dir, &dir, &matR);

	if (g_pKeyManager->IsStayKeyDown(VK_UP))
	{
		m_vPos += dir*0.2f;
	}

	if (g_pKeyManager->IsStayKeyDown(VK_DOWN))
	{
		m_vPos -= dir*0.2f;
	}

	if (g_pKeyManager->IsOnceKeyDown('Z'))
	{
		m_vEnemyPos = 3 * dir;		//테스트로 만들어놓음, 마우스 포인트 일수도 있고, 적 좌표일수도 있고
		g_pSkillManager->Fire("근거리공격", m_vPos, &m_vEnemyPos, NULL);
	}

	if (g_pKeyManager->IsOnceKeyDown('X'))
	{
		m_vEnemyPos = 10 * dir;		//테스트로 만들어놓음, 마우스 포인트 일수도 있고, 적 좌표일수도 있고
		g_pSkillManager->Fire("원거리공격", m_vPos, &m_vEnemyPos, NULL);
	}

	D3DXMatrixTranslation(&matT, m_vPos.x, m_vPos.y, m_vPos.z);
	
	g_pSkillManager->Update();

	m_matWorld = matR*matT;
	m_pCube->SetMatWorld(m_matWorld);
}

void cPlayer::Render()
{
	if (m_pCube)
		m_pCube->Render();

	g_pSkillManager->Render();
}
