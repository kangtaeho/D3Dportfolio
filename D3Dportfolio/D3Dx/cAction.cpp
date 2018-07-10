#include "stdafx.h"
#include "cAction.h"

cAction::cAction()
	: m_bRepeat(true)
	, m_iCurrAni(0)
	, m_iNextAni(0)
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
	int i = m_pAnimController->GetMaxNumAnimationSets();
	for (i = 0; i <= m_pAnimController->GetMaxNumAnimationSets(); ++i)
	{
		m_pAnimController->GetAnimationSet(i, &pAniSet);
		if (strcmp(name, pAniSet->GetName()) == 0)break;
	}

	SAFE_RELEASE(pAniSet);
	if (i > m_pAnimController->GetMaxNumAnimationSets())i = findAnimation("Idle");
	return i;
}

void cAction::setAnimation(const char* name, const char* nextName, bool repeat)
{
	if (m_iCurrAni != findAnimation(name) &&
		m_iNextAni != findAnimation(nextName) &&
		m_bRepeat != repeat)
	{
		m_iCurrAni = findAnimation(name);
		m_iNextAni = findAnimation(nextName);
		m_bRepeat = repeat;
		SetAnimationIndex(m_iCurrAni);
	}
}

void cAction::UpdateAnimation()
{
	if (EndAnimation())
	{
		if (m_bRepeat)
		{
			SetAnimationIndex(m_iNextAni);
		}
		m_pAnimController->AdvanceTime(0, NULL);
	}
	else
	{
		m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);
	}
}

bool cAction::EndAnimation()
{
	LPD3DXANIMATIONSET	pAniSet = NULL;
	D3DXTRACK_DESC		desc;

	m_pAnimController->GetTrackAnimationSet(0, &pAniSet);
	m_pAnimController->GetTrackDesc(0, &desc);
	float period = pAniSet->GetPeriod() / desc.Speed;
	float current = fmod(desc.Position, period);
	float NowPer = current / period;
	float tick = g_pTimeManager->GetElapsedTime() / period;

	SAFE_RELEASE(pAniSet);

	return 1 - NowPer <= tick;
}