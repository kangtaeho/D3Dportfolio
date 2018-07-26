#include "stdafx.h"
#include "cObject.h"


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
	m_fHP = 900.0f;

	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pSphere, NULL);
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
		m_pSkinnedMesh = g_pXfileManager->FindXfile(FullName.c_str());

		if (m_eState == IDLE)
		{
			setAnimation("Idle", false, 1.0f);
		}
		else if (m_fHP > 300 && m_eState == IDLE)
		{
			m_pSkinnedMesh->CloneAniController(&m_pAnimController);
			m_eState = SKILL1;
			setAnimation("Crush", false, 1.0f);
		}
		else if (m_fHP > 0 && m_eState == SKILL1)
		{
			m_pSkinnedMesh->CloneAniController(&m_pAnimController);
			m_eState = SKILL2;
			setAnimation("Crush", false, 1.0f);
		}
		else if(m_fHP <= 0 && m_eState == SKILL2)
		{
			m_pSkinnedMesh->CloneAniController(&m_pAnimController);
			m_eState = SKILL3;
			setAnimation("Crush", false, 1.0f);
		}
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
}
