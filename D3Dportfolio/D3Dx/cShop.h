#pragma once

#define ITEMSIZE D3DXVECTOR3(0.8f,0.8f,0.8f)
class cShop
{
public:
	cShop();
	~cShop();
	
	void setup();
	void update();
	void render();

	void setItemPosition();
};

