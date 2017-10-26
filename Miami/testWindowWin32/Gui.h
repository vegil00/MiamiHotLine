#pragma once
#include"ResManager.h"
#include"Listener.h"
#include"GameManager.h"
enum CURSORMOVE{STOP=0,CURSORUP=1, CURSORDOWN=1<<1};
enum BUTTONSTATUS{NORMAL,MOUSEON,CLICK};
struct sButton
{
	Rect rect;
	VECTOR3 rotate;
	VECTOR3 scale;
	float degree;
	CSingleImg*  texture;
	BUTTONSTATUS status;
	int pressKey;
	int row;
	int col;

};
struct sCursor
{
	VECTOR3 pos;
	CStaticImg* texture = NULL;
	int id;
	int status=0;
};
class CGui:public CMouseListener,public CKeyListener
{private:
	map<int, CStaticImg*> m_BackGrounds;
	map<int,sButton*>m_Buttons;
	sCursor m_Cursor;
	map<int, CStaticImg*>::iterator m_BGiter;
	map<int, sButton*>::iterator m_BTiter;
	Rect m_Rect;


public:
	CGui();
	void OnKeyDown(sInputEvent inputevent);
	void OnKeyUp(sInputEvent inputevent);
	void OnMouseMove(sInputEvent inputevent);
	void OnMouseDown(sInputEvent inputevent);
	void addBackGround(int id, CStaticImg* texture) { m_BackGrounds.insert(make_pair(id, texture)); }
	void addButton(VECTOR3& pos, float width, float height, CSingleImg* tex, int key);
	void update();
	void setRect(VECTOR3 pos, float width, float height);
	void setKey(int id, int key);
	void Render();
	~CGui();
};

