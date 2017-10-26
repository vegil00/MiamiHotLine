#pragma once
#include"ResManager.h"
#include"BulletManager.h"
#include"Listener.h"
#include"Sprite.h"
#include"GameManager.h"
#include"Level.h"
#include"Weapon.h"
#include"Enemy.h"
class CLevel;
class CEnemy;
enum MOVESTATUS { STILL = 0, UP = 1, DOWN = 1 << 1,LEFT=1<<2,RIGHT=1<<3 };
class CPlayer:public CKeyListener,public CMouseListener,public CSprite
{
private:

	
	VECTOR3 m_moveDir;
	int	m_moveStatus;
	int m_preMoveStatus;
	bool pickweapon;
	int row;
	int col;
	int pre_time;
	float changeTime;
	int bullet;
	CLevel* cur_level;
	WEAPONSTATUS weaponStatus;
	ACTSTATUS m_actStatus;
	CWeapon* m_weapon;
	bool punch_LR;
	bool detect;
	bool retry;
public:
	CPlayer();
	void init(float x, float y, float z,int width,int height,TSTRING name,int id,WEAPONSTATUS w);
	void rotate(VECTOR3 rotate, float degree);
	void rotate(VECTOR3 dir);
	void aniUpdate();
	void update();
	bool pick() { return pickweapon; }
	void picked() { pickweapon = 0; }
	void pickWeapon(CWeapon* w);
	void throwWeapon();
	void move();
	void MessageProc(UINT msg, WPARAM wParam, LPARAM lParam);
	void Render();
	void OnKeyDown(sInputEvent keyevent);
	void OnKeyUp(sInputEvent keyevent);
	void OnMouseMove(sInputEvent mouseevent);
	void OnMouseDown(sInputEvent mouseevent);
	void OnMouseUp(sInputEvent mouseevent);
	void setCurLevel(CLevel* level) { cur_level = level; }
	void setAct(ACTSTATUS status) { m_actStatus = status; }
	void atk();
	void excuate(CEnemy* ene);
	void hit(VECTOR3 dir, WEAPONSTATUS wstatus);
	ACTSTATUS getAct() { return m_actStatus; }
	WEAPONSTATUS getWeaponType() { return weaponStatus; }
	CWeapon* getWeapon() { return m_weapon; }
	int getbullet() { return bullet; }
	float getspeed() { return m_speed; }
	bool isdetect() { return detect; }
	bool isretry() { return retry; }
	CLevel* getcurlevel() { return cur_level; }
	
	~CPlayer();
};

