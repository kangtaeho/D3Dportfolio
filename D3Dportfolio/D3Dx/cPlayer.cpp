#include "stdafx.h"
#include "cPlayer.h"
#include "cRayPicking.h"
#include "cSphere.h"
#include "cAStar.h"
#include "cEnemy.h"
#include "cShop.h"

cPlayer::cPlayer()
{

}

cPlayer::~cPlayer()
{

}

void cPlayer::Setup(const char* name)
{
	m_fRange = 400;
	m_fSpeed = 7.0f;
	m_fMAXHP = 300;
	m_fMAXMP = 250;
	m_fHP = 300;
	m_fMP = 250;
	m_fDEF = 50;
	m_fATK = 80;
	m_fATKSpeed = 50;

	cCharacter::Setup(name);

	m_fRadius = 13.0f;

	g_pSkillManager->AddSkill("평타", RANGE_SKILL, 80, m_fRange, 20.0f, 0.3f, 2.5f, 20, true);
	g_pSkillManager->AddSkill("r", OBJECT_SKILL, 100, 500, 10.0f, 0.5f, 20.0f, 40, true, "BantamTrap");
	g_pSkillManager->GetSkill("r")->SetPlayer(this);	// 테두리 때문에

	g_pSkillManager->AddSkill("w", BUFF_SKILL, 0, 0, 0, 0.5, 10, 10, false, NULL);
	g_pSkillManager->GetSkill("w")->SetPlayer(this);
	g_pSkillManager->GetSkill("w")->SetBuffType(MOVEUP);

	g_pSkillManager->AddSkill("e", TOXIC_SKILL, 50, 400, 20.0f, 0.5, 10.0f, 10, true);
	g_pSkillManager->GetSkill("e")->SetPlayer(this);

	//m_pSphere = new cSphere;
	//m_pSphere->Setup(D3DXVECTOR3(200, 5000, 200), 100);
	//
	//m_pEnemy = new cEnemy;
	//m_pEnemy->Setup("order_minion_caster_", 0);

	//m_vecEnemy.push_back(m_pEnemy);
	//m_pVecEnemy = &m_vecEnemy;
	g_pSkillManager->RegisterVecEnemy(m_pVecEnemy);
	m_fRespwan = 0.0f;
}

void cPlayer::Release()
{
	delete m_pSphere;
	g_pSkillManager->Release();
}

void cPlayer::Update()
{
	if (g_pKeyManager->IsStayKeyDown(VK_SPACE))g_pCameraManager->setCameraPos(m_vPosition);
	Check3DMousePointer();

	bool isMove = false;
	isMove = m_AStar.Update(m_vPosition, m_vNextPosition, m_fRotY, m_fSpeed, m_fRadius, m_fRange, m_pEnemyPos);

	g_pSkillManager->Update();

	if (m_fRespwan)
	{
		m_fRespwan -= g_pTimeManager->GetElapsedTime();
		if (m_fRespwan <= 0)
		{
			m_fHP = 300.0f;
			m_vPosition = g_pCollisionManager->SetHeight(D3DXVECTOR3(0, 0, 0));
			m_vNextPosition = m_vPosition;
			m_fRespwan = 0.0f;
		}
	}

	if (m_fHP <= 0)
	{
		setAnimation("Death", false);
		if(!m_fRespwan)
			m_fRespwan = 10.0f;
	}
	else if (g_pSkillManager->IsCasting())
	{
		setAnimation("Attack1");
		if(m_pEnemy)
			m_pEnemy->setEnemy(this);
	}
	else if (isMove)
	{
		setAnimation("Run");
		if (m_pEnemyPos && m_pEnemy)
			*m_pEnemyPos = m_pEnemy->getPosition();
	}
	else
	{
		setAnimation();
	}

}

void cPlayer::Render()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);
	//g_pFontManager->TextFont(ptMouse.x, ptMouse.y, D3DXVECTOR3(255, 0, 255), "2D : %0.2f, %0.2f", (float)ptMouse.x, (float)ptMouse.y);
	//g_pFontManager->TextFont(ptMouse.x, ptMouse.y + 20, D3DXVECTOR3(255, 0, 255), "3D : %0.2f, %0.2f, %0.2f", (float)m_vNextPosition.x, (float)m_vNextPosition.y, (float)m_vNextPosition.z);

	g_pSkillManager->Render();

	//if (m_pSphere)
	//	m_pSphere->Render();
	//
	//if (m_pEnemy)
	//	m_pEnemy->Render();

	cCharacter::Render();
}

void cPlayer::Check3DMousePointer()
{

	if (g_pKeyManager->IsOnceKeyDown('3'))
	{
		g_pSkillManager->IsReady("e");
	}

	if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
	{
		if (!g_pSkillManager->CheckReady()) return;

		SAFE_DELETE(m_pEnemyPos);

		int isPick = 0;
		for (int i = 0; i < m_pVecEnemy->size(); ++i)
		{
			m_vNextPosition = g_pCollisionManager->getRayPosition(isPick, (*m_pVecEnemy)[i]->getPosition(), ((cEnemy*)(*m_pVecEnemy)[i])->getSphere(), (*m_pVecEnemy)[i]->GetRadius()); //포지션 받고	

			if (isPick)
			{
				m_pEnemy = (cEnemy*)(*m_pVecEnemy)[i];
				break;
			}
		}
		


		m_pEnemyPos = new D3DXVECTOR3;
		*m_pEnemyPos = m_vNextPosition;

		m_vClickPos = m_vNextPosition;

		if (g_pSkillManager->GetSkill("e")->GetIsReady())
		{
			if (m_pEnemy)
			{
				m_pEnemy->setEnemy(this);
				g_pSkillManager->Fire("e", &m_vPosition, m_pEnemy->getPositionPointer(), m_pEnemy);
			}
		}
		else if (g_pSkillManager->GetSkill("r")->GetIsReady())
		{
			g_pSkillManager->Fire("r", &m_vPosition, &m_vClickPos, false);
		}

	}

	if (g_pKeyManager->IsOnceKeyDown(VK_RBUTTON) && !isClickUi)
	{
		AttackEnemy(m_pEnemy);
	}

}

void cPlayer::AttackEnemy(cCharacter* enemy)
{
	SAFE_DELETE(m_pEnemyPos);

	int isPick = 0;

	for (int i = 0; i < m_pVecEnemy->size(); ++i)
	{
		m_vNextPosition = g_pCollisionManager->getRayPosition(isPick, (*m_pVecEnemy)[i]->getPosition(), ((cEnemy*)(*m_pVecEnemy)[i])->getSphere(), (*m_pVecEnemy)[i]->GetRadius()); //포지션 받고	
		if (isPick)
		{
			m_pEnemy = (cEnemy*)(*m_pVecEnemy)[i];
			break;
		}
	}
	if (m_pEnemy && m_pEnemy->GetHP() <= 0)
	{
		m_pEnemy = NULL;
		isPick = 0;
		m_vNextPosition = m_vPosition;
	}

	if (isPick)
	{
		m_pEnemyPos = new D3DXVECTOR3;
		*m_pEnemyPos = m_pEnemy->getPosition();
		if (D3DXVec3Length(&(m_vPosition - m_pEnemy->getPosition())) < m_fRange);
		{
			m_fRotY = GetAngle(m_vPosition, m_pEnemy->getPosition());
			g_pSkillManager->Fire("평타", &m_vPosition, m_pEnemy->getPositionPointer(), m_pEnemy);
			//SAFE_DELETE(m_pEnemyPos);
		}
	}
}