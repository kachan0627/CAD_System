#include "stdafx.h"
#include "Vector.h"
#include "Shape.h"

CVector::CVector()
: x(0)
, y(0)
{
}

CVector::CVector(float sx, float sy, float ex, float ey)
{
	Start.x = sx;
	Start.y = sy;
	End.x = ex;
	End.y = ey;
}

CVector::CVector(float sx, float sy, float sz, float ex, float ey, float ez)
{
	Start.x = sx;
	Start.y = sy;
	Start.z = sz;
	End.x = ex;
	End.y = ey;
	End.z = ez;
}

CVector::CVector(CVertex *s, CVertex *e)
{
	s->GetXY(&Start.x, &Start.y);
	e->GetXY(&End.x, &End.y);
}

CVector::~CVector()
{
}


void CVector::SetStartPoint(float sx, float sy)
{
	Start.x = sx;
	Start.y = sy;
}


void CVector::GetStartPoint(float *sx, float *sy)
{
	*sx = Start.x;
	*sy = Start.y;
}

void CVector::SetEndPoint(float ex, float ey)
{
	End.x = ex;
	End.y = ey;
}

void CVector::GetEndPoint(float *ex, float *ey)
{
	*ex = End.x;
	*ey = End.y;
}

float CVector::GetX()
{
	return End.x - Start.x;
}


float CVector::GetY()
{
	return End.y - Start.y;
}

float CVector::GetZ()
{
	return End.z - Start.z;
}

void CVector::SetStartPoint(CVertex *v)
{
	Start.x = v->GetX();
	Start.y = v->GetY();
}

void CVector::SetEndPoint(CVertex *v)
{
	End.x = v->GetX();
	End.y = v->GetY();
}


