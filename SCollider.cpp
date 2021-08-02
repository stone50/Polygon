#define _USE_MATH_DEFINES
#include "SCollider.h"

void SCollider::UpdateMidpoint() {
	Midpoint = SPoint(0.0, 0.0);
	for (SPoint point : Points) {
		Midpoint += point;
	}
	Midpoint /= (float)Points.size();
}

SCollider::SCollider(
	std::vector<SPoint> points,
	std::map<std::string, std::any> members
) :
	Points(points),
	Members(members)
{
	UpdateMidpoint();
}

#pragma region general functions
SPoint* SCollider::AddPoint(SPoint point) {
	Points.push_back(point);

	UpdateMidpoint();

	return &Points.back();
}

SPoint* SCollider::InsertPoint(SPoint point, int index) {
	if (index < 0 || index >(int)Points.size()) {
		return nullptr;
	}
	Points.emplace(Points.begin() + index, point);

	UpdateMidpoint();

	return &Points.at(index);
}

SPoint* SCollider::SetPoint(SPoint* point1, SPoint point2) {
	int index = GetIndexOfPoint(point1);
	if (index == -1) {
		return nullptr;
	}
	Points.at(index) = point2;

	UpdateMidpoint();

	return &Points.at(index);
}

SPoint* SCollider::SetPoint(int index, SPoint point) {
	if (index < 0 || index > (int)Points.size()) {
		return nullptr;
	}
	Points.at(index) = point;

	UpdateMidpoint();

	return &Points.at(index);
}

SPoint* SCollider::GetPointAt(int index) {
	return &Points.at(index);
}

int SCollider::GetIndexOfPoint(SPoint* point) {
	for (int i = 0; i < (int)Points.size(); i++) {
		if (&Points.at(i) == point) {
			return i;
		}
	}
	return -1;
}

bool SCollider::DeletePoint(SPoint* point) {
	int index = GetIndexOfPoint(point);
	if (index == -1) {
		return false;
	}
	Points.erase(Points.begin() + index);

	UpdateMidpoint();

	return true;
}

bool SCollider::DeletePointAt(int index) {
	if (index < 0 || index > (int)Points.size()) {
		return false;
	}
	Points.erase(Points.begin() + index);

	UpdateMidpoint();

	return true;
}

int SCollider::GetPointsSize() {
	return Points.size();
}

/*
* returns true if the given point is within the polygon
* A ray drawn from the given point in any direction will intersect the boundaries of the polygon an odd number of times if the point is within the polygon.
* In this case, the ray is pointing up.
* If the ray is tangent to the boundaries of the polygon, it does not count as an intersection.
*/
bool SCollider::Contains(SPoint point) {
	int intersections = 0;
	int points = Points.size();
	for (int i = 0; i < points; i++) {
		SPoint* pPrev = &Points.at((i + points - 1) % points);
		SPoint* p = &Points.at(i);
		SPoint* pNext = &Points.at((i + 1) % points);

		//check for tangency
		if (*point.GetX() == *p->GetX()) {
			//test if p and pNext are on either side of the point
			if (std::min(*pPrev->GetX(), *pNext->GetX()) < *point.GetX() && std::max(*pPrev->GetX(), *pNext->GetX()) > *point.GetX()) {
				intersections++;
			}
		}
		else {
			/*
			* test if the x coordinate of the point is between the x coordinates of p and pNext
			* Only one side is inclusive to ensure edge cases are dealt with properly.
			*/
			if (std::min(*p->GetX(), *pNext->GetX()) <= *point.GetX() && std::max(*p->GetX(), *pNext->GetX()) > *point.GetX()) {

				//test if the y coordinate of where the ray and the line segment between p and pNext cross is above the point
				if ((((*p->GetY() - *pNext->GetY()) / (*p->GetX() - *pNext->GetX())) * (*point.GetX() - *p->GetX())) - *p->GetY() > *point.GetY()) {
					intersections++;
				}
			}
		}
	}
	return intersections % 2 == 1;
}

/*
* A collision occurs when either of two conditions is met:
*	1. A vertex of one polygon is contained by the other polygon
*	2. Any of the sides intersect
*/
bool SCollider::Collides(SCollider other) {
	//check condition 1
	for (SPoint point : *other.GetPoints()) {
		if (other.Contains(point)) {
			return true;
		}
	}
	for (SPoint point : *other.GetPoints()) {
		if (Contains(point)) {
			return true;
		}
	}

	/*
	* check condition 2
	* loop through the points of the current polygon
	*/
	int points = Points.size();
	int otherPoints = other.Points.size();
	for (int currentIndex = 0; currentIndex < points; currentIndex++) {
		SPoint* pCur = &Points.at(currentIndex);
		SPoint* pCurNext = &Points.at((currentIndex + 1) % points);

		//loop through the points of the other polygon
		for (int otherIndex = 0; otherIndex < otherPoints; otherIndex++) {
			SPoint* pOth = &other.Points.at(otherIndex);
			SPoint* pOthNext = &other.Points.at((otherIndex + 1) % points);

			//find the point of intersection between the lines made by pCur to pCurNext and pOth to pOthNext
			float t1 = *pOthNext->GetX() - *pOth->GetX();
			float t2 = *pCurNext->GetX() - *pCur->GetX();
			float t3 = *pOthNext->GetY() - *pOth->GetY();
			float t4 = *pCurNext->GetY() - *pCur->GetY();
			float t5 = (*pCurNext->GetX() * *pCur->GetY()) - (*pCur->GetX() * *pCurNext->GetY());
			float t6 = *pOthNext->GetX() * *pOth->GetY();
			float t7 = *pOth->GetX() * *pOthNext->GetY();
			float denom = (t2 * t3) - (t1 * t4);
			SPoint intersection = SPoint(
				((t5 * t1) - ((t6 - t7) * t2)) / denom,
				((t5 * t3) + ((t6 + t7) * t4)) / denom
			);

			//test if the point of intersection is on the boundaries of the polygons
			if (*intersection.GetX() > std::max(std::min(*pCur->GetX(), *pCurNext->GetX()), std::min(*pOth->GetX(), *pOthNext->GetX())) &&
				*intersection.GetX() < std::min(std::max(*pCur->GetX(), *pCurNext->GetX()), std::max(*pOth->GetX(), *pOthNext->GetX())) &&
				*intersection.GetY() > std::max(std::min(*pCur->GetY(), *pCurNext->GetY()), std::min(*pOth->GetY(), *pOthNext->GetY())) &&
				*intersection.GetY() < std::min(std::max(*pCur->GetY(), *pCurNext->GetY()), std::max(*pOth->GetY(), *pOthNext->GetY()))) {
				return true;
			}
		}
	}
	return false;
}

void SCollider::Scale(float scale) {
	for (SPoint point : Points) {
		point.SetX(*Midpoint.GetX() + ((*point.GetX() - *Midpoint.GetX()) * scale));
		point.SetY(*Midpoint.GetY() + ((*point.GetY() - *Midpoint.GetY()) * scale));
	}
}

void SCollider::Rotate(float angle) {
	Translate(-Midpoint);
	for (SPoint point : Points) {
		point.SetX(*point.GetX() * (float)cos(angle) + *point.GetY() * (float)sin(angle));
		point.SetY(*point.GetY() * (float)cos(angle) - *point.GetX() * (float)sin(angle));
	}
	Translate(Midpoint);
}

void SCollider::RotateAround(float angle, SPoint point) {
	Translate(-point);
	for (SPoint point : Points) {
		point.SetX(*point.GetX() * (float)cos(angle) + *point.GetY() * (float)sin(angle));
		point.SetY(*point.GetY() * (float)cos(angle) - *point.GetX() * (float)sin(angle));
	}
	Translate(point);
}

void SCollider::Translate(SPoint point) {
	for (SPoint p : Points) {
		p += point;
	}
	Midpoint += point;
}

void SCollider::TranslateTo(SPoint point) {
	Translate(point - Midpoint);
}

std::any* SCollider ::GetMember(std::string name) {
	return &Members[name];
}

std::any* SCollider::SetMember(std::string name, std::any value) {
	Members[name] = value;
	return &Members[name];
}
#pragma endregion

#pragma region getters
std::vector<SPoint>* SCollider::GetPoints() {
	return &Points;
}

SPoint* SCollider::GetMidpoint() {
	return &Midpoint;
}
#pragma endregion

#pragma region setters
std::vector<SPoint>* SCollider::SetPoints(std::vector<SPoint> points) {
	Points = points;

	UpdateMidpoint();

	return &Points;
}
#pragma endregion