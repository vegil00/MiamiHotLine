#include "stdafx.h"
#include "Gui.h"


CGui::CGui()
{
	
	m_Cursor.id = 0;
}

void CGui::OnKeyDown(sInputEvent inputevent)
{
	switch (inputevent.eventkind.keyEvent.key)
	{case 'W':
		m_Cursor.status = CURSORUP;
		break;
	case'S':
		m_Cursor.status = CURSORDOWN;
		break;
	case'J':
		m_Buttons[m_Cursor.id]->status = CLICK;

		break;
	default:break;
	}
}

void CGui::OnKeyUp(sInputEvent inputevent)
{
	switch (inputevent.eventkind.keyEvent.key)
	{case 'W':
	case'S':
		m_Cursor.status = STOP;
		break;
	default:
		break;
	}
}

void CGui::OnMouseMove(sInputEvent inputevent)
{
	int x = inputevent.eventkind.mouseEvent.x;
	int y = inputevent.eventkind.mouseEvent.y;
	for (m_BTiter = m_Buttons.begin(); m_BTiter != m_Buttons.end(); m_BTiter++)
	{
		Rect temp = m_BTiter->second->rect;
		int left = temp.pos.x - temp.width / 2;
		int right= temp.pos.x + temp.width / 2;
		int buttom = temp.pos.y - temp.height / 2;
		int top= temp.pos.y + temp.height / 2;
		if (x > left&&x<right&&y>buttom&&y < top)
		{
			m_BTiter->second->status = MOUSEON;
			m_Cursor.id = m_BTiter->first;
			
		}
		else
		{
			m_BTiter->second->status = NORMAL;
		}
	}
}

void CGui::OnMouseDown(sInputEvent inputevent)
{
	int x = inputevent.eventkind.mouseEvent.x;
	int y = inputevent.eventkind.mouseEvent.y;
	for (m_BTiter = m_Buttons.begin(); m_BTiter != m_Buttons.end(); m_BTiter++)
	{
		Rect temp = m_BTiter->second->rect;
		int left = temp.pos.x - temp.width / 2;
		int right = temp.pos.x + temp.width / 2;
		int buttom = temp.pos.y - temp.height / 2;
		int top = temp.pos.y + temp.height / 2;
		if (x > left&&x<right&&y>buttom&&y < top)
		{
			m_BTiter->second->status = CLICK;

		}
		else
		{
			m_BTiter->second->status = NORMAL;
		}
	}
}

void CGui::addButton(VECTOR3 & pos, float width, float height, CSingleImg * tex, int key)
{
	Rect temp = Rect(pos, width, height);
	sButton* button = new sButton;
	button->rect = temp;
	button->status = NORMAL;
	button->pressKey = key;
	button->texture = tex;
	button->degree = 0;
	button->rotate = VECTOR3(0, 0, -1.0f);
	button->scale = VECTOR3(1, 1, 1);
	button->scale.x = button->rect.width/(tex->getWidth());
	button->scale.y = button->rect.height / (tex->getHeight());

	int id = m_Buttons.size();
	button->col = 0;
	button->row = 0;
	m_Buttons.insert(make_pair(id, button));
}

void CGui::update()

{
	switch (m_Cursor.status)
		
	{
	case CURSORUP:
		m_Cursor.id--;
		break;
	case CURSORDOWN:
		m_Cursor.id++;
		break;
	default:
		break;
	}
	if (m_Cursor.id < 0)
		m_Cursor.id = 0;
	if (m_Cursor.id >= m_Buttons.size())
		m_Cursor.id--;
	m_Cursor.pos.x = m_Buttons[m_Cursor.id]->rect.pos.x - m_Buttons[m_Cursor.id]->rect.width / 2 - 10;
	m_Cursor.pos.y = m_Buttons[m_Cursor.id]->rect.pos.y;
	if (!m_Buttons.empty())
	{
		bool mouseon = false;
		for (m_BTiter = m_Buttons.begin(); m_BTiter != m_Buttons.end(); m_BTiter++)
		{
			if (m_BTiter->second->status == CLICK)
			{
				m_BTiter->second->status = MOUSEON;
				CGameManager::getInstance()->setStatus(m_BTiter->second->pressKey);
				CGameManager::getInstance()->changestatus();
				break;
			}
			if (m_BTiter->second->status == MOUSEON)
			{
				mouseon = true;
				m_BTiter->second->col=1;
			}
			else
			{
				m_BTiter->second->col = 0;;
			}

			//if (!mouseon)
			{
				
			}
		}
		for (int i = 0; i < m_Buttons.size(); i++)
		{
			if (i == m_Cursor.id)
			{
				m_Buttons[i]->col = 1;
			}
			else
			{
				m_Buttons[i]->col = 0;
			}


		}
	}
	
}

void CGui::setRect(VECTOR3 pos, float width, float height)
{
	m_Rect.pos = pos;
	m_Rect.width = width;
	m_Rect.height = height;
}

void CGui::setKey(int id, int key)
{
	if (m_Buttons.find(id) != m_Buttons.end())
	{
		m_Buttons[id]->pressKey = key;
	}
}

void CGui::Render()
{
	if (!m_BackGrounds.empty())
	{
		for (int i = 0; i < m_BackGrounds.size(); i++)
		{
			float imagewidth = m_BackGrounds[i]->getWidth();
			float imageheight = m_BackGrounds[i]->getHeight();
			m_BackGrounds[i]->Render(m_Rect.pos,VECTOR3(0,0,-1),0, m_Rect.width, m_Rect.height, VECTOR3(0, 0, 0),1.0f, 1.0f);
		}
	}
	if (!m_Buttons.empty())
	{
		for (int i = 0; i < m_Buttons.size(); i++)
		{
			float imagewidth = m_Buttons[i]->rect.width;
			float imageheight = m_Buttons[i]->rect.height;
			m_Buttons[i]->texture->setRenderPos(m_Buttons[i]->row,m_Buttons[i]->col);
			m_Buttons[i]->texture->Render(m_Buttons[i]->rect.pos, m_Buttons[i]->rotate,m_Buttons[i]->degree, m_Buttons[i]->scale);
		}
	}
	if (m_Cursor.texture != NULL)
	{
		float width = m_Cursor.texture->getWidth();
		float height = m_Cursor.texture->getHeight();
		m_Cursor.texture->Render(m_Cursor.pos, VECTOR3(0,0,-1),0,width, height, VECTOR3(0, 0, 0), 1.0f,1.0f);
	}
}


CGui::~CGui()
{
}
