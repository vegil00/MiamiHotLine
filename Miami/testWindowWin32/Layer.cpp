#include "stdafx.h"
#include "Layer.h"


CLayer::CLayer()
{
}

void CLayer::Render()
{
	for(map<UINT, CNode*>::iterator it = m_childList.begin(); it != m_childList.end(); it++)
	{
		(*it).second->Render();
	}
}

void CLayer::update()
{
	for (map<UINT, CNode*>::iterator it = m_childList.begin(); it != m_childList.end(); it++)
	{
		(*it).second->update();
	}
}


CLayer::~CLayer()
{
}
