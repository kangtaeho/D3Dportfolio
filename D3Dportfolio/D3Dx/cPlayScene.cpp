#include "stdafx.h"
#include "cPlayScene.h"
#include "cPlayer.h"
#include "cCollisionMap.h"
#include "cController.h"

cPlayScene::cPlayScene()
	:m_pPlayer(NULL)
{
}


cPlayScene::~cPlayScene()
{
	// ����������� Release���� �޸� ������ ����
}

HRESULT cPlayScene::Setup()
{
	m_pPlayer = new cPlayer;
	m_pPlayer->Setup();

	// g_pXfileManager->AddXfile("Map", "summoner rift", "summoner_rift.x");

	D3DXMATRIX matWorld, matT, matS, matR;
	D3DXMatrixRotationY(&matR, D3DX_PI);
	D3DXMatrixScaling(&matS, 300.0f, 300.0f, 300.0f);
	matWorld = matR * matS;
	std::vector<D3DXVECTOR3> vMapGround;
	std::vector<D3DXVECTOR3> vMapObject;
	cCollisionMap colMap;
	colMap.LoadSurface(vMapGround, "map collision", "map_skp_sample.obj", &matWorld);		// �ٴ�
	colMap.LoadSurface(vMapObject, "map collision", "map_collision.obj", &matWorld);


	//�׽�Ʈ�� ��Ʈ�ѷ�
	m_pController = new cController;

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

	if (m_pController)
		m_pController->Update();
}

void cPlayScene::Render()
{
	if (m_pPlayer)
		m_pPlayer->Render();

	{//���߰�
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		D3DXMATRIX mat, matS;
		D3DXMatrixIdentity(&mat);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixScaling(&matS, 300.0f, 300.0f, 300.0f);
		mat = matS;
		// g_pXfileManager->Render("Map", &mat);
	}

	if (m_pController)
		m_pController->Render();
}
