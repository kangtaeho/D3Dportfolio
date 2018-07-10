#pragma once
#include "cSkinnedMesh.h"

#define g_pXfileManager cXManager::GetInstance()

class cSkinnedMesh;

class cXManager
{
	SINGLETONE(cXManager);

private:
	std::map<std::string, cSkinnedMesh*>						m_mapXfile;

	typedef std::map<std::string, cSkinnedMesh*>::iterator		miXfile;

public:
	void Release();

	void AddXfile(const char* name, const char* szFolder, const char* szFile);
	void Update(const char* name);
	void Render(const char* name, D3DXMATRIX* matWorld);
	cSkinnedMesh* FindXfile(const char* name);

	void setAnimation(const char* name, int nIndex);
};

