#include "stdafx.h"
#include "cStat.h"


cStat::cStat()
{
}


cStat::~cStat()
{
}

void cStat::setup()
{
	Screen = g_pTextureManager->addTexture("StatusScreen", "./status/StatusInfoScreen.dds", SUBUI, NULL);
	AttackSpeed = g_pTextureManager->addTexture("AtkSpeed", "./status/atkSpeedUp.dds", SUBUI, NULL);
	Atk = g_pTextureManager->addTexture("Atk", "./status/atkUp.dds", SUBUI, NULL);
	Defense = g_pTextureManager->addTexture("Defense", "./status/defenseUp.dds", SUBUI, NULL);
	MoveSpeed = g_pTextureManager->addTexture("MoveSpeed", "./status/moveSpeedUP.dds", SUBUI, NULL);

	AttackSpeedNum = g_pTextureManager->addTexture("AttackSpeedNum", "./status/StatusNum.dds", SUBUI, NULL);
	AtkNum =  g_pTextureManager->addTexture("AtkNum", "./status/StatusNum.dds", SUBUI, NULL);
	DefenseNum  = g_pTextureManager->addTexture("DefenseNum", "./status/StatusNum.dds", SUBUI, NULL);
	MoveSpeedNum = g_pTextureManager->addTexture("MoveSpeedNum", "./status/StatusNum.dds", SUBUI, NULL);

	AttackSpeedValue = 0;
	AtkValue = 0;
	DefenseValue = 0;
	MoveSpeedValue = 0;
}


void cStat::update()
{

}

void cStat::render()
{
	Screen->Render();
	AttackSpeed->Render();
	Atk->Render();
	Defense->Render();
	MoveSpeed->Render();
	AttackSpeedNum->Render();
	AtkNum->Render();
	DefenseNum->Render();
	MoveSpeedNum->Render();
}