#pragma once

class Bitmap;

class cDamageRender
{
private:
	Bitmap* m_p1;
	Bitmap* m_p10;

	D3DXVECTOR3 m_vPos1;
	D3DXVECTOR3	m_vPos2;

	bool	m_bIsFire;
	float	m_fScale;
	float	m_fSpeed;
	float	m_fCount;

public:
	cDamageRender();
	~cDamageRender();

	void Setup(std::string texName);
	void Update();
	void Render();
	void Release();

	void ShowDamage(D3DXVECTOR3 target, int damage);

};

