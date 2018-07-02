#pragma once

class cGameNode
{
private:

public:
	cGameNode();
	virtual ~cGameNode();

	virtual void Setup();
	virtual void Update();
	virtual void Render();

};

