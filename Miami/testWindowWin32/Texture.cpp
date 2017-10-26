#include"stdafx.h"
#include "Texture.h"



CTexture::CTexture()
{
}

CTexture::CTexture(UINT width, UINT height, UINT texID, imageType type, int r, int c)
{
	this->width = width;
	this->height = height;
	this->textureId = texID;
	m_type = type;
	row = r;
	col = c;
	cur_col = 0;
	cur_row = 0;
	changeTime = 0.25f;
	pre_time = GetTickCount();
}

void CTexture::Render(VECTOR3 archPos, VECTOR3 rotate, float degree, float showWidth, float showHeight, VECTOR3 &imagePos, float imageWidth, float imageHeight)
{
	glEnable(GL_TEXTURE_2D);
	//glColor3f(1.0f, 1.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glPushMatrix();
	
	glTranslatef(archPos.x, archPos.y, archPos.z);
	glRotatef(degree, rotate.x, rotate.y, rotate.z);
	glScalef(showWidth / width, showHeight / height, 1);

	glBegin(GL_QUADS);
	glTexCoord2f(imagePos.x, imagePos.y);
	glVertex3f(-width/2, -height/2, archPos.z);
	glTexCoord2f(imagePos.x, imagePos.y+imageHeight);
	glVertex3f(-width/2, height/2, archPos.z);
	glTexCoord2f(imagePos.x+imageWidth, imagePos.y+ imageHeight);
	glVertex3f(width / 2, height / 2, archPos.z);
	glTexCoord2f(imagePos.x+imageWidth, imagePos.y);
	glVertex3f(width / 2, -height / 2, archPos.z);
	glEnd();
	
	glPopMatrix();
}

CTexture::CTexture(char * path)
{
	GLubyte* pPixelData;
	FILE* file = fopen(path, "r");
	LPBITMAPFILEHEADER fileheader = new BITMAPFILEHEADER;
	LPBITMAPINFOHEADER infoheader = new BITMAPINFOHEADER;
	fread(fileheader, sizeof(BITMAPFILEHEADER), 1, file);
	fread(infoheader, sizeof(BITMAPINFOHEADER), 1, file);
	height = infoheader->biHeight;
	width = infoheader->biWidth;
	int lineLength, totalLength;
	lineLength = width*(infoheader->biBitCount )/ 8;
	while (lineLength % 4 != 0)
		lineLength++;
	totalLength = lineLength*height;
	pPixelData = (GLubyte*)malloc(totalLength);
	fseek(file, 54, SEEK_SET);
	fread(pPixelData, totalLength, 1, file);
	fclose(file);
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pPixelData);
	
	free(pPixelData);
}

void CTexture::Render(VECTOR3 archPos, VECTOR3 rotate, float degree,  float showWidth, float showHeight, int r, int c)
{
	VECTOR3 imagepos = VECTOR3((float)c / (float)col, (float)(row - r - 1) / (float)row, 0);
	//Render(archPos, rotate, degree,  showWidth, showHeight, imagepos, 1.0f / col, 1.0f/ row);
	glEnable(GL_TEXTURE_2D);
	//glColor3f(1.0f, 1.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glPushMatrix();
	glTranslatef(archPos.x, archPos.y, archPos.z);
	glRotatef(degree, rotate.x, rotate.y, rotate.z);
	glScalef(showWidth / width, showHeight / height, 1);
	glBegin(GL_QUADS);
	glTexCoord2f((float)( c ) / col,(float)(row-r-1)/row );
	glVertex3f(-width/2, -height/2, archPos.z);
	glTexCoord2f((float)( c) / col,(float)(row - r ) / row );
	glVertex3f(-width/2,height/2, archPos.z);
	glTexCoord2f( (float)( c+1) / col,(float)(row - r) / row);
	glVertex3f(width / 2, height / 2, archPos.z);
	glTexCoord2f((float)( c + 1) / col,(float)(row - r-1) / row );
	glVertex3f(width / 2,-height / 2, archPos.z);
	glEnd();

	glPopMatrix();
}

void CTexture::Render(VECTOR3  archPos, VECTOR3 rotate, float degree, float showWidth, float showHeight)
{
	Render(archPos, rotate,degree,showWidth, showHeight, cur_row, cur_col);
}

void CTexture::update()
{
	float cur_time = GetTickCount();
	if ((cur_time - pre_time)*0.001f > changeTime)
	{
		pre_time = cur_time;
		cur_col++;
		if (cur_col >= col)
			cur_col = 0;
	}
	
}

void CTexture::setShowPos(int r, int c)
{
	cur_row = r;
	cur_col = c;
}


CTexture::~CTexture()
{
}
