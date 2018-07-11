#pragma once
//애니메이션 넣고 싶으면 퍼블릭 상속
class cAction
{
protected:
	int		m_iCurrAni;
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
	//name에 현재 애니메이션 이름, repeat은 반복할건지, 쓸때는 업데이트에서 계속 setAnimation()을 호출해주시면 됩니다.
	void setAnimation(const char* name = "Idle", bool repeat = true);
	//지금 Idle 상태인가?
	bool isIdle();
	//name을 찾아서 지금 애니메이션인지, 끝나지 않았는지 확인, 이름이 같고 끝나지 않았으면 true, 이름 같은데 끝났으면 false
	bool isNameAniPlaying(const char* name);
};
/*
상속받은 후에 setAnimation을 맘껏 사용~ 애니메이션 잘 됩니다.
랜더할 때 UpdateAnimation호출한 후 LPCSKINNEDMESH에서 Update(m_pAnimController)
애니메이션 받아오지 않는 것은 LPCSKINNEDMESH에서 그냥 Render(NULL) 호출
사용예제는 cCharacter 참조
*/