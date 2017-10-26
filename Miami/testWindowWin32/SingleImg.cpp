#include "stdafx.h"
#include "SingleImg.h"


CSingleImg::CSingleImg()
{
}

void CSingleImg::init(CTexture * tex)
{
	texture = new CTexture;
	texture = tex;
	width = texture->getWidth()/texture->getCol();
	height = texture->getHeight()/texture->getRow();
	row = texture->getRow();
	col= texture->getCol();
}

void CSingleImg::Render(VECTOR3 & archPos, VECTOR3 rotate, float degree, float showWidth, float showHeight, int r, int c)
{
	texture->Render(archPos,  rotate,  degree, showWidth, showHeight, r, c);
}

void CSingleImg::Render(VECTOR3 & archPos, VECTOR3 rotate,  float degree,VECTOR3 scale)
{
	texture->Render(archPos, rotate, degree, width*scale.x,height*scale.y,cur_row,cur_col);
}

void CSingleImg::setRenderPos(int row, int col)
{
	cur_row = row;
	cur_col = col;
}


CSingleImg::~CSingleImg()
{
}
