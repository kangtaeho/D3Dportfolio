#include "stdafx.h"
#include "cKeyManager.h"


cKeyManager::cKeyManager()
{
}


cKeyManager::~cKeyManager()
{
}

void cKeyManager::Setup()
{
	m_KeyCurrent.reset();
	m_KeyPast.reset();

	m_bIsStart = false;
	m_fKeyFPS = 0.0f;
	m_iPressure = 0;
}

void cKeyManager::Update()
{
	m_KeyPast = m_KeyCurrent;
	StartKeyDelay();
}

bool cKeyManager::IsOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		// 키가 눌러있지 않다면
		if (!m_KeyPast[key])
		{
			m_KeyCurrent.set(key, true);
			return true;
		}
	}
	else m_KeyCurrent.set(key, false);

	return false;
}

bool cKeyManager::IsDoubleKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!m_KeyPast[key])
		{
			m_bIsStart = true;
			m_KeyCurrent.set(key, true);
			m_iPressure++;
		}
	}
	else
	{
		m_KeyCurrent.set(key, false);
	}

	if (m_iPressure == 2)
	{
		m_iPressure = 0;
		return true;
	}

	return false;

}

bool cKeyManager::IsOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) m_KeyCurrent.set(key, true);
	else
	{
		if (m_KeyPast[key])
		{
			m_KeyCurrent.set(key, false);
			return true;
		}
	}

	return false;
}

bool cKeyManager::IsStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool cKeyManager::IsToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;

	return false;
}

void cKeyManager::StartKeyDelay()
{
	if (!m_bIsStart) return;

	m_fKeyFPS += g_pTimeManager->GetElapsedTime();

	if (m_fKeyFPS >= 0.4f)
	{
		m_bIsStart = false;
		m_fKeyFPS = 0.0f;
		m_iPressure = 0;
	}
}
