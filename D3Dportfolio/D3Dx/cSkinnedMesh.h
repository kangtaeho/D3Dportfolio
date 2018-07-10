#pragma once

class cSkinnedMesh
{
private:
	LPD3DXFRAME					m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;

	float	m_fBlendTime;
	float	m_fPassedBlendTime;
	bool	m_bBlend;

	int		m_iCurrAni;
	int		m_iNextAni;
	bool	m_bRepeat;

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
	//==================================여기부터
	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);
	
	int findAnimation(const char* name);
	void UpdateAnimation();
	bool EndAnimation();
	//===================================여기까지 안쓰셔도 무방합니다.
	//name에 현재 애니메이션 이름, nextName에 다음 애니메이션 이름(안넣으면 Idle), repeat은 반복할건지 반복하면 next만 반복
	
	void setAnimation(const char* name, const char* nextName = "Idle", bool repeat = true);
};
