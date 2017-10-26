#include"stdafx.h"
#include "Block.h"



CBlock::CBlock()
{
}

CBlock::CBlock(VECTOR3 min, VECTOR3 max)
{
	m_min = min;
	m_max = max;
	m_dir = VECTOR3(0, 0, 0);
	m_pos = 0.5*(m_min + m_max);
	m_dia = (m_pos - m_min).length();
	m_nextPos = m_pos;
}

void CBlock::setroute(VECTOR3 des)
{
	m_des = des;
	m_dir = (m_des - m_min - (m_max - m_min)*0.5).Normalize();
}

void CBlock::update()
{
	


	if (m_des.x<m_max.x&&m_des.y<m_max.y&&m_des.x>m_min.x&&m_des.y>m_min.y)
		m_dir = VECTOR3(0, 0, 0);
		m_min = m_min + m_speed*m_dir;
		m_max = m_max + m_speed*m_dir;
		m_pos = (m_min + m_max) / 2;
		m_nextPos = m_pos + m_dir*m_speed;

}

void CBlock::arrive()
{

}

//bool CBlock::touch(Line* line)
//{
//	
//	
//}
//
//void CBlock::hitline(Line*line)
//{
//	//VECTOR3 dir = VECTOR3(10, 99, 0).Normalize();
//	//Line a = Line(VECTOR3(50, 100, -250), VECTOR3(100, 0, -250));
//	//VECTOR3 test = 2 * a.normalDir.dot(dir)*a.normalDir;
//	//dir = dir - test;
//	VECTOR3 temp=2 * line->normalDir.dot(m_dir)*line->normalDir;
//	m_dir = m_dir - temp;
//	m_dir = m_dir.Normalize();
//}

void CBlock::Render()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(m_min.x, m_min.y, m_min.z);
	glVertex3f(m_max.x, m_min.y, m_max.z);
	glVertex3f(m_max.x,m_max.y,m_max.z);
	glVertex3f(m_min.x, m_max.y, m_min.z);
	glEnd();
	glPopMatrix();
}


CBlock::~CBlock()
{
}
