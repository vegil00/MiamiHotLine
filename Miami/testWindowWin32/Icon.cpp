#include "stdafx.h"
#include "Icon.h"


CIcon::CIcon()
{
}

void CIcon::init(VECTOR3 pos, TSTRING name)
{
	m_pos = pos;
	m_name = name;
	m_texture = (CStaticImg*)CResManager::getInstance()->getRes(m_name);
	width = m_texture->getWidth();
	height = m_texture->getHeight();
	m_RotateDegree = 0;
	
}

void CIcon::Render()
{
	m_texture->Render(m_pos, VECTOR3(0, 0, 1), m_RotateDegree, width, height);
}

void CIcon::rotate(VECTOR3 dir)
{
	dir = dir.Normalize();

	float cos = dir.dot(VECTOR3(1, 0, 0));
	float degree = acos(dir.dot(VECTOR3(1, 0, 0))) * 180 / PI;
	if (dir.y >= 0)
		m_RotateDegree = degree;
	if (dir.y < 0)
		m_RotateDegree = -degree;
}


CIcon::~CIcon()
{
}
