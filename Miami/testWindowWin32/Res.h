#pragma once
#include"Texture.h"
class CRes
{
protected:
	CTexture* texture;
	int width;
	int height;
	
public:
	CRes();
	virtual void update() {}
	virtual void Render(){}
	virtual void init(CTexture* tex);
	void translate(float x, float y, float z);
	void rotate(float degree, float x, float y, float z);
	void scale(float x, float y, float z);
	virtual int getWidth();
	virtual int getHeight();
	virtual ~CRes();
};

