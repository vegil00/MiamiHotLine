#pragma once
#include"Singleton.h"
#include"Texture.h"
#include "FreeImage.h"
class CTextureManager:public CSingleton<CTextureManager>
{private:
	map<string, CTexture*> m_idList;
public:
	CTextureManager();
	CTexture* getTexture(TSTRING name);
	bool bindTexture(TSTRING name);
	bool LoadTexture(string path,string name,imageType type,int row,int col);
	bool LoadTextures(TSTRING path);
	void Render(TSTRING name, VECTOR3& archPos, float showWidth, float showHeight, VECTOR3& imagePos, float imageWidth, float imageHeight);
	
	~CTextureManager();
};

