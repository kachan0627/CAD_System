#pragma once
#include "Shape.h"

typedef struct VePoint {
	float x;
	float y;
	float z;
}VEPOINT;

class CVector
{
public:
	CVector();
	CVector(float sx, float sy, float ex, float ey);
	CVector(float sx, float sy, float sz, float ex, float ey, float ez);
	CVector(CVertex *s, CVertex *e);
	~CVector();
private:
	VEPOINT Start;
	VEPOINT End;
	float x;
	float y;
	float z;
public:
	void SetStartPoint(float sx, float sy);
	void GetStartPoint(float *sx, float *sy);
	void SetEndPoint(float ex, float ey);
	void GetEndPoint(float *ex, float *ey);
	float GetX();
	float GetY();
	float GetZ();
	void SetStartPoint(CVertex *v);
	void SetEndPoint(CVertex *v);
};

