#include "stdafx.h"
#include "cSceneManager.h"
#include "cGameNode.h"


cSceneManager::cSceneManager()
{
}


cSceneManager::~cSceneManager()
{
}

// ����ƽ���� �������ؼ� �̰� ������Ѵ�.
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
	if (!scene) return NULL;		// �������� �� ��ȯ

	for (auto p : m_mapSceneList)
	{
		if (p.first == sceneName) return NULL;	// ���� ���� �̸��� �ִٸ�,
	}

	m_mapSceneList.insert(std::make_pair(sceneName, scene));

	return scene;
}

HRESULT	cSceneManager::ChangeScene(std::string sceneName)
{
	mapSceneIter iter = m_mapSceneList.find(sceneName);

	if (iter == m_mapSceneList.end()) 
		return E_FAIL;		// �ش� ���� ���ٸ� ���� ��ȯ

	if (iter->second == m_pCurrentScene)
		return S_OK;		// ���� ���̶� �����ϸ� �ٲ��� �ʴ´�.

	if (SUCCEEDED(iter->second->Setup()))
	{
		if (m_pCurrentScene)
			delete m_pCurrentScene;		// ���� ������ ����� �̰ͺ��� üũ�غ���

		m_pCurrentScene = iter->second;

		return S_OK;
	}
}