#pragma once

#include "Shape.h"
#include "Vector.h"
#include "math.h"
class CACMath
{
public:
	CACMath();
	~CACMath();
	float Angle(float Px, float Py, float Ax, float Ay, float Bx, float By);
	float CrossProduct(CVector A, CVector B);
	void CrossProduct3(CVector A, CVector B, float *i, float *j, float *k);
	float DotProduct(CVector A, CVector B);
	float Point_PointDistance(float ax, float ay, float bx, float by);
	float Point_LineDistance(float Ax, float Ay, float Bx, float By, float Px, float Py);
	void Perpendicular(float per[2], float Px, float Py, float Ax, float Ay, float Bx, float By);
	bool Check_Point_Line(float px, float py, float ax, float ay, float bx, float by);
	void NormalVector(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz, float *i, float *j, float *k);
};

