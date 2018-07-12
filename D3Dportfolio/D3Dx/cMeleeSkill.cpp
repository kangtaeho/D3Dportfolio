#include "stdafx.h"
#include "cMeleeSkill.h"


cMeleeSkill::cMeleeSkill()
{
}


cMeleeSkill::~cMeleeSkill()
{
}

HRESULT cMeleeSkill::Setup(
	SKILL_TYPE skillType,
	float damage,
	float range,
	float posSpeed,
	float castingTime,
	float cooldown,
	float removeTime,
	bool isTarget,
	const char* name)
{
	cSkill::Setup(skillType, damage, range, posSpeed, castingTime,cooldown, removeTime, isTarget, name);

	return S_OK;
}

void cMeleeSkill::Release()
{
	cSkill::Release();
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
