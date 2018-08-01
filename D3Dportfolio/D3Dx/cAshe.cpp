#include "stdafx.h"
#include "cAshe.h"
#include "cAStar.h"
#include "cRangeSkill.h"
#include "cEnemy.h"
#include <ctime>

cAshe::cAshe()
{

}


cAshe::~cAshe()
{

}

void cAshe::Setup(const char * name)
{
	m_fRange = 400;
	m_fSpeed = 5.0f;
	m_fMAXHP = 300;
	m_fMAXMP = 250;
	m_fHP = 300;
	m_fMP = 250;
	m_fDEF = 50;
	m_fATK = 50;
	m_fATKSpeed = 50;
	m_fSite = 500;
	m_fRadius = 40;
	m_bIsDead = false;
	m_bIsDanger = false;

	m_fNowHP = m_fHP;

	cCharacter::Setup(name);

	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 15, 15, &m_pSphere, NULL);

	m_sMovePos.pos[0]= D3DXVECTOR3(1280, 0, 735);
	m_sMovePos.pos[1]= D3DXVECTOR3(450, 0, -150);
	m_sMovePos.index = 0;
	m_sMovePos.isChange = false;

	m_sBackPos.pos[0] = D3DXVECTOR3(1087, 0, 565);
	m_sBackPos.pos[1] = D3DXVECTOR3(1528, 0, 639);
	m_sBackPos.index = 0;
	m_sBackPos.isChange = false;

	m_sStartPos = m_sMovePos;

	m_vStartPos = D3DXVECTOR3(3445, 0, 2700);
	m_vPosition = D3DXVECTOR3(3445, 0, 2700);
	m_vNextPosition = m_sMovePos.pos[0];

	m_pAttack = new cRangeSkill;
	m_pAttack->Setup(RANGE_SKILL, m_fATK, m_fRange, 25.0f, 0.35f, 3.0f, 20, true, NULL);

	m_pMatScale = new D3DXMATRIX;
	D3DXMatrixScaling(m_pMatScale, 0.8, 0.8, 0.8);

	m_eAIState = AI_PATROL;

}

void cAshe::Release()
{
	if(m_pMatScale) delete m_pMatScale;
	if(m_pEnemyPos) delete m_pEnemyPos;
	delete m_pAttack;
}

void cAshe::Update()
{
	if (m_pAttack)
		m_pAttack->Update();

	ControlAI();
	ChangePos();
	DangerTime();

	RespawnAshe();

}

void cAshe::Render()
{
	if (m_pAttack)
		m_pAttack->Render();

	cCharacter::Render();
}

void cAshe::ChangePos()
{
	if (m_sMovePos.isChange)
	{
		if (m_sMovePos.index == 0)
		{
			m_sMovePos.index++;
			m_sMovePos.isChange = false;
			m_vNextPosition = m_sMovePos.pos[m_sMovePos.index];
		}
		else if (m_sMovePos.index == 1&&m_bIsDanger)
		{
			m_sMovePos = m_sStartPos;
			m_vNextPosition = m_sMovePos.pos[0];
			m_bIsDanger = false;
		}
		else
		{
			srand(GetTickCount());
			int rndNum1 = 150 + rand() % 100;
			int rndNum2 = 150 + rand() % 50;

			int dir1 = 1;
			int dir2 = 1;
			if ((rndNum1 % 2) == 0) dir1 *= -1;
			if ((rndNum2 % 2) == 0) dir2 *= -1;

			m_sMovePos.pos[0] = D3DXVECTOR3(m_vPosition.x + (dir1 *rndNum1), 0, m_vPosition.z + (dir2 *rndNum2));
			m_sMovePos.pos[1] = m_vPosition;
			m_sMovePos.index = 0;
			m_sMovePos.isChange = false;

			m_vNextPosition = m_sMovePos.pos[0];

			m_eAIState = AI_PATROL;
		}

	}
}

void cAshe::ControlAI()
{

	bool isMove = false;
	isMove = m_AStar.Update(m_vPosition, m_vNextPosition, m_fRotY, m_fSpeed, m_fRadius, m_fRange, m_pEnemyPos);


	if (m_fHP <= 0)
	{
		m_fHP = 0;
		setAnimation("Death", false);
		m_vNextPosition = m_vPosition;
		m_bIsDead = true;
		return;
	}
	else if (m_pAttack->GetIsCasting())
	{
		if(m_pEnemy) m_fRotY = GetAngle(m_vPosition, m_pEnemy->getPosition());
		setAnimation("Attack1");
	}
	else if (isMove)
	{
		setAnimation("Run");
	}
	else
	{
		m_sMovePos.isChange = true;
		setAnimation();
	}
	
	if (m_bIsDanger) return;

	if (!m_pEnemy)
	{
	
		for (int i = 0; i < m_vecAllEnemy->size(); i++)
		{
			if (D3DXVec3Length(&((*m_vecAllEnemy)[i]->getPosition() - m_vPosition)) < m_fSite && ((cEnemy*)(*m_vecAllEnemy)[i])->GetHP() > 0)
			{
				m_pEnemy = (cEnemy*)(*m_vecAllEnemy)[i];
				break;
			}
		}
	}
	
	if (m_pEnemy)
	{
		if (!m_pEnemyPos) m_pEnemyPos = new D3DXVECTOR3;

		if (D3DXVec3Length(&(m_vPosition - m_pEnemy->getPosition())) < m_fRange);
		{
			*m_pEnemyPos = m_pEnemy->getPosition();
			m_pAttack->Fire(&m_vPosition, m_pEnemy->getPositionPointer(), m_pEnemy,true);
		}
	}

	if (m_pEnemy)
	{
		if (m_pEnemy->getState() == DEAD && m_pEnemy->GetHP()<=0)
		{
			m_pEnemy = NULL;
			SAFE_DELETE(m_pEnemyPos);
		}
	}
	
}

void cAshe::RespawnAshe()
{
	if (!m_bIsDead) return;

	m_fPassedTime += g_pTimeManager->GetElapsedTime();

	if (m_fPassedTime > 10)
	{
		if (m_pEnemy) m_pEnemy = NULL;
		if(m_pEnemyPos) SAFE_DELETE(m_pEnemyPos);
		setAnimation();
		m_fHP = 300;

		m_vPosition = m_vStartPos;
		m_sMovePos = m_sStartPos;

		m_eAIState = AI_PATROL;

		m_fPassedTime = 0.0f;
		m_bIsDead = false;
	}
}

void cAshe::DangerTime()
{
	m_fDangerTime += g_pTimeManager->GetElapsedTime();

	if (m_fDangerTime > 10.0f)
	{
		m_fNowHP = m_fHP;
		m_fDangerTime = 0.0f;
	}

	if (m_fNowHP - m_fHP > 100)
	{
		BackAshe();
		m_fNowHP = m_fHP;
		m_fDangerTime = 0.0f;
	}
}

void cAshe::BackAshe()
{
	if (m_pEnemy) m_pEnemy = NULL;
	if (m_pEnemyPos) SAFE_DELETE(m_pEnemyPos);

	m_sMovePos = m_sBackPos;

	m_vNextPosition = m_sMovePos.pos[0];

	m_bIsDanger = true;

	m_eAIState = AI_PATROL;

}
