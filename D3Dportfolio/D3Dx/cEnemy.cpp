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
	// �׽�Ʈ���Դϴ�

	cCharacter::Setup(name);
}

void cEnemy::Release()
{
}

void cEnemy::Update()
{
}

void cEnemy::Render()
{
	// �׽�Ʈ�� ü�¹� ǥ��
	g_pFontManager->TextFont(10, 400, "�� ü�� %0.2f", m_fHP);
	cCharacter::Render();
}
