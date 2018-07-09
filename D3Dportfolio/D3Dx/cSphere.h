#pragma once
class cSphere
{
private:
	SYNTHESIZE(D3DXVECTOR3, m_vPos, Pos);
	SYNTHESIZE(float, m_fRadius, Radius);
	SYNTHESIZE(bool , m_bIsShow, IsShow);
	LPD3DXMESH	m_pMesh;

	SYNTHESIZE(float, m_fLenght, Length);

public:
	cSphere();
	~cSphere();

	void Setup(D3DXVECTOR3 pos);
	void Update();
	void Render();

};
