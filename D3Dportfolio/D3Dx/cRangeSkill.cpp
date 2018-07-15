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
	//RemoveCubeTime();
	RemoveTarget();
	AutoFire();
}

void cRangeSkill::Render()
{
	
	 g_pFontManager->TextFont(100, 100, " 쿨다운 %0.2f ", m_fCurrentCooldown);
	 g_pFontManager->TextFont(100, 120, " 오브젝트재거 시간 %0.2f ", m_fPassedTime);
	 
	 if (m_pTargetPos && m_pPlayerPos)
	 {
	 	D3DXVECTOR3 v = (*m_pTargetPos - *m_pPlayerPos);
	 	float le = D3DXVec3Length(&v);
	 	g_pFontManager->TextFont(100, 140, " 거리 %0.3f ", le);
	 }
	

	RenderCube();
}
