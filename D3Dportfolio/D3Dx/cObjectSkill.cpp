#include "stdafx.h"
#include "cObjectSkill.h"


cObjectSkill::cObjectSkill()
{
}


cObjectSkill::~cObjectSkill()
{
}

HRESULT cObjectSkill::Setup(SKILL_TYPE skillType, 
	float damage, 
	float range, 
	float posSpeed, 
	float castingTime, 
	float cooldown, 
	float removeTime, 
	bool isTarget, 
	const char * name)
{
	cSkill::Setup(skillType, damage, range, posSpeed, castingTime, cooldown, removeTime, isTarget, name);
	CreateAOEMesh(10.0f, false, 10.0f);

	return S_OK;
}

void cObjectSkill::Release()
{
	cSkill::Release();
}

void cObjectSkill::Update()
{
	Casting();
	CoolDownSetup();
	MeshMove();
	RemoveMeshTime();	// �ð��� �ى����� �ڵ������� ó��
	AutoFire();
}

void cObjectSkill::Render()
{
	g_pFontManager->TextFont(10, 500, "%d", CooldownTimer());
	RenderVecMesh();
	RenderAOEMesh();
}
