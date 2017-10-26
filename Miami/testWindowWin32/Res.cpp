#include "stdafx.h"
#include "Res.h"


CRes::CRes()
{
	texture = nullptr;
}


void CRes::init(CTexture * tex)
{
	tex = new CTexture;
	 texture = tex; 
	 
}

void CRes::translate(float x, float y, float z)
{
	
	glTranslatef(x, y, z);
	
}

void CRes::rotate(float degree, float x, float y, float z)
{
	glRotatef(degree, x, y, z);
}

void CRes::scale(float x, float y, float z)
{
	glScalef(x, y, z);
}

int CRes::getWidth()
{
	return width;
}

int CRes::getHeight()
{
	return height;
}

CRes::~CRes()
{
}
