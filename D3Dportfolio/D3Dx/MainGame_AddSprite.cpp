#include "stdafx.h"
#include "cMainGame.h"

void cMainGame::addSprite()
{
	//여기다 2d텍스쳐 저장.

	//ui //dds

	//
	g_pTextureManager->addTexture("selecteButton", "./testFile/selected2.dds", BUTTON, NULL);

	g_pTextureManager->addTexture("purchaseButton", "./testFile/purchase.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("purchaseButtonDown", "./testFile/purchaseButtonDown.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("purchaseButtonOver", "./testFile/purchaseButtonOver.dds", BUTTON, NULL);

	g_pTextureManager->addTexture("saleButtonDown", "./testFile/saleButtonDown.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("saleButtonOver", "./testFile/saleButtonOver.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("saleButtonUp", "./testFile/saleButtonUp.dds", BUTTON, NULL);

	g_pTextureManager->addTexture("returnButtonUp", "./testFile/returnButtonUp.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("returnButtonOver", "./testFile/returnButtonOver.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("returnButtonDown", "./testFile/returnButtonDown.dds", BUTTON, NULL);

	g_pTextureManager->addTexture("wholeButtonDown", "./testFile/wholeButtonDown.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("wholeButtonOver", "./testFile/wholeButtonOver.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("wholeButtonUp", "./testFile/wholeButtonUp.dds", BUTTON, NULL);

	g_pTextureManager->addTexture("recommandButtonUp", "./testFile/recommandButtonUp.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("recommandButtonOver", "./testFile/recommandButtonOver.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("recommandButtonDown", "./testFile/recommandButtonDown.dds", BUTTON, NULL);

	g_pTextureManager->addTexture("ListBoxTrue", "./testFile/ListBoxTrue.dds", BUTTON, NULL);
	g_pTextureManager->addTexture("ListBoxFalse", "./testFile/ListBoxFalse.dds", BUTTON, NULL);



	
	//
	//g_pTextureManager->addTexture("""./testFile/basicshoeEx.dds");
	//g_pTextureManager->addTexture("./testFile/hammerEx.dds");
	//g_pTextureManager->addTexture("./testFile/potionEx.dds");
	//g_pTextureManager->addTexture("./testFile/RubyEx.dds");
	//g_pTextureManager->addTexture("./testFile/shortswordEx.dds");
	//g_pTextureManager->addTexture("./testFile/sword2Ex.dds");
	//g_pTextureManager->addTexture("./testFile/sword3Ex.dds");
	//g_pTextureManager->addTexture("./testFile/triforceEx.dds");
	//g_pTextureManager->addTexture("./testFile/wardEx.dds");
}