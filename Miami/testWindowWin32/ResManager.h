#pragma once
#include"FreeImage.h"
#include"Singleton.h"
#include"StaticImg.h"
#include"SingleImg.h"
class CResManager:public CSingleton<CResManager>
{private:
	map<string, CRes*> m_ResList;
public:
	CResManager();
	CRes* getRes(TSTRING name);
	bool LoadRes(string path, string name, imageType type, int row, int col);
	bool LoadRes(string path, string name, imageType type);
	bool LoadAllRes(TSTRING path);
	~CResManager();
};

