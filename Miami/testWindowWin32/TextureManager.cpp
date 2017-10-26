#include"stdafx.h"
#include "TextureManager.h"



CTextureManager::CTextureManager()
{
}

CTexture * CTextureManager::getTexture(TSTRING name)
{
#ifdef _UNICODE
	string imagename = CU_U2A(name);
	if (m_idList.find(imagename.c_str()) == m_idList.end())
		return nullptr;
	else
		return m_idList[imagename.c_str()];
#else
	if (m_idList.find(name) == m_idList.end())
		return nullptr;
	else
		return m_idList[name];
#endif // _UNICODE

	
}

bool CTextureManager::bindTexture(TSTRING name)
{
#ifdef _UNICODE
	string imagename = CU_U2A(name);
	glEnable(GL_TEXTURE_2D);
	if (m_idList.find(imagename) == m_idList.end())
		return false;
	else
	{
		glBindTexture(GL_TEXTURE_2D, m_idList[imagename]->getId());
		return 1;
	}
#else
	glEnable(GL_TEXTURE_2D);
	if (m_idList.find(name) == m_idList.end())
		return false;
	else
	{
		glBindTexture(GL_TEXTURE_2D, m_idList[name]->getId());
		return 1;
	}
#endif // _UNICODE

	
		
}

bool CTextureManager::LoadTexture(string path, string name, imageType type, int row, int col)
{
	
	glEnable(GL_TEXTURE_2D);
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP* dib(0);
	GLubyte* byte;
	UINT width, height;
	UINT texID;
//#ifdef _UNICODE
//	string imagePath = CU_U2A(path);
//	fif = FreeImage_GetFileType(imagePath.c_str(), 0);
//	if (fif == -1)
//		fif = FreeImage_GetFIFFromFilename(imagePath.c_str());
//	if (fif == -1)
//		return false;
//	dib = FreeImage_Load(fif, imagePath.c_str(), 0);
//#else
	fif = FreeImage_GetFileType(path.c_str(), 0);
	if (fif == -1)
		fif = FreeImage_GetFIFFromFilename(path.c_str());
	if (fif == -1)
		return false;
	dib = FreeImage_Load(fif, path.c_str(), 0);
//#endif // _UNICODE

	
	dib = FreeImage_ConvertTo32Bits(dib);
	byte =(BYTE*) FreeImage_GetBits(dib);
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	glGenTextures(1, &texID);
	int a = glGetError();
	glBindTexture(GL_TEXTURE_2D, texID);
	a = glGetError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	a = glGetError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	a = glGetError();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, byte);
	a = glGetError();
	FreeImage_Unload(dib);
	CTexture* texture = new CTexture(width, height, texID,type,row,col);
	
//#ifdef _UNICODE
//	string imagename = CU_U2A(name);
//	m_idList.insert(make_pair(imagename, texture));
//#else
	m_idList.insert(make_pair(name, texture));
//#endif // _UNICODE

	
	return true;
}

bool CTextureManager::LoadTextures(TSTRING path)
{
#ifdef _UNICODE
	string xmlpath = CU_U2A(path);
	TiXmlDocument* doc = new TiXmlDocument(xmlpath.c_str());
#else
	TiXmlDocument* doc = new TiXmlDocument(path.c_str());
#endif // _UNICODE

	
	doc->LoadFile();
	TiXmlElement* root = doc->FirstChildElement();
	for (TiXmlElement* ele=root->FirstChildElement(); ele != nullptr; ele = ele->NextSiblingElement())
	{
		
//#ifdef _UNICODE
//		string n = (ele->Attribute("name"));
//		TSTRING name =CU_A2U( n);
//		string p= ele->Attribute("path");
//		TSTRING imagePath = CU_A2U(p);
//#else
		string name = ele->Attribute("name");
		string imagePath = ele->Attribute("path");
//#endif // _UNICODE

		
		imageType type = (imageType)atoi(ele->Attribute("type"));
		int row, col;
		if (type == ANIMATION)
		{
			row = atoi(ele->Attribute("row"));
			col = atoi(ele->Attribute("col"));
		}
		else
			col=row = 1;
		

		LoadTexture(imagePath, name, type, row, col);

	}
	return true;
}

void CTextureManager::Render(TSTRING name, VECTOR3& archPos, float showWidth, float showHeight, VECTOR3 &imagePos, float imageWidth, float imageHeight)
{
#ifdef _UNICODE
	string imagename = CU_U2A(name);
	map<string, CTexture*>::iterator it = m_idList.find(imagename);
	if (m_idList.find(imagename.c_str()) != m_idList.end())
		m_idList[imagename.c_str()]->Render(archPos,VECTOR3(0,0,-1) ,0.0f,showWidth, showHeight, imagePos, imageWidth, imageHeight);
#else
	map<string, CTexture*>::iterator it = m_idList.find(name);
	if (m_idList.find(name) != m_idList.end())
		m_idList[name]->Render(archPos, VECTOR3(0,0,-1),0,showWidth, showHeight, imagePos, imageWidth, imageHeight);
#endif // _UNICODE

	
}


CTextureManager::~CTextureManager()
{
}
