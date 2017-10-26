#include "stdafx.h"
#include "AudioManager.h"


void CAudioManager::init()
{
	CAudio4Bass::getInstance()->Initialize();
}

bool CAudioManager::loadFileFromXml(TSTRING path)
{
#ifdef _UNICODE
	string xmlpath = CU_U2A(path);


#else
	string xmlpath = path;
#endif // _UNICODE
	TiXmlDocument* doc = new TiXmlDocument(xmlpath.c_str());
	doc->LoadFile();
	TiXmlElement* root = doc->FirstChildElement();
	for (TiXmlElement* ele = root->FirstChildElement(); ele != NULL; ele = ele->NextSiblingElement())
	{
		char* path = new char[50];
		strcpy(path, ele->Attribute("path"));
		int sample = atoi(ele->Attribute("sample"));
		string name = ele->Attribute("name");
		CAudio4Bass::getInstance()->LoadFile(path, sample);
		int id = m_SoundList.size();
		m_SoundList.insert(make_pair(name, id));
	}
	if (doc)
	{
		delete doc;
		doc = NULL;
		return 1;
	}
	return 0;

}
bool CAudioManager::channelPlay(TSTRING name, bool restart)
{
#ifdef _UNICODE
	string soundname = CU_U2A(name);
	soundname.pop_back();

#else
	string soundname = name;
#endif
	if (m_SoundList.find(soundname) != m_SoundList.end())
	{
		if (CAudio4Bass::getInstance()->ChannelPlay(m_SoundList[soundname], restart))
		{
			return 1;
		}
		else
		{
			return false;
		}
	}
	else
		return 0;
}

BOOL CAudioManager::channelStop(TSTRING name)
{
#ifdef _UNICODE
	string soundname = CU_U2A(name);
	soundname.pop_back();

#else
	string soundname = name;
#endif
	if (m_SoundList.find(soundname) != m_SoundList.end())
	{
		if (CAudio4Bass::getInstance()->ChannelStop(m_SoundList[soundname]))
		{
			return 1;
		}
		else
		{
			return false;
		}
	}
	else
		return 0;

}

BOOL CAudioManager::channelPause(TSTRING name)
{
#ifdef _UNICODE
	string soundname = CU_U2A(name);
	soundname.pop_back();

#else
	string soundname = name;
#endif
	if (m_SoundList.find(soundname) != m_SoundList.end())
	{
		if (CAudio4Bass::getInstance()->ChannelPause(m_SoundList[soundname]))
		{
			return 1;
		}
		else
		{
			return false;
		}
	}
	else
		return 0;
}

BOOL CAudioManager::SetVolume(float volume)
{
	return CAudio4Bass::getInstance()->SetVolume(volume);
}

QWORD CAudioManager::GetChannelLength(TSTRING name, DWORD mode)
{
#ifdef _UNICODE
	string soundname = CU_U2A(name);
	soundname.pop_back();

#else
	string soundname = name;
#endif
	return CAudio4Bass::getInstance()->GetChannelLength(m_SoundList[soundname], mode);
}

QWORD CAudioManager::GetChannelPosition(TSTRING name, DWORD mode)
{
#ifdef _UNICODE
	string soundname = CU_U2A(name);
	soundname.pop_back();

#else
	string soundname = name;
#endif
	return CAudio4Bass::getInstance()->GetChannelPosition(m_SoundList[soundname], mode);
}

BOOL CAudioManager::SetChannelPosition(TSTRING name, QWORD pos, DWORD mode)
{
#ifdef _UNICODE
	string soundname = CU_U2A(name);

	soundname.pop_back();
#else
	string soundname = name;
#endif
	return CAudio4Bass::getInstance()->SetChannelPosition(m_SoundList[soundname], pos, mode);
}

BOOL CAudioManager::DeleteMusic(TSTRING name)
{
#ifdef _UNICODE
	string soundname = CU_U2A(name);
	soundname.pop_back();

#else
	string soundname = name;
#endif
	return CAudio4Bass::getInstance()->DeleteMusic(m_SoundList[soundname]);
}

void CAudioManager::Release()
{
	CAudio4Bass::getInstance()->Release();
}

int CAudioManager::GetCurIndex()
{
	return CAudio4Bass::getInstance()->GetCurIndex();
}

void CAudioManager::SetCurIndex(unsigned int index)
{
	CAudio4Bass::getInstance()->SetCurIndex(index);
}

CAudioManager::CAudioManager()
{
}


CAudioManager::~CAudioManager()
{
}
