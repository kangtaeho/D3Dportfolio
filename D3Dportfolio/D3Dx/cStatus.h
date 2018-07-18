#pragma once
#include "cMainUI.h"


class cInventory;
class cItem;
class Bitmap;
class cUIButton;
class cUiSkill;
struct tagSkillInfo
{
	Bitmap* Skill_Q;
	Bitmap* Skill_W;
	Bitmap* Skill_E;
	Bitmap* Skill_R;
	Bitmap* Skill_Passive;

	tagSkillInfo()
	{
		Skill_Q = NULL;
		Skill_W = NULL;
		Skill_E = NULL;
		Skill_R = NULL;
		Skill_Passive = NULL;
	};
};
struct tagStatus
{
	Bitmap* atkUp_texture;
	Bitmap* atkSpeed_texture;
	Bitmap* critical_texture;
	Bitmap* defense_texture;
	Bitmap* magic_texture;
	Bitmap* moveSpeed_texture;
	Bitmap* coolTime_texture;
	Bitmap* magicDefense_texture;
	float Atk;
	float AtkSpeed;
	float ciritical;
	float defense;
	float magic;
	float moveSpeed;
	float coolTime;
	float magicDefense;
	
	tagStatus() {
		atkUp_texture = NULL;
		atkSpeed_texture = NULL;
		critical_texture = NULL;
		defense_texture = NULL;
		magic_texture = NULL;
		moveSpeed_texture = NULL;
		coolTime_texture = NULL;
		magicDefense_texture = NULL;
		Atk = NULL;
		AtkSpeed = NULL;
		ciritical = NULL;
		defense = NULL;
		magic = NULL;
		moveSpeed = NULL;
		coolTime = NULL;
		magicDefense = NULL;
	};
};
struct tagHealthInfo
{
	Bitmap* HpBar;
	Bitmap* MpBar;

	float Hp;
	float Mp;

	tagHealthInfo()
	{
		Hp = NULL;
		Mp = NULL;
		HpBar = NULL;
		MpBar = NULL;
		
	}
};
struct tagPlayerInfo
{
	tagSkillInfo SkillInfo;
	tagStatus    StatusInfo;
	tagHealthInfo HealthInfo;
};

struct tagStatusGoldState
{
	Bitmap* Gold_units;
	Bitmap* Gold_tens;
	Bitmap* Gold_huans;
	Bitmap* Gold_thous;
	int goldIncreaseTime;
	int amount;
	int count;
	tagStatusGoldState() {
		amount = 0; //최대 9999;
		goldIncreaseTime = 0;
		count = 0;
	}
};

class cStatus : public cMainUI
{
private:

	RECT rc;
	float MaxHp;
	float CurrentHp;
	float hit;

	SYNTHESIZE(std::vector<cInventory*>, m_vecInven, vecInven);
	RECT* m_pRect;//클릭할 렉트;

	std::vector<cUiSkill*> m_pStatusSkillInfo;

	cUiSkill* m_pSkillInfo;
	std::vector<cInventory> m_pStatusInvenInfo;

	cInventory* m_pInvenInfo;
	std::vector<D3DXVECTOR3> m_vecInvenPos;

	bool m_pShopOpend;
	tagPlayerInfo*  m_pPlayerInfo;
	tagStatusGoldState m_pStatusGold;
	bool m_bIsHit;
	bool m_bCheckBar;
	float rcRight;
	float rcBottom;
	float rcSize;
	Bitmap* m_pStatusHealthBar;
	Bitmap* m_pStatusMpBar;
	D3DXMATRIX* WorldMatrix;
	D3DXMATRIX* matT;
	D3DXMATRIX* matS;
	D3DXVECTOR3* s;
	D3DXVECTOR3* t;
	Bitmap* m_pCharacterBar;
	Bitmap* m_pCharacterIcon;
	Bitmap* m_pStatusInventory;
	Bitmap* m_pStatusScreen;
	Bitmap* m_pBuffInfo;
	Bitmap* m_pStatusPlayerInfoIcon;
	Bitmap* m_pTeleport;
	cUIButton* m_pSkillButton;

	
	cUIButton* m_pShopButton;

public:
	cStatus();
	virtual ~cStatus();

	virtual void setup();
	virtual void update();
	virtual void release();
	virtual void render();
	

	void HitProgress();
	void setInventoryInfo();
	void GoldUpdate();
	void GoldRender();

	bool isClickedSkill(OUT RECT* Outrc, int index);
	void InvenUpdate();
	void InvenRender();
};

