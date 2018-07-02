#include "stdafx.h"
#include "cSceneManager.h"
#include "cGameNode.h"


cSceneManager::cSceneManager()
{
}


cSceneManager::~cSceneManager()
{
}

// 스테틱으로 선언을해서 이걸 해줘야한다.
cGameNode* cSceneManager::m_pCurrentScene = NULL;
cGameNode* cSceneManager::m_pReadyScene = NULL;

HRESULT cSceneManager::Setup()
{
	m_pCurrentScene = NULL;
	m_pReadyScene = NULL;

	return S_OK;
}

void cSceneManager::Release()
{
	for (auto p : m_mapSceneList)
	{
		if (p.second != NULL)
		{
			SAFE_DELETE(p.second);
		}
	}
	m_mapSceneList.clear();
}

void cSceneManager::Update()
{
	if (m_pCurrentScene)
		m_pCurrentScene->Update();
}

void cSceneManager::Render()
{
	if (m_pCurrentScene)
		m_pCurrentScene->Render();
}

cGameNode* cSceneManager::AddScene(std::string sceneName, cGameNode* scene)
{
	if (!scene) return NULL;		// 씬없으면 널 반환

	for (auto p : m_mapSceneList)
	{
		if (p.first == sceneName) return NULL;	// 같은 씬의 이름이 있다면,
	}

	m_mapSceneList.insert(std::make_pair(sceneName, scene));

	return scene;
}

HRESULT	cSceneManager::ChangeScene(std::string sceneName)
{
	mapSceneIter iter = m_mapSceneList.find(sceneName);

	if (iter == m_mapSceneList.end()) 
		return E_FAIL;		// 해당 씬이 없다면 실패 반환

	if (iter->second == m_pCurrentScene)
		return S_OK;		// 현재 씬이랑 동일하면 바꾸지 않는다.

	if (SUCCEEDED(iter->second->Setup()))
	{
		if (m_pCurrentScene)
			delete m_pCurrentScene;		// 씬에 문제가 생기면 이것부터 체크해보자

		m_pCurrentScene = iter->second;

		return S_OK;
	}
}