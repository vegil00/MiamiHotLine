#pragma once
enum imageType { STATIC = 0, ANIMATION=1 };
class CTexture
{
private:
	GLint width;
	GLint height;
	imageType m_type;
	UINT textureId;
	int row;
	int col;
	int cur_row;
	int cur_col;
	float changeTime;
	float pre_time;
	
public:
	CTexture();
	CTexture(UINT width, UINT height, UINT texID,imageType type,int r,int c);
	void Render(VECTOR3 archPos,VECTOR3 rotate,float degree,float showWidth,float showHeight,VECTOR3& imagePos,float imageWidth,float imageHeight);
	UINT getId() { return textureId; }
	GLint getWidth() { return width; }
	GLint getHeight() { return height; }
	int getRow() { return row; }
	int getCol() { return col; }
	CTexture(char* path);
	void Render(VECTOR3 archPos, VECTOR3 rotate, float degree, float showWidth, float showHeight, int r, int c);
	void Render(VECTOR3 archPos, VECTOR3 rotate, float degree, float showWidth, float showHeight);
	void update();
	void setShowPos(int r, int c);
	void setchangeTime(float time) { changeTime = time; }
	~CTexture();
};

