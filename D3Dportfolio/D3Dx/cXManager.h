#pragma once
#include "cSkinnedMesh.h"

#define g_pXfileManager cXManager::GetInstance()

class cXManager
{
	SINGLETONE(cXManager);

private:
	std::map<std::string, LPCSKINNEDMESH>						m_mapXfile;

	typedef std::map<std::string, LPCSKINNEDMESH>::iterator		miXfile;

public:
	void Release();

	//LPCSkinnedMesh를 선언해서 사용하세요
	LPCSKINNEDMESH AddXfile(const char* name, const char* szFolder, const char* szFile);
	LPCSKINNEDMESH FindXfile(const char* name);
};

/*사용법

LPCSkinnedMesh	Teemo;

Setup()
{
	Teemo = AddXfile("Teemo", "character", "(m_sName + ".x").c_str()");
	Teemo->CloneAniController(&m_pAnimController);
}

Update()
{

}

Render()
{
	D3DXMATRIX	matWorld, matS, matR, matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixRotationY(&matR, m_fRotY);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	matWorld = matS * matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	UpdateAnimation();
	Teemo->Update(m_pAnimController);
}
전체적인 것은 xFileManager를 게임노드에서 돌립니다.
*/