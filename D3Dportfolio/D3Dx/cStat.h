#pragma once

class cStat
{
private:
	Bitmap* Screen;
	Bitmap* AttackSpeed;
	Bitmap* Atk;
	Bitmap* Defense;
	Bitmap* MoveSpeed;
	Bitmap* AttackSpeedNum;
	Bitmap* AtkNum;
	Bitmap* DefenseNum;
	Bitmap* MoveSpeedNum;
	int AttackSpeedValue;
	int AtkValue;
	int DefenseValue;
	int MoveSpeedValue;
public:
	cStat();
	~cStat();

	void setup();
	void update();
	void render();

};

