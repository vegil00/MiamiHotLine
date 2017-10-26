
#include "Matrix.h"



CMatrix::CMatrix()
{
}

CMatrix::CMatrix(int r, int c)
{
	row = r;
	col = c;
	data = new int*[row];
	for (int i = 0; i < row; i++)
	{
		data[i] = new int[col];
		for (int j = 0; j < col; j++)
		{
			if (i == j)
				data[i][j] = 1;
			else
				data[i][j] = 0;
		}
	}
}


CMatrix CMatrix::operator=(CMatrix matrix)
{
	row = matrix.row; 
	col = matrix.col;
	data = new int*[row];
	

		for (int i = 0; i < row; i++)
		{
			data[i] = new int[col];
			for (int j = 0; j < col; j++)
			{
				data[i][j] = matrix.data[i][j];
			}
		}
	
	return *this;
}

CMatrix CMatrix::operator+(CMatrix matrix)
{
	if (matrix.row == row&&matrix.col == col)
	{
		CMatrix temp = CMatrix(row, col);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				temp.data[i][j] = data[i][j]+matrix.data[i][j];
			}
		}
		return temp;
	}
	
}

CMatrix CMatrix::operator-(CMatrix matrix)
{
	if (matrix.row == row&&matrix.col == col)
	{
		CMatrix temp = CMatrix(row, col);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				temp.data[i][j] = data[i][j] + matrix.data[i][j];
			}
		}
		return temp;
	}
	
}

CMatrix CMatrix::operator*(CMatrix matrix)
{
	if (col == matrix.row)
	{
		CMatrix temp = CMatrix(row, matrix.col);
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				int value=0;
				for (int k = 0; k < col; k++)
				{
					
						value += data[i][k] * matrix.data[k][j];
					
					
				}
				temp.data[i][j] = value;
			}
		}
		return temp;
	}
	
}

CMatrix::~CMatrix()
{
}
