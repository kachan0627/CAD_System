#include "stdafx.h"
#include "ACMath.h"
#include "Vector.h"

CACMath::CACMath()
{
}


CACMath::~CACMath()
{
}

//A-PとB-Pから成る線分（P周り）の角度を返す
float CACMath::Angle(float Px, float Py, float Ax, float Ay, float Bx, float By)
{
	CVector a(Px, Py, Ax, Ay), b(Px, Py, Bx, By);

	float AcrossB = CrossProduct(a, b);
	int Z = 1;
	if (AcrossB < 0) {
		AcrossB = fabsf(AcrossB);
		Z = -1;
	}
	float AdotB = DotProduct(a, b);

	return atan2f(AcrossB, AdotB) * Z;
}

//外積を返す（引数は2つのベクトルの値）
float CACMath::CrossProduct(CVector A, CVector B)
{
	float ca;
	float tmp;

	ca  = A.GetX() * B.GetY();
	tmp = A.GetY() * B.GetX();
	ca = ca - tmp;

	return ca;
}

//外積を返す（z軸有り）
void CACMath::CrossProduct3(CVector A, CVector B, float *i, float *j, float *k)
{
	float tmp;

	*i = A.GetY() * B.GetZ();
	tmp = A.GetZ() * B.GetY();
	*i = *i - tmp;

	*j = A.GetZ() * B.GetX();
	tmp = A.GetX() * B.GetZ();
	*j = *j - tmp;

	*k = A.GetX() * B.GetY();
	tmp = A.GetY() * B.GetX();
	*k = *k - tmp;
}


//内積を返す（引数は2つのベクトルの値（終点 - 始点の値））
float CACMath::DotProduct(CVector A, CVector B)
{
	float tmp1, tmp2;
	tmp1 = A.GetX() * B.GetX();
	tmp2 = A.GetY() * B.GetY();

	return tmp1 + tmp2;
}

//2点間の距離を返す
float CACMath::Point_PointDistance(float ax, float ay, float bx, float by)
{
	float dis;

	dis = sqrt(pow(ax - bx, 2) + pow(ay - by, 2));

	return dis;
}

//点と直線の距離を返す
float CACMath::Point_LineDistance(float Px, float Py, float Ax, float Ay, float Bx, float By)
{
	CVector a(Ax, Ay, Bx, By), b(Ax, Ay, Px, Py);

	float sinab = fabsf(CrossProduct(a, b));
	float dis = (pow(Ax - Bx, 2) + pow(Ay - By, 2));
	sinab = sinab / dis;
	return Point_PointDistance(Ax, Ay, Px, Py) * sinab;
}

//直線と、点を通る垂線とが交差する点を返す
void CACMath::Perpendicular(float per[2], float Px, float Py, float Ax, float Ay, float Bx, float By)
{
	CVector a(Ax, Ay, Bx, By), b(Ax, Ay, Px, Py);
	CVector s(Ax, Ay, Bx, By);

	float d = DotProduct(a, b) / Point_PointDistance(Ax, Ay, Bx, By);
	per[0] = { d / Point_PointDistance(Ax, Ay, Bx, By) * s.GetX() + Ax };
	per[1] = { d / Point_PointDistance(Ax, Ay, Bx, By) * s.GetY() + Ay };
}

//点が線分の範囲内にあるかどうかの判定
bool CACMath::Check_Point_Line(float px, float py, float ax, float ay, float bx, float by)
{
	if (Point_PointDistance(px, py, ax, ay) <= Point_PointDistance(ax, ay, bx, by) &&
		Point_PointDistance(px, py, bx, by) <= Point_PointDistance(ax, ay, bx, by))
	{
		return true;
	}

	return false;
}

//法線の計算
void CACMath::NormalVector(float ax, float ay, float az, float bx, float by, float bz, float cx, float cy, float cz, float *i, float *j, float *k)
{
	CVector A = { ax, ay, az, bx, by, bz };
	CVector B = { ax, ay, az, cx, cy, cz };
	float tmp;

	CrossProduct3(A, B, i, j, k);

	if (*i != 0) {
		tmp = fabsf(*i);
		*i = *i / tmp;
	}
	if (*j != 0) {
		tmp = fabsf(*j);
		*j = *j / tmp;
	}
	if (*k != 0) {
		tmp = fabsf(*k);
		*k = *k / tmp;
	}

}
