#include "stdafx.h"
#include "cAction.h"

cAction::cAction()
	: m_bRepeat(true)
	, m_iCurrAni(0)
	, m_fFrameSpeed(1.0f)
{
}

cAction::~cAction()
{
	SAFE_RELEASE(m_pAnimController);
}

void cAction::SetAnimationIndex(int nIndex)
{
	int n = m_pAnimController->GetNumAnimationSets();
	if (nIndex > n)	nIndex = nIndex % n;

	LPD3DXANIMATIONSET	pAniSet = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pAniSet);
	m_pAnimController->SetTrackAnimationSet(0, pAniSet);
	m_pAnimController->SetTrackPosition(0, 0);

	SAFE_RELEASE(pAniSet);
}

int cAction::findAnimation(const char* name)
{
	LPD3DXANIMATIONSET	pAniSet = NULL;
	int i = m_pAnimController->GetMaxNumAnimationSets();							//Index�� �� i ����, �ʱ�ȭ�� ���ǹ�
	for (i = 0; i <= m_pAnimController->GetMaxNumAnimationSets(); ++i)				//�ִϸ��̼� ã��
	{
		m_pAnimController->GetAnimationSet(i, &pAniSet);							//�ִϸ��̼� ���� ��������
		if (strcmp(name, pAniSet->GetName()) == 0)break;							//�̸��� ������ ����
	}

	SAFE_RELEASE(pAniSet);															//������ ������
	if (i > m_pAnimController->GetMaxNumAnimationSets())i = findAnimation("Idle");	//���࿡ �ִϸ��̼� �̸��� ������ Idle�� ����
	return i;																		//Index ����
}

void cAction::setAnimation(const char* name, bool repeat, float fSpeed)
{
	m_fFrameSpeed = fSpeed;
	if (m_iCurrAni == findAnimation(name) &&
		m_bRepeat == repeat)return;						//������ ���� ������� Ȯ�� �� ������ ����
	m_iCurrAni = findAnimation(name);					//�ٷ� ������ �ִϸ��̼�
	m_bRepeat = repeat;									//�ݺ��Ұ���
	SetAnimationIndex(m_iCurrAni);						//���� �ִϸ��̼� ����
}

bool cAction::isIdle()
{
	LPD3DXANIMATIONSET	pAniSet = NULL;
	m_pAnimController->GetTrackAnimationSet(0, &pAniSet);		//�ִϸ��̼� ���� �����ͼ�
	char name[1024];
	sprintf_s(name, "%s", pAniSet->GetName());					//ĳ���Ϳ� ���
	SAFE_RELEASE(pAniSet);										//�ϴ� �ִϸ��̼� ������ �����
	if (std::string(name) == "Idle")return true;				//Ȯ���ؼ� Idle�̸� ��
	return false;												//�ƴϸ� ����
}

void cAction::UpdateAnimation()
{
	if (EndAnimation())																//�ִϸ��̼� �������� Ȯ��
	{
		if (m_bRepeat)																//�ݺ������� Ȯ��
		{
			SetAnimationIndex(m_iCurrAni);											//�ݺ����̸� ���ݰ� Ʋ��
		}
		m_pAnimController->AdvanceTime(0, NULL);									//�ִϸ��̼� �������� �ð� �ø��� ����
	}
	else
	{
		m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime() * m_fFrameSpeed, NULL);		//�ִϸ��̼� �ȳ������� �ð� �ø���
	}
}

bool cAction::EndAnimation()
{
	LPD3DXANIMATIONSET	pAniSet = NULL;
	D3DXTRACK_DESC		desc;

	m_pAnimController->GetTrackAnimationSet(0, &pAniSet);			//�ִϸ��̼� ���� ��������
	m_pAnimController->GetTrackDesc(0, &desc);						//���� Ʈ�� ���� ��������
	float period = pAniSet->GetPeriod() / desc.Speed;				//�ִϸ��̼��� ��ü �ð� / Ʈ���� ���ǵ�
	float current = fmod(desc.Position, period);					//���� �ִϸ��̼��� �帥 �ð��� ������������� ���ϱ�
	float NowPer = current / period;								//���� �帥 �ð��� �ۼ�Ʈ
	float tick = g_pTimeManager->GetElapsedTime() / period;			//�帥 ���� tick��

	SAFE_RELEASE(pAniSet);

	return 1 - NowPer <= tick;										//1 - ���� �帥 �ð��� �ۼ�Ʈ�� �帥 ���� ƽ������ ������, ������ �����Ŵ�.
}

bool cAction::isNameAniPlaying(const char* name)
{
	bool temp = false;
	LPD3DXANIMATIONSET	pAniSet = NULL;

	m_pAnimController->GetTrackAnimationSet(0, &pAniSet);
	if (std::string(pAniSet->GetName()) == std::string(name) && !EndAnimation())temp = true;

	SAFE_RELEASE(pAniSet);

	return temp;
}