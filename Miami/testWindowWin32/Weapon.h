#pragma once
#include"Sprite.h"
class CWeapon:public CSprite
{
protected:
	WEAPONSTATUS m_weaponType;
	ACTSTATUS m_status;
	VECTOR3 m_moveDir;
	bool isVisible;
	int m_bullet;
	float shoot_time;
	int pre_shoot;
	float throwDistance;
	
public:
	CWeapon();
	void init(WEAPONSTATUS weapon,float speed,bool Visible,VECTOR3 mapPos,int id);
	void fall(VECTOR3 mappos);
	void update();
	void Render();
	void move();
	bool shoot();
	void beThrow(VECTOR3 dir,VECTOR3 pos, VECTOR3 screenpos);
	void setAct(ACTSTATUS status);
	ACTSTATUS getAct() { return m_status; }
	void setVisible(bool visible) { isVisible = visible; }
	bool isvisible() { return isVisible; }
	WEAPONSTATUS getWeaponType() { return m_weaponType; }
	int getBulletNum() { return m_bullet; }
	VECTOR3 getMoveDir(){ return m_moveDir; }
	~CWeapon();
};

