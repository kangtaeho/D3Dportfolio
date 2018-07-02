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
	static cGameNode*		m_pCurrentScene;	// «ˆ¿Á æ¿
	static cGameNode*		m_pReadyScene;		// ∫Ø∞Êµ… æ¿

	mapSceneList			m_mapSceneList;		// æ¿¿ª ¥„¿ª ∏ 

public:
	
	HRESULT Setup();
	void Release();
	void Update();
	void Render();

	cGameNode* AddScene(std::string sceneName, cGameNode* scene);		// æ¿ √ﬂ∞°
	HRESULT	ChangeScene(std::string sceneName);							// æ¿ ∫Ø∞Ê

};

