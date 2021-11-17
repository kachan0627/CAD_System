#pragma once
#include "Vertex.h"
#include "Triangle.h"
#include <gl/GL.h>

typedef struct SPoint {
	float x;
	float y;
}SPOINT;

class CShape
{
public:
	CShape();
	~CShape();
private:
	CVertex *vertex_head;
	CTriangle *triangle_head;
	int VertexCount = 0;
	bool ClosedFlag;
	CShape *Next_shape;
	bool ChangeBBFlag = false;
	bool ColorFlag = false;
	SPOINT BB1;
	SPOINT BB2;
	SPOINT BB3;
	SPOINT BB4;
	SPOINT CenterPoint;
	float Color[3];
public:
	void SetNextShape(CShape *pn);
	CShape *GetNextShape(void);
	CVertex* GetLastVertex(CVertex *NowV);
	CVertex* GetLastVertexLoop(CVertex *NowV);
	CVertex* GetLastVertexLoopT(CVertex *NowV);
	CVertex* GetVertexhead(void);
	CVertex* GetVertexheadT(void);
	void AppendVertex(float px, float py);
	void FreeVertex(void);
	int GetVertexCount(void);
	bool GetClosedFlag(void);
	void SetClosedFlag(bool b);
	void AddVertex(float px, float py, CVertex *v);
	void DeleteVertex(CVertex *NowV);
	CVertex* GetNextVertexLoop(CVertex* v);
	CVertex* GetNextVertexLoopT(CVertex* v);
	void preDeleteVertex(CVertex * NowV);
	void preAddVertex(CVertex *New, CVertex *LastV);
	void GetMinMax();
	float GetBBPointX(int n);
	float GetBBPointY(int n);
	void ChangeBBPoint(int n, float x, float y);
	void ClearChangeBBFlag();
	float GetCenterPointX();
	float GetCenterPointY();
	void SetColorFlag(bool b);
	bool GetColorFlag();
	CTriangle* GetTrianglehead();
	void AppendTriangle(float ax, float ay, float bx, float by, float cx, float cy);
	void FreeTriangle();
	void ClearThroughFlag();
	int GetVertexCountT();
	void GetColor(float *r, float *g, float *b);
	void SetColor(float r, float g, float b);
	void CloearColor();
};
