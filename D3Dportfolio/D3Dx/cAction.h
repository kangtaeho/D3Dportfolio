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
	//name�� ���� �ִϸ��̼� �̸�, nextName�� ���� �ִϸ��̼� �̸�(�ȳ����� Idle), repeat�� �ݺ��Ұ��� �ݺ��ϸ� next�� �ݺ�
	void setAnimation(const char* name, const char* nextName = "Idle", bool repeat = true);
};
/*
��ӹ��� �Ŀ� setAnimation�� ���� ���~ �ִϸ��̼� �� �˴ϴ�.
������ �� UpdateAnimationȣ���� �� LPCSKINNEDMESH���� Update(m_pAnimController)
�ִϸ��̼� �޾ƿ��� �ʴ� ���� LPCSKINNEDMESH���� �׳� Render(NULL) ȣ��
��뿹���� cCharacter ����
*/