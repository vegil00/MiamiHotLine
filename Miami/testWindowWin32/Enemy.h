#pragma once
#include"Sprite.h"
#include"Weapon.h"
#include"Level.h"
//enum ACTSTATUS { IDLE = 0, PATROL = 1,SEARCH=2 };

class CWeapon;
class CLevel;
class CEnemy:public CSprite
{
protected:
	int m_action;
	list<sNode*> route;
	vector<VECTOR3> target;
	VECTOR3 cur_target;
	int targetindex;
	VECTOR3 m_moveDir;
	CLevel* cur_level;
	int m_actStatus;
	int row;
	int col;
	int pre_time;
	float changeTime;
	int stun_time;
	WEAPONSTATUS weaponStatus;
	int bullet;
	CWeapon* m_weapon;
	
public:
	CEnemy();
	void init(TSTRING name, VECTOR3 mappos, int width, int height,ACTSTATUS act,CLevel* level,int id,WEAPONSTATUS w);
	void addtarget(VECTOR3 pos);
	void update();
	void move();
	void Render();
	void hit(VECTOR3 dir,WEAPONSTATUS wstatus);
	void beExcuate(WEAPONSTATUS w);
	void aniUpdate();
	void rotate(VECTOR3 rotate, float degree);
	void rotate(VECTOR3 dir);
	void stun(VECTOR3 dir);
	ACTSTATUS getAct() { return (ACTSTATUS)m_actStatus; }
	WEAPONSTATUS getWeapomStatus() { return weaponStatus; }
	void atk(VECTOR3 pos);
	void PickWeapon(CWeapon* w);
	void getRoute();
	~CEnemy();
};

