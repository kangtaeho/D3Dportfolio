#include "stdafx.h"
#include "cDamageRender.h"


cDamageRender::cDamageRender()
	:m_fScale(3.0f)
	,m_fSpeed(2.0f)
	,m_fCount(0.0f)
	,m_bIsFire(false)
	,m_bIs3rd(false)
{
}


cDamageRender::~cDamageRender()
{
}

void cDamageRender::Setup(std::string texName)
{

	g_pTextureManager->addTexture(texName, "./select/number02.png", ANIMATION, 10, 1);
	m_p1 = g_pTextureManager->findTexture(texName);
	m_p1->setPosition(D3DXVECTOR3(0, 0, 0));
	m_p1->setScale(D3DXVECTOR3(1, 1, 1));
	m_p1->setCurrentFrame(0);

	g_pTextureManager->addTexture(texName.append("10"), "./select/number02.png", ANIMATION, 10, 1);
	m_p10 = g_pTextureManager->findTexture(texName);
	m_p10->setPosition(D3DXVECTOR3(0, 0, 0));
	m_p10->setScale(D3DXVECTOR3(1, 1, 1));
	m_p10->setCurrentFrame(0);

	g_pTextureManager->addTexture(texName.append("10"), "./select/number02.png", ANIMATION, 10, 1);
	m_p100 = g_pTextureManager->findTexture(texName);
	m_p100->setPosition(D3DXVECTOR3(0, 0, 0));
	m_p100->setScale(D3DXVECTOR3(1, 1, 1));
	m_p100->setCurrentFrame(0);

}

void cDamageRender::Update()
{
	if (m_p1)
		m_p1->update(0);

	if (m_p10)
		m_p10->update(0);

	if (m_p100)
		m_p100->update(0);

	if (m_bIsFire)
	{
		m_p1->setScale(D3DXVECTOR3(m_fScale, m_fScale, m_fScale));
		m_p10->setScale(D3DXVECTOR3(m_fScale, m_fScale, m_fScale));
		m_p100->setScale(D3DXVECTOR3(m_fScale, m_fScale, m_fScale));

		m_vPos1 = D3DXVECTOR3(m_vPos1.x, m_vPos1.y + m_fSpeed, m_vPos1.z);
		m_vPos2 = D3DXVECTOR3(m_vPos2.x, m_vPos2.y + m_fSpeed, m_vPos2.z);
		m_vPos3 = D3DXVECTOR3(m_vPos3.x, m_vPos3.y + m_fSpeed, m_vPos3.z);

		m_p1->setPosition(m_vPos1);
		m_p10->setPosition(m_vPos2);
		m_p100->setPosition(m_vPos3);

		m_fCount += m_fSpeed;

		if (m_fScale > 1.0f) m_fScale -= 0.2f;

		if (m_fCount > 60.f)
		{
			m_bIsFire = false;
			m_bIs3rd = false;
			m_fScale = 3.0f;
			m_fCount = 0;
		}

	}
}

void cDamageRender::Render()
{
	if (m_bIsFire)
	{
		if (m_p1)
			m_p1->aniRender();

		if (m_p10)
			m_p10->aniRender();

		if (m_p100&&m_bIs3rd)
			m_p100->aniRender();
	}

}

void cDamageRender::Release()
{

}

void cDamageRender::ShowDamage(D3DXVECTOR3 target, int damage)
{
	D3DXVECTOR3 tempposition(0, 0, 0);
	D3DXMATRIX WorldMatrix, matProj, matViewPort, matView;
	D3DXMatrixTranslation(&WorldMatrix, target.x, target.y, target.z);
	D3DVIEWPORT9 tempViewPort;
	g_pD3DDevice->GetViewport(&tempViewPort); //
	D3DXMatrixIdentity(&matViewPort);
	matViewPort._11 = tempViewPort.Width / (float)2;
	matViewPort._22 = -(int)tempViewPort.Height / (float)2;
	matViewPort._33 = tempViewPort.MaxZ - tempViewPort.MinZ;
	matViewPort._41 = tempViewPort.X + tempViewPort.Width / (float)2;
	matViewPort._42 = tempViewPort.Y + tempViewPort.Height / (float)2;
	matViewPort._43 = tempViewPort.MinZ;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);

	WorldMatrix = WorldMatrix * matView * matProj * matViewPort;
	D3DXVec3TransformCoord(&tempposition, &tempposition, &WorldMatrix);

	D3DXVECTOR3 pos1(tempposition.x + 15, tempposition.y-50, 0);
	D3DXVECTOR3 pos10(tempposition.x , tempposition.y-50, 0);
	D3DXVECTOR3 pos100(tempposition.x - 15, tempposition.y - 50, 0);

	m_vPos1 = pos1;
	m_vPos2 = pos10;
	m_vPos3 = pos100;

	m_p1->setPosition(pos1);
	m_p10->setPosition(pos10);
	m_p100->setPosition(pos100);

	int third = damage / 100;
	int second = (damage-(third*100)) / 10;
	int first = (damage -(third * 100)) % 10;

	if (damage >= 100)	m_bIs3rd = true;

	m_p1->setCurrentFrame(first);
	m_p10->setCurrentFrame(second);
	m_p100->setCurrentFrame(third);

	m_bIsFire = true;

}
