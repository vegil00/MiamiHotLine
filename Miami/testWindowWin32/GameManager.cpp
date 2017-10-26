#include"stdafx.h"
#include "GameManager.h"

//
//CGameManager* CGameManager::m_Instance = nullptr;
//CGameManager * CGameManager::getInstance()
//{
//	if (m_Instance == nullptr)
//		m_Instance = new CGameManager;
//	return m_Instance;
//}

void CGameManager::init( HINSTANCE hInstance, WNDPROC winproc, int ncmdshow)
{
	WNDCLASSEX wcex;
	wcex.cbClsExtra = 0;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.cbWndExtra = 0;
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex.hCursor = nullptr;
	wcex.hIcon = nullptr;
	wcex.hIconSm = NULL;
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = winproc;
	wcex.lpszClassName = _T("test");
	wcex.lpszMenuName = nullptr;
	wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wcex);
	m_hWnd = CreateWindow(wcex.lpszClassName, _T("testWnd"), WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, hInstance, 0);
	//DWORD A= GetLastError();
	m_hDC = GetDC(m_hWnd);
	initGL();
	ShowWindow(m_hWnd, ncmdshow);
	UpdateWindow(m_hWnd);

	
	
	ZeroMemory(&m_msg, sizeof(MSG));
	//block1 = CBall(VECTOR3(400, 400, -0), 10);
	
	//block1.setspeed(5);
	//block1.setroute(VECTOR3(-400, -400, -0));
	//field[0] = Line(VECTOR3(150, 500, -0), VECTOR3(650, 500, -0));
	//field[1] = Line(VECTOR3(650, 500, -0), VECTOR3(700,300, -0));
	//field[2] = Line(VECTOR3(700, 300, -0), VECTOR3(650, 100, -0));
	//field[3] = Line(VECTOR3(650, 100, -0), VECTOR3(150,100, -0));
	//field[4] = Line(VECTOR3(150, 100, -0), VECTOR3(100, 300, -0));
	//field[5] = Line(VECTOR3(100,300, -0), VECTOR3(150,500, -0));
	//field[6]= Line(VECTOR3(350, 200, -0), VECTOR3(450,350, -0));
	//texture = CTexture("../bin/textures/map0_0.bmp");
	CAudioManager::getInstance()->init();
	CAudioManager::getInstance()->loadFileFromXml(_T("../bin/script/sound.xml"));
	srand(time(NULL));
	m_Status = TITLE;
	CResManager::getInstance()->LoadAllRes(_T("../bin/script/Texture.xml"));
	m_player = new CPlayer;

	title = new CGui;
	title->setRect(VECTOR3(400, 300, 0), 800, 600);
	
	title->addBackGround(0, (CStaticImg*)CResManager::getInstance()->getRes(_T("title")));
	title->addButton(VECTOR3(400, 200, 0), 140, 9, (CSingleImg*)CResManager::getInstance()->getRes(_T("GAMESTART")), 2);
	title->addButton(VECTOR3(400, 190, 0), 140, 9, (CSingleImg*)CResManager::getInstance()->getRes(_T("SOULTRADE")), 0);
	CBulletManager::getInstance()->init(_T("../bin/script/bulletinfo.xml"), _T("../bin/script/bulletpool.xml"));
	CInputManager::getInstance()->addKeyListener(_T("title"), title);
	
	CInputManager::getInstance()->addMouseListener(_T("title"), title);
	levelselect = new CGui;
	levelselect->addBackGround(0, (CStaticImg*)CResManager::getInstance()->getRes(_T("levelselect")));
	levelselect->addButton(VECTOR3(300, 300, 0), 36, 59, (CSingleImg*)CResManager::getInstance()->getRes(_T("level1")), 4);
	levelselect->addButton(VECTOR3(500, 300, 0), 36, 59, (CSingleImg*)CResManager::getInstance()->getRes(_T("level2")), 5);
	levelselect->setRect(VECTOR3(400, 300, 0), 800, 600);
	gamemenu = new CGui;
	gamemenu->setRect(VECTOR3(600, 300, 0), 384, 514);
	gamemenu->addBackGround(0, (CStaticImg*)CResManager::getInstance()->getRes(_T("gamemenu")));
	gamemenu->addButton(VECTOR3(600, 300, 0), 303, 59, (CSingleImg*)CResManager::getInstance() ->getRes(_T("play")),3);
	gamemenu->addButton(VECTOR3(600, 200, 0), 303, 59, (CSingleImg*)CResManager::getInstance()->getRes(_T("eject")), 1);
	CSenceManager::getInstance()->init(_T("../bin/script/levels.xml"), m_hWnd, m_player);
	//level1 = new CLevel;
	//level1->init(_T("../bin/script/level/map1.txt"),  _T("../bin/script/level/level1.xml"),m_hWnd,m_player);
	/*CEnemy* ene1 = new CEnemy;
	ene1->init(_T("enemy_mafia"), VECTOR3(16 * 19, 15 * 16, 0), 8, 16,PATROL,level1,40,M16);
	ene1->addtarget(VECTOR3(18.5f * 16, 15.5f * 16, 0));
	ene1->addtarget(VECTOR3(21.5f * 16, 16.5f* 16, 0));
	ene1->addtarget(VECTOR3(23.5f * 16, 12.5f * 16, 0));
	ene1->addtarget(VECTOR3(8.5f * 16, 18.5f * 16, 0));
	
	level1->AddChild(ene1);
	CWeapon* shootgun = new CWeapon;
	shootgun->init(SHOOTGUN, 5, 1, VECTOR3(430, 300, 0));
	CWeapon* m16 = new CWeapon;
	m16->init(M16, 5, 1, VECTOR3(460, 300, 0));
	shootgun->setId(90);
	
	m16->setId(91);

	level1->AddChild(shootgun);
	level1->AddChild(m16);
	BulletInfo* info = CBulletManager::getInstance()->getBulletInfo(_T("bullet"));
	for (int i = 0; i < 30; i++)
	{
		CBullet* bullet = new CBullet;
		bullet->init(info->atk, info->speed, info->name, info->touchcol, info->width, info->height, info->type);
		bullet->setId(i + 1);
		level1->AddChild(bullet);

	}
	
	level1->addPlayer(m_player);*/
	changeStatus = 0;
}

void CGameManager::initGL()
{
	PIXELFORMATDESCRIPTOR pfd;
	pfd.bReserved = 0;
	pfd.cAccumAlphaBits = 0;
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.cColorBits = 24;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.cAccumBits = 0;
	pfd.cAccumBlueBits = 0;
	pfd.cAccumGreenBits = 0;
	pfd.cAccumRedBits = 0;
	pfd.cAlphaBits = 0;
	pfd.cAlphaShift = 0;
	pfd.cAuxBuffers = 0;
	pfd.cBlueBits = 0;
	pfd.cBlueShift = 0;
	pfd.cDepthBits = 16;
	pfd.cGreenBits = 0;
	pfd.cGreenShift = 0;
	pfd.cRedBits = 0;
	pfd.cRedShift = 0;
	pfd.cStencilBits = 0;
	pfd.dwDamageMask = 0;
	pfd.dwLayerMask = 0;
	pfd.dwVisibleMask = 0;


	int pixelFormat = ChoosePixelFormat(m_hDC, &pfd);
	SetPixelFormat(m_hDC, pixelFormat, &pfd);
	m_hRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hRC);
	glClearColor(0, 0, 0, 1.0f);
	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,800,0,600);
	//gluPerspective(45.0f, (GLdouble)800 / 600, 0.1f, 10000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	selectFont(48, ANSI_CHARSET, "Comic Sans MS");

}

void CGameManager::mainLoop()
{
	while (m_msg.message != WM_QUIT)
	{
		static int pre_time = GetTickCount();
		int cur_time = GetTickCount();
		if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
		float elapsedtime = (cur_time - pre_time)*0.001f;
		if (elapsedtime> 1.0f / 60)
		{
			Render();
			update(elapsedtime);
			pre_time = cur_time;

		}
		else {
			Sleep(1);
		}
	}
}

void CGameManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	VECTOR3 mapPos = VECTOR3(400, 300, 0);
	switch (m_Status)
	{
	case TITLE:
		title->Render();
		break;
	case LEVELSELECT:
		levelselect->Render();
		break;
	case GAME:
	case GAMEMENU:
		//glColor3f(1.0f,1.0f, 1.0f);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		//CResManager::getInstance()->Render(_T("map"), mapPos, 800.0f, 600.0f, mapPos, 1.0f, 1.0f);
		//texture.Render(mapPos, 800.0f, 600.0f, mapPos, 1, 1);
		//VECTOR3 playerPos = VECTOR3(100, 0, 0);
		//VECTOR3 playercol = VECTOR3(0.1 * col, 0, 0);

		//((CStaticImg*)(CResManager::getInstance()->getRes(_T("map"))))->Render(VECTOR3(400, 300, 0),VECTOR3(0,0,-1),0.0f, 800, 600);
		CSenceManager::getInstance()->Render();
		//m_player->rotate(VECTOR3(0, 0, 1), 45);
		//m_player->Render();
		//CBulletManager::getInstance()->Render();
		//texture.Render(Rect(VECTOR3(0,0,0),800,600), Rect(VECTOR3(0.5, 0.5, 0), 0.5f,0.5f ));
		//double err = GetLastError();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glColor3f(1.0f, 0.0f, 0.0f);

		//block1.Render();
		//for (int i = 0; i <7; i++)
		//{
		//	field[i].Render();
		//}
		if (m_Status == GAMEMENU)
			gamemenu->Render();
		break;
	default:break;
	}

	SwapBuffers(m_hDC);
	//DWORD A=GetLastError();
	
}

void CGameManager::update(int time)
{
	//for (int i = 0; i < 7; i++)
	//{
	//	if (i == 6)
	//	{
	//		GetLastError();
	//	}
	//	if (block1.touch(&field[i]))
	//	{
	//		if (i == 6)
	//		{
	//			GetLastError();
	//		}
	//		block1.hitline(&field[i]);
	//		break;
	//	}
	//}
	//block1.update();
	if (changeStatus)
	{
		changeStatus = 0;
		switch (m_Status)

		{case TITLE:
			CInputManager::getInstance()->addKeyListener(_T("title"), title);
			CInputManager::getInstance()->addMouseListener(_T("title"), title);
			break;
		case LEVELSELECT:
			CInputManager::getInstance()->removeKeyListener(_T("title"));
			CInputManager::getInstance()->removeMouseListener(_T("title"));
			CInputManager::getInstance()->addKeyListener(_T("levelselect"),levelselect);
			CInputManager::getInstance()->addMouseListener(_T("levelselect"),levelselect);
			break;
		case GAME:
			CInputManager::getInstance()->removeKeyListener(_T("levelselect"));
			CInputManager::getInstance()->removeMouseListener(_T("levelselect"));
			CInputManager::getInstance()->addKeyListener(_T("player"), m_player);
			CInputManager::getInstance()->addMouseListener(_T("player"), m_player);

			break;
		case GAMEMENU:
			CInputManager::getInstance()->removeKeyListener(_T("player"));
			CInputManager::getInstance()->removeMouseListener(_T("player"));
			CInputManager::getInstance()->addKeyListener(_T("gamemenu"), gamemenu);
			CInputManager::getInstance()->addMouseListener(_T("gamemenu"), gamemenu);
			break;
		default:
			break;
		}
	}
	
	//col++;
	//if (col >= 10)
	//	col = 0;
	switch (m_Status)
	{case TITLE:
		

		title->update();
		break;
	case LEVELSELECT:
		levelselect->update();
		break;
	case GAME:
		
		//m_player->update();
		CBulletManager::getInstance()->update();
		//level1->setPlayerPos(m_player->getmapPos());
		CSenceManager::getInstance()->update();
		break;
	case GAMEMENU:
		gamemenu->update();
		break;
	default:
		break;
	}
}

void CGameManager::MessageProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	CInputManager::getInstance()->messageProc(m_hWnd,msg, wParam, lParam);
	//m_player->MessageProc(msg, wParam, lParam);
}

void CGameManager::clearupRC()
{
	if (m_hRC)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hRC);
	}
	if (m_hDC)
	{
		ReleaseDC(m_hWnd, m_hDC);
	}
		
	

}

void CGameManager::setStatus(int value)
{
	if (value == 0)
	{
		PostQuitMessage(0);
	}
	if (value >= 1 && value <= 3)
	{
		m_Status = (GAMESTATUS)value;
		if(value==1||value==2)
		CSenceManager::getInstance()->reset();
	}
	if (value >= 4)
	{
		m_Status = GAME;
		CSenceManager::getInstance()->setSence(value);
		gamemenu->setKey(0, value);
		

	}
}

CGameManager::CGameManager()
{
	m_player = NULL;
	level1 = NULL;
	title = NULL;
}


CGameManager::~CGameManager()
{
	//delete title;
}
