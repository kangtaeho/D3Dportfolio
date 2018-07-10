#pragma once
//애니메이션 넣고 싶으면 퍼블릭 상속
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

	//==================================여기부터
	int findAnimation(const char* name);
	void UpdateAnimation();
	bool EndAnimation();
	void SetAnimationIndex(int nIndex);
	//===================================여기까지 안쓰셔도 무방합니다.
	//name에 현재 애니메이션 이름, nextName에 다음 애니메이션 이름(안넣으면 Idle), repeat은 반복할건지 반복하면 next만 반복
	void setAnimation(const char* name, const char* nextName = "Idle", bool repeat = true);
};
/*
상속받은 후에 setAnimation을 맘껏 사용~ 애니메이션 잘 됩니다.
랜더할 때 UpdateAnimation호출한 후 LPCSKINNEDMESH에서 Update(m_pAnimController)
애니메이션 받아오지 않는 것은 LPCSKINNEDMESH에서 그냥 Render(NULL) 호출
사용예제는 cCharacter 참조
*/