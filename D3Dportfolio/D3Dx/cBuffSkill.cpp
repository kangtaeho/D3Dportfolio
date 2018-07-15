#include "stdafx.h"
#include "cBuffSkill.h"


cBuffSkill::cBuffSkill()
{
}


cBuffSkill::~cBuffSkill()
{
}

HRESULT cBuffSkill::Setup(SKILL_TYPE skillType, float damage, float range, float posSpeed, float castingTime, float cooldown, float removeTime, bool isTarget, const char * name)
{

	cSkill::Setup(skillType, damage, range, posSpeed, castingTime, cooldown, removeTime, isTarget, name);
	return S_OK;
}

void cBuffSkill::Release()
{
}

void cBuffSkill::Update()
{
	Casting();
	CoolDownSetup();
	BuffEnd();
	ReadyIsCasting();
}

void cBuffSkill::Render()
{
}
