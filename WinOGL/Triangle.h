#pragma once
typedef struct TPoint {
	float x;
	float y;
}TPOINT;

class CTriangle
{
public:
	CTriangle();
	CTriangle(float ax, float ay, float bx, float by, float cx, float cy);
	~CTriangle();
private:
	CTriangle *Next_Triangle;
	TPOINT A;
	TPOINT B;
	TPOINT C;
public:
	void SetNextTriangle(CTriangle *nt);
	CTriangle *GetNextTriangle();
	float GetX(int n);
	float GetY(int n);
};