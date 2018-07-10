#include "stdafx.h"
#include "cMeleeSkill.h"


cMeleeSkill::cMeleeSkill()
{
}


cMeleeSkill::~cMeleeSkill()
{
}

HRESULT cMeleeSkill::Setup(SKILL_TYPE skillType, float damage, float range, float posSpeed, float cooldown, float removeTime, bool isTarget)
{
	cSkill::Setup(skillType, damage, range, posSpeed, cooldown, removeTime, isTarget);

	return S_OK;
}

void cMeleeSkill::Release()
{
	delete m_pCube;
}

void cMeleeSkill::Update()
{
	Casting();
	CoolDownSetup();
}

void cMeleeSkill::Render()
{
	RenderCube();
}
