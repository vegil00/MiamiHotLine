#include"stdafx.h"
//wstring CU_A2U(string& str)
//{
//	int size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
//	wstring wstr;
//	wstr.resize(size);
//	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wstr[0], size);
//	return wstr;
//}
//string CU_U2A(wstring& wstr)
//{
//	int size = wstr.size();
//	string str;
//	str.resize(size);
//	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), -1, &str[0], size, 0, 0);
//	return str;
//}