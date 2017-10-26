#pragma once
class CMatrix
{
public:
	int row;
	int col;
	int** data;
	CMatrix();
	CMatrix(int r, int c);
	void setValue(int r, int c, int value) { data[r][c] = value; }
	CMatrix operator=(CMatrix matrix);
	CMatrix operator+(CMatrix matrix);
	CMatrix operator-(CMatrix matrix);
	CMatrix operator*(CMatrix matrix);
	~CMatrix();
};

