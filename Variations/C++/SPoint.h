#pragma once

#include <string>
#include <map>
#include <any>

class SPoint
{
	float X;									//x value
	float Y;									//y value
	std::map<std::string, std::any> Members;	//additional members

public:
#pragma region operators
	SPoint& operator+=(SPoint point);	//adds 'point' to this
	SPoint& operator-=(SPoint point);	//subtracts 'point' from this
	SPoint& operator*=(float num);		//multiplies 'num' to this
	SPoint& operator/=(float num);		//divides 'num' from this
	SPoint operator+(SPoint point);		//adds 'point' and this
	SPoint operator-(SPoint point);		//subtracts 'point' and this
	SPoint operator*(float num);		//multiplies 'num' and this
	SPoint operator/(float num);		//divides 'num' and this
	SPoint operator-();					//subtracts 0 and this
#pragma endregion

	SPoint(
		float x = 0,
		float y = 0,
		std::map<std::string, std::any> members = std::map<std::string, std::any>()
	);

#pragma region general functions

	//Returns a pointer to member 'name'
	std::any* GetMember(std::string name);

	//Assigns member 'name' to 'value'
	//Returns a pointer to member 'name'
	std::any* SetMember(std::string name, std::any value);
#pragma endregion

#pragma region getters

	//Returns a pointer to 'X'
	float* GetX();

	//Returns a pointer to 'Y'
	float* GetY();
#pragma endregion

#pragma region setters

	//Assigns 'X' to 'x'
	//Returns a pointer to 'X'
	float* SetX(float x);

	//Assigns 'Y' to 'y'
	//Returns a pointer to 'Y'
	float* SetY(float y);
#pragma endregion
};
