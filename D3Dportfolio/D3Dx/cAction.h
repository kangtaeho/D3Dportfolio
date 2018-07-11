#pragma once
//�ִϸ��̼� �ְ� ������ �ۺ� ���
class cAction
{
protected:
	int		m_iCurrAni;
	int		m_iNextAni;
	bool	m_bRepeat;

	LPD3DXANIMATIONCONTROLLER m_pAnimController;

public:
	cAction();
	~cAction();

	//==================================�������
	int findAnimation(const char* name);
	void UpdateAnimation();
	bool EndAnimation();
	void SetAnimationIndex(int nIndex);
	//===================================������� �Ⱦ��ŵ� �����մϴ�.
	//name�� ���� �ִϸ��̼� �̸�, repeat�� �ݺ��Ұ���, ������ ������Ʈ���� ��� setAnimation()�� ȣ�����ֽø� �˴ϴ�.
	void setAnimation(const char* name = "Idle", bool repeat = true);
	//���� Idle �����ΰ�?
	bool isIdle();
};
/*
��ӹ��� �Ŀ� setAnimation�� ���� ���~ �ִϸ��̼� �� �˴ϴ�.
������ �� UpdateAnimationȣ���� �� LPCSKINNEDMESH���� Update(m_pAnimController)
�ִϸ��̼� �޾ƿ��� �ʴ� ���� LPCSKINNEDMESH���� �׳� Render(NULL) ȣ��
��뿹���� cCharacter ����
*/