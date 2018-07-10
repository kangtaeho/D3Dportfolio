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

void cXManager::Update()
{
	for (auto p : m_mapXfile)
	{
		p.second->Update();
	}
}

void cXManager::Render()
{
	for (auto p : m_mapXfile)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &p.second->GetWorld());
		p.second->Render(NULL);
	}
}

LPCSKINNEDMESH cXManager::AddXfile(const char* name, const char* szFolder, const char* szFile)
{
	cSkinnedMesh* temp = FindXfile(name);
	if(temp) return temp;
	temp = new cSkinnedMesh;
	temp->Setup(szFolder, szFile);
	m_mapXfile.insert(std::make_pair(name, temp));
	return temp;
}

LPCSKINNEDMESH cXManager::FindXfile(const char* name)
{
	miXfile p = m_mapXfile.find(name);
	if (p != m_mapXfile.end())return p->second;
	return NULL;
}
