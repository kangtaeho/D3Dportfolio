#include "stdafx.h"
#include "cPlayScene.h"
#include "cPlayer.h"
#include "cSphere.h"
#include "cCollisionMap.h"

cPlayScene::cPlayScene()
	: m_pPlayer(NULL)
{
}


cPlayScene::~cPlayScene()
{
	// 사용하지말고 Release에서 메모리 해제를 하자
}

HRESULT cPlayScene::Setup()
{

	//g_pXfileManager->AddXfile("Map", "summoner rift", "summoner_rift.x");

	D3DXMATRIX matWorld, matT, matS, matR;
	D3DXMatrixRotationY(&matR, D3DX_PI);
	D3DXMatrixScaling(&matS, 300.0f, 300.0f, 300.0f);
	matWorld = matR * matS;
	std::vector<D3DXVECTOR3> vMapGround;
	std::vector<D3DXVECTOR3> vMapObject;
	
	colMap = new cCollisionMap;
	//colMap->LoadSurface(vMapGround, "map collision", "map_skp_sample.obj", &matWorld);		// 바닥
	//colMap->LoadSurface(vMapObject, "map collision", "map_collision.obj", &matWorld);

	m_pPlayer = new cPlayer;
	m_pPlayer->Setup("Teemo");
	m_pPlayer->setMap(colMap->getMap());						// 바닥
	m_pPlayer->setCollisionMap(colMap->getCollisionMap());		// 벽충돌인듯

	return S_OK;
}

void cPlayScene::Release()
{
	delete m_pPlayer;

}

void cPlayScene::Update()
{
	if (m_pPlayer)
		m_pPlayer->Update();
}

void cPlayScene::Render()
{
	if (m_pPlayer)
		m_pPlayer->Render();

	{//맵추가
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		D3DXMATRIX mat, matS;
		D3DXMatrixIdentity(&mat);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixScaling(&matS, 300.0f, 300.0f, 300.0f);
		mat = matS;
	}

	// colMap->Render();

}
