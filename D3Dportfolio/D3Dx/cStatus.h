#pragma once
#include "cMainUI.h"
#include "citem.h"
#include "cHealthProgress.h"
class cInventory;
class Bitmap;
class cUIButton;
class cUiSkill;
class cStat;
class cPlayer;
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

struct tagStatNum
{
	Bitmap* AttackSpeedNum_unit;
	Bitmap* AttackSpeedNum_ten;
	Bitmap* AttackSpeedNum_huand;

	Bitmap* AtkNum_unit;
	Bitmap* AtkNum_ten;
	Bitmap* AtkNum_huand;

	Bitmap* DefenseNum_unit;
	Bitmap* DefenseNum_ten;
	Bitmap* DefenseNum_huand;

	Bitmap* MoveSpeedNum_unit;
	Bitmap* MoveSpeedNum_ten;
	Bitmap* MoveSpeedNum_huand;

	tagStatNum()
	{
		AttackSpeedNum_unit = g_pTextureManager->addTexture("AttackSpeedNum_unit", "./status/StatusNum.dds", ANIMATION,10.0f,1.0f);
		AttackSpeedNum_ten = g_pTextureManager->addTexture("AttackSpeedNum_ten", "./status/StatusNum.dds", ANIMATION, 10.0f, 1.0f);
		AttackSpeedNum_huand = g_pTextureManager->addTexture("AttackSpeedNum_huand", "./status/StatusNum.dds", ANIMATION, 10.0f, 1.0f);

		AtkNum_unit = g_pTextureManager->addTexture("AtkNum_unit", "./status/StatusNum.dds", ANIMATION, 10.0f, 1.0f);
		AtkNum_ten = g_pTextureManager->addTexture("AtkNum_ten", "./status/StatusNum.dds", ANIMATION, 10.0f, 1.0f);
		AtkNum_huand = g_pTextureManager->addTexture("AtkNum_huand", "./status/StatusNum.dds", ANIMATION, 10.0f, 1.0f);

		DefenseNum_unit = g_pTextureManager->addTexture("DefenseNum_unit", "./status/StatusNum.dds", ANIMATION, 10.0f, 1.0f);
		DefenseNum_ten = g_pTextureManager->addTexture("DefenseNum_ten", "./status/StatusNum.dds", ANIMATION, 10.0f, 1.0f);
		DefenseNum_huand = g_pTextureManager->addTexture("DefenseNum_huand", "./status/StatusNum.dds", ANIMATION, 10.0f, 1.0f);

		MoveSpeedNum_unit = g_pTextureManager->addTexture("MoveSpeedNum_unit", "./status/StatusNum.dds", ANIMATION, 10.0f, 1.0f);
		MoveSpeedNum_ten = g_pTextureManager->addTexture("MoveSpeedNum_ten", "./status/StatusNum.dds", ANIMATION, 10.0f, 1.0f);
		MoveSpeedNum_huand = g_pTextureManager->addTexture("MoveSpeedNum_huand", "./status/StatusNum.dds", ANIMATION, 10.0f, 1.0f);
	}
};
struct tagStatInfo
{
	Bitmap* Screen;
	Bitmap* AttackSpeed;
	Bitmap* Atk;
	Bitmap* Defense;
	Bitmap* MoveSpeed;

	tagStatNum* StatNum;
	tagStatInfo()
	{
		Screen = g_pTextureManager->addTexture("StatusScreen", "./status/StatusInfoScreen.dds", SUBUI, NULL);
		AttackSpeed = g_pTextureManager->addTexture("AtkSpeed", "./status/atkSpeedUp.dds", SUBUI, NULL);
		Atk = g_pTextureManager->addTexture("Atk", "./status/atkUp.dds", SUBUI, NULL);
		Defense = g_pTextureManager->addTexture("Defense", "./status/defenseUp.dds", SUBUI, NULL);
		MoveSpeed = g_pTextureManager->addTexture("MoveSpeed", "./status/moveSpeedUP.dds", SUBUI, NULL);
			
		StatNum = new tagStatNum;
	}
};
class cStatus : public cMainUI
{
private:
	cHealthProgress * m_pHealthProgress;
	cPlayer* m_pPlayer;
	float prevRectSize;
	bool m_bUsedSkill;
	bool m_bSelected;
	Bitmap* m_pSkill_Done_Q;
	Bitmap* m_pSkill_Done_W;
	Bitmap* m_pSkill_Done_E;
	Bitmap* m_pSkill_Done_R;

	tagStatInfo*  m_pStatInfo;

	std::string m_sSkill_Name;

	RECT HpRc;
	RECT MpRc;
	
	RECT* m_pRect;//클릭할 렉트;

	std::vector<cUiSkill*> m_pStatusSkillInfo;
	std::map<std::string,cUiSkill*> m_mapStatusSkillInfo;


	cUiSkill* m_pSkillInfo;
	std::vector<cInventory*> m_pStatusInvenInfo;

	cInventory* m_pInvenInfo;
	std::vector<D3DXVECTOR3> m_vecInvenPos;

	bool m_pShopOpend;
	tagPlayerInfo*  m_pPlayerInfo;
	tagStatusGoldState m_pStatusGold;

	//맞았니 , 스킬썼니 체크

	
	float HprcRight;
	float HprcBottom;
	float HprcSize;

	bool m_bIsUsed;
	

	float MpRcRight;
	float MpRcBottom;
	float MpRcSize;
	//
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
	
	cUIButton* m_pSkillButton;

	
	cUIButton* m_pShopButton;


	
	SYNTHESIZE(Bitmap*, m_pTeleport, BTelePort);
	SYNTHESIZE(int, AttackSpeedValue, AttackSpeed);
	SYNTHESIZE(int, AtkValue, Atk);
	SYNTHESIZE(int, DefenseValue, Defense);
	SYNTHESIZE(int, MoveSpeedValue, MoveSpeed);

	SYNTHESIZE(bool, m_bIsHit, IsHit);
	SYNTHESIZE(bool, m_bCheckHpBar, CheckHpBar);
	SYNTHESIZE(bool, m_bCheckMpBar, CheckMpBar);
	// 스텟치
	SYNTHESIZE(int, MaxHp, MAXHP);
	SYNTHESIZE(int, CurrentHp, CURRENTHP);
	SYNTHESIZE(int, hit, HitValue);
	SYNTHESIZE(int, MaxMp, MAXMP);
	SYNTHESIZE(int, CurrentMp, CURRENTMP);
	SYNTHESIZE(int, UsedMp, USEDMP);
	//
	SYNTHESIZE(std::vector<cInventory*>, m_vecInven, vecInven);

	SYNTHESIZE(cUIButton*, buttonState, ButtonState);
	SYNTHESIZE(citem, tempItemInfo, tempItemInform);
	SYNTHESIZE(bool, recorrect, Recorrect);

public:
	cStatus();
	virtual ~cStatus();

	virtual void setup();
	virtual void update();
	virtual void release();
	virtual void render();
	

	void reSizeProgressBar();

	void HitProgress();
	void setInventoryInfo();
	void GoldUpdate() override;
	void GoldRender() override;
	bool isClickedSkill(OUT RECT* Outrc, int index);
	void InvenUpdate();
	void InvenRender();

	virtual bool isClickUi() override;

	void setAddressLinkWithPlayer(cPlayer* player) { m_pPlayer = player; }
	void setAddressLinkWithHealthProgress(cHealthProgress* hp) { m_pHealthProgress = hp; }
};

