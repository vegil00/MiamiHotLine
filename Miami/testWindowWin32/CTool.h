#include"stdafx.h"
#pragma once

static float minf(float a, float b)
{
	if (a < b)
		return a;
	else return b;
}
 static float maxf(float a, float b)
{
	if (a > b)
		return a;
	else
		return b;
}
static bool RectCollision(VECTOR3* rect1, VECTOR3* rect2)
{
	for (int i = 0; i < 4; i++)
	{
		if ((rect1[i].x>minf(rect2[0].x, rect2[2].x) && rect1[i].x<maxf(rect2[0].x, rect2[2].x)) || (rect1[i].x>minf(rect2[1].x, rect2[3].x) && rect1[i].x < maxf(rect2[1].x, rect2[3].x)))
		{
			if ((rect1[i].y > minf(rect2[0].y, rect2[2].y) && rect1[i].y<maxf(rect2[0].y, rect2[2].y)) || (rect1[i].x>minf(rect2[1].y, rect2[3].y) && rect1[i].y < maxf(rect2[1].y, rect2[3].y)))
			{
				return 1;
			}
		}
		if ((rect2[i].x>minf(rect1[0].x, rect1[2].x) && rect2[i].x<maxf(rect1[0].x, rect1[2].x)) || (rect2[i].x>minf(rect1[1].x, rect1[3].x) && rect2[i].x < maxf(rect1[1].x, rect1[3].x)))
		{
			if ((rect2[i].y > minf(rect1[0].y, rect1[2].y) && rect2[i].y<maxf(rect1[0].y, rect1[2].y)) || (rect2[i].y>minf(rect1[1].y, rect1[3].y) && rect2[i].y < maxf(rect1[1].y, rect1[3].y)))
			{
				return 1;
			}
		}
	}
	return 0;
}

static void xFather(int childX, int childY, int fatherX, int fatherY, sNode ** cur_map, VECTOR3 end)
{
	int endX = end.x;
	int endY = end.y;
	sNode* child = &cur_map[childY][childX];
	sNode* father = &cur_map[fatherY][fatherX];
	if (child->inList != 1)
	{
		child->inList = 1;
		child->father = father;
		child->G = fabs(child->x - endX) * 10 + fabs(child->y - endY) * 10;
		if ((child->x) != (father->x) && (child->y) != (father->y))
		{
			child->H = father->H + 14;
		}
		else
		{
			child->H = father->H + 10;
		}
		child->F = child->G + child->H;
	}
	else if (child->inList == 1)
	{
		sNode* temp = child->father;
		int h = child->H;
		child->father = father;
		if ((child->x) != (father->x) && (child->y) != (father->y))
		{
			child->H = father->H + 14;
		}
		else
		{
			child->H = father->H + 10;
		}
		child->F = child->H + child->G;
		if (child->H > h)
		{
			child->father = temp;
			if ((child->x) != (temp->x) && (child->y) != (temp->y))
			{
				child->H = temp->H + 14;
			}
			else
			{
				child->H = temp->H + 10;
			}
			child->F = child->G + child->H;

		}

	}

}

static list<sNode*> findRoute(VECTOR3 begin, VECTOR3 end, sNode ** cur_map,int row,int col)
{
	list<sNode*> openlist;
	list<sNode*> closelist;
	list<sNode*> route;
	closelist.clear();
	openlist.clear();
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j <col; j++)
		{

			cur_map[i][j].F = 10000;
			cur_map[i][j].inList = 0;
			cur_map[i][j].x = j;
			cur_map[i][j].y = i;
			cur_map[i][j].father = NULL;

		}
	}

	int startX = (int)begin.x;
	int startY = (int)(begin.y);
	int endX = end.x;
	int endY = end.y;
	openlist.push_back(&cur_map[startY][startX]);
	cur_map[startY][startX].inList = 1;
	if (startX >= 0 && startX < col && startY >= 0 && startY < row)
	{
		cur_map[startY][startX].G = fabs((startX - endX) * 10) + fabs((startY - endY) * 10);
		cur_map[startY][startX].H = 0;
		cur_map[startY][startX].F = cur_map[startY][startX].G + cur_map[startY][startX].H;
	}

	sNode* temp = new sNode;
	while (/*cur_map[endY][endX].inList != 1&&*/openlist.size()>0)
	{
		
		if (cur_map[endY][endX].inList == 1)
		{
			temp=&cur_map[endY][endX];
			break;
		}
		temp->F = 10000;

		for (list<sNode*>::iterator it = openlist.begin(); it != openlist.end(); it++)
		{


			if ((*it)->inList == 1)
			{
				if (temp->F >= (*it)->F)
				{
					temp = (*it);
				}
			}

		}
		
		temp->inList = 2;
		openlist.clear();
		closelist.push_back(&cur_map[temp->y][temp->x]);
		if (temp->x - 1 >= 0 && temp->y >= 0 && temp->x - 1 <col && temp->y < row)
		{
			if (cur_map[temp->y][temp->x - 1].con == 0 && cur_map[temp->y][temp->x - 1].inList != 2)
			{
				openlist.push_back(&cur_map[temp->y][temp->x - 1]);
				xFather(temp->x - 1, temp->y, temp->x, temp->y, cur_map, end);
			}
		}
		if (temp->x + 1 >= 0 && temp->y >= 0 && temp->x + 1 < col && temp->y < row)
		{
			if (cur_map[temp->y][temp->x + 1].con == 0 && cur_map[temp->y][temp->x + 1].inList != 2)
			{
				openlist.push_back(&cur_map[temp->y][temp->x + 1]);
				xFather(temp->x + 1, temp->y, temp->x, temp->y, cur_map, end);
			}
		}
		if (temp->x >= 0 && temp->y - 1 >= 0 && temp->x < col && temp->y - 1 <row)
		{
			if (cur_map[temp->y - 1][temp->x].con == 0 && cur_map[temp->y - 1][temp->x].inList != 2)
			{
				openlist.push_back(&cur_map[temp->y - 1][temp->x]);
				xFather(temp->x, temp->y - 1, temp->x, temp->y, cur_map, end);
			}
		}
		if (temp->x >= 0 && temp->y + 1 >= 0 && temp->x < col && temp->y + 1 <row)
		{
			if (cur_map[temp->y + 1][temp->x].con == 0 && cur_map[temp->y + 1][temp->x].inList != 2)
			{
				openlist.push_back(&cur_map[temp->y + 1][temp->x]);
				xFather(temp->x, temp->y + 1, temp->x, temp->y, cur_map, end);
			}
		}
		if (temp->x + 1 >= 0 && temp->y + 1 >= 0 && temp->x + 1 < col && temp->y + 1 <row)
		{
			if (cur_map[temp->y + 1][temp->x + 1].con == 0 && cur_map[temp->y + 1][temp->x + 1].inList != 2)
			{
				openlist.push_back(&cur_map[temp->y + 1][temp->x + 1]);
				xFather(temp->x + 1, temp->y + 1, temp->x, temp->y, cur_map, end);
			}
		}
		if (temp->x - 1 >= 0 && temp->y - 1 >= 0 && temp->x - 1 < col && temp->y - 1 < row)
		{
			if (cur_map[temp->y - 1][temp->x - 1].con == 0 && cur_map[temp->y - 1][temp->x - 1].inList != 2)
			{
				openlist.push_back(&cur_map[temp->y - 1][temp->x - 1]);
				xFather(temp->x - 1, temp->y - 1, temp->x, temp->y, cur_map, end);
			}
		}
		if (temp->x + 1 >= 0 && temp->y - 1 >= 0 && temp->x + 1 < col && temp->y - 1 < row)
		{
			if (cur_map[temp->y - 1][temp->x + 1].con == 0 && cur_map[temp->y - 1][temp->x + 1].inList != 2)
			{
				openlist.push_back(&cur_map[temp->y - 1][temp->x + 1]);
				xFather(temp->x + 1, temp->y - 1, temp->x, temp->y, cur_map, end);
			}
		}
		if (temp->x - 1 >= 0 && temp->y + 1 >= 0 && temp->x - 1 < col && temp->y + 1 <row)
		{
			if (cur_map[temp->y + 1][temp->x - 1].con == 0 && cur_map[temp->y + 1][temp->x - 1].inList != 2)
			{
				openlist.push_back(&cur_map[temp->y + 1][temp->x - 1]);
				xFather(temp->x - 1, temp->y + 1, temp->x, temp->y, cur_map, end);
			}
		}
		if (openlist.size() <= 0)
		{
			return route;
		}
	}

	route.clear();
	while (temp->father != NULL)
	{
		route.push_front(&cur_map[temp->y][temp->x]);
		temp = temp->father;
	}

	return route;
}

static GLint lists=0;
static void selectFont(int size, int charset, const char *face)
{
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, face);

	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);

	// 申请MAX_CHAR个连续的显示列表编号  
	lists = glGenLists(128);
	// 把每个字符的绘制命令都装到对应的显示列表中  
	wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, lists);
}

static void drawString(const char* str) //屏幕显示字体   22222
{
	// 调用每个字符对应的显示列表，绘制每个字符  
	for (; *str != '\0'; ++str) {
		glCallList(glGenLists(128) + *str);
	}
}
