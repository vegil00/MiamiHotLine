#include"stdafx.h"
struct sNode
{
	int x;
	int y;
	int G;
	int H;
	int F;
	bool con;
	int inList;
	sNode* father;
};
void father(int childX, int childY, int fatherX, int fatherY, sNode** cur_map, VECTOR3 end)
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

list<sNode> findRoute(VECTOR3 begin, VECTOR3 end, sNode** cur_map)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{

			cur_map[i][j].F = 10000;
			cur_map[i][j].inList = 0;
			cur_map[i][j].x = j;
			cur_map[i][j].y = i;
			cur_map[i][j].father = NULL;

		}
	}
	list<sNode> openlist;
	list<sNode> closelist;
	int startX = (int)begin.x;
	int startY = (int)(begin.y);
	int endX = end.x;
	int endY = end.y;
	openlist.push_back(cur_map[startY][startX]);
	cur_map[startY][startX].inList = 1;
	if (startX >= 0 && startX < 20 && startY >= 0 && startY < 20)
	{
		cur_map[startY][startX].G = fabs((startX - endX) * 10) + fabs((startY - endY) * 10);
		cur_map[startY][startX].H = 0;
		cur_map[startY][startX].F = cur_map[startY][startX].G + cur_map[startY][startX].H;
	}

	sNode* temp = new sNode;
	while (cur_map[endY][endX].inList != 1)
	{

		temp->F = 10000;
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (cur_map[i][j].inList == 1)
				{
					if (temp->F >= cur_map[i][j].F)
					{
						temp = &cur_map[i][j];
					}
				}
			}
		}
		temp->inList = 2;

		closelist.push_back(cur_map[temp->y][temp->x]);
		if (temp->x - 1 >= 0 && temp->y >= 0 && temp->x - 1 < 20 && temp->y < 20)
		{
			if (cur_map[temp->y][temp->x - 1].con == 0 && cur_map[temp->y][temp->x - 1].inList != 2)
			{
				father(temp->x - 1, temp->y, temp->x, temp->y, cur_map, end);
			}
		}
		if (temp->x + 1 >= 0 && temp->y >= 0 && temp->x + 1 < 20 && temp->y < 20)
		{
			if (cur_map[temp->y][temp->x + 1].con == 0 && cur_map[temp->y][temp->x + 1].inList != 2)
			{
				father(temp->x + 1, temp->y, temp->x, temp->y, cur_map, end);
			}
		}
		if (temp->x >= 0 && temp->y - 1 >= 0 && temp->x  < 20 && temp->y - 1< 20)
		{
			if (cur_map[temp->y - 1][temp->x].con == 0 && cur_map[temp->y - 1][temp->x].inList != 2)
			{
				father(temp->x, temp->y - 1, temp->x, temp->y, cur_map, end);
			}
		}
		if (temp->x >= 0 && temp->y + 1 >= 0 && temp->x  < 20 && temp->y + 1< 20)
		{
			if (cur_map[temp->y + 1][temp->x].con == 0 && cur_map[temp->y + 1][temp->x].inList != 2)
			{
				father(temp->x, temp->y + 1, temp->x, temp->y, cur_map, end);
			}
		}
		if (temp->x + 1 >= 0 && temp->y + 1 >= 0 && temp->x + 1 < 20 && temp->y + 1< 20)
		{
			if (cur_map[temp->y + 1][temp->x + 1].con == 0 && cur_map[temp->y + 1][temp->x + 1].inList != 2)
			{
				father(temp->x + 1, temp->y + 1, temp->x, temp->y, cur_map, end);
			}
		}
		if (temp->x - 1 >= 0 && temp->y - 1 >= 0 && temp->x - 1 < 20 && temp->y - 1< 20)
		{
			if (cur_map[temp->y - 1][temp->x - 1].con == 0 && cur_map[temp->y - 1][temp->x - 1].inList != 2)
			{
				father(temp->x - 1, temp->y - 1, temp->x, temp->y, cur_map, end);
			}
		}
		if (temp->x + 1 >= 0 && temp->y - 1 >= 0 && temp->x + 1 < 20 && temp->y - 1< 20)
		{
			if (cur_map[temp->y - 1][temp->x + 1].con == 0 && cur_map[temp->y - 1][temp->x + 1].inList != 2)
			{
				father(temp->x + 1, temp->y - 1, temp->x, temp->y, cur_map, end);
			}
		}
		if (temp->x - 1 >= 0 && temp->y + 1 >= 0 && temp->x - 1 < 20 && temp->y + 1< 20)
		{
			if (cur_map[temp->y + 1][temp->x - 1].con == 0 && cur_map[temp->y + 1][temp->x - 1].inList != 2)
			{
				father(temp->x - 1, temp->y + 1, temp->x, temp->y, cur_map, end);
			}
		}
	}
	list<sNode>route;
	while (temp->father != NULL)
	{
		route.push_front(cur_map[temp->y][temp->x]);
		temp = temp->father;
	}

	return route;
}
int main()
{
	sNode** map;
	map = new sNode*[20];
	for (int i = 0; i < 20; i++)
	{
		map[i] = new sNode[20];
		for (int j = 0; j < 20; j++)
		{
			if (i == 0 || i == 19 || j == 0 || j == 19)
			{
				map[i][j].con = 1;
			}
			else
			{
				map[i][j].con = 0;
			}
			if (j == 10 && (i > 2 && i < 15))
			{
				map[i][j].con = 1;
			}
			

		}
	}

	findRoute(VECTOR3(5, 5, 0), VECTOR3(15, 15, 0), map);
}