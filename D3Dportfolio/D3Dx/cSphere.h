#pragma once
class cSphere
{
private:
	SYNTHESIZE(float, m_fRadius, Radius);
	SYNTHESIZE(bool , m_bIsShow, IsShow);
	LPD3DXMESH	m_pMesh;

	SYNTHESIZE_REF(D3DXVECTOR3, m_vPos, Pos);
	SYNTHESIZE(float, m_fLenght, Length);

public:
	cSphere();
	~cSphere();

	void Setup(D3DXVECTOR3 pos, float radius);
	void Update();
	void Render();

};
