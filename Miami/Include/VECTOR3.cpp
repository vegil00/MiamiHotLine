#include "VECTOR3.h"





VECTOR3::VECTOR3(VECTOR3 begin, VECTOR3 des)
{
	this->x = des.x - begin.x;
	this->y= des.y - begin.y;
	this->z = des.z - begin.z;
}

VECTOR3::VECTOR3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void VECTOR3::operator=(VECTOR3 a)
{
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
}

VECTOR3 VECTOR3::Normalize()
{
	return VECTOR3(this->x / length(), this->y / length(), this->z / length());
}

float VECTOR3::dot(VECTOR3 a)
{
	return this->x*a.x + this->y*a.y + this->z*a.z;
}

VECTOR3 VECTOR3::cross(VECTOR3 a)
{
	return VECTOR3(this->y*a.z-this->z*a.y,this->z*a.x-this->x*a.z,this->x*a.y-this->y*a.x);

}

VECTOR3::~VECTOR3()
{
}
