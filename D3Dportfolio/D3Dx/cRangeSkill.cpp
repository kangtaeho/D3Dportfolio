#include "stdafx.h"
#include "cRangeSkill.h"


cRangeSkill::cRangeSkill()
{
}


cRangeSkill::~cRangeSkill()
{
}

HRESULT cRangeSkill::Setup(SKILL_TYPE skillType, float damage, float range, float posSpeed, float cooldown, float castingTime, float removeTime, bool isTarget)
{

	cSkill::Setup(skillType, damage, range, posSpeed, cooldown, castingTime, removeTime, isTarget);

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
}

void cRangeSkill::Render()
{
	g_pFontManager->TextFont(100, 100, " 쿨다운 %0.2f ", m_fCurrentCooldown);
	g_pFontManager->TextFont(100, 120, " 오브젝트재거 시간 %0.2f ", m_fPassedTime);
	RenderCube();
}
