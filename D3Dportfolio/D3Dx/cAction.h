#pragma once
//�ִϸ��̼� �ְ� ������ �ۺ� ���
class cAction
{
protected:
	int		m_iCurrAni;
	bool	m_bRepeat;
	float	m_fFrameSpeed;

	LPD3DXANIMATIONCONTROLLER m_pAnimController;

public:
	cAction();
	~cAction();

	LPD3DXANIMATIONCONTROLLER& getAniController() { return m_pAnimController; }

	void aniCloneAniController(LPD3DXANIMATIONCONTROLLER* ppAnimController) { m_pAnimController->CloneAnimationController(m_pAnimController->GetMaxNumAnimationOutputs(), m_pAnimController->GetMaxNumAnimationSets(), m_pAnimController->GetMaxNumTracks(), m_pAnimController->GetMaxNumEvents(), ppAnimController); }

	//==================================�������
	int findAnimation(const char* name);
	void UpdateAnimation();
	bool EndAnimation();
	void SetAnimationIndex(int nIndex);
	//===================================������� �Ⱦ��ŵ� �����մϴ�.
	//name�� ���� �ִϸ��̼� �̸�, repeat�� �ݺ��Ұ���, ������ ������Ʈ���� ��� setAnimation()�� ȣ�����ֽø� �˴ϴ�.
	void setAnimation(const char* name = "Idle", bool repeat = true, float fSpeed = 1.0f);
	void setAnimation(const char* name, float fSpeed) { setAnimation(name, m_bRepeat, fSpeed); }
	//�̸��� �ٲ� �� ���� �ִϸ��̼��� �����մϴ�.
	//�̸��� ������ �ݺ��� �ӵ��� �ٲٴ� ��, ���� �ִϸ��̼��� ��� �̾�ϴ�.
	void setAnimation(bool repeat, float fSpeed) { m_bRepeat = repeat; m_fFrameSpeed = fSpeed; }
	void setAnimation(bool repeat) { m_bRepeat = repeat; }
	void setAnimation(float fSpeed) { m_fFrameSpeed = fSpeed; }
	//���� Idle �����ΰ�?
	bool isIdle();
	//name�� ã�Ƽ� ���� �ִϸ��̼�����, ������ �ʾҴ��� Ȯ��, �̸��� ���� ������ �ʾ����� true, �̸� ������ �������� false
	bool isNameAniPlaying(const char* name);
};
/*
��ӹ��� �Ŀ� setAnimation�� ���� ���~ �ִϸ��̼� �� �˴ϴ�.
������ �� UpdateAnimationȣ���� �� LPCSKINNEDMESH���� Update(m_pAnimController)
�ִϸ��̼� �޾ƿ��� �ʴ� ���� LPCSKINNEDMESH���� �׳� Render(NULL) ȣ��
��뿹���� cCharacter ����
*/