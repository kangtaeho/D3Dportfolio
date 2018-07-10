#include "stdafx.h"
#include "cRangeSkill.h"


cRangeSkill::cRangeSkill()
{
}


cRangeSkill::~cRangeSkill()
{
}

HRESULT cRangeSkill::Setup(SKILL_TYPE skillType, float damage, float range, float posSpeed, float cooldown, float removeTime, bool isTarget)
{

	cSkill::Setup(skillType, damage, range, posSpeed, cooldown, removeTime, isTarget);

	return S_OK;
}

void cRangeSkill::Release()
{
	delete m_pCube;
}

void cRangeSkill::Update()
{
	Casting();
	CoolDownSetup();
	Move();
	RemoveTime();
	RemoveTarget();
	AutoFire();
}

void cRangeSkill::Render()
{
	
	g_pFontManager->TextFont(100, 100, " ��ٿ� %0.2f ", m_fCurrentCooldown);
	g_pFontManager->TextFont(100, 120, " ������Ʈ��� �ð� %0.2f ", m_fPassedTime);
	
	if (m_pTargetPos && m_pPlayerPos)
	{
		D3DXVECTOR3 v = (*m_pTargetPos - *m_pPlayerPos);
		float le = D3DXVec3Length(&v);
		g_pFontManager->TextFont(100, 140, " �Ÿ� %0.3f ", le);
	}
	

	RenderCube();
}
