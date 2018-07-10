#include "stdafx.h"
#include "cXManager.h"


cXManager::cXManager()
{
}


cXManager::~cXManager()
{
}

void cXManager::Release()
{
	for (auto p : m_mapXfile)
	{
		SAFE_DELETE(p.second);
	}
}

void cXManager::AddXfile(const char* name, const char* szFolder, const char* szFile)
{
	cSkinnedMesh* temp = new cSkinnedMesh;
	temp->Setup(szFolder, szFile);
	m_mapXfile.insert(std::make_pair(name, temp));
}

void cXManager::Update(const char* name)
{
	if (FindXfile(name))
		FindXfile(name)->Update();
}

void cXManager::Render(const char* name, D3DXMATRIX* matWorld)
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, matWorld);
	if(FindXfile(name))
		FindXfile(name)->Render(NULL);
}

cSkinnedMesh* cXManager::FindXfile(const char* name)
{
	miXfile p = m_mapXfile.find(name);
	if (p != m_mapXfile.end())return p->second;
	return NULL;
}
