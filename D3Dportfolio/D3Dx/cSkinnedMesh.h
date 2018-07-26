#pragma once

class cSkinnedMesh
{
private:
	LPD3DXFRAME					m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	LPD3DXANIMATIONCONTROLLER	m_pAnimControllerParent;

	float	m_fBlendTime;
	float	m_fPassedBlendTime;
	bool	m_bBlend;

public:
	cSkinnedMesh();
	~cSkinnedMesh();

	void Release(LPD3DXFRAME pFrame);

	void CloneAniController(LPD3DXANIMATIONCONTROLLER* ppAnimController) { m_pAnimControllerParent->CloneAnimationController(m_pAnimControllerParent->GetMaxNumAnimationOutputs(), m_pAnimControllerParent->GetMaxNumAnimationSets(), m_pAnimControllerParent->GetMaxNumTracks(), m_pAnimControllerParent->GetMaxNumEvents(), ppAnimController); }
	
	void Setup(const char* szFolder, const char* szFile);
	//�ִϸ��̼� �ִ� ���� ���� �� ������Ʈ
	void Update(LPD3DXANIMATIONCONTROLLER pAnimController);
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);
	//�׳� ������ ���� �� ����
	void Render(LPD3DXFRAME pFrame);

	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);

	void SetAnimationIndexBlend(int nIndex);
};

#define LPCSKINNEDMESH cSkinnedMesh*
