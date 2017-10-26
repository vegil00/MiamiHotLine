#include "stdafx.h"
#include "Player.h"



CPlayer::CPlayer()
{
	cur_level = NULL;
	m_weapon = NULL;
}

void CPlayer::init(float x, float y, float z,int width, int height,TSTRING name,int id,WEAPONSTATUS w)
{
	m_speed = 2;
	m_mapPos = VECTOR3(x, y, z);
	m_dir = VECTOR3(1, 0, 0);
	m_scale = VECTOR3(1, 1, 1);
	m_preMoveStatus=m_moveStatus = STILL;
	m_name = name;
	detect = 0;
	m_rotate = VECTOR3(0, 0, -1);
	m_RotateDegree = 0.0f;
	row = 0;
	col = 0;
	changeTime = 0.5f;
	//m_mapPos = VECTOR3(0, 0, 0);
	pre_time = GetTickCount();
	m_type = PLAYER;
	//m_mapPos = VECTOR3(288, 288, 0);
	m_scale = VECTOR3(2, 2, 0);
	m_id = 99;
	m_width = width;
	m_height = height;
	alive = 1;
	retry = 0;
	m_rect[0] = VECTOR3(m_mapPos.x - width / 2,m_mapPos.y-height/2,0);
	m_rect[1] = VECTOR3(m_mapPos.x + width / 2, m_mapPos.y - height / 2, 0);
	m_rect[2] = VECTOR3(m_mapPos.x + width / 2, m_mapPos.y+ height / 2, 0);
	m_rect[3] = VECTOR3(m_mapPos.x - width / 2, m_mapPos.y + height / 2, 0);
	pickweapon = 0;
	weaponStatus =w;
	m_id = id;
	m_actStatus = IDLE;
	if (m_weapon == NULL)
	{
		
		m_weapon = new CWeapon;
		m_weapon->setId(m_id - 1);
	}
		
	switch (w)
	{
	case HAND:
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name);
		break;
	case KATANA:
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_katana"));
		if(m_weapon->getId()==m_id-1)
		m_weapon->init(KATANA, 5, false, m_mapPos, m_id - 1);
		
		bullet = m_weapon->getBulletNum();
		break;
	case STICK:
		break;
	case M16:
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name+_T("_m16"));
		if (m_weapon->getId() == m_id - 1)
		m_weapon->init(M16, 5, false, m_mapPos,m_id-1);
		bullet = m_weapon->getBulletNum();
		
		break;
	case SHOOTGUN:
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_shootgun"));
		if (m_weapon->getId() == m_id - 1)
		m_weapon->init(SHOOTGUN, 5, false, m_mapPos,m_id-1);
		bullet = m_weapon->getBulletNum();
		
		break;
	
	default:
		break;
	}
	
	
}

void CPlayer::rotate(VECTOR3 rotate, float degree)
{
	m_rotate = rotate;
	m_RotateDegree = degree;

}

void CPlayer::rotate(VECTOR3 dir)
{
	

	dir = dir.Normalize();
	
	float cos = dir.dot(VECTOR3(1, 0, 0));
	float degree = acos(dir.dot(VECTOR3(1, 0, 0)))*180/PI;
	if(dir.y>=0)
	rotate(VECTOR3(0, 0, 1), degree);
	if(dir.y<0)
		rotate(VECTOR3(0, 0, 1), -degree);
	
	
}

void CPlayer::aniUpdate()
{
	int cur_time = GetTickCount();
	if ((cur_time - pre_time)*0.001f > changeTime)
	{
		pre_time = cur_time;
		col++;
		if (col >= m_texture->getCol())
		{
			col = 0;
			if (m_actStatus == SHOOT|| m_actStatus == EXCUATING||m_actStatus==MEELE)
			{
				changeTime = 0.5f;
				TSTRING resname;
				switch (weaponStatus)
				{case SHOOTGUN:
					
					resname = m_name + _T("_shootgun");
					m_texture = (CSingleImg*)CResManager::getInstance()->getRes(resname);
					m_actStatus = IDLE;
					
					break;
				case HAND:
					resname = m_name;
					m_texture = (CSingleImg*)CResManager::getInstance()->getRes(resname);
					m_actStatus = IDLE;
					break;
				case KATANA:
					m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name+_T("_katana"));
					m_actStatus = IDLE;
					m_width = 8;
					break;
				default:
					break;
				}
			}
			
			
		}
			
	}
	
}

void CPlayer::update()
{
	if (alive)
	{
		aniUpdate();
		switch (m_moveStatus)
		{
		case UP:
			m_moveDir = VECTOR3(0, -1, 0);
			//row = 3;
			break;
		case DOWN:
			m_moveDir = VECTOR3(0, 1, 0);
			//row = 0;
			break;
		case LEFT:
			m_moveDir = VECTOR3(-1, 0, 0);
			//row = 1;
			break;
		case RIGHT:
			m_moveDir = VECTOR3(1, 0, 0);
			//row = 2;
			break;
		case UP | LEFT:
			m_moveDir = VECTOR3(-1, -1, 0).Normalize();
			//row = 6;
			break;
		case UP | RIGHT:
			m_moveDir = VECTOR3(1, -1, 0).Normalize();
			//row = 7;
			break;
		case DOWN | LEFT:
			m_moveDir = VECTOR3(-1, 1, 0).Normalize();
			//row = 4;
			break;
		case DOWN | RIGHT:
			m_moveDir = VECTOR3(1, 1, 0).Normalize();
			//row = 5;
			break;
		case STILL:
			m_moveDir = VECTOR3(0, 0, 0);
		default:
			break;
		}
		m_prePos = m_mapPos;

		move();
		if (m_actStatus == SHOOT&&weaponStatus == M16)
		{
			if (bullet == 0)
			{
				m_actStatus = IDLE;
				m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_m16"));
				changeTime = 0.5f;
			}
			if (m_weapon->shoot())
			{
				bullet = m_weapon->getBulletNum();
				float degree = ((float)(rand() % 2 * (pow(-1, rand() % 2 + 1))) / 180.0f)*PI;
				VECTOR3 dir = VECTOR3(m_dir.x*cos(degree) + m_dir.y*sin(degree), -m_dir.x*sin(degree) + m_dir.y*cos(degree), m_dir.z);
				if (cur_level != NULL)
				{

					cur_level->shoot(PLAYERBULLET, m_mapPos + 5 * VECTOR3(m_dir.x, -m_dir.y, m_dir.z), dir, M16);
					CAudioManager::getInstance()->channelPlay(_T("sndM16"),1);
				}
			}
		}
		if (m_preMoveStatus != m_moveStatus&&m_actStatus == IDLE)
		{
			col = 0;
			m_preMoveStatus = m_moveStatus;

		}
		if (m_moveStatus == STILL&&m_actStatus == IDLE)
		{

			col = 0;
			//m_texture->setShowPos(row, col);
		}

		rotate(m_dir);
	}
	
}



void CPlayer::pickWeapon(CWeapon* w)
{
	/*if (weaponStatus != HAND)
		throwWeapon();*/
	if (w->getAct() == IDLE)
	{
		m_weapon = w;
		w->setVisible(0);
		weaponStatus = w->getWeaponType();
		
		switch (weaponStatus)
		{
		case SHOOTGUN:
		
			
			
			m_texture=(CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_shootgun"));
			break;
		case M16:
			m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_m16"));
			break;
		case KATANA:
			
			m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_katana"));
			break;
		default:
			break;
		}
		col = 0;
		bullet = m_weapon->getBulletNum();
	}
	
}

void CPlayer::throwWeapon()
{
	if (weaponStatus != HAND)
	{
		weaponStatus = HAND;
		col = 0;
		
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name);
		m_weapon->beThrow(m_dir, m_mapPos,m_pos);
		m_weapon = NULL;
		CAudioManager::getInstance()->channelPlay(_T("sndThrow"), 0);
	}
	
}

void CPlayer::move()
{
	//m_pos =m_pos+ m_moveDir*m_speed;
	m_mapPos = m_mapPos + m_moveDir*m_speed;//m_moveDir*m_speed;
	
}

void CPlayer::MessageProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	//switch (msg)
	//{
	//case WM_KEYDOWN:
	//	switch (wParam)
	//	{
	//	case 'W':
	//		if(!(m_moveStatus&DOWN))
	//		m_moveStatus = m_moveStatus|UP;
	//		break;
	//	case 'S':
	//		if (!(m_moveStatus&UP))
	//		m_moveStatus = m_moveStatus | DOWN;
	//		break;
	//	case 'A':
	//		if (!(m_moveStatus&RIGHT))
	//		m_moveStatus = m_moveStatus | LEFT;

	//		break;
	//	case 'D':
	//		if (!(m_moveStatus&LEFT))
	//		m_moveStatus = m_moveStatus | RIGHT;
	//		break;
	//	default:
	//		break;
	//	}
	//	break;
	//case WM_KEYUP:
	//	switch (wParam)
	//	{
	//	case 'W':
	//		m_moveStatus &= (~UP);
	//		break;
	//	case 'S':
	//		m_moveStatus &= (~DOWN);
	//		
	//		break;
	//	case 'A':
	//		m_moveStatus &= (~LEFT);
	//		break;
	//	case 'D':
	//		m_moveStatus &= (~RIGHT);
	//		break;
	//	default:
	//		break;
	//	}
	//	break;
	//default:break;
	//}
}

void CPlayer::Render()
{
	m_texture->setRenderPos(row, col);
	m_texture->Render(m_pos, m_rotate,m_RotateDegree,m_scale);
	//switch (m_moveStatus)
	//{
	//case STILL:
	//	m_texture->Render(m_pos, width, height, row, col);
	//	break;
	//default: break;
	//}
}

void CPlayer::OnKeyDown(sInputEvent keyevent)
{
	//if (alive)
	{
		switch (keyevent.eventkind.keyEvent.key)
		{
		case 'W':
			if (!(m_moveStatus&DOWN))
				m_moveStatus = m_moveStatus | UP;
			break;
		case 'S':
			if (!(m_moveStatus&UP))
				m_moveStatus = m_moveStatus | DOWN;
			break;
		case 'A':
			if (!(m_moveStatus&RIGHT))
				m_moveStatus = m_moveStatus | LEFT;

			break;
		case 'D':
			if (!(m_moveStatus&LEFT))
				m_moveStatus = m_moveStatus | RIGHT;
			break;
		case 'R':
			if (!alive)
				retry = 1;
			break;
		case VK_ESCAPE:
			CGameManager::getInstance()->setStatus(GAMEMENU);
			CGameManager::getInstance()->changestatus();
			break;
		case VK_SPACE:
			m_actStatus = EXCUATE;
			break;
		case VK_SHIFT:
			detect = 1;
			break;
		default:
			break;
		}
		}
		
	
	
	
	
}

void CPlayer::OnKeyUp(sInputEvent keyevent)
{
	if (alive)
	{
		switch (keyevent.eventkind.keyEvent.key)
		{
		case 'W':
			m_moveStatus &= (~UP);
			break;
		case 'S':
			m_moveStatus &= (~DOWN);

			break;
		case 'A':
			m_moveStatus &= (~LEFT);
			break;
		case 'D':
			m_moveStatus &= (~RIGHT);
			break;
		case VK_SHIFT:
			detect = 0;
			break;
		default:
			break;
		}
	}

	
}

void CPlayer::OnMouseMove(sInputEvent mouseevent)
{
	if (alive)
	{
		if (m_actStatus != EXCUATING)
		{
			m_dir = VECTOR3(mouseevent.eventkind.mouseEvent.x, mouseevent.eventkind.mouseEvent.y, 0) - m_pos;
			m_dir = m_dir.Normalize();
		}
	}
	
	
	
}

void CPlayer::OnMouseDown(sInputEvent mouseevent)
{
	if (alive)
	{
		if (mouseevent.eventkind.mouseEvent.key == MOUSE_LB_DOWN)
		{
			m_dir = VECTOR3(mouseevent.eventkind.mouseEvent.x, mouseevent.eventkind.mouseEvent.y, 0) - m_pos;
			m_dir = m_dir.Normalize();
			//CBulletManager::getInstance()->Shoot(_T("bullet"), m_pos + 5 * m_dir, m_dir);
			atk();
		}
		if (mouseevent.eventkind.mouseEvent.key == MOUSE_RB_DOWN)
		{

			pickweapon = 1;
		}
	}
	
	
}

void CPlayer::OnMouseUp(sInputEvent mouseevent)
{
	if (alive)
	{
		if (mouseevent.eventkind.mouseEvent.key == MOUSE_LB_UP)
		{
			if (m_actStatus == SHOOT&&weaponStatus == M16)
			{
				m_actStatus = IDLE;
				m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_m16"));
				col = 0;
			}
		}
	}
	
}

void CPlayer::atk()
{
	TSTRING resname;
	if (bullet > 0&&weaponStatus!=HAND&&weaponStatus!=KATANA)
	{
		bool test;
		VECTOR3 dir;
		float degree;
		
		m_actStatus = SHOOT;
		if (m_weapon->shoot())
		{
			switch (weaponStatus)
			{
			case SHOOTGUN:
				
					resname = m_name + _T("_shootgun_fire");
					m_texture = (CSingleImg*)CResManager::getInstance()->getRes(resname);
					 test=CAudioManager::getInstance()->channelPlay(_T("sndShootgun"), 1);
					
					changeTime = 0.05f;
					for (int i = 0; i < 10; i++)
					{

						degree = ((float)(rand() % 5 * (pow(-1, rand() % 2 + 1))) / 180.0f)*PI;
						//degree = (float)i / 180.0f*PI;
						dir = VECTOR3(m_dir.x*cos(degree) + m_dir.y*sin(degree), -m_dir.x*sin(degree) + m_dir.y*cos(degree), m_dir.z);
						dir = dir.Normalize();
						if (cur_level != NULL)
						{

							cur_level->shoot(PLAYERBULLET, m_mapPos + 5 * VECTOR3(m_dir.x, -m_dir.y, m_dir.z), dir, SHOOTGUN);
						}

					}
				

				break;
			case M16:
				resname = m_name + _T("_m16_fire");
				m_texture = (CSingleImg*)CResManager::getInstance()->getRes(resname);
				changeTime = 0.05f;
				degree = ((float)(rand() % 2 * (pow(-1, rand() % 2 + 1))) / 180.0f)*PI;
				dir = VECTOR3(m_dir.x*cos(degree) + m_dir.y*sin(degree), -m_dir.x*sin(degree) + m_dir.y*cos(degree), m_dir.z);
				if (cur_level != NULL)
				{

					cur_level->shoot(PLAYERBULLET, m_mapPos + 5 * VECTOR3(m_dir.x, -m_dir.y, m_dir.z), dir, M16);
				}
				break;
			default:
				break;
			}
		}
		
		
		bullet = m_weapon->getBulletNum();
	}
	if (m_actStatus==IDLE)
	{
		if ((weaponStatus == HAND))
		{
			changeTime = 0.05f;
			m_actStatus = MEELE;
			col = 0;
			if (punch_LR)
			{
				resname = m_name + _T("_punch1");

				punch_LR = 0;
				m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_punch1"));
			}
			else
			{
				resname = m_name + _T("_punch2");
				punch_LR = 1;
				m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name +_T("_punch2"));
			}
		}
	
		if (weaponStatus==KATANA)
		{
			changeTime = 0.05f;
			m_actStatus = MEELE;
			m_width = 24;
			col = 0;
			resname = m_name + _T("_katana_slash");
			m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_katana_slash"));
		}
		
	}
	
}

void CPlayer::excuate(CEnemy * ene)
{
	if (alive)
	{
		m_dir = ene->getDir();

		m_mapPos = ene->getmapPos();
		ene->beExcuate(weaponStatus);
		TSTRING resname;
		switch (weaponStatus)
		{
		default:
			resname = m_name + _T("_excuate_kick");
			break;
		}
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(resname);
		col = 0;
		m_actStatus = EXCUATING;

		changeTime = 0.05f;
	}
	

}

void CPlayer::hit(VECTOR3 dir, WEAPONSTATUS wstatus)
{
	alive = 0;
	m_dir =dir;
	rotate(m_dir);
	switch (wstatus)
	{case M16:
	case SHOOTGUN:
		alive = 0;
		m_texture = (CSingleImg*)CResManager::getInstance()->getRes(m_name + _T("_hitbyshootgun"));
		break;
	default:
		break;
	}
}


CPlayer::~CPlayer()
{
}
