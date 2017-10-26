#pragma once
enum nodeType{PLAYER,ENEMY,BULLET,WEAPON};
class CNode
{
protected:
	VECTOR3 m_pos;//ÆÁÄ»×ø±ê
	VECTOR3 m_rotate;
	VECTOR3 m_scale;
	UINT m_id;
	float m_RotateDegree;
	map<UINT,CNode*> m_childList;
	CNode* m_father;
	TSTRING m_name;
	int m_type;
	VECTOR3 m_mapPos;
	VECTOR3 m_prePos;
	VECTOR3 m_rect[4];
	int m_width;
	int m_height;

public:
	CNode();
	virtual void update(){}
	virtual void Render(){}
	nodeType getType() { return (nodeType)m_type; }
	void AddChild(CNode* node);
	void RemoveChild(CNode* node);
	void RemoveAllChild();
	void setPos(VECTOR3 pos) { m_pos = pos; }
	VECTOR3 getmapPos() { return m_mapPos; }
	void setmapPos(VECTOR3 pos) { m_mapPos = pos; }
	VECTOR3 getPrePos() { return m_prePos; }
	VECTOR3 getPos() { return m_pos; }
	void setId(int id) { m_id = id; }
	UINT getId() { return m_id; }
	~CNode();
};

