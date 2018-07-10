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
	//==================================�������
	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);
	
	int findAnimation(const char* name);
	void UpdateAnimation();
	bool EndAnimation();
	//===================================������� �Ⱦ��ŵ� �����մϴ�.
	//name�� ���� �ִϸ��̼� �̸�, nextName�� ���� �ִϸ��̼� �̸�(�ȳ����� Idle), repeat�� �ݺ��Ұ��� �ݺ��ϸ� next�� �ݺ�
	
	void setAnimation(const char* name, const char* nextName = "Idle", bool repeat = true);
};
