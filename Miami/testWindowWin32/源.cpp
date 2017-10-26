#include"stdafx.h"
#include"GameManager.h"
#include"Matrix.h"
LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CGameManager::getInstance()->MessageProc(msg,wParam,lParam);
	switch (msg)
	{
	case WM_DESTROY:
		CGameManager::getInstance()->clearupRC();
		PostQuitMessage(0);
			break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}
	
}
INT WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpcmdline, INT nCmdShow)
{

	CGameManager::getInstance()->init(hInstance,WinProc,nCmdShow);
	CMatrix m1(4, 4);
	CMatrix m2(4, 4);
	CMatrix m3 = m1 + m2;
	CGameManager::getInstance()->mainLoop();
	return 1;
}