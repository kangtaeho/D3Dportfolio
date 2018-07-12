#pragma once
#include "cSkill.h"
class cObjectSkill :
	public cSkill
{
public:
	cObjectSkill();
	virtual~cObjectSkill();


	virtual HRESULT Setup(
		SKILL_TYPE skillType,
		float damage,
		float range,
		float posSpeed,
		float castingTime,
		float cooldown,
		float removeTime,
		bool isTarget,
		const char* name);

	virtual void	Release();
	virtual void	Update();
	virtual void	Render();

};

