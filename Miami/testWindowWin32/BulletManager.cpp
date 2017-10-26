#include "stdafx.h"
#include "BulletManager.h"


CBulletManager::CBulletManager()
{
}

void CBulletManager::init(TSTRING binfo, TSTRING bpool)
{
	TiXmlDocument* doc = new TiXmlDocument;
	doc = readXml(binfo);
	doc->LoadFile();
	TiXmlElement* root = doc->FirstChildElement();
	BulletInfo* info = new BulletInfo;
	for (TiXmlElement* ele = root; ele != nullptr; ele = ele->NextSiblingElement())
	{
		int atk = atoi(ele->Attribute("ATK"));
		float speed = atof(ele->Attribute("SPEED"));
#ifdef _UNICODE
		string temp = ele->Attribute("NAME");
		wstring name =CU_A2U(temp);
#else
		string name = ele->Attribute("NAME");
#endif // _UNICODE

		
		int width =atoi( ele->Attribute("WIDTH"));
		int height = atoi(ele->Attribute("HEIGHT"));
		int coltouch = atoi(ele->Attribute("TOUCHCOL"));
		BULLETTYPE type = (BULLETTYPE)atoi(ele->Attribute("TYPE"));
		
		info->atk = atk;
		info->speed = speed;
		info->name = name;
		info->touchcol = coltouch;
		info->width = width;
		info->height = height;
		info->type = type;
		
#ifdef _UNICODE
		bullet_info.insert(make_pair(temp, info));
#else
		bullet_info.insert(make_pair(name, info));
#endif // _UNICODE
		
		
		
	}
	doc = readXml(bpool);
	doc->LoadFile();
	root = doc->FirstChildElement();
	
	for (TiXmlElement* ele = root; ele != NULL; ele = ele->NextSiblingElement())
	{
		string name = ele->Attribute("name");
		
		if(bullet_info.find(name)!=bullet_info.end())
		info = bullet_info[name];
		int num = atoi(ele->Attribute("num"));
		for (int i = 0; i < num; i++)
		{
			CBullet* bullet = new CBullet;
			bullet->init(info->atk, info->speed,info->name,info->touchcol,info->width,info->height,info->type);
			bullet_pool.push_back(bullet);
		}
	}
}

void CBulletManager::Shoot(TSTRING name, VECTOR3 pos, VECTOR3 dir)
{
#ifdef _UNICODE
	string bulletname = CU_U2A(name);
	for (int i = 0; i < bullet_pool.size(); i++)
	{
		if (bulletname == bullet_pool[i]->getName() && !(bullet_pool[i]->visible()))
		{
			//bullet_pool[i]->activate(pos, dir);
			break;
		}
	}
#else
	for (int i = 0; i < bullet_pool.size(); i++)
	{
		if (name == bullet_pool[i]->getName() && !(bullet_pool[i]->visible()))
		{
			//bullet_pool[i]->activate(pos, dir);
			break;
		}
	}
#endif // _UNICODE

	
}

void CBulletManager::Render()
{
	for (int i = 0; i < bullet_pool.size(); i++)
	{
		bullet_pool[i]->Render();
	}
}

void CBulletManager::update()
{
	if (!bullet_pool.empty())
	{
		for (int i = 0; i < bullet_pool.size(); i++)
		{
			bullet_pool[i]->update();
			if (bullet_pool[i]->visible())
			{
				VECTOR3 pos = bullet_pool[i]->getPos();
				if (pos.x < 0 || pos.x>800 || pos.y < 0 || pos.y>600)
				{
					bullet_pool[i]->diactivate();
				}
			}
			
		}
	}
}

BulletInfo * CBulletManager::getBulletInfo(TSTRING name)
{
#ifdef _UNICODE
	string bulletname = CU_U2A(name);
#else
	string bulletname = name;
#endif // _UNICODE
	if (bullet_info.find(bulletname.c_str()) != bullet_info.end())
		return bullet_info[bulletname.c_str()];
	else
		return NULL;
}


CBulletManager::~CBulletManager()
{
}
