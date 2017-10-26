#pragma once
enum eEventType
{
	NONE=0,
	MOUSE_INPUTEVENT=1,
	
	KEY_INPUTEVENT=2
	

};

enum eMouseEvent
{
	MOUSE_LB_DOWN=0,
	MOUSE_RB_DOWN=1,
	MOUSE_MB_DOWN=2,
	
	MOUSE_LB_UP=3,
	MOUSE_RB_UP=4,
	MOUSE_MB_UP=5,

	MOUSE_WHEEL=6,
	MOUSE_MOVE=7
};

struct sMouseEvent
{
	eMouseEvent key;
	int x;
	int y;
};
struct sKeyEvent
{
	char key;
	bool keyDown;
};
struct  sInputEvent
{
	eEventType type;
	
	union event
	{
		sMouseEvent mouseEvent;
		sKeyEvent keyEvent;
	};
	event eventkind;
};