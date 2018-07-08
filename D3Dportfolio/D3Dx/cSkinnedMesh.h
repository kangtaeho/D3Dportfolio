#pragma once

class cSkinnedMesh
{
private:
	LPD3DXFRAME					m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;

	float	m_fBlendTime;
	float	m_fPassedBlendTime;
	bool	m_bBlend;

public:
	cSkinnedMesh();
	~cSkinnedMesh();

	void Release(LPD3DXFRAME pFrame);

	void Setup(const char* szFolder, const char* szFile);
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	void Render(LPD3DXFRAME pFrame);

	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);

	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);
};
