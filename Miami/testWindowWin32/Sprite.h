#pragma once
#include"Node.h"
#include"ResManager.h"
enum ACTSTATUS{IDLE=0, PATROL = 1, SEARCH = 2,MEELE = 3,BETHROW=4,STUN=5,EXCUATE=6,SHOOT=7,BEEXCUATE=9,EXCUATING=8};
enum WEAPONSTATUS{HAND=0,KATANA=1,STICK=2,M16=3,SHOOTGUN=4};
class CSprite:public CNode
{protected:
	VECTOR3 m_dir;
	float m_speed;
	bool alive;
	CSingleImg* m_texture;
public:
	CSprite();
	void die() { alive = 0; }
	virtual void move(){}
	virtual void hitByBullet(VECTOR3 dir){}
	virtual void aniUpdate() {}
	virtual void updateboundbox();
	VECTOR3* getRect() { return &m_rect[0]; }
	VECTOR3 getDir() { return m_dir; }
	bool isAlive() { return alive; }
	virtual void setAct(ACTSTATUS status){}
	virtual void rotate(VECTOR3 rotate, float degree);
	virtual void rotate(VECTOR3 dir);
	virtual ACTSTATUS getAct() { return (ACTSTATUS)0; }
	
	
	~CSprite();
};

