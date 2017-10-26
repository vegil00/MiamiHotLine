#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
	
	m_texture = nullptr;
	
}

void CBullet::init(int atk,  float speed, TSTRING name,int coltouch,int width, int height, BULLETTYPE type)
{
	m_dir = VECTOR3(0, 0, 0);
	m_atk = atk;
	m_type = BULLET;
	m_speed = speed;
	isVisible = false;
	m_texture = new CSingleImg;
	m_texture = (CSingleImg*)CResManager::getInstance()->getRes(name);
	touch_col = coltouch;
#ifdef _UNICODE
	m_name = CU_U2A(name);
#else
	m_name = name;
#endif // _UNICODE

	cur_image = 0;
	m_width = width;
	m_height = height;
	m_pos = VECTOR3(0, 0, 0);
	m_scale = VECTOR3(1, 1, 1);
	
	
	preChange = GetTickCount();
	isTouch = false;
}

void CBullet::touch()
{
	isTouch = true;
	cur_image = touch_col - 1;
	m_dir = VECTOR3(0, 0, 0);
}

void CBullet::activate(VECTOR3 pos, VECTOR3 dir, WEAPONSTATUS wstatus)
{
	m_pos = pos;
	m_dir = dir.Normalize();
	float cos = m_dir.dot(VECTOR3(1, 0, 0));
	if(m_dir.y>0)
	m_RotateDegree = acos(m_dir.dot(VECTOR3(1, 0, 0))) * 180 / PI;
	else
		m_RotateDegree = -acos(m_dir.dot(VECTOR3(1, 0, 0))) * 180 / PI;
	isVisible = true;
	cur_image = 0;
}

void CBullet::activate(VECTOR3 pos, VECTOR3 dir, VECTOR3 mappos, WEAPONSTATUS wstatus)
{
	m_pos = pos;
	m_mapPos = mappos;
	m_dir = dir.Normalize();
	float cos = m_dir.dot(VECTOR3(1, 0, 0));
	if (m_dir.y>0)
		m_RotateDegree = acos(m_dir.dot(VECTOR3(1, 0, 0))) * 180 / PI;
	else
		m_RotateDegree = -acos(m_dir.dot(VECTOR3(1, 0, 0))) * 180 / PI;
	isVisible = true;
	m_weaponType = wstatus;
	cur_image = 0;
}

void CBullet::activate(BULLETTYPE type, VECTOR3 mappos,VECTOR3 pos, VECTOR3 dir,WEAPONSTATUS wstatus)
{
	m_mapPos = mappos;
	m_pos = pos;
	m_dir = dir.Normalize();
	m_bulletType = type;
	if (m_dir.y>0)
		m_RotateDegree = acos(m_dir.dot(VECTOR3(1, 0, 0))) * 180 / PI;
	else
		m_RotateDegree = -acos(m_dir.dot(VECTOR3(1, 0, 0))) * 180 / PI;
	isVisible = true;
	m_weaponType = wstatus;
	cur_image = 0;
}

void CBullet::move()
{
	//m_pos = m_pos+m_speed*m_dir;
	m_mapPos = m_mapPos + m_speed*VECTOR3(m_dir.x, -m_dir.y, m_dir.z);
}

void CBullet::Render()
{
	if (isVisible)
	{
		m_texture->setRenderPos(0, cur_image);
		
		m_texture->Render(m_pos, VECTOR3(0, 0, 1),  m_RotateDegree, m_scale);
	}
	
}

void CBullet::update()
{
	if (isVisible)
	{
		//m_mapPos = m_mapPos + m_speed*VECTOR3(m_dir.x,-m_dir.y,m_dir.z);
		move();
		int curTime = GetTickCount();
		float time = (curTime - preChange)*0.001f;
		if ((curTime - preChange)*0.001f > 0.1f)
		{
			preChange = curTime;
			if (isTouch)
			{
				cur_image++;
				if (cur_image >= m_texture->getCol())
					isVisible = false;
			}
			else {
				cur_image++;
				if (cur_image >= touch_col)
					cur_image = touch_col - 1;
			}
		}
		
	}
	
}


CBullet::~CBullet()
{
}
