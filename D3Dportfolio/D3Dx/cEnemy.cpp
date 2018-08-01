#include "stdafx.h"
#include "cEnemy.h"
#include "cRangeSkill.h"
#include "cHealthProgress.h"

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
	m_fMAXHP = 100;
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
	m_pCircle.iIndex = Blue;

	m_pEnemy = NULL;
	m_fSite = 300.0f;
	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pSphere, NULL);

	m_pAttack = new cRangeSkill;
	m_bAttack = false;

	m_pProgressBar = new cHealthProgress;
	Bitmap* Container;  Bitmap* HpBar; 
	Container = g_pTextureManager->addTexture("EnemyContainer", "./status/EnemyHpContainer.dds", NULL, NULL);
	HpBar = g_pTextureManager->addTexture("EnemyHpBar", "./status/EnemyHpBar.dds", PROGRESSBAR, 1, 1);
	//MpBar = g_pTextureManager->addTexture("EnemyMpBar", "./status/EnemyMpBar.dds", PROGRESSBAR, 1, 1);

	m_pProgressBar->SetContainer(Container);
	m_pProgressBar->SetHpBar(HpBar);
	m_pProgressBar->SetMaxHp(m_fMAXHP);
	m_pProgressBar->SetCurrentHp(m_fHP);
	//m_pProgressBar->SetMpBar(MpBar);
	m_pProgressBar->setup();
}

void cEnemy::Release()
{
}

void cEnemy::Update()
{
	m_isLive = m_bLive;

	if (m_pEnemy)
	{
		if (D3DXVec3Length(&(m_pEnemy->getPosition() - m_vPosition)) > 800.0f)m_pEnemy = NULL;
	}
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
	else if (m_AStar.UpdateForEnemy(m_vPosition, m_vNextPosition, m_fRotY, m_fSpeed, m_fRadius, m_fRange, tempEnemyPosition, m_pEnemy))setAnimation("Run");
	else if(m_pEnemy)
	{
		m_pAttack->Setup(RANGE_SKILL, 10, 100 + m_pEnemy->GetRadius(), D3DXVec3Length(&(m_pEnemy->getPosition() - m_vPosition)), 0.0f, 0.0f, 10, true, NULL);
		setAnimation("Attack");
		if (MidAnimation())
		{
			if (!m_bAttack)
			{
				m_pAttack->Fire(&m_vPosition, m_pEnemy->getPositionPointer(), m_pEnemy, true);
				m_bAttack = true;
			}
		}
		else m_bAttack = false;
	}

	m_pAttack->Update();

	D3DXVECTOR3 tempposition(0, 0, 0);
	D3DXMATRIX WorldMatrix, matProj, matViewPort, matView;
	D3DXMatrixTranslation(&WorldMatrix, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	D3DVIEWPORT9 tempViewPort;
	g_pD3DDevice->GetViewport(&tempViewPort);
	D3DXMatrixIdentity(&matViewPort);
	matViewPort._11 = tempViewPort.Width / (float)2;
	matViewPort._22 = -(int)tempViewPort.Height / (float)2;
	matViewPort._33 = tempViewPort.MaxZ - tempViewPort.MinZ;
	matViewPort._41 = tempViewPort.X + tempViewPort.Width / (float)2;
	matViewPort._42 = tempViewPort.Y + tempViewPort.Height / (float)2;
	matViewPort._43 = tempViewPort.MinZ;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	WorldMatrix = WorldMatrix * matView * matProj * matViewPort;
	D3DXVec3TransformCoord(&tempposition, &tempposition, &WorldMatrix);

	//m_pProgressBar->setBarPosition(tempposition, tempposition);

	m_pProgressBar->GetContainer()->setPosition(D3DXVECTOR3(tempposition.x - 45, tempposition.y - 70, tempposition.z));
	m_pProgressBar->GetHpBar()->setPosition(m_pProgressBar->GetContainer()->GetPosition());

	m_pProgressBar->update();
	m_pProgressBar->GetHpBar()->GetrectFrameSize()->right = m_fHP;

	if (m_pProgressBar->GetHpBar()->GetrectFrameSize()->right <= 0)
	{
		m_pProgressBar->GetHpBar()->GetrectFrameSize()->right = 0;
	}
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

	if (m_pProgressBar->GetHpBar()->GetrectFrameSize()->right > 0)
	{
		m_pProgressBar->render();
	}
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//
	//matT;
	//D3DXMatrixIdentity(&matT);
	//g_pD3DDevice->SetTexture(0, NULL);
	//D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y + m_fRadius, m_vPosition.z);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matT);
	//m_pSphere->DrawSubset(0);
	//
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}
