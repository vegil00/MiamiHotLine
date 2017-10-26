#pragma once
#include"ResManager.h"
#include"Sprite.h"
enum BULLETTYPE { PLAYERBULLET = 0,ENEMYBULLET=1 };
class CBullet:public CSprite
{private:
	int m_atk;
	
	CSingleImg* m_texture;
	bool isVisible;
	bool isTouch;
	int cur_image;
	int touch_col;

	
	string m_name;
	BULLETTYPE m_bulletType;
	WEAPONSTATUS m_weaponType;
	int preChange;



public:
	CBullet();
	void init(int atk,float speed,TSTRING name,int coltouch,int width,int height,BULLETTYPE type);
	void touch();
	void activate(VECTOR3 pos,VECTOR3 dir, WEAPONSTATUS wstatus);
	void activate(VECTOR3 pos, VECTOR3 dir,VECTOR3 mappos, WEAPONSTATUS wstatus);
	void activate(BULLETTYPE type, VECTOR3 mappos, VECTOR3 pos, VECTOR3 dir, WEAPONSTATUS wstatus);
	void diactivate() { isVisible = false; }
	void move();
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	VECTOR3 getPos() { return m_pos; }
	string getName() { return m_name; }
	bool visible() { return isVisible; }
	void Render();
	void update();
	BULLETTYPE getBulletType() { return m_bulletType; }
	WEAPONSTATUS getWeaponType() { return m_weaponType; }
	~CBullet();
};

