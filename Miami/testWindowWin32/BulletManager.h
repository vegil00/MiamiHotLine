#pragma once
#include"Singleton.h"
#include"Bullet.h"
//#include"Snece.h"
//class CSnece;
struct BulletInfo {
	int atk;
	int speed;
	int width;
	int height;
	TSTRING name;
	int touchcol;
	BULLETTYPE type;

};
class CBulletManager:public CSingleton<CBulletManager>
{private:
	map<string, BulletInfo*> bullet_info;
	vector<CBullet*> bullet_pool;
public:
	CBulletManager();
	void init(TSTRING binfo,TSTRING bpool);
	void Shoot(TSTRING name, VECTOR3 pos, VECTOR3 dir);
	void Render();
	void update();
	BulletInfo* getBulletInfo(TSTRING name);
	vector<CBullet*>* getPool() { return &bullet_pool; }
	~CBulletManager();
};

