#include "stdafx.h"
#include "InputManager.h"


CInputManager::CInputManager()
{
	
}


CInputManager::~CInputManager()
{
}

void CInputManager::addMouseListener(TSTRING name, CMouseListener * listener)
{
#ifdef _UNICODE
	string listenerName = CU_U2A(name);
	if (m_MouseListeners.find(listenerName) == m_MouseListeners.end())
		m_MouseListeners.insert(make_pair(listenerName, listener));
#else
	if (m_MouseListeners.find(name) == m_MouseListeners.end())
		m_MouseListeners.insert(make_pair(name, listener));
#endif // _UNICODE

	
}

void CInputManager::addKeyListener(TSTRING name, CKeyListener * listener)
{
#ifdef _UNICODE
	string listenerName = CU_U2A(name);
	if (m_KeyListeners.find(listenerName) == m_KeyListeners.end())
		m_KeyListeners.insert(make_pair(listenerName, listener));
#else
	if (m_KeyListeners.find(name) == m_KeyListeners.end())
		m_KeyListeners.insert(make_pair(name, listener));
#endif // _UNICODE

	
}

void CInputManager::removeMouseListener(TSTRING name)
{
#ifdef _UNICODE
	string listenername = CU_U2A(name);
	
	if (m_MouseListeners.find(listenername) != m_MouseListeners.end())
		m_MouseListeners.erase(m_MouseListeners.find(listenername));
#else
	
	if (m_MouseListeners.find(name) != m_MouseListeners.end())
		m_MouseListeners.erase(m_MouseListeners.find(name));
#endif // _UNICODE

}

void CInputManager::removeKeyListener(TSTRING name)
{
#ifdef _UNICODE
	string listenername = CU_U2A(name);
	if (m_KeyListeners.find(listenername) != m_KeyListeners.end())
		m_KeyListeners.erase(m_KeyListeners.find(listenername));
#else
	if (m_KeyListeners.find(name) != m_KeyListeners.end())
		m_KeyListeners.erase(m_KeyListeners.find(name));
#endif // _UNICODE

}

void CInputManager::messageProc(HWND hwnd,UINT msg, WPARAM wParam, LPARAM lParam)
{
	sInputEvent inputevent;
	ZeroMemory(&inputevent, sizeof(sInputEvent));
	RECT rect;
	switch (msg)
	{case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
		inputevent.type = MOUSE_INPUTEVENT;
		inputevent.eventkind.mouseEvent.x =LOWORD(lParam);
		
		GetClientRect(hwnd, &rect);
		inputevent.eventkind.mouseEvent.y =rect.bottom-rect.top- HIWORD(lParam);
		
		switch (wParam)
		{
		case MK_LBUTTON:
			
			inputevent.eventkind.mouseEvent.key = MOUSE_LB_DOWN;
			
			for (m_MouseIter = m_MouseListeners.begin(); m_MouseIter != m_MouseListeners.end(); m_MouseIter++)
			{
				m_MouseIter->second->OnMouseDown(inputevent);
			}
			break;
		case MK_RBUTTON:
			inputevent.eventkind.mouseEvent.key = MOUSE_RB_DOWN;
			for (m_MouseIter = m_MouseListeners.begin(); m_MouseIter != m_MouseListeners.end(); m_MouseIter++)
			{
				m_MouseIter->second->OnMouseDown(inputevent);
			}
			break;
		default:
			break;
		}
		break;
	case WM_LBUTTONUP:
		inputevent.eventkind.mouseEvent.key = MOUSE_LB_UP;
		for (m_MouseIter = m_MouseListeners.begin(); m_MouseIter != m_MouseListeners.end(); m_MouseIter++)
		{
			m_MouseIter->second->OnMouseUp(inputevent);
		}
		break;
	case WM_MOUSEMOVE:
		inputevent.type = MOUSE_INPUTEVENT;
		inputevent.eventkind.mouseEvent.x = LOWORD(lParam);
		
		GetClientRect(hwnd, &rect);
		inputevent.eventkind.mouseEvent.y = rect.bottom - rect.top - HIWORD(lParam);
		inputevent.eventkind.mouseEvent.key = MOUSE_MOVE;

		for (m_MouseIter = m_MouseListeners.begin(); m_MouseIter != m_MouseListeners.end(); m_MouseIter++)
		{
			m_MouseIter->second->OnMouseMove(inputevent);
		}
		break;
	case WM_KEYDOWN:
		inputevent.type = KEY_INPUTEVENT;
		inputevent.eventkind.keyEvent.key = wParam;
		inputevent.eventkind.keyEvent.keyDown = true;
		for (m_KeyIter = m_KeyListeners.begin(); m_KeyIter != m_KeyListeners.end(); m_KeyIter++)
		{
			m_KeyIter->second->OnKeyDown(inputevent);
		}

		break;
	
	case WM_KEYUP:
		inputevent.type = KEY_INPUTEVENT;
		inputevent.eventkind.keyEvent.key = wParam;
		inputevent.eventkind.keyEvent.keyDown = false;
		for (m_KeyIter = m_KeyListeners.begin(); m_KeyIter != m_KeyListeners.end(); m_KeyIter++)
		{
			m_KeyIter->second->OnKeyUp(inputevent);
		}
		break;
	default:
		break;
	}
}

CMouseListener * CInputManager::getMouseListener(TSTRING name)
{
	return nullptr;
}

CKeyListener * CInputManager::getKeyListener(TSTRING name)
{
	return nullptr;
}
