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
	// 테스트용입니다

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
	cCharacter::Render();
}
