#include "stdafx.h"
#include "cCharacter.h"
#include "cRayPicking.h"


cCharacter::cCharacter()
	: m_vPosition(0, 0, 0)
	, m_fRotY(0.0f)
	, m_vNextPosition(0, 0, 0)
	, m_pSkinnedMesh(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacter::~cCharacter()
{
	SAFE_RELEASE(m_pAnimController);
}

void cCharacter::Setup(const char* name)
{
	m_pSkinnedMesh = g_pXfileManager->AddXfile(name, "character", (std::string(name) + ".x").c_str());
	m_pSkinnedMesh->CloneAniController(&m_pAnimController);
}

void cCharacter::Release()
{
}

void cCharacter::Update()
{

}

void cCharacter::Render()
{
	D3DXMATRIX	matWorld, matS, matR, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//애니메이션을 넣을때 cAction을 상속받은 후 아래처럼 사용
	UpdateAnimation();
	m_pSkinnedMesh->Update(m_pAnimController);
}
