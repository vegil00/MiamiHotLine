#pragma once
#include<math.h>
class VECTOR3
{
public:
	float x;
	float y;
	float z;
	VECTOR3() { x = 0; y = 0; z = 0; }
	 VECTOR3(VECTOR3 begin, VECTOR3 des);
	 VECTOR3(float x,float y,float z);
	 void operator=(VECTOR3 a);
	 VECTOR3  operator+(VECTOR3 a)
	 {
		 
		 return VECTOR3(x + a.x, y + a.y, z + a.z);
	 }
	 VECTOR3 operator-(VECTOR3 a)
	 {
		
		 return VECTOR3(x - a.x, y - a.y, z - a.z);

	 }
	 bool operator==(VECTOR3 a)
	 {
		 if (this->x == a.x&&this->y == a.y&&this->z == a.z)
			 return true;
		 else
			 return 0;
	 }
	
	 float length() { return sqrtf(x*x + y*y + z*z); }
	 VECTOR3 Normalize();
	 template<class T>
	 VECTOR3 friend operator*(T a, VECTOR3& v)
	 {
		 return VECTOR3((float)a*v.x, (float)a*v.y, (float)a*v.z);
	 }
	 template<class T>
	 VECTOR3 friend operator*(VECTOR3& v,T a)
	 {
		 return VECTOR3((float)a*v.x, (float)a*v.y, (float)a*v.z);
	 }
	 float dot(VECTOR3 a);
	 VECTOR3 cross(VECTOR3 a);
	 VECTOR3 reverse() { return VECTOR3(-this->x,-this->y,-this->z); }
	~VECTOR3();
};


//VECTOR3::VECTOR3(VECTOR3 begin, VECTOR3 des)
//{
//	this->x = des.x - begin.x;
//	this->y = des.y - begin.y;
//	this->z = des.z - begin.z;
//}
//
//VECTOR3::VECTOR3(float x, float y, float z)
//{
//	this->x = x;
//	this->y = y;
//	this->z = z;
//}
//
//void VECTOR3::operator=(VECTOR3 a)
//{
//	this->x = a.x;
//	this->y = a.y;
//	this->z = a.z;
//}
//
//VECTOR3 VECTOR3::Normalize()
//{
//	return VECTOR3(this->x / length(), this->y / length(), this->z / length());
//}
//
//float VECTOR3::dot(VECTOR3 a)
//{
//	return this->x*a.x + this->y*a.y + this->z*a.z;
//}
//
//VECTOR3 VECTOR3::cross(VECTOR3 a)
//{
//	return VECTOR3(this->y*a.z - this->z*a.y, this->z*a.x - this->x*a.z, this->x*a.y - this->y*a.x);
//
//}
//
//VECTOR3::~VECTOR3()
//{
//}
