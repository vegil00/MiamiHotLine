#include "stdafx.h"
#include "Snece.h"


CSnece::CSnece()
{
	m_backGround = NULL;
	
}

void CSnece::init(TSTRING path, TSTRING background, HWND hwnd)
{
	/*for (list<CNode*>::iterator it = m_childList.begin(); it != m_childList.end(); it++)
	{
		(*it)->Render();
	}*/
}

void CSnece::Render()
{
	for (map<UINT,CNode*>::iterator it = m_childList.begin(); it != m_childList.end(); it++)
	{
		(*it).second->Render();
	}
}

void CSnece::update()
{
	for (map<UINT, CNode*>::iterator it = m_childList.begin(); it != m_childList.end(); it++)
	{
		(*it).second->update();
	}
}


CSnece::~CSnece()
{
}
