#include "stdafx.h"
#include "Sprite.h"


CSprite::CSprite()
{
	alive = true;
}


void CSprite::updateboundbox()
{
	VECTOR3 dir = VECTOR3(m_dir.x, -m_dir.y, m_dir.z);
	VECTOR3 left = dir.cross(VECTOR3(0, 0, 1));
	left = left.Normalize();
	this->m_height;
	m_rect[0] = m_mapPos + m_height*0.5f*left + m_width*0.5f*dir;
	m_rect[1] = m_mapPos + m_height*0.5f*left - m_width*0.5f*dir;
	m_rect[2] = m_mapPos - m_height*0.5f*left - m_width*0.5f*dir;
	m_rect[3] = m_mapPos - m_height*0.5f*left + m_width*0.5f*dir;
}

void CSprite::rotate(VECTOR3 rotate, float degree)
{
	m_rotate = rotate;
	m_RotateDegree = degree;
}

void CSprite::rotate(VECTOR3 dir)
{
	dir = dir.Normalize();

	float cos = dir.dot(VECTOR3(1, 0, 0));
	float degree = acos(dir.dot(VECTOR3(1, 0, 0))) * 180 / PI;
	if (dir.y >= 0)
		rotate(VECTOR3(0, 0, 1), degree);
	if (dir.y<0)
		rotate(VECTOR3(0, 0, 1), -degree);
}

CSprite::~CSprite()
{
}
