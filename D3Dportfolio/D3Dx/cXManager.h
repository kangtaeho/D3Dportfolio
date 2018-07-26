#pragma once
#include "cSkinnedMesh.h"

#define g_pXfileManager cXManager::GetInstance()

class cXManager
{
	SINGLETONE(cXManager);

private:
	std::map<std::string, LPCSKINNEDMESH>						m_mapXfile;

	typedef std::map<std::string, LPCSKINNEDMESH>::iterator		miXfile;

	FILE* fp;
	std::vector<std::string> m_vecAllFileName;
	std::vector<std::string> m_vecAllFolderName;
	std::vector<int>			AllFileSize;
	std::vector<int>			LoadFileSize;
	int FileIndex;

public:
	bool Setup(int& allfilesize, int& loadfilesize);
	void Release();

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