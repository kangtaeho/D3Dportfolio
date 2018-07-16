#pragma once

class citem;

class cInventory
{
private:
	//아이템이있나체크 bool.
	//아이템의 위치.
	//아이템의 정보.
	SYNTHESIZE(citem*, item, invitemInfo);
	SYNTHESIZE(bool, isItem, hadItem);
	SYNTHESIZE(D3DXVECTOR3, m_vInvenPos, vInvenPos);
public:
	cInventory();
	~cInventory();

	void render();
};

