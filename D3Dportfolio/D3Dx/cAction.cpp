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
	int i = m_pAnimController->GetMaxNumAnimationSets();							//Index가 될 i 선언, 초기화는 무의미
	for (i = 0; i <= m_pAnimController->GetMaxNumAnimationSets(); ++i)				//애니메이션 찾자
	{
		m_pAnimController->GetAnimationSet(i, &pAniSet);							//애니메이션 정보 가져오기
		if (strcmp(name, pAniSet->GetName()) == 0)break;							//이름이 같으면 정지
	}

	SAFE_RELEASE(pAniSet);															//썼으니 지우자
	if (i > m_pAnimController->GetMaxNumAnimationSets())i = findAnimation("Idle");	//만약에 애니메이션 이름이 없으면 Idle로 하자
	return i;																		//Index 리턴
}

void cAction::setAnimation(const char* name, bool repeat, float fSpeed)
{
	m_fFrameSpeed = fSpeed;
	if (m_iCurrAni == findAnimation(name) &&
		m_bRepeat == repeat)return;						//원래랑 같은 명령인지 확인 후 같으면 리턴
	m_iCurrAni = findAnimation(name);					//바로 실행할 애니메이션
	m_bRepeat = repeat;									//반복할건지
	SetAnimationIndex(m_iCurrAni);						//현재 애니메이션 실행
}

bool cAction::isIdle()
{
	LPD3DXANIMATIONSET	pAniSet = NULL;
	m_pAnimController->GetTrackAnimationSet(0, &pAniSet);		//애니메이션 정보 가져와서
	char name[1024];
	sprintf_s(name, "%s", pAniSet->GetName());					//캐릭터에 담고
	SAFE_RELEASE(pAniSet);										//일단 애니메이션 정보는 지우고
	if (std::string(name) == "Idle")return true;				//확인해서 Idle이면 참
	return false;												//아니면 거짓
}

void cAction::UpdateAnimation()
{
	if (EndAnimation())																//애니메이션 끝났는지 확인
	{
		if (m_bRepeat)																//반복용인지 확인
		{
			SetAnimationIndex(m_iCurrAni);											//반복용이면 지금거 틀자
		}
		m_pAnimController->AdvanceTime(0, NULL);									//애니메이션 끝났으면 시간 올리지 말자
	}
	else
	{
		m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime() * m_fFrameSpeed, NULL);		//애니메이션 안끝났으면 시간 올리자
	}
}

bool cAction::EndAnimation()
{
	LPD3DXANIMATIONSET	pAniSet = NULL;
	D3DXTRACK_DESC		desc;

	m_pAnimController->GetTrackAnimationSet(0, &pAniSet);			//애니메이션 정보 가져오기
	m_pAnimController->GetTrackDesc(0, &desc);						//현재 트랙 정보 가져오기
	float period = pAniSet->GetPeriod() / desc.Speed;				//애니메이션의 전체 시간 / 트랙의 스피드
	float current = fmod(desc.Position, period);					//현재 애니메이션이 흐른 시간을 나머지계산으로 구하기
	float NowPer = current / period;								//현재 흐른 시간의 퍼센트
	float tick = g_pTimeManager->GetElapsedTime() / period;			//흐른 값의 tick값

	SAFE_RELEASE(pAniSet);

	return 1 - NowPer <= tick;										//1 - 현재 흐른 시간의 퍼센트가 흐른 값의 틱값보다 작은지, 작으면 끝난거다.
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