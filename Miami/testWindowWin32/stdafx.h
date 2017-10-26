#pragma once
#include<windows.h>
#include<math.h>
#include<tchar.h>
#include<glew.h>
#include<GLUT.H>
#include<stdio.h>
#include<string>
#include<map>
#include<vector>
#include<list>
#include<time.h>
using namespace std;
#include "tinyxml.h"
#include "tinystr.h"
#include"bass.h"

#include"VECTOR3.h"

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
#include"CTool.h"
struct Rect
{
	VECTOR3 pos;
	float width;
	float height;
	Rect(VECTOR3 pos, float width, float height)
	{
		this->pos = pos;
		this->width = width;
		this->height = height;
	}
	Rect()
	{
		pos = VECTOR3(0, 0, 0);
		width = 0;
		height = 0;
	}
};
#define TSTRING basic_string<TCHAR>

#include"AudioManager.h"
#define PI 3.1415926f

static wstring CU_A2U(string& str)
{
	int size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wstring wstr;
	wstr.resize(size);
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wstr[0], size);
	return wstr;
}

static string CU_U2A(wstring& wstr)
{
	int size = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), -1, NULL, 0, 0, 0);
	string str;
	str.resize(size);
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), -1, &str[0], size, 0, 0);
	return str;
}
static TiXmlDocument* readXml(TSTRING path)
{
#ifdef _UNICODE
	string xmlpath = CU_U2A(path);
	TiXmlDocument* doc = new TiXmlDocument(xmlpath.c_str());
#else
	TiXmlDocument* doc = new TiXmlDocument(path.c_str());
#endif // _UNICODE
	return doc;

}