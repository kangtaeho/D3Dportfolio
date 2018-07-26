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
	// 테스트용입니다
	m_fRadius = 50;
	m_fHP = 300;
	m_vPosition = m_AStar.PushDestination(m_vPosition, m_fRadius); //만약에 충돌을 받으면 밀어낸다
	m_vPosition = g_pCollisionManager->SetHeight(m_vPosition);
																   // 테스트용입니다
	D3DXVECTOR3 tempsphere = m_vPosition;
	tempsphere.y += m_fRadius;
	tempSphere.Setup(tempsphere, m_fRadius);

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
	// 테스트용 체력바 표시
<<<<<<< HEAD
<<<<<<< HEAD
	g_pFontManager->TextFont(10, 400, D3DXVECTOR3(255,0,255),"적 체력 %0.2f", m_fHP);
=======
	// g_pFontManager->TextFont(10, 400, "적 체력 %0.2f", m_fHP);
>>>>>>> a818d4dde10241bb11b7e3db0e4f72377a58860f
=======
	// g_pFontManager->TextFont(10, 400, "적 체력 %0.2f", m_fHP);
>>>>>>> e2dd74fe8b197019b5f75729843c90185624dcc7
	cCharacter::Render();
	tempSphere.Render();
}
