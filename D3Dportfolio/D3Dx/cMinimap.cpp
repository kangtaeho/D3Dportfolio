#include "stdafx.h"
#include "cMinimap.h"


cMinimap::cMinimap()
{
}


cMinimap::~cMinimap()
{
}

void cMinimap::setup()
{
	m_MapTexture = g_pTextureManager->addTexture("MiniMap", "./status/GetIsPlatform.dds",UI, NULL);

	m_MapTexture->setPosition(D3DXVECTOR3(1150, 650, 0));
}
void cMinimap::update()
{
	m_MapTexture->update();
}
void cMinimap::Render()
{
	m_MapTexture->Render();
}
