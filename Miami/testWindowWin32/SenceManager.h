#pragma once
#include"Singleton.h"
#include"Snece.h"
#include"Level.h"

class CSenceManager:public CSingleton<CSenceManager>
{private:
	map<int, CSnece*> m_sencelist;
	CSnece* cur_sence;
public:
	CSenceManager();
	void init(TSTRING path,HWND hwnd,CPlayer* player);
	void setSence(int id);
	void Render() { cur_sence->Render(); }
	void update() { cur_sence->update(); }
	void reset();
	~CSenceManager();
};

