#include "stdafx.h"
#include "cObject.h"
#include "cRangeSkill.h"
#include "cHealthProgress.h"

cObject::cObject()
{
}


cObject::~cObject()
{
}

void cObject::Setup(const char * name, int BlueTeam, float scale)
{
	std::string FullName = name;
	m_sName = name;
	m_bBlue = BlueTeam;
	if (m_sName.c_str()[0] == 'T')
	{
		FullName += "0_";
	}
	if (BlueTeam)
	{
		FullName += "Blue";
	}
	else
	{
		FullName += "Red";
	}
	cCharacter::Setup(FullName.c_str());

	if (m_sName.c_str()[0] == 'T')
	{
		setAnimation("Idle", false, 1.0f);
	}
	else
	{
		setAnimation("Idle");
	}

	m_fScale = scale;
	m_eState = IDLE;
	m_fMAXHP = 900.0f;
	m_fHP = 900.0f;
	m_fSite = 700;
	m_pAttack = new cRangeSkill;
	m_pAttack->Setup(RANGE_SKILL, 40, 600, 15, 0, 2, 1000, true, NULL);

	m_vFirePosition = m_vPosition;
	m_vFirePosition.y += 250.0f;

	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pSphere, NULL);

	m_pObjectProgressBar = new cHealthProgress;
	Bitmap* Container;  Bitmap* HpBar; Bitmap* MpBar;
	Container = g_pTextureManager->addTexture("TowerContainer", "./status/TowerHpContainer.dds", NULL, NULL);
	HpBar = g_pTextureManager->addTexture("TowerHpBar", "./status/TowerHpBar.dds", PROGRESSBAR, 1, 1);

	m_pObjectProgressBar->SetContainer(Container);
	m_pObjectProgressBar->SetHpBar(HpBar);
	m_pObjectProgressBar->SetMaxHp(m_fMAXHP);
	m_pObjectProgressBar->SetCurrentHp(m_fHP);

	m_pObjectProgressBar->setup();
}

void cObject::Release()
{
}

void cObject::Update()
{
	if (m_sName.c_str()[0] == 'T')
	{
		std::string FullName = m_sName;
		if (m_fHP > 600)
		{
			FullName += "0_";
		}
		else if (m_fHP > 300)
		{
			FullName += "1_";
		}
		else if (m_fHP > 0)
		{
			FullName += "2_";
		}
		else
		{
			FullName += "3_";
		}
		if (m_bBlue)
		{
			FullName += "Blue";
		}
		else
		{
			FullName += "Red";
		}
		if (m_pSkinnedMesh != g_pXfileManager->FindXfile(FullName.c_str()))
		{
			SAFE_RELEASE(m_pAnimController);
			m_pSkinnedMesh = g_pXfileManager->FindXfile(FullName.c_str());
			m_pSkinnedMesh->CloneAniController(&m_pAnimController);
		}

		if (m_fHP > 600)
		{
			setAnimation("Idle", false, 1.0f);
		}
		else if (m_fHP > 300)
		{
			setAnimation("Crush", false, 1.0f);
		}
		else if (m_fHP > 0)
		{
			setAnimation("Crush", false, 1.0f);
		}
		else if(m_fHP <= 0)
		{
			setAnimation("Crush", false, 1.0f);
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
			if (m_pEnemy->GetHP() <= 0 || D3DXVec3Length(&(m_pEnemy->getPosition() - m_vPosition)) > m_fSite)m_pEnemy = NULL;
		}
		if (m_pEnemy && m_fHP > 0)
		{
			m_pAttack->Fire(&m_vFirePosition, m_pEnemy->getPositionPointer(), m_pEnemy, true);
		}

		m_pAttack->Update();
	}
	else
	{
		if (m_fHP > 0 && m_eState == IDLE)
		{
			setAnimation("Idle");
		}
		else if (m_fHP > 0)
		{
			if (isNameAniPlaying("Respawn"))
			{
				setAnimation("Respawn", false, 1.0f);
			}
			else
			{
				m_eState = IDLE;
			}
		}
		else if (m_fHP <= 0 && m_eState == IDLE)
		{
			setAnimation("Death", false, 1.0f);
			if (!isNameAniPlaying("Death"))
			{
				m_eState = DEAD;
			}
		}
		else
		{
			setAnimation("Death_Idle");
		}
	}

	D3DXVECTOR3 SpherePosition = m_vPosition;
	SpherePosition.y += m_fRadius;

	D3DXVECTOR3 tempposition(0, 0, 0);
	D3DXMATRIX WorldMatrix, matProj, matViewPort, matView;
	D3DXMatrixTranslation(&WorldMatrix, SpherePosition.x, SpherePosition.y, SpherePosition.z);
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

	m_pObjectProgressBar->setBarPosition(tempposition, tempposition);

	m_pObjectProgressBar->GetContainer()->setPosition(D3DXVECTOR3(tempposition.x - 45, tempposition.y - 150, 0));
	m_pObjectProgressBar->GetHpBar()->setPosition(m_pObjectProgressBar->GetContainer()->GetPosition());

	m_pObjectProgressBar->update();
	m_pObjectProgressBar->GetHpBar()->GetrectFrameSize()->right = m_fHP;

	if (m_pObjectProgressBar->GetHpBar()->GetrectFrameSize()->right <= 0) m_pObjectProgressBar->GetHpBar()->GetrectFrameSize()->right = 0;
}

void cObject::Render()
{
	D3DXMATRIX	matWorld, matS, matR, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXMatrixScaling(&matS, m_fScale, m_fScale, m_fScale);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//애니메이션을 넣을때 cAction을 상속받은 후 아래처럼 사용
	UpdateAnimation();
	m_pSkinnedMesh->Update(m_pAnimController);

	if (m_sName.c_str()[0] == 'T')
	{
		m_pAttack->Render();
	}
	m_pObjectProgressBar->render();
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//
	//g_pD3DDevice->SetTexture(0, NULL);
	//m_matWorld = matR * matT;
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//m_pSphere->DrawSubset(0);
	//
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}
