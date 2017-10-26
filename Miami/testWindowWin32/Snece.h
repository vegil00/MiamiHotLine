#pragma once
#include"Layer.h"
#include"ResManager.h"

class CSnece:public CLayer
{
protected:
	CStaticImg* m_backGround;
	
	RECT screen;
	
	float imageWidth;
	float imageHeight;
public:
	CSnece();
	void init(TSTRING path, TSTRING background, HWND hwnd);
	void Render();
	void update();
	~CSnece();
};

