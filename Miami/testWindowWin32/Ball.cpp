#include"stdafx.h"
#include "Ball.h"



CBall::CBall()
{
}

CBall::CBall(VECTOR3 pos, float radius)
{
	m_pos = pos;
	m_radius = radius;
	m_dir = VECTOR3(0, 0, 0);
	m_nextPos = m_pos;
}

void CBall::setroute(VECTOR3 des)
{
	
	m_dir = (des -m_pos).Normalize();
}

void CBall::update()
{
	
	m_pos = m_pos + m_speed*m_dir;
	m_nextPos = m_pos + m_dir*m_speed;
}

bool CBall::touch(Line * line)
{
	float len = m_pos.dot(line->normalDir);
	float dis = line->normalLine.length() - len;
	float nextlen = m_nextPos.dot(line->normalDir);
	float nextdis = line->normalLine.length() - nextlen;

	if (nextdis < 7)
	{
		if (dis < m_radius&&nextdis <= m_radius)
		{
			GetLastError();
		}
		GetLastError();
	}
	VECTOR3 temp = m_pos + line->normalDir*dis;
	VECTOR3 test = (temp - line->start).Normalize();
	float a = (temp - line->start).length();
	float b = (line->end - temp).length();
	float c = (line->end - line->start).length();
	int ste = (temp - line->start).length() + (line->end - temp).length() - (line->end - line->start).length();
	if (ste <= 1 && ste >= -1)
	{
		if (dis > 0)
		{
			if ((dis >= m_radius&&nextdis <= m_radius))
				return true;
			else if (dis < m_radius&&nextdis <= m_radius)
			{
				GetLastError();
			}
			else return 0;
		}
		else
		{
			if (dis < -m_radius&&nextdis > -m_radius)
				return true;
			else
				return 0;
		}

	}
	else
		return false;
	
}

void CBall::hitline(Line * line)
{
	VECTOR3 temp = 2 * line->normalDir.dot(m_dir)*(line->normalDir);
	m_dir = m_dir - temp;
	m_dir = m_dir.Normalize();
}

void CBall::Render()
{
	glPushMatrix();
	glBegin(GL_POINTS);
	for (int i = 0; i < 100; i++)
	{
		glVertex3f(m_pos.x+m_radius*cos(2 * 3.14f / 100 * i), m_pos.y+m_radius*sin(2 * 3.14f / 100 * i),m_pos.z);
	}
	
	glEnd();
	glPopMatrix();
}



CBall::~CBall()
{
}
