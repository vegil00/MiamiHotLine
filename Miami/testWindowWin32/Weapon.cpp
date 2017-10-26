#include "stdafx.h"
#include "Weapon.h"


CWeapon::CWeapon()
{
}

void CWeapon::init(WEAPONSTATUS weapon,float speed, bool Visible, VECTOR3 mapPos,int id)
{
	m_weaponType = weapon;
	m_speed = speed;
	m_mapPos = mapPos;
	isVisible = Visible;
	m_dir = VECTOR3(1, 0, 0);
	m_moveDir = VECTOR3(0, 0, 0);
	m_scale = VECTOR3(2, 2, 0);
	m_RotateDegree = 0;
	m_type = WEAPON;
	m_status = IDLE;
	pre_shoot = GetTickCount();
	throwDistance = 0;
	m_width = 16;
	m_height = 4;
	m_id = id;
	
	switch (weapon)
	{
	case SHOOTGUN:
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(_T("Shootgun"));
		m_bullet = 6;
		shoot_time = 1.0f;
		
		break;
	case M16:
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(_T("M16"));
		m_bullet = 30;
		shoot_time = 0.05f;
		break;
	case KATANA:
		m_bullet = 1;
		shoot_time = 0.5f;
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(_T("katana"));
		break;
	default:
		break;
	}
}

void CWeapon::fall(VECTOR3 mappos)
{
	m_mapPos = mappos;
	isVisible= 1;
	m_dir = VECTOR3(0, 0, 1);
	m_status = IDLE;
	

}

void CWeapon::update()
{
	int a = m_id;
	if (m_status == BETHROW)
	{
		m_prePos = m_mapPos;
		m_RotateDegree+=(50);
		m_dir = VECTOR3(cos(m_RotateDegree), -sin(m_RotateDegree), 0);
		
		move();
		if (throwDistance >= 100)
			m_status = IDLE;
		updateboundbox();
	}
		
}


void CWeapon::Render()
{
	if (isVisible)
	{
		m_texture->setRenderPos(0, 0);
		m_texture->Render(m_pos, VECTOR3(0, 0, 1), m_RotateDegree, m_scale);
	}
}

void CWeapon::move()
{
	m_mapPos = m_mapPos + m_moveDir*m_speed;
	throwDistance += m_speed;
}

bool CWeapon::shoot()
{
	int cur_time = GetTickCount();
	if (m_bullet > 0&&(cur_time-pre_shoot)*0.001f>shoot_time)
	{
		pre_shoot = cur_time;
		if(m_weaponType!=KATANA&&m_weaponType!=STICK)
		m_bullet--;
		if (m_bullet < 0)
			m_bullet = 0;
		return 1;
	}
	else return 0;
}

void CWeapon::beThrow(VECTOR3 dir,VECTOR3 pos,VECTOR3 screenpos)
{
	m_status = BETHROW;
	isVisible = 1;
	m_moveDir = VECTOR3(dir.x, -dir.y, dir.z);
	m_mapPos = pos;
	m_pos = screenpos;
	throwDistance = 0;
}

void CWeapon::setAct(ACTSTATUS status)
{
	m_status = status;
	if (status == IDLE)
		m_moveDir = VECTOR3(0, 0, 0);
}

CWeapon::~CWeapon()
{
}
