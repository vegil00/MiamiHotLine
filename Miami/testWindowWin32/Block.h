#pragma once

class CBlock
{
private:
	VECTOR3 m_min;
	VECTOR3 m_max;
	VECTOR3 m_dir;
	VECTOR3 m_des;
	VECTOR3 m_pos;
	VECTOR3 m_nextPos;
	float m_speed;
	bool m_move;
	float m_dia;
public:
	CBlock();
	CBlock(VECTOR3 min, VECTOR3 max);
	void setspeed(float speed) { m_speed = speed; }
	void setroute(VECTOR3 des);
	void update();
	void arrive();
	void Render();
	~CBlock();
};

