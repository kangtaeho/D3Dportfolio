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
	void Update();
	void Render();

	//LPCSkinnedMesh를 선언해서 사용하세요
	LPCSKINNEDMESH AddXfile(const char* name, const char* szFolder, const char* szFile);
	LPCSKINNEDMESH FindXfile(const char* name);
};

/*사용법

LPCSkinnedMesh Teemo;

Setup()
{
	Teemo = AddXfile("Teemo", "character", "(m_sName + ".x").c_str()");
}

Update()
{
	Teemo->setAnimation("Run");						이러면 달리다가 Idle
	Teemo->setAnimation("Run", "Run");				이러면 달리다가 계속 달림
	Teemo->setAnimation("Run", "Run", false);		이러면 달리다가 멈춤
	Teemo->setWorld(m_matWorld);					월드매트릭스를 넣어줍니다~
}

전체적인 것은 xFileManager를 게임노드에서 돌립니다.
*/