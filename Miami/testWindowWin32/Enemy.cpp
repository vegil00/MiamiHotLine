#include "stdafx.h"
#include "Enemy.h"


CEnemy::CEnemy()
{
	m_moveDir = VECTOR3(0, 0, 0);
	m_RotateDegree = 0;
	m_actStatus = 0;
	m_weapon = NULL;
}

void CEnemy::init(TSTRING name,VECTOR3 mappos,int width,int height,ACTSTATUS act,CLevel* level,int id, WEAPONSTATUS w)
{

	m_name = name;
	m_mapPos = mappos;
	m_id = id;
	m_dir = VECTOR3(1, 0, 0);
	m_moveDir = VECTOR3(0, 0, 0);
	row = 0;
	col = 0;
	pre_time = GetTickCount();
	changeTime = 0.1f;
	m_scale = VECTOR3(2, 2, 0);
	m_type = ENEMY;
	alive = 1;
	m_RotateDegree = 0;
	m_rotate = VECTOR3(0, 0, 1);
	m_width = width;
	m_height = height;
	m_actStatus = act;
	cur_level = level;
	targetindex = 0;
	route.clear();
	m_speed = 1;
	weaponStatus = w;
	changeTime = 0.5f;
	switch (w)
	{
	case HAND:
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(name + _T("_idle"));
		break;
	case KATANA:
		break;
	case STICK:
		break;
	case M16:
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_M16"));
		if(m_weapon==NULL)
		m_weapon = new CWeapon;
		m_weapon->init(M16, 5, false, m_mapPos,m_id+40);
		m_weapon->setId(m_id + 40);
		cur_level->AddChild(m_weapon);
		break;
	case SHOOTGUN:
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_shootgun"));
		if (m_weapon == NULL)
		m_weapon = new CWeapon;
		m_weapon->init(SHOOTGUN, 5, false, m_mapPos, m_id + 40);
		m_weapon->setId(m_id + 40);
		cur_level->AddChild(m_weapon);
		break;
	default:
		break;
	}
}

void CEnemy::addtarget(VECTOR3 pos)
{
	 target.push_back(pos); 
}

void CEnemy::update()
{
	int a = m_id;
	if (alive)
	{
		aniUpdate();
		
	
			
		
			


		int cur_time=GetTickCount();
		
		switch (m_actStatus)
		{
		case IDLE:
			changeTime = 0.5f;
			m_moveDir = VECTOR3(m_dir.x, -m_dir.y, m_dir.z);
			break;
		case PATROL:
			if (route.empty())
				getRoute();
			move();
			m_dir = VECTOR3(m_moveDir.x, -m_moveDir.y, 0);
			
			if ((m_mapPos - target[targetindex]).length() <= 8)
			{
				targetindex++;
				if (targetindex >= target.size())
					targetindex = 0;
				getRoute();
			}
			break;
		case SHOOT:
			m_moveDir = VECTOR3(m_dir.x, -m_dir.y, m_dir.z);
			break;
		case SEARCH:
			break;
	
		case STUN:
			if ((cur_time - stun_time)*0.001f > 10.0f)
			{
				if (target.size() <= 0)
				{
					m_actStatus = IDLE;
					m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name+_T("_idle"));
					col = 0;
				}
				else
				{
					m_actStatus = PATROL;
					switch(weaponStatus)
					{
					case M16:
						m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_M16"));
						break;
					case HAND:
						m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_idle"));
						default: break;
					}
					
				}
				
			}
				

			break;
		default:
			break;

		}
		rotate(m_dir);
	}
	
	
}

void CEnemy::move()
{
	m_prePos = m_mapPos;
	m_mapPos = m_mapPos + m_moveDir*m_speed;
	
	if ((m_mapPos - cur_target).length() <= 8)
	{
		route.pop_front();
		if (route.size() > 0)
		{
			int posX = ((float)((*(route.begin()))->x) + 0.5f)*(cur_level->getcolwidth());
			int posY = ((float)((*(route.begin()))->y) + 0.5f)*(cur_level->getrowheight());
			cur_target = VECTOR3(posX, posY, 0);
		}
		
	}
	m_moveDir = (cur_target - m_mapPos).Normalize();

	
}

void CEnemy::Render()
{
	m_texture->setRenderPos(row, col);
	m_texture->Render(m_pos, VECTOR3(0, 0, 1), m_RotateDegree, m_scale);
	
}

void CEnemy::hit(VECTOR3 dir, WEAPONSTATUS wstatus)
{
	
	TSTRING resname ;
	switch (wstatus)
	{
	case SHOOTGUN:
	case M16:
	case KATANA:
		resname = m_name + _T("_hitByShootgun");
		
		alive = 0;
		cur_level->enemydie();
		if(wstatus==KATANA)
		CAudioManager::getInstance()->channelPlay(_T("sndCut1"), 0);
		break;
	case HAND:
		resname = m_name + _T("_stun");
		stun_time = GetTickCount();
		CAudioManager::getInstance()->channelPlay(_T("sndPunch"), 0);
		m_actStatus = STUN;
		break;
	default:
		break;

	}

	
	
	m_texture = (CSingleImg*)CResManager::getInstance()->getRes(resname);
	col = 0;
	row = 0;
	m_weapon->fall(m_mapPos);
	
	weaponStatus = HAND;
	
	rotate(dir);
	
}

void CEnemy::beExcuate(WEAPONSTATUS w)
{
	m_actStatus = BEEXCUATE;
	TSTRING resname;
	switch(w)
	{
	case KATANA:
		break;
	case STICK:
		break;
	default:
		resname = m_name + _T("_excuated_kick");
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(resname);
		col = 0;
		break;
	}
	changeTime = 0.05f;
}

void CEnemy::aniUpdate()
{
	if (alive)
	{
		int temp = m_id;
		int cur_time = GetTickCount();
		if ((cur_time - pre_time)*0.001f > changeTime)
		{
			pre_time = cur_time;
			col++;
			if (col >= m_texture->getCol())
			{
				if (m_actStatus != BEEXCUATE)
				{
					col = 0;
					if (m_actStatus == SHOOT)
					{
						if (target.size() > 0)
						{
							m_actStatus = PATROL;
							m_moveDir = (cur_target - m_mapPos).Normalize();
						}
						else
						{
							m_actStatus = IDLE;
						}
						switch (weaponStatus)
						{
						case M16:

							m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_M16"));
							break;
						case HAND:
							m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_idle"));
							break;
						case SHOOTGUN:
							m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_shootgun"));
							changeTime = 0.5f;
							break;
						default:
							break;
						}
					}
				}

				if (m_actStatus == BEEXCUATE)
				{
					col = m_texture->getCol() - 1;
					alive = 0;
					cur_level->enemydie();
				}

			}

		}
	}
	
}

void CEnemy::rotate(VECTOR3 rotate, float degree)
{
	m_rotate = rotate;
	m_RotateDegree = degree;
}

void CEnemy::rotate(VECTOR3 dir)
{
	dir = dir.Normalize();

	float cos = dir.dot(VECTOR3(1, 0, 0));
	float degree = acos(dir.dot(VECTOR3(1, 0, 0))) * 180 / PI;
	if (dir.y >= 0)
		rotate(VECTOR3(0, 0, 1), degree);
	if (dir.y<0)
		rotate(VECTOR3(0, 0, 1), -degree);
}

void CEnemy::stun(VECTOR3 dir)
{
	VECTOR3 v = dir;
	rotate(dir);
	m_actStatus = STUN;
	TSTRING resname = m_name + _T("_stun");
	m_texture = (CSingleImg*)CResManager::getInstance()->getRes(resname);
}


void CEnemy::atk(VECTOR3 pos)
{
	VECTOR3 dir = (pos - m_mapPos).Normalize();
	
	if (dir.dot(VECTOR3(m_dir.x, -m_dir.y, m_dir.z))>=0.707f)
	{
		float distance = (pos - m_mapPos).length();
		bool see = 1;
		VECTOR3 ray = m_mapPos;
		for (int i = 0; i < distance; i++)
		{
			ray = ray + dir;
			int x = ray.x / cur_level->getcolwidth();
			int y = ray.y / cur_level->getrowheight();
			if (cur_level->getcollision(x, y))
			{
				see = 0;
				break;
			}
		}
		if (see)
		{
			m_dir = VECTOR3(dir.x, -dir.y, dir.z);
			rotate(m_dir);
			float degree;
			TSTRING resname;

			//dir.y = dir.y;
			m_moveDir = VECTOR3(0, 0, 0);

			if (m_weapon->shoot())
			{
				switch (weaponStatus)
				{
				case SHOOTGUN:
					m_actStatus = SHOOT;
					resname = m_name + _T("_shootgun_fire");
					m_texture = (CSingleImg*)CResManager::getInstance()->getRes(resname);

					changeTime = 0.05f;
					CAudioManager::getInstance()->channelPlay(_T("sndShotgun"), 0);
					for (int i = 0; i < 10; i++)
					{

						degree = ((float)(rand() % 5 * (pow(-1, rand() % 2 + 1))) / 180.0f)*PI;
						//degree = (float)i / 180.0f*PI;
						dir = VECTOR3(m_dir.x*cos(degree) + m_dir.y*sin(degree), -m_dir.x*sin(degree) + m_dir.y*cos(degree), m_dir.z);
						dir = dir.Normalize();
						if (cur_level != NULL)
						{

							cur_level->shoot(ENEMYBULLET, m_mapPos + 5 * VECTOR3(m_dir.x, -m_dir.y, m_dir.z), dir, SHOOTGUN);
						}


					}


					break;
				case M16:
					m_actStatus = SHOOT;
					resname = m_name + _T("_M16_fire");
					m_texture = (CSingleImg*)CResManager::getInstance()->getRes(resname);
					changeTime = 0.05f;
					degree = ((float)(rand() % 2 * (pow(-1, rand() % 2 + 1))) / 180.0f)*PI;
					dir = VECTOR3(m_dir.x*cos(degree) + m_dir.y*sin(degree), -m_dir.x*sin(degree) + m_dir.y*cos(degree), m_dir.z);
					CAudioManager::getInstance()->channelPlay(_T("sndM16"), 0);
					if (cur_level != NULL)
					{

						cur_level->shoot(ENEMYBULLET, m_mapPos + 5 * VECTOR3(m_dir.x, -m_dir.y, m_dir.z), dir, M16);
					}
					break;
				default:
					break;
				}
			}
		}
	}
	
	


	bullet = m_weapon->getBulletNum();
}



void CEnemy::PickWeapon(CWeapon * w)
{
	m_weapon = w;
	weaponStatus = w->getWeaponType();
	w->setVisible(0);
	switch (w->getWeaponType())
	{case M16:
		m_weapon = w;
		weaponStatus = w->getWeaponType();
		w->setVisible(0);
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_M16"));
		changeTime = 0.5f;
		break;
	case SHOOTGUN:
		m_weapon = w;
		weaponStatus = w->getWeaponType();
		w->setVisible(0);
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_shootgun"));
		changeTime = 0.5f;
		break;

	default:
		break;
	}
	col = 0;
}

void CEnemy::getRoute()
{
	int targetX = target[targetindex].x / (cur_level->getcolwidth());
	int targetY = target[targetindex].y / (cur_level->getrowheight());
	int posX = m_mapPos.x / (cur_level->getcolwidth());
	int posY = m_mapPos.y / (cur_level->getrowheight());
	route.clear();
	route=findRoute(VECTOR3(posX, posY, 0), VECTOR3(targetX, targetY, 0), cur_level->getmapInfo(), cur_level->getrow(), cur_level->getcol());
	posX = ((float)((*(route.begin()))->x) + 0.5f)*(cur_level->getcolwidth());
	posY = ((float)((*(route.begin()))->y) + 0.5f)*(cur_level->getrowheight());
	cur_target = VECTOR3(posX, posY, 0);
}

CEnemy::~CEnemy()
{
}
