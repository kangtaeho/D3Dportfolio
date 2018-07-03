#include "stdafx.h"
#include "cMainGame.h"

void cMainGame::addSprite()
{
	//여기다 2d텍스쳐 저장.

	//ui //jpg
	BITMAP->addTexture("./testFile/shop2.jpg");
	BITMAP->addTexture("./testFile/shop.jpg");
	//
	BITMAP->addTexture("./testFile/bought.jpg");
	BITMAP->addTexture("./testFile/seleted.jpg");
	BITMAP->addTexture("./testFile/wholeitem.jpg");
	BITMAP->addTexture("./testFile/recommand.jpg");
	BITMAP->addTexture("./testFile/purchase.jpg");
	//
	BITMAP->addTexture("./testFile/basicshoeEx.jpg");
	BITMAP->addTexture("./testFile/hammerEx.jpg");
	BITMAP->addTexture("./testFile/potionEx.jpg");
	BITMAP->addTexture("./testFile/RubyEx.jpg");
	BITMAP->addTexture("./testFile/shortswordEx.jpg");
	BITMAP->addTexture("./testFile/sword2Ex.jpg");
	BITMAP->addTexture("./testFile/sword3Ex.jpg");
	BITMAP->addTexture("./testFile/triforceEx.jpg");
	BITMAP->addTexture("./testFile/wardEx.jpg");
	
	//item //dds
	BITMAP->addTexture("./item/1001_Boots_of_Speed.dds");
	BITMAP->addTexture("./item/1036_Long_Sword.dds");
	BITMAP->addTexture("./item/1042_Dagger.dds");
	BITMAP->addTexture("./item/3044_Phage.dds");
	BITMAP->addTexture("./item/3057_Sheen.dds");
	BITMAP->addTexture("./item/3078_Trinity_Force.dds");
	BITMAP->addTexture("./item/3095_Orb_of_Valor.dds");
	BITMAP->addTexture("./item/3350_GreaterYellowTrinket.dds");
}