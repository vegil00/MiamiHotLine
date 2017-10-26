#pragma once
#include"Listener.h"
#include"Singleton.h"
class CInputManager:public CSingleton<CInputManager>
{
private:
	map<string, CMouseListener*> m_MouseListeners;
	map<string, CKeyListener*> m_KeyListeners;
	map<string, CMouseListener*>::iterator m_MouseIter;
	map<string, CKeyListener*>::iterator m_KeyIter;
public:
	CInputManager();
	~CInputManager();
	void addMouseListener(TSTRING name, CMouseListener* listener);
	void addKeyListener(TSTRING name, CKeyListener* listener);
	void removeMouseListener(TSTRING name);
	void removeKeyListener(TSTRING name);
	void messageProc(HWND hwnd,UINT msg, WPARAM wParam, LPARAM lParam);
	CMouseListener* getMouseListener(TSTRING name);
	CKeyListener* getKeyListener(TSTRING name);
};

