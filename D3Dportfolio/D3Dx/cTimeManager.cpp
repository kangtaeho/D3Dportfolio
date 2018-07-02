#include "stdafx.h"
#include "cTimeManager.h"


cTimeManager::cTimeManager()
	:m_fWorldTime(0.0f)
	, m_fElapsedTime(0.0f)

{
	m_dwLastUpdateTime = GetTickCount();
}


cTimeManager::~cTimeManager()
{

}


void cTimeManager::Update()
{
	DWORD	dwCurrentTime = GetTickCount();

	// 1프레임 당 경과된 시간 = (현제시간 -시작할때의 시간)/1000.0
	m_fElapsedTime = (dwCurrentTime - m_dwLastUpdateTime) / 1000.0f;
	m_dwLastUpdateTime = dwCurrentTime;

	m_lFPSframeCount++;
	m_fFPStimeElapsed += m_fElapsedTime;
	m_fWorldTime += m_fElapsedTime;


	if (m_fFPStimeElapsed > 1.0f)
	{
		m_lFrameRate = m_lFPSframeCount;
		m_lFPSframeCount = 0;
		m_fFPStimeElapsed = 0.0f;
	}

}

void cTimeManager::Render()
{
	if (!g_pFontManager->GetIsSetup()) return;

	g_pFontManager->TextFont(10, 10, "FPS : %d", m_lFrameRate);
	g_pFontManager->TextFont(10, 30, "WorldTime : %f", m_fWorldTime);
	g_pFontManager->TextFont(10, 50, "ElapsedTime : %f", m_fElapsedTime);

}

float cTimeManager::GetElapsedTime()
{
	return m_fElapsedTime;
}

float cTimeManager::GetLastUpdateTime()
{
	return m_dwLastUpdateTime / 1000.0f;
}

float cTimeManager::GetWorldTime()
{
	return m_fWorldTime;
}
