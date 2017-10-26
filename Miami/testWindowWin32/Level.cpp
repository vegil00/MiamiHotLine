#include "stdafx.h"
#include "Level.h"


CLevel::CLevel()
{
	m_collision = NULL;
	shootgun = NULL;
	m16 = NULL;
	m_player = NULL;
	leave_area = NULL;
	blood = NULL;
	go = NULL;
	retry = NULL;
	/*row = 50;
	col = 60;
	colwidth = rowheight = 16;*/
	
}

void CLevel::init(TSTRING map,   TSTRING levelconfig, HWND hwnd,  CPlayer* player)
{
	
#ifdef _UNICODE
	string mappath = CU_U2A(map);

	string config = CU_U2A(levelconfig);
	info = config;
#else
	string mappath = mappath;
	string levelpath = levelconfig;
	string config = levelconfig;
	info = config;
#endif // _UNICODE
	m_backGround = new CStaticImg;
	/*m_backGround = (CStaticImg*)CResManager::getInstance()->getRes(background);*/
	FILE* file = fopen(mappath.c_str(), "r");
	
	
	 fscanf(file, "width:%d,height:%d,tilewidth:%d,tileheight:%d", &col, &row, &colwidth, &rowheight);
	
	int value = 0;
	m_collision = new sNode*[row];
	for (int i = 0; i < row; i++)
	{
		m_collision[i] = new sNode[col];
		for (int j = 0; j <col; j++)
		{
			fscanf(file, "%d,", &value);
			m_collision[i][j].con = value;
		}
	}
	fclose(file);
	
	GetClientRect(hwnd, &screen);
	m_CameraPos = VECTOR3(288, 288, 0);
	showRect.left = (m_CameraPos.x) - 8*colwidth;
	showRect.bottom = (m_CameraPos.y) + 6*rowheight;
	showRect.right = (m_CameraPos.x) + 8*colwidth;
	showRect.top = (m_CameraPos.y) - 6*rowheight;
	imageWidth = (float)(showRect.right - showRect.left) / (col*colwidth);
	imageHeight = (float)(showRect.bottom - showRect.top) / (row*rowheight);
	shootgun = new CIcon;
	shootgun->init(VECTOR3(5, 5, 0), _T("ammo_shootgun"));
	m16 = new CIcon;
	m16->init(VECTOR3(5, 5, 0), _T("ammo_rifle"));
	blood = new CIcon;
	blood->init(VECTOR3(0, 0, 0), _T("blood")); 
	leave_area = new CIcon;
	leave_area->init(VECTOR3(600,50, 0), _T("leave_area"));
	go = new CIcon;
	go->init(VECTOR3(0, 0, 0), _T("go"));
	retry = new CIcon;
	retry->init(VECTOR3(120, 28, 0), _T("retry"));
	ene_num = 0;
	TiXmlDocument* doc = new TiXmlDocument(config.c_str());
	doc->LoadFile();
	TiXmlElement* root = doc->FirstChildElement();
	leave = VECTOR3(0, 0, 0);
	leave.x = atoi(root->Attribute("leaveX"));
	leave.y = atoi(root->Attribute("leaveY"));
	
#ifdef _UNICODE
	string temp = root->Attribute("background");

	TSTRING name = CU_A2U(temp);
	name.pop_back();
#else
	TSTRING name = ene->Attribute("name");
#endif // _UNICODE

	m_backGround = (CStaticImg*)CResManager::getInstance()->getRes(name);
	for (TiXmlElement* ele = root->FirstChildElement(); ele != NULL; ele = ele->NextSiblingElement())
	{
		int type = atoi(ele->Attribute("type"));
		if (type == 1)
		{
			if (ele->FirstChildElement() != NULL)
			{
				for (TiXmlElement* ene = ele->FirstChildElement(); ene != NULL; ene = ene->NextSiblingElement())
				{
					ene_num++;
#ifdef _UNICODE
					string temp = ene->Attribute("name");
					
						TSTRING name =CU_A2U(temp);
						name.pop_back();
#else
					TSTRING name = ene->Attribute("name");
#endif // _UNICODE
					int id = atoi(ene->Attribute("id"));
					WEAPONSTATUS wstatus = (WEAPONSTATUS)(atoi(ene->Attribute("weapon")));
					ACTSTATUS astatus = (ACTSTATUS)(atoi(ene->Attribute("status")));
					float posX = atoi(ene->Attribute("posX"));
					float posY = atoi(ene->Attribute("posY"));
					int width= atoi(ene->Attribute("width"));
					int height= atoi(ene->Attribute("height"));
					CEnemy* enemy = new CEnemy;
					enemy->init(name, VECTOR3(posX, posY, 0), width, height, astatus, this, id, wstatus);
					if (ene->FirstChildElement() != NULL)
					{
						for (TiXmlElement* target = ene->FirstChildElement(); target != NULL; target = target->NextSiblingElement())
						{
							VECTOR3 targetPos = VECTOR3(0, 0, 0);
							targetPos.x = atoi(target->Attribute("posX"));
							targetPos.y = atoi(target->Attribute("posY"));
							enemy->addtarget(targetPos);
						}
					}
					this->AddChild(enemy);

				}
			}
			
		}
		if (type == 2)
		{
			int num = atoi(ele->Attribute("num"));
#ifdef _UNICODE
			string temp = ele->Attribute("name");
			TSTRING name = CU_A2U(temp);
			name.pop_back();
#else
			TSTRING name = ele->Attribute("name");
#endif // _UNICODE
			int atk = atoi(ele->Attribute("atk"));
			int speed = atoi(ele->Attribute("speed"));
			int width = atoi(ele->Attribute("width"));
			int height = atoi(ele->Attribute("height"));
			for (int i = 0; i < num; i++)
			{
				CBullet* bullet = new CBullet;
				bullet->init(atk, speed, name, 1, width, height,(BULLETTYPE)0);
				bullet->setId(i + 100);
				this->AddChild(bullet);
			}
		}
		if (type == 3)
		{
			if (ele->FirstChildElement() != NULL)
			{
				for (TiXmlElement* weapon = ele->FirstChildElement(); weapon != NULL; weapon = weapon->NextSiblingElement())
				{
					WEAPONSTATUS wstatus = (WEAPONSTATUS)(atoi(weapon->Attribute("type")));
					int id = atoi(weapon->Attribute("id"));
					float speed = atoi(weapon->Attribute("speed"));
					float posX = atoi(weapon->Attribute("posX"));
					float posY = atoi(weapon->Attribute("posY"));
					CWeapon* w = new CWeapon;
					w->init(wstatus, speed, 1, VECTOR3(posX, posY, 0),id);
					this->AddChild(w);
				}
			}
		}
		if (type == 4)
		{
			float posX = atoi(ele->Attribute("posX"));
			float posY = atoi(ele->Attribute("posY"));
			int width = atoi(ele->Attribute("width"));
			int height = atoi(ele->Attribute("height"));
#ifdef _UNICODE
			string temp = ele->Attribute("name");
			TSTRING name = CU_A2U(temp);
			name.pop_back();
#else
			TSTRING name = ele->Attribute("name");
#endif // _UNICODE
			int id = atoi(ele->Attribute("id"));
			WEAPONSTATUS wstatus= (WEAPONSTATUS)(atoi(ele->Attribute("weapon")));
			player->init(posX, posY, 0, width, height, name, id, wstatus);
			this->addPlayer(player);
		}
		
	}
	
}

void CLevel::init(string map, string levelconfig, HWND hwnd, CPlayer * player)
{

	string mappath = map;
	
	string config = levelconfig;
	info = config;
	
	m_backGround = new CStaticImg;
	/*m_backGround = (CStaticImg*)CResManager::getInstance()->getRes(background);*/
	FILE* file = fopen(mappath.c_str(), "r");

	int a = GetLastError();
	fscanf(file, "width:%d,height:%d,tilewidth:%d,tileheight:%d", &col, &row, &colwidth, &rowheight);
	a = GetLastError();
	int value = 0;
	m_collision = new sNode*[row];
	for (int i = 0; i < row; i++)
	{
		m_collision[i] = new sNode[col];
		for (int j = 0; j <col; j++)
		{
			fscanf(file, "%d,", &value);
			m_collision[i][j].con = value;
		}
	}
	fclose(file);
	
	GetClientRect(hwnd, &screen);
	m_CameraPos = VECTOR3(288, 288, 0);
	showRect.left = (m_CameraPos.x) - 8 * colwidth;
	showRect.bottom = (m_CameraPos.y) + 6 * rowheight;
	showRect.right = (m_CameraPos.x) + 8 * colwidth;
	showRect.top = (m_CameraPos.y) - 6 * rowheight;
	imageWidth = (float)(showRect.right - showRect.left) / (col*colwidth);
	imageHeight = (float)(showRect.bottom - showRect.top) / (row*rowheight);
	shootgun = new CIcon;
	shootgun->init(VECTOR3(5, 5, 0), _T("ammo_shootgun"));
	m16 = new CIcon;
	m16->init(VECTOR3(5, 5, 0), _T("ammo_rifle"));
	blood = new CIcon;
	blood->init(VECTOR3(0, 0, 0), _T("blood"));
	leave_area = new CIcon;
	leave_area->init(VECTOR3(600, 50, 0), _T("leave_area"));
	go = new CIcon;
	go->init(VECTOR3(0, 0, 0), _T("go"));
	retry = new CIcon;
	retry->init(VECTOR3(120, 28, 0), _T("retry"));
	ene_num = 0;
	TiXmlDocument* doc = new TiXmlDocument(config.c_str());
	doc->LoadFile();
	TiXmlElement* root = doc->FirstChildElement();
	leave = VECTOR3(0, 0, 0);
	leave.x = atoi(root->Attribute("leaveX"));
	leave.y = atoi(root->Attribute("leaveY"));
	next = atoi(root->Attribute("next"));
	m_id = atoi(root->Attribute("id"));
#ifdef _UNICODE
	string temp = root->Attribute("background");

	TSTRING name = CU_A2U(temp);
	name.pop_back();
#else
	TSTRING name = ene->Attribute("name");
#endif // _UNICODE

	m_backGround = (CStaticImg*)CResManager::getInstance()->getRes(name);
	for (TiXmlElement* ele = root->FirstChildElement(); ele != NULL; ele = ele->NextSiblingElement())
	{
		int type = atoi(ele->Attribute("type"));
		if (type == 1)
		{
			if (ele->FirstChildElement() != NULL)
			{
				for (TiXmlElement* ene = ele->FirstChildElement(); ene != NULL; ene = ene->NextSiblingElement())
				{
					ene_num++;
#ifdef _UNICODE
					string temp = ene->Attribute("name");

					TSTRING name = CU_A2U(temp);
					name.pop_back();
#else
					TSTRING name = ene->Attribute("name");
#endif // _UNICODE
					int id = atoi(ene->Attribute("id"));
					WEAPONSTATUS wstatus = (WEAPONSTATUS)(atoi(ene->Attribute("weapon")));
					ACTSTATUS astatus = (ACTSTATUS)(atoi(ene->Attribute("status")));
					float posX = atoi(ene->Attribute("posX"));
					float posY = atoi(ene->Attribute("posY"));
					int width = atoi(ene->Attribute("width"));
					int height = atoi(ene->Attribute("height"));
					CEnemy* enemy = new CEnemy;
					enemy->init(name, VECTOR3(posX, posY, 0), width, height, astatus, this, id, wstatus);
					if (ene->FirstChildElement() != NULL)
					{
						for (TiXmlElement* target = ene->FirstChildElement(); target != NULL; target = target->NextSiblingElement())
						{
							VECTOR3 targetPos = VECTOR3(0, 0, 0);
							targetPos.x = atoi(target->Attribute("posX"));
							targetPos.y = atoi(target->Attribute("posY"));
							enemy->addtarget(targetPos);
						}
					}
					this->AddChild(enemy);

				}
			}

		}
		if (type == 2)
		{
			int num = atoi(ele->Attribute("num"));
#ifdef _UNICODE
			string temp = ele->Attribute("name");
			TSTRING name = CU_A2U(temp);
			name.pop_back();
#else
			TSTRING name = ele->Attribute("name");
#endif // _UNICODE
			int atk = atoi(ele->Attribute("atk"));
			int speed = atoi(ele->Attribute("speed"));
			int width = atoi(ele->Attribute("width"));
			int height = atoi(ele->Attribute("height"));
			for (int i = 0; i < num; i++)
			{
				CBullet* bullet = new CBullet;
				bullet->init(atk, speed, name, 1, width, height, (BULLETTYPE)0);
				bullet->setId(i + 100);
				this->AddChild(bullet);
			}
		}
		if (type == 3)
		{
			if (ele->FirstChildElement() != NULL)
			{
				for (TiXmlElement* weapon = ele->FirstChildElement(); weapon != NULL; weapon = weapon->NextSiblingElement())
				{
					WEAPONSTATUS wstatus = (WEAPONSTATUS)(atoi(weapon->Attribute("type")));
					int id = atoi(weapon->Attribute("id"));
					float speed = atoi(weapon->Attribute("speed"));
					float posX = atoi(weapon->Attribute("posX"));
					float posY = atoi(weapon->Attribute("posY"));
					CWeapon* w = new CWeapon;
					w->init(wstatus, speed, 1, VECTOR3(posX, posY, 0), id);
					this->AddChild(w);
				}
			}
		}
		if (type == 4)
		{
			float posX = atoi(ele->Attribute("posX"));
			float posY = atoi(ele->Attribute("posY"));
			int width = atoi(ele->Attribute("width"));
			int height = atoi(ele->Attribute("height"));
#ifdef _UNICODE
			string temp = ele->Attribute("name");
			TSTRING name = CU_A2U(temp);
			name.pop_back();
#else
			TSTRING name = ele->Attribute("name");
#endif // _UNICODE
			int id = atoi(ele->Attribute("id"));
			WEAPONSTATUS wstatus = (WEAPONSTATUS)(atoi(ele->Attribute("weapon")));
			player->init(posX, posY, 0, width, height, name, id, wstatus);
			this->addPlayer(player);
		}

	}

}

void CLevel::reset()
{
	TiXmlDocument* doc = new TiXmlDocument(info.c_str());
	doc->LoadFile();
	TiXmlElement* root = doc->FirstChildElement();
	leave = VECTOR3(0, 0, 0);
	leave.x = atoi(root->Attribute("leaveX"));
	leave.y = atoi(root->Attribute("leaveY"));
	ene_num = 0;
	for (TiXmlElement* ele = root->FirstChildElement(); ele != NULL; ele = ele->NextSiblingElement())
	{
		int type = atoi(ele->Attribute("type"));
		if (type == 1)
		{
			if (ele->FirstChildElement() != NULL)
			{
				for (TiXmlElement* ene = ele->FirstChildElement(); ene != NULL; ene = ene->NextSiblingElement())
				{
					ene_num++;
#ifdef _UNICODE
					string temp = ene->Attribute("name");

					TSTRING name = CU_A2U(temp);
					name.pop_back();
#else
					TSTRING name = ene->Attribute("name");
#endif // _UNICODE
					int id = atoi(ene->Attribute("id"));
					WEAPONSTATUS wstatus = (WEAPONSTATUS)(atoi(ene->Attribute("weapon")));
					ACTSTATUS astatus = (ACTSTATUS)(atoi(ene->Attribute("status")));
					float posX = atoi(ene->Attribute("posX"));
					float posY = atoi(ene->Attribute("posY"));
					int width = atoi(ene->Attribute("width"));
					int height = atoi(ene->Attribute("height"));
					
					((CEnemy*)m_childList[id])->init(name, VECTOR3(posX, posY, 0), width, height, astatus, this, id, wstatus);
					
					

				}
			}

		}
		if (type == 2)
		{
			int num = atoi(ele->Attribute("num"));
#ifdef _UNICODE
			string temp = ele->Attribute("name");
			TSTRING name = CU_A2U(temp);
			name.pop_back();
#else
			TSTRING name = ele->Attribute("name");
#endif // _UNICODE
			int atk = atoi(ele->Attribute("atk"));
			int speed = atoi(ele->Attribute("speed"));
			int width = atoi(ele->Attribute("width"));
			int height = atoi(ele->Attribute("height"));
			for (int i = 0; i < num; i++)
			{
				
				((CBullet*)m_childList[i+100])->init(atk, speed, name, 1, width, height, (BULLETTYPE)0);
				
			}
		}
		if (type == 3)
		{
			if (ele->FirstChildElement() != NULL)
			{
				for (TiXmlElement* weapon = ele->FirstChildElement(); weapon != NULL; weapon = weapon->NextSiblingElement())
				{
					WEAPONSTATUS wstatus = (WEAPONSTATUS)(atoi(weapon->Attribute("type")));
					int id = atoi(weapon->Attribute("id"));
					float speed = atoi(weapon->Attribute("speed"));
					float posX = atoi(weapon->Attribute("posX"));
					float posY = atoi(weapon->Attribute("posY"));
					
					((CWeapon*)m_childList[id])->init(wstatus, speed, 1, VECTOR3(posX, posY, 0), id);
					
				}
			}
		}
		if (type == 4)
		{
			float posX = atoi(ele->Attribute("posX"));
			float posY = atoi(ele->Attribute("posY"));
			int width = atoi(ele->Attribute("width"));
			int height = atoi(ele->Attribute("height"));
#ifdef _UNICODE
			string temp = ele->Attribute("name");
			TSTRING name = CU_A2U(temp);
			name.pop_back();
#else
			TSTRING name = ele->Attribute("name");
#endif // _UNICODE
			int id = atoi(ele->Attribute("id"));
			WEAPONSTATUS wstatus = (WEAPONSTATUS)(atoi(ele->Attribute("weapon")));
			m_player->init(posX, posY, 0, width, height, name, id, wstatus);
			m_player->setCurLevel(this);
			m_CameraPos = m_player->getmapPos();
			
		}

	}
}

void CLevel::Render()
{

	m_backGround->Render(VECTOR3(400, 300, 0), VECTOR3(0, 0, 0), 0, 800, 600, VECTOR3((float)showRect.left/(float)(col*colwidth),1.0f-(float)showRect.bottom/(float)(row*rowheight),0), imageWidth, imageHeight);
	for (map<UINT, CNode*>::iterator it = m_childList.begin(); it != m_childList.end(); it++)
	{
		if (((*it).second->getType() == ENEMY || (*it).second->getType() == PLAYER) &&((CSprite*)(*it).second)->isAlive()==false)
		{
			blood->setPos((*it).second->getPos());
			blood->Render();
		}
		(*it).second->Render();
	}
	//m_player->Render();
	
	if (m_player->getWeaponType() != HAND&&m_player->getWeaponType() != STICK&&m_player->getWeaponType() != KATANA)
	{
		//char* bulletnum=new char;
		//itoa(m_player->getbullet(), bulletnum, 10);
		//glColor3f(1.0f, 0.0f, 0.0f);     //设置字体颜色  
		//glRasterPos2i(400, 300);  //起始位置  
		//drawString(bulletnum);
		//glColor3f(1.0f, 1.0f, 1.0f);
		switch (m_player->getWeaponType())

		{
		case SHOOTGUN:
			for (int i = 0; i < m_player->getbullet(); i++)
			{
				shootgun->setPos(VECTOR3(shootgun->getPos().x+10, shootgun->getPos().y, 0));
				shootgun->Render();
			}
			shootgun->setPos(VECTOR3(5, 5, 0));
			
			
			break;
		case M16:
			for (int i = 0; i < m_player->getbullet(); i++)
			{
				m16->setPos(VECTOR3(m16->getPos().x + 10, m16->getPos().y, 0));
				m16->Render();
			}
			m16->setPos(VECTOR3(5, 5, 0));
		
		
			break;
		default:
			break;
		}
	}
	if (ene_num == 0)
	{
		leave_area->Render();
		go->Render();
	}
	if (ene_num > 0 && m_player->isAlive() == false)
	{
		retry->Render();
	}
	

}



void CLevel::update()
{
	imageWidth = (float)(showRect.right - showRect.left) / (col*colwidth);
	imageHeight = (float)(showRect.bottom - showRect.top) / (row*rowheight);
	VECTOR3 offset;
	float scaleX = (float)(showRect.right - showRect.left) / (screen.right - screen.left);
float scaleY = (float)(showRect.bottom - showRect.top) / (screen.bottom - screen.top);
if ((m_CameraPos - m_player->getmapPos()).length() > 10&&m_player->isdetect()==0)
{
	m_CameraPos = m_CameraPos + ((m_player->getmapPos() - m_CameraPos).Normalize()) * m_player->getspeed();
}
if ((m_CameraPos - m_player->getmapPos()).length() <40 && m_player->isdetect() == 1)
{
	m_CameraPos = m_CameraPos +VECTOR3(m_player->getDir().x,-m_player->getDir().y,0)*5;
}
if (ene_num > 0 && !m_player->isAlive())
{
	if(m_player->isretry())
	this->reset();
}
if (ene_num == 0)
{
	offset = leave - m_CameraPos;
	offset.x = offset.x / scaleX;
	offset.y = -offset.y / scaleY;
	VECTOR3 pos=VECTOR3(400, 300, 0) + offset;
	if (pos.x < 20)
	{
		pos.x = 20;
		go->rotate(VECTOR3(offset.x, offset.y, 0));

	}
		
	if (pos.x > 760)
	{
		pos.x = 760;
		go->rotate(VECTOR3(offset.x, offset.y, 0));

	}
		
	if (pos.y > 560)
	{
		pos.y = 560;
		go->rotate(VECTOR3(offset.x, offset.y, 0));

	}
		
	if (pos.y < 20)
	{
		pos.y = 20;
		go->rotate(VECTOR3(offset.x, offset.y, 0));

	}
	if (pos.y > 20 && pos.x > 20 && pos.x < 760 && pos.y < 560)
	{
		go->rotate(VECTOR3(1, 0, 0));
	}
	
	go->setPos(pos);
	if ((m_player->getmapPos() - leave).length() < 10)
	{
		this->reset();
		this->resetplayer();
		CGameManager::getInstance()->setStatus(next);
		CGameManager::getInstance()->changestatus();
		
	}
	

}

for (map<UINT, CNode*>::iterator it = m_childList.begin(); it != m_childList.end(); it++)
{
	(*it).second->update();
	offset = (*it).second->getmapPos() - m_CameraPos;
	offset.x = offset.x / scaleX;
	offset.y = -offset.y / scaleY;
	(*it).second->setPos(VECTOR3(400, 300, 0) + offset);
	VECTOR3 pos = (*it).second->getmapPos();
	VECTOR3 targetpos;
	pos.x = pos.x / colwidth;
	pos.y = pos.y / rowheight;
	switch ((*it).second->getType())
	{
	case PLAYER:
		if (m_collision[(int)pos.y][(int)pos.x].con)
			(*it).second->setmapPos((*it).second->getPrePos());
		((CSprite*)(*it).second)->updateboundbox();
		
		if (((CPlayer*)(*it).second)->pick())
		{
			((CPlayer*)(*it).second)->throwWeapon();
			for (map<UINT, CNode*>::iterator it1 = m_childList.begin(); it1 != m_childList.end(); it1++)
			{
				if ((*it1).second->getType() == WEAPON && ((CWeapon*)(*it1).second)->isvisible() && ((CWeapon*)(*it1).second)->getAct() == IDLE)
				{
					if (((*it1).second->getmapPos() - (*it).second->getmapPos()).length() <= 5)
					{
						((CPlayer*)(*it).second)->pickWeapon((CWeapon*)(*it1).second);
						break;
					}

				}
			}
			((CPlayer*)(*it).second)->picked();
		}
		if (((CPlayer*)(*it).second)->getAct() == EXCUATE)
		{
			for (map<UINT, CNode*>::iterator it1 = m_childList.begin(); /*it1 != m_childList.end()*/; it1++)
			{
				if (it1 == m_childList.end())
				{
					((CPlayer*)(*it).second)->setAct(IDLE);
					break;
				}
				if ((*it1).second->getType() == ENEMY && ((CEnemy*)(*it1).second)->getAct() == STUN)
				{
					if (/*((*it1).second->getmapPos() - (*it).second->getmapPos()).length() <= 5*/RectCollision(((CPlayer*)(*it).second)->getRect(), ((CEnemy*)(*it1).second)->getRect()))
					{
						((CPlayer*)(*it).second)->excuate(((CEnemy*)(*it1).second));
						break;
					}

				}
				
					
					
				
			}
		}
		if (((CPlayer*)(*it).second)->getAct() == MEELE)
		{
			for (map<UINT, CNode*>::iterator it1 = m_childList.begin(); it1 != m_childList.end(); it1++)
			{
				if ((*it1).second->getType() == ENEMY && ((CEnemy*)(*it1).second)->getAct() != STUN && ((CEnemy*)(*it1).second)->isAlive())
				{
					if (RectCollision(((CPlayer*)(*it).second)->getRect(), ((CEnemy*)(*it1).second)->getRect()))
					{
						((CEnemy*)(*it1).second)->hit(((CSprite*)(*it).second)->getDir(), ((CPlayer*)(*it).second)->getWeaponType());
					}
				}
			}
		}
		break;
	case ENEMY:
		/*if (m_collision[(int)pos.y][(int)pos.x].con)
			(*it).second->setmapPos((*it).second->getPrePos());*/
		if ((*it).second->getId() == 1)
		{
			GetLastError();
		}
		if (((CEnemy*)(*it).second)->getWeapomStatus() == HAND && ((CEnemy*)(*it).second)->getAct() != STUN&& ((CEnemy*)(*it).second)->isAlive()&&((CEnemy*)(*it).second)->getAct() !=BEEXCUATE)
		{
			for (map<UINT, CNode*>::iterator it1 = m_childList.begin(); it1 != m_childList.end(); it1++)
			{

				if ((*it1).second->getType() == WEAPON)
				{

					if (((CWeapon*)(*it1).second)->isvisible() && RectCollision(((CSprite*)(*it).second)->getRect(), ((CSprite*)(*it1).second)->getRect()))
					{
						((CEnemy*)(*it).second)->PickWeapon(((CWeapon*)(*it1).second));
						break;
					}

				}
			}
		}
		if (((*it).second->getmapPos() - m_player->getmapPos()).length() < 160&& ((CEnemy*)(*it).second)->getWeapomStatus()!=HAND&& ((CEnemy*)(*it).second)->getAct()!=SHOOT&&m_player->isAlive())

		{
			
				{
					((CEnemy*)(*it).second)->atk(m_player->getmapPos());

				}
			}
			
			((CSprite*)(*it).second)->updateboundbox();
			break;
		case WEAPON:
			if (((CWeapon*)(*it).second)->isvisible())
			{
				if (m_collision[(int)pos.y][(int)pos.x].con)
				{
					(*it).second->setmapPos((*it).second->getPrePos());
					((CWeapon*)(*it).second)->setAct(IDLE);
				}
				((CSprite*)(*it).second)->updateboundbox();
				if (((CWeapon*)(*it).second)->getAct() == BETHROW)
				{
					for (map<UINT, CNode*>::iterator it1 = m_childList.begin(); it1 != m_childList.end(); it1++)
					{
						if ((*it1).second->getType() == ENEMY&& ((CSprite*)(*it1).second)->isAlive()&&((CEnemy*)(*it1).second)->getAct()!=STUN)
						{
							if (RectCollision((((CSprite*)(*it).second)->getRect()), (((CSprite*)(*it1).second)->getRect())))
							{
								
								//((CEnemy*)(*it1).second)->stun(VECTOR3(((CWeapon*)(*it).second)->getMoveDir().x, -((CWeapon*)(*it).second)->getMoveDir().y, 0));
								((CEnemy*)(*it1).second)->hit(VECTOR3(((CWeapon*)(*it).second)->getMoveDir().x, -((CWeapon*)(*it).second)->getMoveDir().y, 0), HAND);
								((CWeapon*)(*it).second)->setAct(IDLE);
								CAudioManager::getInstance()->channelPlay(_T("sndWeaponHit"), 0);
								
							}
						}
					}
				}
					
			}
			break;
		case BULLET:
			if (((CBullet*)(*it).second)->visible())
			{
				((CBullet*)(*it).second)->updateboundbox();
				for (map<UINT, CNode*>::iterator it1 = m_childList.begin(); it1 != m_childList.end(); it1++)
				{
				
					if (((CSprite*)(*it1).second)->isAlive())
					{
						if ((((CBullet*)(*it).second)->getBulletType() == PLAYERBULLET && (*it1).second->getType() == ENEMY)  )
						{
							targetpos = (*it1).second->getmapPos();
							targetpos.x /= colwidth;
							targetpos.y /= rowheight;
							if (RectCollision((((CSprite*)(*it).second)->getRect()), (((CSprite*)(*it1).second)->getRect())))
							{
								((CBullet*)(*it).second)->diactivate();
								((CEnemy*)(*it1).second)->hit(((CSprite*)(*it).second)->getDir(),((CBullet*)(*it).second)->getWeaponType());
								break;
							}
						}
						if ((((CBullet*)(*it).second)->getBulletType() == ENEMYBULLET && (*it1).second->getType() == PLAYER))
						{
							((CPlayer*)(*it1).second)->hit(((CBullet*)(*it).second)->getDir(), ((CBullet*)(*it).second)->getWeaponType());
						}
						
					}
					
					
				
				
				}
				if (m_collision[(int)pos.y][(int)pos.x].con)
				{
					((CBullet*)(*it).second)->diactivate();

				}
			}
		
			break;
		default:
			break;
		}



	}
	

	showRect.left = (int)(m_CameraPos.x) - 8 *colwidth;
	showRect.bottom = (int)(m_CameraPos.y)  + 6 * rowheight;
	showRect.right = (int)(m_CameraPos.x)  + 8 * colwidth;
	showRect.top = (int)(m_CameraPos.y)  - 6* rowheight;
	if (showRect.left < 0)
		showRect.left = 0;
	if (showRect.top < 0)
		showRect.top = 0;
	if (showRect.right >= col*colwidth)
		showRect.right = col*colwidth;
	if (showRect.bottom >= row*rowheight)
		showRect.bottom = row*rowheight;
}

void CLevel::setPlayerPos(float x, float y, float z)
{
	m_CameraPos = VECTOR3(x, y, z);
}

void CLevel::addPlayer(CPlayer * player)
{
	
	m_player = player;
	AddChild(player);
	player->setCurLevel(this);
	m_CameraPos = player->getmapPos();
	


	if (m_player->getWeaponType() != HAND)
	{
		AddChild(m_player->getWeapon());
	}
}

void CLevel::resetplayer()
{
	//if (m_player->getcurlevel() != this)
	{
		TiXmlDocument* doc = new TiXmlDocument(info.c_str());
		doc->LoadFile();
		TiXmlElement* root = doc->FirstChildElement();
		for (TiXmlElement* ele = root->FirstChildElement(); ele != NULL; ele = ele->NextSiblingElement())
		{
			if (atoi(ele->Attribute("type")) == 4)
			{
				float posX = atoi(ele->Attribute("posX"));
				float posY = atoi(ele->Attribute("posY"));
				int width = atoi(ele->Attribute("width"));
				int height = atoi(ele->Attribute("height"));
#ifdef _UNICODE
				string temp = ele->Attribute("name");
				TSTRING name = CU_A2U(temp);
				name.pop_back();
#else
				TSTRING name = ele->Attribute("name");
#endif // _UNICODE
				int id = atoi(ele->Attribute("id"));
				WEAPONSTATUS wstatus = (WEAPONSTATUS)(atoi(ele->Attribute("weapon")));
				m_player->init(posX, posY, 0, width, height, name, id, wstatus);
				if (m_player->getWeaponType() != HAND)
				{
					if (m_childList[m_player->getId() - 1] != NULL)
					{
						((CWeapon*)m_childList[m_player->getId() - 1])->init(wstatus, 5, false, m_player->getmapPos(), m_player->getId() - 1);
						m_player->pickWeapon((CWeapon*)m_childList[m_player->getId() - 1]);
					}
					
					else
					{
						m_childList[m_player->getId() - 1] = new CWeapon;
						((CWeapon*)m_childList[m_player->getId() - 1])->init(wstatus, 5, false, m_player->getmapPos(), m_player->getId() - 1);
						m_player->pickWeapon((CWeapon*)m_childList[m_player->getId() - 1]);
					}
				}
				
				break;
			}
		}
	}
}

void CLevel::shoot(BULLETTYPE type, VECTOR3 pos, VECTOR3 dir, WEAPONSTATUS wstatus)
{
	VECTOR3 temp = pos;
	VECTOR3 offset;
	float scaleX = (float)(showRect.right - showRect.left) / (screen.right - screen.left);
	float scaleY = (float)(showRect.bottom - showRect.top) / (screen.bottom - screen.top);
	offset = pos - m_CameraPos;
	offset.x = offset.x / scaleX;
	offset.y = -offset.y / scaleY;
	for (map<UINT, CNode*>::iterator it = m_childList.begin(); it != m_childList.end(); it++)
	{
		if ((*it).second->getType() == BULLET)
		{
			if (!((CBullet*)((*it).second))->visible())
			{
				((CBullet*)((*it).second))->activate(type, pos,VECTOR3(400,300,0)+offset ,dir,wstatus);
				break;
			}
		}
	}
}

void CLevel::shoot(BULLETTYPE type, VECTOR3 mappos, VECTOR3 pos, VECTOR3 dir, WEAPONSTATUS wstatus)
{
	
	for (map<UINT, CNode*>::iterator it = m_childList.begin(); it != m_childList.end(); it++)
	{
		if ((*it).second->getType() == BULLET)
		{
			if (!((CBullet*)((*it).second))->visible())
			{
				((CBullet*)((*it).second))->activate(type, mappos, pos, dir,wstatus);
				break;
			}
		}
	}
}


void CLevel::enemydie()
{
	ene_num--; 
}

CLevel::~CLevel()
{
}
