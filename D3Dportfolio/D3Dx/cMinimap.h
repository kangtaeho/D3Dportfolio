#pragma once
class cMinimap 
{
private:
	Bitmap* m_MapTexture;
public:
	cMinimap();
	~cMinimap();

	void setup();
	void update();
	void Render();
};

