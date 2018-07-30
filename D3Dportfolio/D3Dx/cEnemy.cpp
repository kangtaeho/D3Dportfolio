#include "stdafx.h"
#include "cEnemy.h"
#include "cRangeSkill.h"


cEnemy::cEnemy()
{
}


cEnemy::~cEnemy()
{
	SAFE_RELEASE(m_pAttack);
}

void cEnemy::Setup(const char * name, bool Blue)
{
	m_bLive = true;
	// 테스트용입니다
	m_fRadius = 30;
	m_fHP = 100;
	m_vPosition = m_AStar.PushDestination(m_vPosition, m_fRadius); //만약에 충돌을 받으면 밀어낸다
	m_vPosition = g_pCollisionManager->SetHeight(m_vPosition);
																   // 테스트용입니다
	m_fSpeed = 3.0f;
	m_fRange = 80.0f;
	m_fBlue = Blue;

	std::string FullName = name;
	if (Blue)
	{
		FullName += "Blue";
	}
	else
	{
		FullName += "Red";

		std::vector<int> vecGoLine;
		for (int i = 0; i < m_vecGoLine.size(); ++i)
		{
			vecGoLine.push_back(m_vecGoLine[m_vecGoLine.size() - 1 - i]);
		}
		m_vecGoLine = vecGoLine;
	}


	cCharacter::Setup(FullName.c_str());
	m_pCircle.fRadius = m_fRadius;
	m_pCircle.mPosition = m_vPosition;

	m_pEnemy = NULL;
	m_fSite = 300.0f;
	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pSphere, NULL);

	m_pAttack = new cRangeSkill;

}

void cEnemy::Release()
{
}

void cEnemy::Update()
{
	D3DXVECTOR3 SpherePosition = m_vPosition;
	SpherePosition.y += m_fRadius;
	m_pCircle.mPosition = m_vPosition;
	if (m_vecGoLine.size())
	{
		m_vNextPosition = m_stAllCircleLine.vecCircle[m_vecGoLine.front()]->mPosition;
		if (g_pCollisionManager->NextTickInCircle(m_vPosition, m_fRadius, m_stAllCircleLine.vecCircle[m_vecGoLine.front()]->mPosition, m_stAllCircleLine.vecCircle[m_vecGoLine.front()]->fRadius))
		{
			m_vecGoLine.erase(m_vecGoLine.begin());
		}
	}

	if (!m_pEnemy)
	{
		for (int tempEnemy = 0; tempEnemy < m_vecAllEnemy->size(); ++tempEnemy)
		{
			if (D3DXVec3Length(&((*m_vecAllEnemy)[tempEnemy]->getPosition() - m_vPosition)) < m_fSite && ((cEnemy*)(*m_vecAllEnemy)[tempEnemy])->GetHP() > 0)
			{
				m_pEnemy = (*m_vecAllEnemy)[tempEnemy];

				break;
			}
		}
	}
	else
	{
		if (m_pEnemy->GetHP() <= 0)m_pEnemy = NULL;
	}
	D3DXVECTOR3* tempEnemyPosition = NULL;
	if (m_pEnemy)tempEnemyPosition = m_pEnemy->getPositionPointer();
	if (m_fHP <= 0)
	{
		setAnimation("Death", false);
		if (EndAnimation())m_bLive = false;
	}
	else if (m_AStar.UpdateForEnemy(m_vPosition, m_vNextPosition, m_fRotY, m_fSpeed, m_fRadius, m_fRange, tempEnemyPosition, 0))setAnimation("Run");
	else if(m_pEnemy)
	{
		m_pAttack->Setup(RANGE_SKILL, 10, 100 + m_pEnemy->GetRadius(), 20, 3, 0, 10, true, NULL);
		m_pAttack->SetIsReady(true);
		m_pAttack->Fire(&m_vPosition, m_pEnemy->getPositionPointer(), m_pEnemy, false);
		setAnimation("Attack");
	}

	m_pAttack->Update();
}

void cEnemy::Render()
{
	D3DXMATRIX	matWorld, matS, matR, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//애니메이션을 넣을때 cAction을 상속받은 후 아래처럼 사용
	UpdateAnimation();
	m_pSkinnedMesh->Update(m_pAnimController);

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	matT;
	D3DXMatrixIdentity(&matT);
	g_pD3DDevice->SetTexture(0, NULL);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y + m_fRadius, m_vPosition.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matT);
	m_pSphere->DrawSubset(0);

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}
