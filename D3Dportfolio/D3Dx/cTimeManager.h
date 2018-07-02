#pragma once

#define g_pTimeManager cTimeManager::GetInstance()

class cTimeManager
{
private:
	SINGLETONE(cTimeManager);

	DWORD			m_dwLastUpdateTime;

	float			m_fElapsedTime;
	float			m_fStartTime;
	float			m_fWorldTime;
	float			m_fFPStimeElapsed;

	unsigned long	m_lFrameRate;
	unsigned long	m_lFPSframeCount;

public:

	void Update();		// 실시간으로 메인게임 업데이트에 있어야함
	void Render();

	float GetElapsedTime();
	float GetLastUpdateTime();

	float GetWorldTime();

};

