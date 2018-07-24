#include "stdafx.h"
#include "citem.h"
#include "Bitmap.h"

citem::citem()
{
}
citem::~citem()
{
	
}
void citem::setup(const char* itemName,const char* textureFileName,int itemState, int iteminfo)
{
	D3DXIMAGE_INFO stImageInfo;

	m_pItemStat = new tagItemStat;
	m_pItemStat->itemName = itemName;
	m_pItemStat->itemState = (tagItemState)itemState;
	m_pItemStat->itemInfo = (tagItemInformation)iteminfo;
	m_pItemStat->Itemtexture = g_pTextureManager->addTexture(itemName, textureFileName, ITEM, m_pItemStat->itemState);
	stImageInfo = m_pItemStat->Itemtexture->GetImageInfo();
	m_pItemStat->m_stSize.nHeight = stImageInfo.Height;
	m_pItemStat->m_stSize.nWidth = stImageInfo.Width;
	m_pItemStat->price = 0;
	m_pItemStat->Attack = 0.0f;
	m_pItemStat->Defence = 0.0f;
	m_pItemStat->Speed = 0.0f;
	m_pItemStat->AttackSpeed = 0.0f;
	m_pItemStat->Hp = 0.0f;
	m_pItemStat->Mp = 0.0f;
	m_pItemStat->SetEffected(false);
	if(m_pItemStat->itemInfo != CONSUME)
	m_pItemStat->Itemtexture->setScale(D3DXVECTOR3(0.5f, 0.5f, 0.0f));

	m_pItemStat->ItemPriceTexture_f = g_pTextureManager->addTexture("itemGoldNum", "./item/itemNum.dds", ANIMATION, 10.0f, 1.0f);
	m_pItemStat->ItemPriceTexture_s = g_pTextureManager->addTexture("itemGoldNum", "./item/itemNum.dds", ANIMATION, 10.0f, 1.0f);
	m_pItemStat->ItemPriceTexture_t = g_pTextureManager->addTexture("itemGoldNum", "./item/itemNum.dds", ANIMATION, 10.0f, 1.0f);
	m_pItemStat->ItemPriceTexture_f->setScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_pItemStat->ItemPriceTexture_s->setScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_pItemStat->ItemPriceTexture_t->setScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void citem::render()
{
	m_pItemStat->Itemtexture->Render();


	m_pItemStat->ItemPriceTexture_f->update(0);
	if (m_pItemStat->price / 100 != 0)
	m_pItemStat->ItemPriceTexture_f->aniRender();

	m_pItemStat->ItemPriceTexture_s->update(0);
	m_pItemStat->ItemPriceTexture_t->update(0);

	m_pItemStat->ItemPriceTexture_s->aniRender();
	m_pItemStat->ItemPriceTexture_t->aniRender();

	cBluePrint::render();
}
