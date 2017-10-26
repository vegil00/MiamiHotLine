#pragma once
#include"Node.h"
#include"ResManager.h"
class CIcon:public CNode
{
private:
	CStaticImg* m_texture;
	float width;
	float height;
	

public:
	CIcon();
	void init(VECTOR3 pos,TSTRING name);
	void Render();
	void rotate(VECTOR3 dir);
	
	~CIcon();
};

