#pragma once
#include"Snece.h"
#include"Bullet.h"
#include"GameManager.h"
#include"Player.h"
#include "Icon.h"
class CPlayer;
class CLevel:public CSnece
{private:
	sNode** m_collision;
	VECTOR3 m_CameraPos;
	RECT showRect;
	int row;
	int col;
	int rowheight;
	int colwidth;
	CPlayer* m_player;
	CIcon* shootgun ;
	CIcon* m16;
	CIcon* leave_area;
	CIcon* blood;
	CIcon* go;
	CIcon* retry;
	VECTOR3 leave;
	int ene_num;
	string info;
	int next;
public:
	CLevel();
	void init(TSTRING mappath,  TSTRING levelconfig,HWND hwnd,CPlayer* player);
	void init(string mappath, string levelconfig, HWND hwnd, CPlayer* player);
	void reset();
	void Render();
	void update();
	void setPlayerPos(float x, float y, float z);
	void setPlayerPos(VECTOR3 pos) { m_CameraPos = pos; }
	void addPlayer(CPlayer* player);
	void resetplayer();
	void shoot(BULLETTYPE type, VECTOR3 pos, VECTOR3 dir, WEAPONSTATUS wstatus);
	void shoot(BULLETTYPE type, VECTOR3 mappos,VECTOR3 pos, VECTOR3 dir,WEAPONSTATUS wstatus);
	int getrow() { return row; }
	int getcol() { return col; }
	int getrowheight() { return rowheight;}
	int getcolwidth() { return colwidth; }
	sNode** getmapInfo() { return m_collision; }
	bool getcollision(int x, int y) { return m_collision[y][x].con; }
	void enemydie();
	//VECTOR3 getPlayerPos() { return m_player->getmapPos(); }
	
	~CLevel();
};

