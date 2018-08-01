#include "stdafx.h"
#include "cRangeSkill.h"


cRangeSkill::cRangeSkill()
{
}


cRangeSkill::~cRangeSkill()
{
}

HRESULT cRangeSkill::Setup(
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

	cSkill::Setup(skillType, damage, range, posSpeed, castingTime, cooldown, removeTime, isTarget, name);

	return S_OK;
}

void cRangeSkill::Release()
{
	cSkill::Release();
}

void cRangeSkill::Update()
{
	Casting();
	CoolDownSetup();
	Move();
	RemoveTarget();
	AutoFire();
	UpdateDamageRender();
}

void cRangeSkill::Render()
{

	 if (m_pTargetPos && m_pPlayerPos)
	 {
	 	D3DXVECTOR3 v = (*m_pTargetPos - *m_pPlayerPos);
	 	float le = D3DXVec3Length(&v);
	 	//g_pFontManager->TextFont(100, 140, D3DXVECTOR3(255, 0, 255), " °Å¸® %0.3f ", le);
	 }
	
	RenderCube();
	RenderDR();
}
