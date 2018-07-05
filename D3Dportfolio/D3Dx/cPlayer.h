#pragma once

class cCube;
class cPlayer
{
private:
	cCube*			m_pCube;		// �ϴ� ĳ���� �����ϱ�

	float			m_fRotY;
	D3DXMATRIX		m_matWorld;
	D3DXVECTOR3		m_vPos;

	D3DXVECTOR3		m_vEnemyPos;	// �׽�Ʈ�� �� ��ǥ

public:
	cPlayer();
	~cPlayer();

	HRESULT Setup();
	void Release();
	void Update();
	void Render();

};

