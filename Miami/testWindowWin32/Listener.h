#pragma once
#include"sEvent.h"
class CMouseListener
{
public:
	virtual void OnMouseDown(sInputEvent){}
	virtual void OnMouseUp(sInputEvent) {}
	virtual void OnMouseMove(sInputEvent) {}
	virtual void OnMouseWheel(sInputEvent) {}
};
class CKeyListener
{
public:
	virtual void OnKeyDown(sInputEvent) {}
	virtual void OnKeyUp(sInputEvent) {}
};