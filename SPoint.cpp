#include "SPoint.h"

#pragma region operators
SPoint& SPoint::operator+=(SPoint point) {
	X += point.X;
	Y += point.Y;
	return *this;
}

SPoint& SPoint::operator-=(SPoint point) {
	X -= point.X;
	Y -= point.Y;
	return *this;
}

SPoint& SPoint::operator*=(float num) {
	X *= num;
	Y *= num;
	return *this;
}

SPoint& SPoint::operator/=(float num) {
	X /= num;
	Y /= num;
	return *this;
}

SPoint SPoint::operator+(SPoint point) {
	return SPoint(X + point.X, Y + point.Y);
}

SPoint SPoint::operator-(SPoint point) {
	return SPoint(X - point.X, Y - point.Y);
}

SPoint SPoint::operator*(float num) {
	return SPoint(X * num, Y * num);
}

SPoint SPoint::operator/(float num) {
	return SPoint(X / num, Y / num);
}

SPoint SPoint::operator-() {
	return SPoint(-X, -Y);
}
#pragma endregion

SPoint::SPoint(
	float x,
	float y,
	std::map<std::string, std::any> members
) :
	X(x),
	Y(y),
	Members(members)
{}

#pragma region general functions
std::any* SPoint::GetMember(std::string name) {
	return &Members[name];
}

std::any* SPoint::SetMember(std::string name, std::any value) {
	Members[name] = value;
	return &Members[name];
}
#pragma endregion

#pragma region getters
float* SPoint::GetX() {
	return &X;
}

float* SPoint::GetY() {
	return &Y;
}
#pragma endregion

#pragma region setters
float* SPoint::SetX(float x) {
	X = x;
	return &X;
}

float* SPoint::SetY(float y) {
	Y = y;
	return &Y;
}
#pragma endregion