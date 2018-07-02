#pragma once

struct ST_MESH
{
	ST_PNT_VERTEX v;
	int index;
};

class cCube
{
public:
	cCube();
	~cCube();

private:
	std::vector<ST_PNT_VERTEX>	m_vecVertex;
	std::vector<ST_PNT_VERTEX>	m_vecIndex;

	D3DXVECTOR3					m_vPosition;
	D3DXMATRIX					m_matWorld;

	ID3DXMesh*					m_pMesh;

	float						m_fRotY;
public:
	void Setup(D3DXVECTOR3 size, LPCWSTR texName);
	void Update();
	void Render();
};

