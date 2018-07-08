#pragma once
class cGrid
{
private:
	std::vector<ST_PNT_VERTEX>	m_vecVertex;
	LPD3DXMESH					m_pMesh;

public:
	cGrid();
	~cGrid();

	HRESULT Setup(int gridNum);
	void Release();
	void Update();
	void Render();

};

