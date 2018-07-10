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

	//LPCSkinnedMesh�� �����ؼ� ����ϼ���
	LPCSKINNEDMESH AddXfile(const char* name, const char* szFolder, const char* szFile);
	LPCSKINNEDMESH FindXfile(const char* name);
};

/*����

LPCSkinnedMesh Teemo;

Setup()
{
	Teemo = AddXfile("Teemo", "character", "(m_sName + ".x").c_str()");
}

Update()
{
	Teemo->setAnimation("Run");						�̷��� �޸��ٰ� Idle
	Teemo->setAnimation("Run", "Run");				�̷��� �޸��ٰ� ��� �޸�
	Teemo->setAnimation("Run", "Run", false);		�̷��� �޸��ٰ� ����
	Teemo->setWorld(m_matWorld);					�����Ʈ������ �־��ݴϴ�~
}

��ü���� ���� xFileManager�� ���ӳ�忡�� �����ϴ�.
*/