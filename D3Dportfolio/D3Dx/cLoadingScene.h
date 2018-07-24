#pragma once
#include "cGameNode.h"

class cPlayer;
class cShop;
class cStatus;
class Bitmap;

class cLoadingScene :
	public cGameNode
{
private:
	cPlayer*		m_pPlayer;
	cShop*			m_pShop;
	cStatus*		m_pStatus;

	bool m_bLoadingCompletion;

public:
	cLoadingScene();
	~cLoadingScene();

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

	void LoadingData();
};

