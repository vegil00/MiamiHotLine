#pragma once
#include"Res.h"
class CStaticImg:public CRes
{private:
public:
	CStaticImg();
	void init(CTexture* tex);
	
	void Render(VECTOR3 &archPos, VECTOR3 rotate, float degree, float showWidth, float showHeight, VECTOR3 &imagePos, float imageWidth, float imageHeight);
	void Render(VECTOR3 &archPos, VECTOR3 rotate, float degree, float showWidth, float showHeight);
	~CStaticImg();
};

