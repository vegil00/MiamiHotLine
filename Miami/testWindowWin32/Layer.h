#pragma once
#include"Sprite.h"
class CLayer:public CSprite
{protected:

public:
	CLayer();
	void Render();
	void update();
	~CLayer();
};

