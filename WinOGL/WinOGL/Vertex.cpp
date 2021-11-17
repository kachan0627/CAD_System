#include "stdafx.h"
#include "Vertex.h"

CVertex::CVertex()
{
}

CVertex::CVertex(float px, float py)
{
	SetX(px);
	SetY(py);
}

CVertex::~CVertex()
{
}


void CVertex::SetX(float px)
{
	x = px;
}


float CVertex::GetX(void)
{
	return x;
}

void CVertex::GetX(float *nx)
{
	*nx = x;
}

void CVertex::SetY(float py)
{
	y = py;
}


float CVertex::GetY(void)
{
	return y;
}

void CVertex::GetY(float *ny)
{
	*ny = y;
}

void CVertex::SetNextVertex(CVertex *pn)
{
	Next_Vertex = pn;
}

CVertex *CVertex::GetNextVertex(void)
{
	return Next_Vertex;
}

void CVertex::GetXY(float xy[2])
{
	xy[0] = x;
	xy[1] = y;
}

void CVertex::GetXY(float *nx, float *ny)
{
	*nx = x;
	*ny = y;
}

void CVertex::SetThroughFlag(bool b)
{
	ThroughFlag = b;
}


bool CVertex::GetThroughFlag()
{
	return ThroughFlag;
}
