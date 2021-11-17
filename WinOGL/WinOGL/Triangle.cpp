#include "stdafx.h"
#include "Triangle.h"


CTriangle::CTriangle()
{
}

CTriangle::CTriangle(float ax, float ay, float bx, float by, float cx, float cy)
{
	A.x = ax;
	A.y = ay;
	B.x = bx;
	B.y = by;
	C.x = cx;
	C.y = cy;
}

CTriangle::~CTriangle()
{
}


void CTriangle::SetNextTriangle(CTriangle *nt)
{
	Next_Triangle = nt;
}


CTriangle *CTriangle::GetNextTriangle()
{
	return Next_Triangle;
}

float CTriangle::GetX(int n)
{
	if (n == 1) {
		return A.x;
	}
	else if (n == 2) {
		return B.x;
	}
	else if (n == 3){
		return C.x;
	}

	return 0;
}


float CTriangle::GetY(int n)
{
	if (n == 1) {
		return A.y;
	}
	else if (n == 2) {
		return B.y;
	}
	else if (n == 3){
		return C.y;
	}

	return 0;
}
