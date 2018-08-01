#include "stdafx.h"
#include "cAshe.h"
#include "cAStar.h"
#include "cRangeSkill.h"

cAshe::cAshe()
{

}


cAshe::~cAshe()
{

}

void cAshe::Setup(const char * name)
{
	m_fRange = 400;
	m_fSpeed = 7.0f;
	m_fMAXHP = 300;
	m_fMAXMP = 250;
	m_fHP = 300;
	m_fMP = 250;
	m_fDEF = 50;
	m_fATK = 50;
	m_fATKSpeed = 50;

	cCharacter::Setup(name);

	m_vPosition = D3DXVECTOR3(3445, 0, 2700);
	m_vNextPosition = D3DXVECTOR3(0, 0, 0);
}

void cAshe::Release()
{

}

void cAshe::Update()
{
	bool isMove = false;
	isMove = m_AStar.Update(m_vPosition, m_vNextPosition, m_fRotY, m_fSpeed, m_fRadius, m_fRange, m_pEnemyPos);

	if (isMove)
	{
		setAnimation("Run");
	}
	else
	{
		setAnimation();
	}

}

void cAshe::Render()
{
	cCharacter::Render();
}
