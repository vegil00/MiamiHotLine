#include "stdafx.h"
#include "SenceManager.h"


CSenceManager::CSenceManager()
{
	cur_sence = NULL;
}

void CSenceManager::init(TSTRING path, HWND hwnd, CPlayer* player)
{
	#ifdef _UNICODE
			string senceinfo = CU_U2A(path);
		#else
			string senceinfo = name;
		#endif // DEBUG
	TiXmlDocument* doc = new TiXmlDocument(senceinfo.c_str());
	doc->LoadFile();
	for (TiXmlElement* root = doc->FirstChildElement(); root != NULL; root = root->NextSiblingElement())
	{
		int type = atoi(root->Attribute("type"));
		if (type == 2)
		{
			CLevel* level = new CLevel;
			string map = root->Attribute("map");
			string config = root->Attribute("config");
			level->init(map, config, hwnd, player);
			m_sencelist.insert(make_pair(level->getId(), level));
		}
	}
}

//CSnece * CSenceManager::getSCence(TSTRING name)
//{
//#ifdef _UNICODE
//	string sencename = CU_U2A(name);
//#else
//	string sencename = name;
//#endif // DEBUG
//	if (m_sencelist.find(sencename) != m_sencelist.end())
//		return m_sencelist[sencename];
//	else
//	return nullptr;
//}

void CSenceManager::setSence(int id)
{
	if (m_sencelist.find(id) != m_sencelist.end())
	{
		if (cur_sence == NULL)
		{
			cur_sence = m_sencelist[id];
			((CLevel*)m_sencelist[id])->reset();
			((CLevel*)m_sencelist[id])->resetplayer();
		}
		else
		{
			if (cur_sence->getId() != id)
			{
				cur_sence = m_sencelist[id];
				((CLevel*)m_sencelist[id])->reset();
				((CLevel*)m_sencelist[id])->resetplayer();
			}
		}
		 
		
	}
}


void CSenceManager::reset()
{
	if (cur_sence != NULL)
	{
		((CLevel*)cur_sence)->reset();
		((CLevel*)cur_sence)->resetplayer();
	}
	
}

CSenceManager::~CSenceManager()
{
}
