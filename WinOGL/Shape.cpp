#include "stdafx.h"
#include "Shape.h"

CShape::CShape()
: VertexCount(0)
, ClosedFlag(false)
{
	Color[0] = 1;
	Color[1] = 1;
	Color[2] = 1;
}

CShape::~CShape()
{
}

void CShape::SetNextShape(CShape *pn)
{
	Next_shape = pn;
}

CShape *CShape::GetNextShape(void)
{
	return Next_shape;
}

void CShape::AppendVertex(float px, float py)
{
	CVertex *V1 = new CVertex(px, py);
	V1->SetNextVertex(vertex_head);
	vertex_head = V1;
	VertexCount++;
}

void CShape::FreeVertex(void)
{
	for (CVertex *tmp = vertex_head; vertex_head != NULL;) {
		tmp = tmp->GetNextVertex();
		delete vertex_head;
		vertex_head = tmp;
	}
}

CVertex* CShape::GetVertexhead(void)
{
	return vertex_head;
}

CVertex* CShape::GetVertexheadT(void)
{
	CVertex *v = GetVertexhead();
	if (!v->GetThroughFlag())
	{
		return v;
	}
	else
	{
		v = GetNextVertexLoopT(v);
		return v;
	}
}


//Shapeに格納されているVertexの数を返す
int CShape::GetVertexCount()
{
	return VertexCount;
}

//ClosedFlagを返す
bool CShape::GetClosedFlag(void)
{
	return ClosedFlag;
}

//ClosedFlagを変更する
void CShape::SetClosedFlag(bool b)
{
	ClosedFlag = b;
}

//点を追加する
void CShape::AddVertex(float px, float py, CVertex *LastV)
{
	CVertex *V1 = new CVertex(px, py);
	V1->SetNextVertex(LastV->GetNextVertex());
	LastV->SetNextVertex(V1);
	VertexCount++;
}

void CShape::preAddVertex(CVertex *NewV, CVertex *LastV)
{
	NewV->SetNextVertex(LastV->GetNextVertex());
	LastV->SetNextVertex(NewV);
	VertexCount++;
}

//点を削除する
void CShape::DeleteVertex(CVertex *NowV)
{
	CVertex *LastV = GetLastVertex(NowV);

	//消す点が始点の場合
	if (NowV->GetNextVertex() == NULL) {
		LastV->SetNextVertex(NULL);
	}
	//消す点が終点の場合
	else if (LastV == NULL) {
		vertex_head = NowV->GetNextVertex();
	}
	//それ以外の場合
	else {
		LastV->SetNextVertex(NowV->GetNextVertex());
	}

	delete NowV;
	VertexCount--;
}

//１つ前のVertexを返す（ただしNowV == vertex_headならNULLを返す）
CVertex* CShape::GetLastVertex(CVertex *NowV)
{
	if (NowV == vertex_head) {
		return NULL;
	}

	CVertex *LastV = vertex_head;
	while (LastV != NULL) {
		if (LastV->GetNextVertex() != NULL) {
			if (LastV->GetNextVertex() == NowV) {
				return LastV;
			}
		}
		else {
			return LastV;
		}

		LastV = LastV->GetNextVertex();
	}
	return NULL;
}

//ループするGetNextVertex（基本的にNULLにならないので注意）
CVertex* CShape::GetNextVertexLoop(CVertex* v)
{
	if (v->GetNextVertex() != NULL) {
		return v->GetNextVertex();
	}
	else
	{
		return vertex_head;
	}

	return NULL;
}

//ループするGetNextVertex（基本的にNULLにならないので注意）
//ThroughFlagもチェックする
CVertex* CShape::GetNextVertexLoopT(CVertex* v)
{
	v = GetNextVertexLoop(v);

	//ThroughFlag == falseの場合
	if (!v->GetThroughFlag())
	{
		return v;
	}
	//ThroughFlag == trueの場合
	else
	{
		for (int j = 0; j < GetVertexCount(); j++) {
			if (!v->GetThroughFlag()) break;
			v = GetNextVertexLoop(v);
			if (j == GetVertexCount()) { return NULL; }
		}
		return v;
	}

	return NULL;
}

//ループするGetLastVertex（基本的にNULLにならないので注意）
CVertex* CShape::GetLastVertexLoop(CVertex *NowV)
{
	if (NowV == vertex_head) {
		CVertex *v = vertex_head;
		for (int i = 0; i < VertexCount - 1; i++) {
			v = v->GetNextVertex();
		}
		return v;
	}
	else {
		CVertex *LastV = vertex_head;
		while (LastV != NULL) {
			if (LastV->GetNextVertex() != NULL) {
				if (LastV->GetNextVertex() == NowV) {
					return LastV;
				}
			}
			else {
				return LastV;
			}

			LastV = LastV->GetNextVertex();
		}
	}

	return NULL;
}

//ループするGetLastVertex（基本的にNULLにならないので注意）
//ThroughFlagもチェックする
CVertex* CShape::GetLastVertexLoopT(CVertex *NowV)
{
	CVertex *v = GetLastVertexLoop(NowV);

	//ThroughFlag == falseの場合
	if (!v->GetThroughFlag())
	{
		return v;
	}
	//ThroughFlag == trueの場合
	else
	{
		for (int j = 0; j < GetVertexCount(); j++) {
			if (!v->GetThroughFlag()) break;
			v = GetLastVertexLoop(v);
			if (j == GetVertexCount()) { return NULL; }
		}
		return v;
	}

	return NULL;
}


//消してしまわないDeleteVertex
void CShape::preDeleteVertex(CVertex *NowV)
{
	CVertex *LastV = GetLastVertex(NowV);

	//消す点が始点の場合
	if (NowV->GetNextVertex() == NULL) {
		LastV->SetNextVertex(NULL);
	}
	//消す点が終点の場合
	else if (LastV == NULL) {
		vertex_head = NowV->GetNextVertex();
	}
	//それ以外の場合
	else {
		LastV->SetNextVertex(NowV->GetNextVertex());
	}

	VertexCount--;
}

void CShape::GetMinMax()
{
	CVertex *v = vertex_head;
	float MinX = v->GetX();
	float MaxX = v->GetX();
	float MinY = v->GetY();
	float MaxY = v->GetY();
	v = v->GetNextVertex();

	while (v != NULL) {
		if (MinX > v->GetX()) {
			MinX = v->GetX();
		}
		if (MaxX < v->GetX()) {
			MaxX = v->GetX();
		}
		if (MinY > v->GetY()) {
			MinY = v->GetY();
		}
		if (MaxY < v->GetY()) {
			MaxY = v->GetY();
		}
		v = v->GetNextVertex();
	}

	BB1 = { MinX, MaxY };
	BB2 = { MaxX, MaxY };
	BB3 = { MaxX, MinY };
	BB4 = { MinX, MinY };
	CenterPoint.x = (MaxX - MinX) / 2 + MinX;
	CenterPoint.y = (MaxY - MinY) / 2 + MinY;
}

float CShape::GetBBPointX(int n)
{
	if (ChangeBBFlag == false) {
		GetMinMax();
	}

	if (n == 1) {
		return BB1.x;
	}
	else if (n == 2) {
		return BB2.x;
	}
	else if (n == 3) {
		return BB3.x;
	}
	else if (n == 4) {
		return BB4.x;
	}
	
	return 0;
}

float CShape::GetBBPointY(int n)
{
	if (ChangeBBFlag == false) {
		GetMinMax();
	}

	if (n == 1) {
		return BB1.y;
	}
	else if (n == 2) {
		return BB2.y;
	}
	else if (n == 3) {
		return BB3.y;
	}
	else if (n == 4) {
		return BB4.y;
	}

	return 0;
}

void CShape::ChangeBBPoint(int n, float x, float y)
{
	if (n == 1) {
		BB1.x = x;
		BB1.y = y;
	}
	else if (n == 2) {
		BB2.x = x;
		BB2.y = y;
	}
	else if (n == 3) {
		BB3.x = x;
		BB3.y = y;
	}
	else if (n == 4) {
		BB4.x = x;
		BB4.y = y;
	}
	else {
		return;
	}

	ChangeBBFlag = true;
}


void CShape::ClearChangeBBFlag()
{
	ChangeBBFlag = false;
}


float CShape::GetCenterPointX()
{
	return CenterPoint.x;
}


float CShape::GetCenterPointY()
{
	return CenterPoint.y;
}

void CShape::SetColorFlag(bool b)
{
	ColorFlag = b;
}


bool CShape::GetColorFlag()
{
	return ColorFlag;
}


CTriangle* CShape::GetTrianglehead()
{
	return triangle_head;
}


void CShape::AppendTriangle(float ax, float ay, float bx, float by, float cx, float cy)
{
	CTriangle *T1 = new CTriangle(ax, ay, bx, by, cx, cy);
	T1->SetNextTriangle(triangle_head);
	triangle_head = T1;
}


void CShape::FreeTriangle()
{
	for (CTriangle *tmp = triangle_head; triangle_head != NULL;) {
		tmp = tmp->GetNextTriangle();
		delete triangle_head;
		triangle_head = tmp;
	}
}


void CShape::ClearThroughFlag()
{
	CVertex *v = vertex_head;
	while (v != NULL) {
		v->SetThroughFlag(false);
		v = v->GetNextVertex();
	}
}

//個数を返す（ただしThroughFlagが立っているものは除く）
int CShape::GetVertexCountT()
{
	CVertex *v = vertex_head;
	int n = 0;

	while (v != NULL) {
		if (!v->GetThroughFlag()) { n++; }

		v = v->GetNextVertex();
		while (v != NULL) {
			if (!v->GetThroughFlag()) { break; }
			v = v->GetNextVertex();
		}
	}

	return n;
}


void CShape::GetColor(float *r, float *g, float *b)
{
	*r = Color[0];
	*g = Color[1];
	*b = Color[2];
}


void CShape::SetColor(float r, float g, float b)
{
	Color[0] = r;
	Color[1] = g;
	Color[2] = b;
}


void CShape::CloearColor()
{
	Color[0] = 1;
	Color[1] = 1;
	Color[2] = 1;
}
