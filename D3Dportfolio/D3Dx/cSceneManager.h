#pragma once

#define g_pSceneManager cSceneManager::GetInstance()

class cGameNode;

class cSceneManager
{
	SINGLETONE(cSceneManager);

public:
	typedef std::map<std::string, cGameNode*>	mapSceneList;
	typedef std::map<std::string, cGameNode*>::iterator mapSceneIter;

private:
	static cGameNode*		m_pCurrentScene;	// ���� ��
	static cGameNode*		m_pReadyScene;		// ����� ��

	mapSceneList			m_mapSceneList;		// ���� ���� ��

public:
	
	HRESULT Setup();
	void Release();
	void Update();
	void Render();

	cGameNode* AddScene(std::string sceneName, cGameNode* scene);		// �� �߰�
	HRESULT	ChangeScene(std::string sceneName);							// �� ����

};

