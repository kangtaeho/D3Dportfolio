#include "stdafx.h"
#include "cUiSkill.h"


cUiSkill::cUiSkill()
{
}


cUiSkill::~cUiSkill()
{
}


void cUiSkill::update()
{
	SkillInfo->update();
}
void cUiSkill::render()
{
	SkillInfo->Render();
}
