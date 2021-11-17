#pragma once

#include "Shape.h"
#include "ACMath.h"
#include <gl/GL.h>

typedef struct DPoint {
	float x;
	float y;
}DPOINT;

class CACDraw
{
public:
	CACDraw();
	~CACDraw();
	CACMath ACM;
	bool WhichShape(CShape *s);
public:
	void Draw(CShape *s);
	void DrawShape(CShape *s, GLfloat size, GLfloat width, GLfloat R, GLfloat G, GLfloat B);
	void DrawLine(CShape *s, CVertex *v, GLfloat size, GLfloat width, GLfloat R, GLfloat G, GLfloat B);
	void DrawPoint(CVertex *v, GLfloat size, GLfloat R, GLfloat G, GLfloat B);
	void DrawPoint(float x, float y, GLfloat size, GLfloat R, GLfloat G, GLfloat B);
	void DrawDotLine(CVertex *v, float x, float y, GLfloat size, GLfloat width, GLfloat R, GLfloat G, GLfloat B);
	void DrawBB(CShape *s, GLfloat size, GLfloat width, GLfloat R, GLfloat G, GLfloat B);
	void DrawColor(CShape *s);
	void DrawXYZ();
	void DrawXYZ(int n);

	bool Judge1(CShape *s, CVertex *StartV, CVertex *EndV);
	bool Judge2(CShape *s, CVertex *StartV, CVertex *EndV);
	bool CheckPoint(DPOINT p, DPOINT q);
	void GetTrianglePoint(CShape *s);
	void DrawColor(CShape *s, float R, float G, float B);
};

