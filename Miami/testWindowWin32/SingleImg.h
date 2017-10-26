#pragma once
#include"Res.h"
class CSingleImg:public CRes
{
private:
	int row;
	int col;
	int cur_row;
	int cur_col;
public:
	CSingleImg();
	void init(CTexture* tex);
	void Render(VECTOR3& archPos, VECTOR3 rotate, float degree, float showWidth, float showHeight, int r, int c);
	void Render(VECTOR3& archPos, VECTOR3 rotate,  float degree,VECTOR3 scale);
	void setRenderPos(int row, int col);
	int getWidth() { return width; }
	int getHeight() { return height; }
	int getRow() { return row; }
	int getCol() { return col; }
	~CSingleImg();
};

