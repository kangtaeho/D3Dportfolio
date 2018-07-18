#include "stdafx.h"
#include "cSelectScene.h"
#include "Bitmap.h"

cSelectScene::cSelectScene()
	: m_bIsLockIn(false)
	, m_fStartTime(0.0f)
	, m_fPassedTime(0.0f)
	, m_fLimitedTime(20.0f)
	, m_bIsStartCountDown(false)
{
}


cSelectScene::~cSelectScene()
{
}

HRESULT cSelectScene::Setup()
{
	g_pTextureManager->addTexture("selectWin", "./select/selectWin.png", NULL, NULL);
	g_pTextureManager->addTexture("selectPlayerWin01", "./select/selectPlayerWin01.png", NULL, NULL);
	g_pTextureManager->addTexture("selectPlayerWin02", "./select/selectPlayerWin02.png", NULL, NULL);
	g_pTextureManager->addTexture("selectRect", "./select/selectRect.png", NULL, NULL);
	g_pTextureManager->addTexture("pickIn01", "./select/pickIn01.png", NULL, NULL);
	g_pTextureManager->addTexture("pickIn02", "./select/pickIn02.png", NULL, NULL);
	g_pTextureManager->addTexture("pickIn03", "./select/pickIn03.png", NULL, NULL);
	g_pTextureManager->addTexture("skin", "./select/skin.png", NULL, NULL);
	g_pTextureManager->addTexture("numFirst", "./select/number.png", ANIMATION, 10, 1);
	g_pTextureManager->addTexture("numSecond", "./select/number.png", ANIMATION, 10, 1);
	m_vecIcon.push_back(g_pTextureManager->addTexture("cIcon01", "./select/cIcon01.png", NULL, NULL));
	m_vecIcon.push_back(g_pTextureManager->addTexture("cIcon02", "./select/cIcon02.png", NULL, NULL));
	m_vecIcon.push_back(g_pTextureManager->addTexture("cIcon03", "./select/cIcon03.png", NULL, NULL));
	m_vecIcon.push_back(g_pTextureManager->addTexture("cIcon04", "./select/cIcon04.png", NULL, NULL));
	m_vecIcon.push_back(g_pTextureManager->addTexture("cIcon05", "./select/cIcon05.png", NULL, NULL));
	m_vecIcon.push_back(g_pTextureManager->addTexture("cIcon06", "./select/cIcon06.png", NULL, NULL));
	m_vecIcon.push_back(g_pTextureManager->addTexture("cIcon07", "./select/cIcon07.png", NULL, NULL));
	m_vecIcon.push_back(g_pTextureManager->addTexture("cIcon08", "./select/cIcon08.png", NULL, NULL));
	m_vecIcon.push_back(g_pTextureManager->addTexture("cIcon09", "./select/cIcon09.png", NULL, NULL));
	m_vecIcon.push_back(g_pTextureManager->addTexture("cIcon10", "./select/cIcon10.png", NULL, NULL));


	for (int i = 0; i < 10; i++)
	{
		int left = 293 + (69 * i);
		rc_Select[i].left = left;
		rc_Select[i].right = left + 62;
		rc_Select[i].top = 177;
		rc_Select[i].bottom = 177 + 63;
	}

	rc_PickIn = MakeRectLT(782, 483, 176, 47);

	m_pMainSelectWin = g_pTextureManager->findTexture("selectWin");
	m_pMainSelectWin->setPosition(D3DXVECTOR3(0, 0, 0));
	m_pMainSelectWin->setScale(D3DXVECTOR3(1, 1, 1));

	m_pPlayerSelect = g_pTextureManager->findTexture("selectPlayerWin02");
	m_pPlayerSelect->setPosition(D3DXVECTOR3(22.0, 67.0, 0));
	m_pPlayerSelect->setScale(D3DXVECTOR3(1, 1, 1));

	m_pSelect= g_pTextureManager->findTexture("selectRect");
	m_pSelect->setPosition(D3DXVECTOR3(rc_Select[0].left, rc_Select[0].top, 0));
	m_pSelect->setScale(D3DXVECTOR3(1, 1, 1));

	m_pPickIn= g_pTextureManager->findTexture("pickIn03");
	m_pPickIn->setPosition(D3DXVECTOR3(rc_PickIn.left, rc_PickIn.top, 0));
	m_pPickIn->setScale(D3DXVECTOR3(1, 1, 1));


	m_pNumFirst = g_pTextureManager->findTexture("numFirst");
	m_pNumFirst->setPosition(D3DXVECTOR3(313, 68, 0));
	m_pNumFirst->setScale(D3DXVECTOR3(1, 1, 1));
	m_pNumFirst->setCurrentFrame(0);

	m_pNumSecond = g_pTextureManager->findTexture("numSecond");
	m_pNumSecond->setPosition(D3DXVECTOR3(293, 68, 0));
	m_pNumSecond->setScale(D3DXVECTOR3(1, 1, 1));
	m_pNumSecond->setCurrentFrame(0);

	m_fStartTime = g_pTimeManager->GetLastUpdateTime();

	return S_OK;
}

void cSelectScene::Update()
{
	Control();

	if (m_pMainSelectWin)
		m_pMainSelectWin->update();
	
	if (m_pPlayerSelect)
		m_pPlayerSelect->update();
	
	if (m_pPlayerChamp)
		m_pPlayerChamp->update();
	
	if (m_pEnemyChamp)
		m_pEnemyChamp->update();
	
	if (m_pSelect)
		m_pSelect->update();

	if (m_pPickIn)
		m_pPickIn->update();

	if (m_pSkin)
		m_pSkin->update();

	if (m_pNumFirst)
		m_pNumFirst->update(0);

	if (m_pNumSecond)
		m_pNumSecond->update(0);

	SelectTimer();

	if (g_pKeyManager->IsOnceKeyDown('0'))
	{
		g_pSceneManager->ChangeScene("플레이씬");
	}

}

void cSelectScene::Render()
{
	if (m_pMainSelectWin)
		m_pMainSelectWin->Render();

	if (m_pPlayerSelect)
		m_pPlayerSelect->Render();

	if (m_pPlayerChamp)
		m_pPlayerChamp->Render();

	if (m_pEnemyChamp)
		m_pEnemyChamp->Render();

	if (m_pSelect)
		m_pSelect->Render();

	if (m_pPickIn)
		m_pPickIn->Render();

	if (m_pSkin)
		m_pSkin->Render();

	if (m_pNumFirst)
		m_pNumFirst->aniRender();

	if (m_pNumSecond)
		m_pNumSecond->aniRender();

	g_pFontManager->TextFont(10, 300, "타임 %0.2f", m_fPassedTime);
}

void cSelectScene::Release()
{
	if (m_pMainSelectWin)
		m_pMainSelectWin->release();

	if (m_pPlayerSelect)
		m_pPlayerSelect->release();

	if (m_pPlayerChamp)
		m_pPlayerChamp->release();

	if (m_pEnemyChamp)
		m_pEnemyChamp->release();

	if (m_pSelect)
		m_pSelect->release();

	if (m_pPickIn)
		m_pPickIn->release();

	if (m_pSkin)
		m_pSkin->release();

	if (m_pNumFirst)
		m_pNumFirst->release();

	if (m_pNumSecond)
		m_pNumSecond->release();
}

void cSelectScene::Control()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	// 이건 픽인
	if (!m_bIsLockIn)	// 락인이 아닐때
	{
		if (PtInRect(&rc_PickIn, ptMouse))
		{
			m_pPickIn = g_pTextureManager->findTexture("pickIn01");
			m_pPickIn->setPosition(D3DXVECTOR3(rc_PickIn.left, rc_PickIn.top, 0));
			m_pPickIn->setScale(D3DXVECTOR3(1, 1, 1));
		}
		else
		{
			m_pPickIn = g_pTextureManager->findTexture("pickIn03");
			m_pPickIn->setPosition(D3DXVECTOR3(rc_PickIn.left, rc_PickIn.top, 0));
			m_pPickIn->setScale(D3DXVECTOR3(1, 1, 1));
		}

		// 이건 챔피언
		for (int i = 0; i < 10; i++)
		{
			if (PtInRect(&rc_Select[i], ptMouse))
			{
				if (m_pSelect)
					m_pSelect->setPosition(D3DXVECTOR3(rc_Select[i].left, rc_Select[i].top, 0));
			}
		}

	}

	if (g_pKeyManager->IsOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 10; i++)
		{
			if (PtInRect(&rc_Select[i], ptMouse))
			{
				m_nPickIndex = i;
				m_pPlayerChamp = m_vecIcon[i];
				m_pPlayerChamp->setPosition(D3DXVECTOR3(83, 73, 0));
				m_pPlayerChamp->setScale(D3DXVECTOR3(1, 1, 1));
			}
		}

		if (PtInRect(&rc_PickIn, ptMouse)&&!m_bIsLockIn)
		{
			CountDown();
			SelectChampion();
		}

	}
	
}

void cSelectScene::SelectTimer()
{
	m_fPassedTime = g_pTimeManager->GetLastUpdateTime() - m_fStartTime;

	int time = m_fLimitedTime - m_fPassedTime;


	int second = time / 10;
	int first = time % 10;

	m_pNumFirst->setCurrentFrame(first);
	m_pNumSecond->setCurrentFrame(second);


	if (time < 0)
	{
		if (m_fLimitedTime == 10)
		{
			g_pSceneManager->ChangeScene("플레이씬");
		}
		else
		{
			CountDown();
		}
	}

}

void cSelectScene::SelectChampion()
{
	m_pPickIn = g_pTextureManager->findTexture("pickIn02");
	m_pPickIn->setPosition(D3DXVECTOR3(rc_PickIn.left, rc_PickIn.top, 0));
	m_pPickIn->setScale(D3DXVECTOR3(1, 1, 1));

	m_pPlayerSelect = g_pTextureManager->findTexture("selectPlayerWin01");
	m_pPlayerSelect->setPosition(D3DXVECTOR3(22.0, 67.0, 0));
	m_pPlayerSelect->setScale(D3DXVECTOR3(1, 1, 1));
	m_bIsLockIn = true;

	srand(GetTickCount());
	int rndNum = rand() % 10;

	while (rndNum == m_nPickIndex)
	{
		rndNum = rand() % 10;
	}

	m_pEnemyChamp = m_vecIcon[rndNum];
	m_pEnemyChamp->setPosition(D3DXVECTOR3(1111, 74, 0));
	m_pEnemyChamp->setScale(D3DXVECTOR3(1, 1, 1));

	m_pSkin = g_pTextureManager->findTexture("skin");
	m_pSkin->setPosition(D3DXVECTOR3(278, 112, 0));
	m_pSkin->setScale(D3DXVECTOR3(1, 1, 1));
}

void cSelectScene::CountDown()
{
	m_fStartTime = g_pTimeManager->GetLastUpdateTime();
	m_fLimitedTime = 10.0f;
	SelectChampion();
}
