#include "stdafx.h"
#include "cAshe.h"
#include "cAStar.h"
#include "cRangeSkill.h"
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

	cCharacter::Setup(name);

	m_sMovePos.pos[0]= D3DXVECTOR3(1280, 0, 735);
	m_sMovePos.pos[1]= D3DXVECTOR3(450, 0, -150);
	m_sMovePos.index = 0;
	m_sMovePos.isChange = false;

	m_vStartPos = D3DXVECTOR3(3445, 0, 2700);
	m_vPosition = D3DXVECTOR3(3445, 0, 2700);
	m_vNextPosition = m_sMovePos.pos[0];

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
		m_sMovePos.isChange = true;
		setAnimation();
	}

	ChangePos();

}

void cAshe::Render()
{
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
		}

	}
}
