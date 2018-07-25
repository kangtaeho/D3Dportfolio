#include "stdafx.h"
#include "cPlayer.h"
#include "cRayPicking.h"
#include "cSphere.h"
#include "cAStar.h"
#include "cEnemy.h"

cPlayer::cPlayer()
{
	
}

cPlayer::~cPlayer()
{
	
}

void cPlayer::Setup(const char* name)
{
	m_fRange = 400;
	m_fSpeed = 10.0f;
	m_fHP = 300;
	m_fMP = 250;

	cCharacter::Setup(name);
	g_pSkillManager->AddSkill("평타", RANGE_SKILL, 100, m_fRange, 20.0f, 0.5f, 3.0f, 20, true);
	g_pSkillManager->AddSkill("r", OBJECT_SKILL, 100, 500, 10.0f, 0.5f, 10.0f, 10, true, "BantamTrap");
	g_pSkillManager->GetSkill("r")->SetPlayer(this);	// 테두리 때문에
	g_pSkillManager->AddSkill("w", BUFF_SKILL, 0, 0, 0, 0.5, 10, 10, false, NULL);
	g_pSkillManager->GetSkill("w")->SetPlayer(this);
	g_pSkillManager->GetSkill("w")->SetBuffType(MOVEUP);

	g_pSkillManager->AddSkill("e", TOXIC_SKILL, 50, 400, 20.0f, 0.5, 5.0f, 10, true);

	m_pSphere = new cSphere;
	m_pSphere->Setup(D3DXVECTOR3(200, 5000, 200), 100);

	m_pEnemy = new cEnemy;
	m_pEnemy->Setup("order_minion_caster_Red");

}

void cPlayer::Release()
{
	delete m_pSphere;
	g_pSkillManager->Release();
}

void cPlayer::Update()
{
	Check3DMousePointer();

	m_AStar.Update(m_vPosition,m_vNextPosition, m_fRotY, m_fSpeed, m_fRadius, m_fRange,m_pEnemyPos);
	//m_AStar.Stop(m_vPosition, m_fRange, m_pEnemyPos, 0);

	g_pSkillManager->Update();

	if (g_pSkillManager->IsCasting())
	{
		setAnimation("Attack1");
		//m_AStar.Stop();
	}
	else if(m_AStar.getAStarSize())
	{
		setAnimation("Run");
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
	g_pFontManager->TextFont(ptMouse.x, ptMouse.y, "2D : %0.2f, %0.2f", (float)ptMouse.x, (float)ptMouse.y);
	g_pFontManager->TextFont(ptMouse.x, ptMouse.y + 20, "3D : %0.2f, %0.2f, %0.2f", (float)m_vNextPosition.x, (float)m_vNextPosition.y, (float)m_vNextPosition.z);

	g_pSkillManager->Render();

	if(m_pSphere)
	m_pSphere->Render();

	if (m_pEnemy)
		m_pEnemy->Render();

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
		m_vNextPosition = g_pCollisionManager->getRayPosition(isPick, m_pEnemy->getPosition(), m_pEnemy->GetRadius()); //포지션 받고
		//m_vNextPosition = m_AStar.PushDestination(m_vNextPosition, m_fRadius); //만약에 충돌을 받으면 밀어낸다
		//m_AStar.Setup(m_vPosition, m_fRadius, m_vNextPosition);

		m_pEnemyPos = new D3DXVECTOR3;
		*m_pEnemyPos = m_vNextPosition;

		m_vClickPos = m_vNextPosition;

		if (g_pSkillManager->GetSkill("e")->GetIsReady())
		{
			g_pSkillManager->Fire("e", &m_vPosition, m_pEnemy->getPositionPointer(), m_pEnemy);
		}
		else if (g_pSkillManager->GetSkill("r")->GetIsReady())
		{
			g_pSkillManager->Fire("r", &m_vPosition, &m_vClickPos, false);
		}

	}

	if (g_pKeyManager->IsOnceKeyDown(VK_RBUTTON))
	{

		AttackEnemy(m_pEnemy);

		// SAFE_DELETE(m_pEnemyPos);
		// 
		// int isPick = 0;
		// // m_vNextPosition = g_pCollisionManager->getRayPosition(isPick,m_pSphere->m_pMesh,m_pSphere->GetPos()); //포지션 받고
		// m_vNextPosition = m_AStar.PushDestination(m_vNextPosition, m_fRadius); //만약에 충돌을 받으면 밀어낸다
		// m_AStar.Setup(m_vPosition, m_fRadius, m_vNextPosition);
		// 
		// if (isPick)
		// {
		// 	m_pEnemyPos = new D3DXVECTOR3;
		// 	*m_pEnemyPos = m_pSphere->GetPos();
		// 	if (D3DXVec3Length(&(m_vPosition - m_pSphere->GetPos())) < m_fRange);
		// 	{			
		// 		m_fRotY = GetAngle(m_vPosition, m_pSphere->GetPos());
		// 		g_pSkillManager->Fire("평타", &m_vPosition, &m_pSphere->GetPos());
		// 	}
		// }

	}

}

void cPlayer::AttackEnemy(cEnemy* enemy)
{
	SAFE_DELETE(m_pEnemyPos);

	int isPick = 0;
	m_vNextPosition = g_pCollisionManager->getRayPosition(isPick, enemy->getPosition(),enemy->GetRadius()); //포지션 받고
	//m_vNextPosition = m_AStar.PushDestination(m_vNextPosition, m_fRadius); //만약에 충돌을 받으면 밀어낸다
	//m_AStar.Setup(m_vPosition, m_fRadius, m_vNextPosition);

	if (isPick)
	{
		m_pEnemyPos = new D3DXVECTOR3;
		*m_pEnemyPos = enemy->getPosition();
		if (D3DXVec3Length(&(m_vPosition - enemy->getPosition())) < m_fRange);
		{
			m_fRotY = GetAngle(m_vPosition, enemy->getPosition());
			g_pSkillManager->Fire("평타", &m_vPosition, enemy->getPositionPointer(), enemy);
		}
	}
}