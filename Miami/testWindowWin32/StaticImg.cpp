#include "stdafx.h"
#include "StaticImg.h"


CStaticImg::CStaticImg()
{
}

void CStaticImg::init(CTexture * tex)
{
	texture = new CTexture;
	texture = tex;
	width = texture->getWidth();
	height = texture->getHeight();
}

void CStaticImg::Render(VECTOR3 & archPos, VECTOR3 rotate, float degree, float showWidth, float showHeight, VECTOR3 & imagePos, float imageWidth, float imageHeight)
{
	texture->Render(archPos,  rotate,  degree, showWidth, showHeight, imagePos, imageWidth, imageHeight);
}

void CStaticImg::Render(VECTOR3 & archPos, VECTOR3 rotate, float degree, float showWidth, float showHeight)
{
	texture->Render(archPos,  rotate,  degree, showWidth, showHeight, VECTOR3(0,0,0), 1.0f, 1.0f);
}


CStaticImg::~CStaticImg()
{
}
