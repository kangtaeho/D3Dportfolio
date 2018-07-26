#include "stdafx.h"
#include "cEnemy.h"


cEnemy::cEnemy()
{
}


cEnemy::~cEnemy()
{
}

void cEnemy::Setup(const char * name)
{
	// �׽�Ʈ���Դϴ�
	m_fRadius = 50;
	m_fHP = 300;
	m_vPosition = m_AStar.PushDestination(m_vPosition, m_fRadius); //���࿡ �浹�� ������ �о��
	m_vPosition = g_pCollisionManager->SetHeight(m_vPosition);
																   // �׽�Ʈ���Դϴ�
	D3DXVECTOR3 tempsphere = m_vPosition;
	tempsphere.y += m_fRadius;
	tempSphere.Setup(tempsphere, m_fRadius);

	cCharacter::Setup(name);
	m_pCircle.fRadius = m_fRadius;
	m_pCircle.mPosition = m_vPosition;
}

void cEnemy::Release()
{
}

void cEnemy::Update()
{
	D3DXVECTOR3 SpherePosition = m_vPosition;
	SpherePosition.y += m_fRadius;
	tempSphere.SetPos(SpherePosition);
	m_pCircle.mPosition = m_vPosition;
}

void cEnemy::Render()
{
<<<<<<< HEAD
<<<<<<< HEAD
	// �׽�Ʈ�� ü�¹� ǥ��

	g_pFontManager->TextFont(10, 400, D3DXVECTOR3(255,0,255),"�� ü�� %0.2f", m_fHP);
=======

>>>>>>> 4cf02ca6945bd55248615b80adc7cc3b156ca955
=======

>>>>>>> 4cf02ca6945bd55248615b80adc7cc3b156ca955
	cCharacter::Render();
	tempSphere.Render();
}
