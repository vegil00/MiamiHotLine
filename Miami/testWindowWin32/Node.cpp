#include "stdafx.h"
#include "Node.h"


CNode::CNode()
{
	m_father = NULL;
}


void CNode::AddChild(CNode * node)
{
	if (node->m_father != NULL)
	{
		node->m_father->RemoveChild(node);
		node->m_father = this;
	}

	m_childList.insert(make_pair(node->getId(), node));
}

void CNode::RemoveChild(CNode* node)
{
	for (map<UINT,CNode*>::iterator it = m_childList.begin(); it != m_childList.end();)
	{
		if ((*it).second == node)
		{
			m_childList.erase(it);
			break;
		}

	}
	
}

void CNode::RemoveAllChild()
{
	for (map<UINT, CNode*>::iterator it = m_childList.begin(); it != m_childList.end();)
	{
		it = m_childList.erase(it);
	}
}

CNode::~CNode()
{
}
