#include "stdafx.h"
#include "ACDraw.h"

CACDraw::CACDraw()
{
}


CACDraw::~CACDraw()
{
}

//図形を描画する（基本形）
void CACDraw::Draw(CShape *s)
{
	DrawShape(s, 5, 1.0, 0.7, 0.7, 0.7);
}

//図形を描画する
void CACDraw::DrawShape(CShape *s, GLfloat size, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
	//閉じた図形の場合
	if (s->GetClosedFlag()) {
		//点の描画
		glColor3f(R, G, B);
		glPointSize(size);
		glBegin(GL_POINTS);
		for (CVertex *v = s->GetVertexhead(); v != NULL; v = v->GetNextVertex()) {
			glVertex2f(v->GetX(), v->GetY());
		}
		glEnd();

		//稜線の描画
		glColor3f(R, G, B);
		glLineWidth(width);
		glBegin(GL_LINE_LOOP);
		for (CVertex *v = s->GetVertexhead(); v != NULL; v = v->GetNextVertex()) {
			glVertex2f(v->GetX(), v->GetY());
		}
		glEnd();
	}
	//開いた図形の場合
	else {
		//点の描画
		glColor3f(R, G, B);
		glPointSize(size);
		glBegin(GL_POINTS);
		for (CVertex *v = s->GetVertexhead(); v != NULL; v = v->GetNextVertex()) {
			glVertex2f(v->GetX(), v->GetY());
		}
		glEnd();

		//稜線の描画
		glColor3f(R, G, B);
		glLineWidth(width);
		glBegin(GL_LINE_STRIP);
		for (CVertex *v = s->GetVertexhead(); v != NULL; v = v->GetNextVertex()) {
			glVertex2f(v->GetX(), v->GetY());
		}
		glEnd();
	}
}

//稜線（と点）を描画する
void CACDraw::DrawLine(CShape *s, CVertex *v, GLfloat size, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
	//点の描画
	CVertex *tmp = v;
	glColor3f(R, G, B);
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(tmp->GetX(), tmp->GetY());
	tmp = s->GetNextVertexLoop(tmp);
	glVertex2f(tmp->GetX(), tmp->GetY());
	glEnd();

	//稜線の描画
	tmp = v;
	glColor3f(R, G, B);
	glLineWidth(width);
	glBegin(GL_LINES);
	glVertex2f(tmp->GetX(), tmp->GetY());
	tmp = s->GetNextVertexLoop(tmp);
	glVertex2f(tmp->GetX(), tmp->GetY());
	glEnd();
}

//点線で稜線（と点）を描画する
void CACDraw::DrawDotLine(CVertex *v, float x, float y, GLfloat size, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
	//点の描画
	glColor3f(R, G, B);
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(v->GetX(), v->GetY());
	glVertex2f(x, y);
	glEnd();

	//稜線の描画
	glColor3f(R, G, B);
	glLineWidth(width);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xF0F0);
	glBegin(GL_LINES);
	glVertex2f(v->GetX(), v->GetY());
	glVertex2f(x, y);
	glEnd();

	glDisable(GL_LINE_STIPPLE);
}

//点を描画する
void CACDraw::DrawPoint(CVertex *v, GLfloat size, GLfloat R, GLfloat G, GLfloat B)
{
	glColor3f(R, G, B);
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(v->GetX(), v->GetY());
	glEnd();
}

//点を描画する
void CACDraw::DrawPoint(float x, float y, GLfloat size, GLfloat R, GLfloat G, GLfloat B)
{
	glColor3f(R, G, B);
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

//点線でBBを描画する
void CACDraw::DrawBB(CShape *s, GLfloat size, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
	//点の描画
	glColor3f(R, G, B);
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(s->GetBBPointX(1), s->GetBBPointY(1));
	glVertex2f(s->GetBBPointX(2), s->GetBBPointY(2));
	glVertex2f(s->GetBBPointX(3), s->GetBBPointY(3));
	glVertex2f(s->GetBBPointX(4), s->GetBBPointY(4));
	glEnd();

	//稜線の描画
	glColor3f(R, G, B);
	glLineWidth(width);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xF0F0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(s->GetBBPointX(1), s->GetBBPointY(1));
	glVertex2f(s->GetBBPointX(2), s->GetBBPointY(2));
	glVertex2f(s->GetBBPointX(3), s->GetBBPointY(3));
	glVertex2f(s->GetBBPointX(4), s->GetBBPointY(4));
	glEnd();

	glDisable(GL_LINE_STIPPLE);
}

//面張り（通常）
void CACDraw::DrawColor(CShape *s)
{
	float R, G, B;
	s->GetColor(&R, &G, &B);
	DrawColor(s, R, G, B);
}

//面張り（色指定）
void CACDraw::DrawColor(CShape *s, float R, float G, float B)
{
	//ClosedShapeFlagかColorFlagがfalseだったら何もしない
	if (s->GetClosedFlag() == false || s->GetColorFlag() == false) {
		return;
	}

	GetTrianglePoint(s);

	glColor3f(R, G, B);
	glBegin(GL_TRIANGLES);
	CTriangle *t = s->GetTrianglehead();
	while (t != NULL) {
		glVertex2f(t->GetX(1), t->GetY(1));
		glVertex2f(t->GetX(2), t->GetY(2));
		glVertex2f(t->GetX(3), t->GetY(3));
		t = t->GetNextTriangle();
	}
	glEnd();


	//***************ここからテスト用補助線***************
	/*
	for (CTriangle *t = s->GetTrianglehead(); t != NULL; t = t->GetNextTriangle()) {
	glColor3f(1, 0, 0);
	glLineWidth(1.0);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xFFFF);
	glBegin(GL_LINE_LOOP);
	glVertex2f(t->GetX(1), t->GetY(1));
	glVertex2f(t->GetX(2), t->GetY(2));
	glVertex2f(t->GetX(3), t->GetY(3));
	glEnd();
	}

	v = s->GetVertexheadT();
	glColor3f(1, 0, 0);
	glLineWidth(1.0);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xFFFF);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 3; i++) {
	glVertex2f(v->GetX(), v->GetY());
	v = s->GetNextVertexLoopT(v);
	}
	glEnd();
	*/
	//*******************ここまで*************************
}

//XYZ軸の描画
void CACDraw::DrawXYZ()
{
	glEnable(GL_DEPTH_TEST);
	glLineWidth(1.0);
	glBegin(GL_LINES);

	//X軸
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);

	//Y軸
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);

	//Z軸
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, -1.0);
	glVertex3f(0.0, 0.0, 1.0);

	glEnd();
	glDisable(GL_DEPTH_TEST);
}

void CACDraw::DrawXYZ(int n)
{
	glEnable(GL_DEPTH_TEST);
	glLineWidth(3.0);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xFFFF);
	glBegin(GL_LINES);

	if (n == 1) {
		//X軸
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-1.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
	}
	else if (n == 2) {
		//Y軸
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, -1.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
	}
	else if (n == 3) {
		//Z軸
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, -1.0);
		glVertex3f(0.0, 0.0, 1.0);
	}

	glEnd();
	glDisable(GL_DEPTH_TEST);
}





//ここから下は計算とか判定とかとか
//凸形状ならtrue、凹形状ならfalseを返す
bool CACDraw::WhichShape(CShape *s)
{
	//凸形状化どうか判定
	float *check;
	check = new float[s->GetVertexCount()];
	DPOINT A, B, C;
	CVertex *v = s->GetVertexhead();

	//Bが先頭からNULLまで動く、Aはその1つ前、Cはその1つ後
	for (int i = 0; i < s->GetVertexCount(); i++) {
		v->GetXY(&B.x, &B.y);
		s->GetLastVertexLoop(v)->GetXY(&A.x, &A.y);
		s->GetNextVertexLoop(v)->GetXY(&C.x, &C.y);

		check[i] = ACM.Angle(B.x, B.y, A.x, A.y, C.x, C.y);

		v = v->GetNextVertex();
	}
	float sum = 0;
	for (int j = 0; j < s->GetVertexCount(); j++) {
		check[j] = fabsf(check[j] * 180 / 3.14);
		sum = sum + check[j];
	}
	//小数点以下を切り捨て
	sum = (int)sum;
	delete[] check;

	int tmp = s->GetVertexCount() - 2;
	if (tmp * 180 == sum) {
		return true;
	}

	return false;
}

//交差判定
bool CACDraw::Judge1(CShape *s, CVertex *StartV, CVertex *EndV)
{
	//BsとBeの設定
	DPOINT Bs, Be;
	StartV->GetXY(&Bs.x, &Bs.y);
	EndV->GetXY(&Be.x, &Be.y);

	CVertex *v = s->GetVertexhead();

	//AsとAeの設定
	DPOINT As, Ae;
	v->GetXY(&Ae.x, &Ae.y);
	v = v->GetNextVertex();

	for (int i = 0; i < s->GetVertexCount(); i++) {
		v->GetXY(&As.x, &As.y);

		if (!CheckPoint(As, Bs) && !CheckPoint(Ae, Be) && !CheckPoint(As, Be) && !CheckPoint(Ae, Bs)) {
			CVector A(As.x, As.y, Ae.x, Ae.y), a1(As.x, As.y, Bs.x, Bs.y), a2(As.x, As.y, Be.x, Be.y);
			CVector B(Bs.x, Bs.y, Be.x, Be.y), b1(Bs.x, Bs.y, As.x, As.y), b2(Bs.x, Bs.y, Ae.x, Ae.y);

			if (ACM.CrossProduct(A, a1) * ACM.CrossProduct(A, a2) <= 0 && ACM.CrossProduct(B, b1) * ACM.CrossProduct(B, b2) <= 0) {
				return false;
			}
		}

		v->GetXY(&Ae.x, &Ae.y);
		v = s->GetNextVertexLoop(v);
	}
	return true;
}

//中点の内包判定（通常の内包判定とtrueとfalseが逆なので注意）
bool CACDraw::Judge2(CShape *s, CVertex *StartV, CVertex *EndV)
{
	//中点の座標
	DPOINT P = { (StartV->GetX() + EndV->GetX()) / 2, (StartV->GetY() + EndV->GetY()) / 2 };
	DPOINT A, B;

	//角度を格納するための配列の設定
	float *check;
	check = new float[s->GetVertexCount()];

	CVertex *v = s->GetVertexhead();
	v->GetXY(&A.x, &A.y);
	v = v->GetNextVertex();

	for (int i = 0; i < s->GetVertexCount(); i++) {
		v->GetXY(&B.x, &B.y);

		check[i] = ACM.Angle(P.x, P.y, A.x, A.y, B.x, B.y);

		v->GetXY(&A.x, &A.y);
		v = s->GetNextVertexLoop(v);
	}

	float sum = 0;
	for (int j = 0; j < s->GetVertexCount(); j++) {
		sum = sum + check[j];
	}
	//3桁目までで切り捨てて判定する
	sum = (int)(fabsf(sum) * 100);

	//314 * 2 = 628
	delete[] check;
	if (sum == 628) {
		return true;
	}

	return false;
}

//点の比較
bool CACDraw::CheckPoint(DPOINT p, DPOINT q)
{
	if (p.x == q.x && p.y == p.y) {
		return true;
	}

	return false;
}




void CACDraw::GetTrianglePoint(CShape *s)
{
	//ClosedShapeFlagかColorFlagがfalseだったら何もしない
	if (s->GetClosedFlag() == false || s->GetColorFlag() == false) {
		return;
	}

	//Triangleの消去
	s->FreeTriangle();

	while (s->GetVertexCountT() != 3) {
		//vは中央の点を指す
		CVertex *v = s->GetVertexhead()->GetNextVertex();
		if (v->GetThroughFlag()) {
			v = s->GetNextVertexLoopT(v);
		}

		for (int i = 0; i < s->GetVertexCountT(); i++) {
			//LastVとNextVの更新処理
			CVertex *LastV = s->GetLastVertexLoopT(v);
			CVertex *NextV = s->GetNextVertexLoopT(v);

			//判定
			if (Judge1(s, LastV, NextV) && Judge2(s, LastV, NextV)) {
				s->AppendTriangle(LastV->GetX(), LastV->GetY(), v->GetX(), v->GetY(), NextV->GetX(), NextV->GetY());
				v->SetThroughFlag(true);
				break;
			}

			//vの更新処理
			v = s->GetNextVertexLoopT(v);
		}
	}

	CVertex *v = s->GetVertexheadT();
	DPOINT tmp[3];
	for (int i = 0; i < 3; i++) {
		tmp[i].x = v->GetX();
		tmp[i].y = v->GetY();
		v = s->GetNextVertexLoopT(v);
	}
	s->AppendTriangle(tmp[0].x, tmp[0].y, tmp[1].x, tmp[1].y, tmp[2].x, tmp[2].y);

	//解放とかの処理
	s->ClearThroughFlag();
}
