#include "stdafx.h"
#include "cToxicSkill.h"


cToxicSkill::cToxicSkill()
{
}


cToxicSkill::~cToxicSkill()
{
}

HRESULT cToxicSkill::Setup(SKILL_TYPE skillType, float damage, float range, float posSpeed, float castingTime, float cooldown, float removeTime, bool isTarget, const char * name)
{
	cSkill::Setup(skillType, damage, range, posSpeed, castingTime, cooldown, removeTime, isTarget, name);
	CreateAOEMesh(false, 200.0f);
	return S_OK;
}

void cToxicSkill::Release()
{
	cSkill::Release();
}

void cToxicSkill::Update()
{
	Casting();
	CoolDownSetup();
	Move();
	RemoveTarget();
	AutoFire();
	DamagedToxic();
}

void cToxicSkill::Render()
{
	RenderCube();
	//RenderAOEMesh();
}
