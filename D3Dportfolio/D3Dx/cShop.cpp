#include "stdafx.h"
#include "cShop.h"


cShop::cShop()
{
}


cShop::~cShop()
{
}


void cShop::setup()
{

}
void cShop::update()
{

}

void cShop::render()
{
	//상점 열림
	BITMAP->setScale("./testFile/shop.jpg", D3DXVECTOR3(0.50f, 0.50f, 0.50f));
	BITMAP->setPosition("./testFile/shop.jpg", D3DXVECTOR3(300, 0, 0));
	BITMAP->Render("./testFile/shop.jpg");

	//아이템위치세팅
	setItemPosition();
}
void cShop::setItemPosition()
{
	BITMAP->setScale("./item/1001_Boots_of_Speed.dds", ITEMSIZE);
	BITMAP->Render("./item/1001_Boots_of_Speed.dds");

	BITMAP->setScale("./item/1036_Long_Sword.dds", ITEMSIZE);
	BITMAP->Render("./item/1036_Long_Sword.dds");

	BITMAP->setScale("./item/1042_Dagger.dds", ITEMSIZE);
	BITMAP->Render("./item/1042_Dagger.dds");

	BITMAP->setScale("./item/3044_Phage.dds", ITEMSIZE);
	BITMAP->Render("./item/3044_Phage.dds");

	BITMAP->setScale("./item/3057_Sheen.dds", ITEMSIZE);
	BITMAP->Render("./item/3057_Sheen.dds");

	BITMAP->setScale("./item/3078_Trinity_Force.dds", ITEMSIZE);
	BITMAP->Render("./item/3078_Trinity_Force.dds");

	BITMAP->setScale("./item/3095_Orb_of_Valor.dds", ITEMSIZE);
	BITMAP->Render("./item/3095_Orb_of_Valor.dds");

	BITMAP->setScale("./item/3350_GreaterYellowTrinket.dds", ITEMSIZE);
	BITMAP->Render("./item/3350_GreaterYellowTrinket.dds");
}