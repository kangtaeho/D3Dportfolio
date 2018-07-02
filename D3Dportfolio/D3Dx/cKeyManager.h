#pragma once

#define g_pKeyManager cKeyManager::GetInstance()
#define KEYMAX 256

class cKeyManager
{
	SINGLETONE(cKeyManager);

private:
	SYNTHESIZE(std::bitset<KEYMAX>, m_KeyPast, KeyPast);
	SYNTHESIZE(std::bitset<KEYMAX>, m_KeyCurrent, KeyCurrent);

	bool		m_bIsStart;
	float		m_fKeyFPS;
	int			m_iPressure;

public:

	void Setup();
	void Update();
	
	bool IsOnceKeyDown(int key);
	bool IsOnceKeyUp(int key);
	bool IsStayKeyDown(int key);
	bool IsToggleKey(int key);
	bool IsDoubleKeyDown(int key);
	
	void StartKeyDelay();
};

