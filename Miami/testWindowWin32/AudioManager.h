#pragma once
#include"Singleton.h"
#include"Audio4Bass.h"
class CAudioManager:public CSingleton<CAudioManager>
{private:
	map<string, int>m_SoundList;
public:
	void init();
	bool loadFileFromXml(TSTRING path);
	bool channelPlay(TSTRING name, bool restart);
	BOOL channelStop(TSTRING name);
	BOOL channelPause(TSTRING name);
	BOOL SetVolume(float volume);
	QWORD GetChannelLength(TSTRING name, DWORD mode);
	QWORD GetChannelPosition(TSTRING name, DWORD mode);
	BOOL SetChannelPosition(TSTRING name, QWORD pos, DWORD mode);
	BOOL DeleteMusic(TSTRING name);
	void Release();
	int GetCurIndex();
	void SetCurIndex(unsigned int index);
	CAudioManager();
	~CAudioManager();
};

