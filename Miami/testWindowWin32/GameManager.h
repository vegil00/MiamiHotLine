#pragma once
#include"Singleton.h"
#include"Block.h"
#include "Ball.h"
#include"Res.h"
#include"ResManager.h"
#include"Player.h"
#include"InputManager.h"
#include"BulletManager.h"
#include"Gui.h"
#include"Level.h"
#include"Enemy.h"
#include"Weapon.h"
#include"SenceManager.h"
class CGui;
class CPlayer;
class CLevel;
class CWeapon;
enum GAMESTATUS{TITLE=1,LEVELSELECT=2,GAME=4,GAMEMENU=3};
class CGameManager:public CSingleton<CGameManager>
{private:
	HWND m_hWnd;
	HDC m_hDC;
	HGLRC m_hRC;
	MSG m_msg;
	//CBall block1;
	//Line field[7];
	//CTexture texture;
	CPlayer* m_player;
	GAMESTATUS m_Status;
	CGui* title;
	CGui* levelselect;
	CGui* gamemenu;
	bool changeStatus;
	CLevel* level1;

	
public:
	void init(HINSTANCE hInstance,WNDPROC winproc,int ncmdshow);
	void changestatus() { changeStatus = 1; }
	void initGL();
	void mainLoop();
	void Render();
	void update(int time);
	void MessageProc(UINT msg, WPARAM wParam, LPARAM lParam);
	void clearupRC();
	void setStatus(int value);
	CGameManager();
	~CGameManager();
};

