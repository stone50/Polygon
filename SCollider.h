#pragma once

#include <vector>
#include "SPoint.h"

class SCollider
{
	std::vector<SPoint> Points;					//list of vertices
	SPoint Midpoint;							//average of all vertices
	std::map<std::string, std::any> Members;	//additional members

	void UpdateMidpoint();

public:
	SCollider(
		std::vector<SPoint> points = std::vector<SPoint>(),
		std::map<std::string, std::any> members = std::map<std::string, std::any>()
	);

#pragma region general functions

	//Adds 'point' to the end of 'Points'
	//Returns a pointer to the point
	SPoint* AddPoint(SPoint point);

	//Adds 'point' to 'Points' at 'index'
	//Returns a pointer to the point -- Returns nullptr if 'index' is out of range
	SPoint* InsertPoint(SPoint point, int index);

	//Assigns the point at 'point1' to 'point2'
	//Returns a pointer to the point -- Returns nullptr if 'Points' does not contain the point at 'point1'
	SPoint* SetPoint(SPoint* point1, SPoint point2);

	//Assigns the point at 'index' to 'point'
	//Returns a pointer to the point -- Returns nullptr if 'index' is out of range
	SPoint* SetPoint(int index, SPoint point);

	//Returns a pointer to the point at 'index' -- Returns nullptr if 'index' is out of range
	SPoint* GetPointAt(int index);

	//Returns the index of the point at 'point' -- Returns -1 if 'Points' does not contain the point at 'point'
	int GetIndexOfPoint(SPoint* point);

	//Removes the point at 'point'
	//Returns true -- Returns false if 'Points' does not contain the point at 'point'
	bool DeletePoint(SPoint* point);

	//Removes the point at 'index'
	//Returns true -- Returns false if 'index' is out of range
	bool DeletePointAt(int index);

	//Returns the size of 'Points'
	int GetPointsSize();

	//Returns true if 'point' is inside this collider, otherwise returns false
	bool Contains(SPoint point);

	//Returns true if 'collider' collides with this collider, otherwise returns false
	bool Collides(SCollider collider);

	//Scales the collider by 'scale'
	void Scale(float scale);

	//Rotates the collider counterclockwise by 'angle' around 'Midpoint'
	void Rotate(float angle);

	//Rotates the collider counterclockwise by 'angle' around 'point'
	void RotateAround(float angle, SPoint point);

	//Translates the polyogn by 'point'
	void Translate(SPoint point);

	//Translates the collider so that the value of 'Midpoint' is the same value of 'point'
	void TranslateTo(SPoint point);

	//Returns a pointer to member 'name'
	std::any* GetMember(std::string name);

	//Assigns member 'name' to 'value'
	//Returns a pointer to member 'name'
	std::any* SetMember(std::string name, std::any value);
#pragma endregion

#pragma region getters

	//Returns 'Points'
	std::vector<SPoint>* GetPoints();

	//Returns 'Midpoint'
	SPoint* GetMidpoint();
#pragma endregion

#pragma region setters

	//Assigns 'Points' to 'points'
	//Returns a pointer to 'Points'
	std::vector<SPoint>* SetPoints(std::vector<SPoint> points);
#pragma endregion
};