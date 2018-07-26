#pragma once
#include "cBluePrint.h"
class Bitmap;

struct tagItemStat
{

	float Hp;
	float Mp;
	float Attack;
	float Defence;
	float Speed;
	float AttackSpeed;
	int price;
	ST_UI_SIZE m_stSize;
	std::string itemName;
	Bitmap* Itemtexture;
	Bitmap* ItemPriceTexture_f;
	Bitmap* ItemPriceTexture_s;
	Bitmap* ItemPriceTexture_t;
	tagItemState itemState;
	tagItemInformation itemInfo;

	SYNTHESIZE( bool, EffectToStat,Effected);
};

class citem : public cBluePrint
{
private:
	SYNTHESIZE(tagItemStat*, m_pItemStat, ItemInfo);
public:
	citem();
	virtual ~citem();

 	virtual void setup(const char* itemName, const char* textureFileName, int itemState, int iteminfo);
	virtual void render();

	Bitmap* GetItemTexture() { return m_pItemStat->Itemtexture; }
};

