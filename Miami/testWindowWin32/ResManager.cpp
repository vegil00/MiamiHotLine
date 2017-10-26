#include "stdafx.h"
#include "ResManager.h"


CResManager::CResManager()
{
}

CRes * CResManager::getRes(TSTRING name)
{
#ifdef _UNICODE
	string imagename = CU_U2A(name);
	if (m_ResList.find(imagename.c_str()) == m_ResList.end())
		return nullptr;
	else
		return m_ResList[imagename.c_str()];
#else
	if (m_ResList.find(name.c_str()) == m_ResList.end())
		return nullptr;
	else
		return m_ResList[name.c_str()];
#endif // _UNICODE
	//if (m_ResList.find(name) == m_ResList.end())
	//			return nullptr;
	//		else
	//			return m_ResList[name.c_str()];
}

bool CResManager::LoadRes(string path, string name, imageType type, int row, int col)
{
	/*if (m_ResList.size() >= 17)
	{
		GetLastError();
	}*/
	glEnable(GL_TEXTURE_2D);
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP* dib(0);
	GLubyte* byte;
	UINT width, height;
	UINT texID;
	

	fif = FreeImage_GetFileType(path.c_str(), 0);
	if (fif == -1)
		fif = FreeImage_GetFIFFromFilename(path.c_str());
	if (fif == -1)
		return false;
	dib = FreeImage_Load(fif, path.c_str(), 0);
	//#endif // _UNICODE


	dib = FreeImage_ConvertTo32Bits(dib);
	byte = (BYTE*)FreeImage_GetBits(dib);
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

	FreeImage_Unload(dib);
	CTexture* texture = new CTexture(width, height, texID, type, row, col);
	CSingleImg* staticImg = new CSingleImg;

	staticImg->init(texture);
	m_ResList.insert(make_pair(name, staticImg));

//#ifdef _UNICODE
//	wstring imagename = CU_A2U(name);
//	m_ResList.insert(make_pair(imagename, staticImg));
//#else
//	m_ResList.insert(make_pair(name, staticImg));
//#endif
	
}

bool CResManager::LoadRes(string path, string name, imageType type)
{
	glEnable(GL_TEXTURE_2D);
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP* dib(0);
	GLubyte* byte;
	UINT width, height;
	UINT texID;

	fif = FreeImage_GetFileType(path.c_str(), 0);
	if (fif == -1)
		fif = FreeImage_GetFIFFromFilename(path.c_str());
	if (fif == -1)
		return false;
	dib = FreeImage_Load(fif, path.c_str(), 0);
	//#endif // _UNICODE


	dib = FreeImage_ConvertTo32Bits(dib);
	byte = (BYTE*)FreeImage_GetBits(dib);
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

	FreeImage_Unload(dib);
	CTexture* texture = new CTexture(width, height, texID, type, 1, 1);
	CStaticImg* staticImg = new CStaticImg;

	staticImg->init(texture);
	m_ResList.insert(make_pair(name, staticImg));
//#ifdef _UNICODE
//	wstring imagename = CU_A2U(name);
//	m_ResList.insert(make_pair(imagename, staticImg));
//#else
//	m_ResList.insert(make_pair(name, staticImg));
//#endif
	



	return true;
}

bool CResManager::LoadAllRes(TSTRING path)
{
#ifdef _UNICODE
	string xmlpath = CU_U2A(path);
	TiXmlDocument* doc = new TiXmlDocument(xmlpath.c_str());
#else
	TiXmlDocument* doc = new TiXmlDocument(path.c_str());
#endif // _UNICODE


	doc->LoadFile();
	TiXmlElement* root = doc->FirstChildElement();
	for (TiXmlElement* ele = root; ele != nullptr; ele = ele->NextSiblingElement())
	{

		
		string name = ele->Attribute("name");
		string imagePath = ele->Attribute("path");
		


		imageType type = (imageType)atoi(ele->Attribute("imgType"));
		int row, col;
		if (type == ANIMATION)
		{
			row = atoi(ele->Attribute("countDir"));
			col = atoi(ele->Attribute("countFrame"));
			LoadRes(imagePath, name, type, row, col);
		}
		else if(type==STATIC)
			LoadRes(imagePath, name, type);


		

	}
	return true;

}


CResManager::~CResManager()
{
}
