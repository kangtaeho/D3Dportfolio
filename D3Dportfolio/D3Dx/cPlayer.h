#pragma once

class cCube;
class cPlayer
{
private:
	cCube*			m_pCube;		// 일단 캐릭터 없으니깐

	float			m_fRotY;
	D3DXMATRIX		m_matWorld;
	D3DXVECTOR3		m_vPos;

	D3DXVECTOR3		m_vEnemyPos;	// 테스트용 적 좌표

public:
	cPlayer();
	~cPlayer();

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

};

