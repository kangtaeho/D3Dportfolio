#pragma once

class citem;

class cInventory
{
private:
	//���������ֳ�üũ bool.
	//�������� ��ġ.
	//�������� ����.
	SYNTHESIZE(citem*, item, invitemInfo);
	SYNTHESIZE(bool, isItem, hadItem);
	SYNTHESIZE(D3DXVECTOR3, m_vInvenPos, vInvenPos);
public:
	cInventory();
	~cInventory();

	void render();
};

