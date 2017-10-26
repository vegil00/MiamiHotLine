#pragma once
struct Line
{
	VECTOR3 start;
	VECTOR3 end;
	VECTOR3 normalLine;
	VECTOR3 normalDir;

	Line()
	{
		end = VECTOR3(0, 0, 0);
		start = VECTOR3(0, 0, 0);
	}
	Line(VECTOR3 s, VECTOR3 e)
	{
		start = s;
		end = e;
		VECTOR3 line = e - s;
		line = line.Normalize();
		normalLine = start + start.reverse().dot(line)*line;
		normalLine = VECTOR3(normalLine.x, normalLine.y, 0);
		normalDir = normalLine.Normalize();
	}
	void Render()
	{
		glPushMatrix();
		glBegin(GL_LINES);
		glVertex3f(start.x, start.y, start.z);
		glVertex3f(end.x, end.y, end.z);
		glEnd();
		glPopMatrix();
	}
};

class CBall
{
private:
	VECTOR3 m_pos;
	float m_radius;
	
	VECTOR3 m_dir;
	

	VECTOR3 m_nextPos;
	float m_speed;
	
public:
	CBall();
	CBall(VECTOR3 pos, float radius);
	void setspeed(float speed) { m_speed = speed; }
	void setroute(VECTOR3 des);
	void update();
	
	bool touch(Line* line);
	void hitline(Line* line);
	void Render();
	~CBall();
};

