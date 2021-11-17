
#include "stdafx.h"
#include "AdminControl.h"

CShape *shape_head = NULL;

CAdminControl::CAdminControl()
: ShapeCount(0)
, ButtonMode(0)
{
}

CAdminControl::~CAdminControl()
{
}

//全部描画する
void CAdminControl::Draw()
{
	//視点変更モード
	if (GetButtonMode() == 11) {
		if (WatchValue.z == 0) {
			glTranslatef(WatchValue.x, WatchValue.y, 0);
			SetWatchValue(0, 0, 0);
		}
		else {
			glScalef(WatchValue.z, WatchValue.z, 1);
			SetWatchValue(0, 0, 0);
		}
	}
	else if (GetButtonMode() == 12) {
		//x軸中心の場合
		if (GetXYZ() == 1) {
			glRotatef(WatchValue.z, 1, 0, 0);
		}
		//y軸中心の場合
		else if (GetXYZ() == 2) {
			glRotatef(WatchValue.z, 0, 1, 0);
		}
		//z軸中心の場合
		else {
			glRotatef(WatchValue.z, 0, 0, 1);
		}
		SetWatchValue(0, 0, 0);
	}

	//XYZ軸
	if (GetSubButtonMode(1)) {
		ACD.DrawXYZ();
		if (GetButtonMode() == 11 || GetButtonMode() == 12) {
			ACD.DrawXYZ(GetXYZ());
		}
	}

	if (GetButtonMode() != 11 && GetButtonMode() != 12) {
		//2次元の描画
		Draw2();
	}
	else {
		//3次元の描画
		Draw3();
	}
}

//全部描画する（2次元）
void CAdminControl::Draw2()
{
	if (shape_head != NULL) {
		//全体
		//面張り
		CShape *s = shape_head;
		if (GetSubButtonMode(0)) {
			while (s != NULL) {
				//面張りの例外処理いろいろ
				if (s == NowPointS || s == NowLineS || s == NowShape) {
					s = s->GetNextShape();
				}
				else {
					ACD.DrawColor(s);
					s = s->GetNextShape();
				}
			}
		}
		//枠と点
		for (CShape *s = shape_head; s != NULL; s = s->GetNextShape()) {
			ACD.Draw(s);
		}

		//各モードごとの処理
		//描画モード
		if (GetButtonMode() == 0 && !shape_head->GetClosedFlag())
		{
			ACD.DrawDotLine(shape_head->GetVertexhead(), NewPoint.x, NewPoint.y, 5, 1, 1, 1, 1);

			if (NowPointV != NULL) {
				ACD.DrawPoint(NowPointV, 8, 1, 1, 1);
				ClearChoice();
			}
		}
		//編集モード（移動）
		else if (GetButtonMode() == 1) {
			if (NowPointV != NULL) {
				ACD.DrawPoint(NowPointV, 10, 0, 1.0, 0);
			}
			else if (NowLineV != NULL) {
				ACD.DrawLine(NowLineS, NowLineV, 5, 1.0, 0, 1.0, 0);
			}
			else if (NowShape != NULL) {
				ACD.DrawShape(NowShape, 5, 1.0, 0, 1.0, 0);
			}
		}
		//編集モード（追加）
		else if (GetButtonMode() == 2) {
			if (NowLineV != NULL) {
				ACD.DrawPoint(NewPoint.x, NewPoint.y, 10, 0, 1.0, 0);
			}
		}
		//編集モード（削除）
		else if (GetButtonMode() == 3) {
			if (NowPointV != NULL) {
				ACD.DrawPoint(NowPointV, 10, 0, 1.0, 0);
			}
			else if (NowShape != NULL) {
				ACD.DrawShape(NowShape, 5, 1.0, 0, 1, 0);
			}
		}
		//編集モード（拡大・縮小）
		else if (GetButtonMode() == 4) {
			if (NowShape != NULL) {
				if (DrawBBFlag == true) {
					ACD.DrawShape(NowShape, 5, 1.0, 0.7, 0.7, 0.7);
					ACD.DrawBB(NowShape, 5, 1, 0, 1.0, 0);
					if (GetBBPoint() != 0) {
						ACD.DrawPoint(NowShape->GetBBPointX(BBPoint), NowShape->GetBBPointY(BBPoint), 10, 0, 1.0, 0);
					}
				}
				else {
					ACD.DrawShape(NowShape, 5, 1.0, 0, 1, 0);
				}
			}
		}
		//編集モード（回転）
		else if (GetButtonMode() == 5) {
			if (NowShape != NULL) {
				if (DrawBBFlag == true) {
					ACD.DrawShape(NowShape, 5, 1.0, 0.7, 0.7, 0.7);
					ACD.DrawBB(NowShape, 5, 1, 0, 1.0, 0);
					ACD.DrawPoint(NowShape->GetCenterPointX(), NowShape->GetCenterPointY(), 8, 0, 1, 0);
					if (GetBBPoint() != 0) {
						ACD.DrawPoint(NowShape->GetBBPointX(BBPoint), NowShape->GetBBPointY(BBPoint), 10, 0, 1.0, 0);
					}
				}
				else {
					ACD.DrawShape(NowShape, 5, 1.0, 0, 1, 0);
				}
			}
		}
		//色編集
		else if (GetButtonMode() == 6) {
			SetSubButtonMode(101);
			while (s != NULL) {
				ACD.GetTrianglePoint(s);
				s = s->GetNextShape();
			}

			if (NowShape != NULL && DrawBBFlag == true) {
				ACD.DrawColor(NowShape);
				ACD.DrawShape(NowShape, 5, 1.0, 0.7, 0.7, 0.7);
				ACD.DrawBB(NowShape, 5, 1, 0, 1.0, 0);
			}
		}
	}
}

//全部描画する（3次元）
void CAdminControl::Draw3()
{
	CShape *s = shape_head;

	//強制的に面張り
	SetSubButtonMode(101);
	while (s != NULL) {
		ACD.GetTrianglePoint(s);
		s = s->GetNextShape();
	}

	//法線ベクトル
	float Ni, Nj, Nk;

	//マテリアルの設定
	//環境光
	float dif[4] = { 1.0, 1.0, 1.0, 1.0 };
	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	//******************ここから描画処理*********************
	s = shape_head;
	CTriangle *t;

	while (s != NULL) {
		//色
		float R, G, B;
		s->GetColor(&R, &G, &B);
		float C[4] = { R, G, B, 10 };

		//真っ黒は見えないので対策
		if (R == 0 && G == 0 && B == 0) {
			C[0] = 0.025;
			C[1] = 0.025;
			C[2] = 0.025;
		}

		glMaterialfv(GL_FRONT, GL_DIFFUSE, C);
		glMaterialfv(GL_FRONT, GL_AMBIENT, C);

		//右回りの時true
		bool RightFlag = true;

		//表面
		t = s->GetTrianglehead();
		while (t != NULL) {
			glBegin(GL_TRIANGLES);

			ACM.NormalVector(t->GetX(1), t->GetY(1), 0, t->GetX(2), t->GetY(2), 0, t->GetX(3), t->GetY(3), 0, &Ni, &Nj, &Nk);
			glNormal3f(-Ni, -Nj, -Nk);
			if (Nk < 0) {
				RightFlag = false;
				glNormal3f(Ni, Nj, Nk);
			}

			glVertex3f(t->GetX(1), t->GetY(1), 0);
			glVertex3f(t->GetX(2), t->GetY(2), 0);
			glVertex3f(t->GetX(3), t->GetY(3), 0);

			glEnd();

			t = t->GetNextTriangle();
		}

		//裏面
		t = s->GetTrianglehead();
		while (t != NULL) {

			glBegin(GL_TRIANGLES);

			ACM.NormalVector(t->GetX(1), t->GetY(1), high, t->GetX(2), t->GetY(2), high, t->GetX(3), t->GetY(3), high, &Ni, &Nj, &Nk);
			glNormal3f(Ni, Nj, Nk);
			if (RightFlag == false) {
				glNormal3f(-Ni, -Nj, -Nk);
			}

			glVertex3f(t->GetX(1), t->GetY(1), high);
			glVertex3f(t->GetX(2), t->GetY(2), high);
			glVertex3f(t->GetX(3), t->GetY(3), high);

			glEnd();

			t = t->GetNextTriangle();
		}

		//側面
		t = s->GetTrianglehead();
		while (t != NULL) {
			for (int i = 1; i <= 3; i++) {
				int j = i + 1;
				if (j > 3) { j = 1; }

				glBegin(GL_TRIANGLES);

				ACM.NormalVector(t->GetX(i), t->GetY(i), 0, t->GetX(i), t->GetY(i), high, t->GetX(j), t->GetY(j), high, &Ni, &Nj, &Nk);
				glNormal3f(-Ni, -Nj, -Nk);
				if (RightFlag == false) {
					glNormal3f(Ni, Nj, Nk);
				}

				glVertex3f(t->GetX(i), t->GetY(i), 0);
				glVertex3f(t->GetX(i), t->GetY(i), high);
				glVertex3f(t->GetX(j), t->GetY(j), high);

				glEnd();

				//***************************************************************

				glBegin(GL_TRIANGLES);

				ACM.NormalVector(t->GetX(i), t->GetY(i), 0, t->GetX(j), t->GetY(j), 0, t->GetX(j), t->GetY(j), high, &Ni, &Nj, &Nk);
				glNormal3f(Ni, Nj, Nk);
				if (RightFlag == false) {
					glNormal3f(-Ni, -Nj, -Nk);
				}

				glVertex3f(t->GetX(i), t->GetY(i), 0);
				glVertex3f(t->GetX(j), t->GetY(j), 0);
				glVertex3f(t->GetX(j), t->GetY(j), high);

				glEnd();
			}

			t = t->GetNextTriangle();
		}

		s = s->GetNextShape();
	}

	//**********************ここまで*************************
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);
}

//ワールド座標を格納する
void CAdminControl::SetWorldPoint(float wx, float wy)
{
	//1点目の処理
	if (shape_head == NULL || shape_head->GetClosedFlag()) {
		AppendShape();
		shape_head->AppendVertex(wx, wy);
		SetFirstPoint(wx, wy);
	}
	//2点目以降の処理
	else {
		shape_head->AppendVertex(wx, wy);
	}
}

//ワールド座標を格納する
void CAdminControl::SetWorldPoint()
{
	
	SetWorldPoint(NewPoint.x, NewPoint.y);
}

//点を移動させる
void CAdminControl::MovePoint(float NowX, float NowY)
{
	if (NowPointV != NULL) {

		NowPointV->SetX(NowX);
		NowPointV->SetY(NowY);

		if (NowPointV->GetNextVertex() == NULL) {
			SetFirstPoint(NowX, NowY);
		}
	}
}

//LastPointに移動させる
void CAdminControl::MovePoint()
{
	if (NowPointV != NULL) {
		NowPointV->SetX(LastPoint.x);
		NowPointV->SetY(LastPoint.y);

		if (NowPointV->GetNextVertex() == NULL) {
			SetFirstPoint(LastPoint.x, LastPoint.y);
		}
	}
}

//図形の移動
void CAdminControl::MoveShape(float x, float y)
{
	if (NowShape != NULL) {
		DrawBBFlag = false;
		ClearBBPoint(1);

		CVertex *v = NowShape->GetVertexhead();
		CVector move(MoveBeforPoint.x, MoveBeforPoint.y, x, y);

		while (v != NULL) {
			v->SetX(v->GetX() + move.GetX());
			v->SetY(v->GetY() + move.GetY());

			if (v->GetNextVertex() == NULL) {
				SetFirstPoint(v->GetX() + move.GetX(), v->GetY() + move.GetY());
			}
			v = v->GetNextVertex();
		}
	}
}

//元の場所に移動
void CAdminControl::MoveShape()
{
	if (NowShape != NULL || NowLineV != NULL) {
		CVertex *v;

		if (NowShape != NULL) {
			v = NowShape->GetVertexhead();
		}
		else {
			v = NowLineS->GetVertexhead();
		}

		CVector move(MoveBeforPoint.x, MoveBeforPoint.y, LastPoint.x, LastPoint.y);

		while (v != NULL) {
			v->SetX(v->GetX() + move.GetX());
			v->SetY(v->GetY() + move.GetY());

			if (v->GetNextVertex() == NULL) {
				SetFirstPoint(v->GetX() + move.GetX(), v->GetY() + move.GetY());
			}
			v = v->GetNextVertex();
		}
	}
}

//点を追加する
void CAdminControl::AddWorldPoint(void)
{
	if (NowLineV != NULL) {
		NowLineS->AddVertex(NewPoint.x, NewPoint.y, NowLineV);
	}
}

//点を削除する
void CAdminControl::DeleteWorldPoint(void)
{
	//0→エラー無し、1→3点以下になる、2→交差または内包する
	DeleteError = 0;

	if (NowPointV != NULL) {
		LastV_delete = NowPointS->GetLastVertexLoop(NowPointV);

		if (NowPointS->GetClosedFlag()) {
			if (NowPointS->GetVertexCount() > 3) {
				NowPointS->preDeleteVertex(NowPointV);
				if (JudgeAll()) {
					delete NowPointV;
				}
				else {
					NowPointS->preAddVertex(NowPointV, LastV_delete);
					DeleteError = 2;
				}
			}
			else {
				DeleteError = 1;
			}
		}
		else {
			if (NowPointS->GetLastVertex(NowPointV) == NULL || NowPointV->GetNextVertex() == NULL) {
				if (NowPointS->GetVertexCount() > 1) {
					if (NowPointV->GetNextVertex() == NULL) {
						SetFirstPoint(LastV_delete->GetX(), LastV_delete->GetY());
					}

					NowPointS->DeleteVertex(NowPointV);
				}
			}
			else if (NowPointS->GetVertexCount() > 1) {
				NowPointS->preDeleteVertex(NowPointV);

				if (JudgeAll()) {
					delete NowPointV;
				}
				else
				{
					NowPointS->preAddVertex(NowPointV, LastV_delete);
					DeleteError = 2;
				}
			}
		}

		ClearChoice();
	}
}

//図形を削除する
void CAdminControl::DeleteShape()
{
	if (NowShape != NULL) {
		CShape *LastS = NULL;
		CShape *s = shape_head;
		while (s != NULL) {
			if (NowShape == shape_head) {
				break;
			}

			if (s->GetNextShape() == NowShape) {
				LastS = s;
				break;
			}
			s = s->GetNextShape();
		}

		NowShape->FreeVertex();
		NowShape->FreeTriangle();

		//消す図形が1番目の場合
		if (LastS == NULL) {
			shape_head = NowShape->GetNextShape();
		}
		//消す図形が最後の場合
		else if (NowShape->GetNextShape() == NULL) {
			LastS->SetNextShape(NULL);
		}
		//それ以外の場合
		else {
			LastS->SetNextShape(NowShape->GetNextShape());
		}

		delete NowShape;
	}

	ClearChoice();
}

//拡大・縮小
void CAdminControl::ScalingShape(float NowX, float NowY)
{
	if (NowShape != NULL) {
		CVertex *v = NowShape->GetVertexhead();
		//倍率
		ACPOINT tmp = { NowShape->GetBBPointX(BBPoint) - NowShape->GetBBPointX(BBPointOtherSide), NowShape->GetBBPointY(BBPoint) - NowShape->GetBBPointY(BBPointOtherSide) };
		ACPOINT tmp2 = { NowX - NowShape->GetBBPointX(BBPointOtherSide), NowY - NowShape->GetBBPointY(BBPointOtherSide) };
		ACPOINT mag = { tmp2.x / tmp.x - 1, tmp2.y / tmp.y - 1 };

		if (ACM.Point_PointDistance(NowShape->GetBBPointX(1), NowShape->GetBBPointY(1), NowShape->GetBBPointX(2), NowShape->GetBBPointY(2)) <= 0.05) {
			if (mag.x < 1) {
				mag.x = 0;
			}
		}
		if (ACM.Point_PointDistance(NowShape->GetBBPointX(2), NowShape->GetBBPointY(2), NowShape->GetBBPointX(3), NowShape->GetBBPointY(3)) <= 0.05) {
			if (mag.y < 1) {
				mag.y = 0;
			}
		}

		while (v != NULL) {
			ACPOINT move = { v->GetX() - NowShape->GetBBPointX(BBPointOtherSide), v->GetY() - NowShape->GetBBPointY(BBPointOtherSide) };
			v->SetX(mag.x * move.x + v->GetX());
			v->SetY(mag.y * move.y + v->GetY());

			if (v->GetNextVertex() == NULL) {
				SetFirstPoint(v->GetX(), v->GetY());
			}
			v = v->GetNextVertex();
		}
	}
}

//拡大・縮小
void CAdminControl::ScalingShape()
{
	if (NowShape != NULL) {
		CVertex *v = NowShape->GetVertexhead();
		//倍率
		ACPOINT tmp = { NowShape->GetBBPointX(BBPoint) - NowShape->GetBBPointX(BBPointOtherSide), NowShape->GetBBPointY(BBPoint) - NowShape->GetBBPointY(BBPointOtherSide) };
		ACPOINT tmp2 = { LastPoint.x - NowShape->GetBBPointX(BBPointOtherSide), LastPoint.y - NowShape->GetBBPointY(BBPointOtherSide) };
		ACPOINT mag = { tmp2.x / tmp.x - 1, tmp2.y / tmp.y - 1 };

		if (ACM.Point_PointDistance(NowShape->GetBBPointX(1), NowShape->GetBBPointY(1), NowShape->GetBBPointX(2), NowShape->GetBBPointY(2)) <= 0.05) {
			if (mag.x < 1) {
				mag.x = 0;
			}
		}
		if (ACM.Point_PointDistance(NowShape->GetBBPointX(2), NowShape->GetBBPointY(2), NowShape->GetBBPointX(3), NowShape->GetBBPointY(3)) <= 0.05) {
			if (mag.y < 1) {
				mag.y = 0;
			}
		}

		while (v != NULL) {
			ACPOINT move = { v->GetX() - NowShape->GetBBPointX(BBPointOtherSide), v->GetY() - NowShape->GetBBPointY(BBPointOtherSide) };
			v->SetX(mag.x * move.x + v->GetX());
			v->SetY(mag.y * move.y + v->GetY());

			if (v->GetNextVertex() == NULL) {
				SetFirstPoint(v->GetX(), v->GetY());
			}
			v = v->GetNextVertex();
		}
	}
}

//回転
void CAdminControl::TurnShape(float NowX, float NowY)
{
	if (NowShape != NULL) {
		CVertex *v = NowShape->GetVertexhead();

		//基点
		ACPOINT CardinalPoint = { NowShape->GetCenterPointX(), NowShape->GetCenterPointY() };

		//角度
		float angle = ACM.Angle(CardinalPoint.x, CardinalPoint.y, MoveBeforPoint.x, MoveBeforPoint.y, NowX, NowY);

		float CosAngle = cos(angle);
		float SinAngle = sin(angle);

		//BBの回転
		float tmpx, tmpy;
		for (int i = 1; i <= 4; i++) {
			ACPOINT move = { NowShape->GetBBPointX(i) - CardinalPoint.x, NowShape->GetBBPointY(i) - CardinalPoint.y };
			float tmp1, tmp2;

			tmp1 = move.x * CosAngle;
			tmp2 = move.y * SinAngle;
			tmpx = tmp1 - tmp2 + CardinalPoint.x;

			tmp1 = move.x * SinAngle;
			tmp2 = move.y * CosAngle;
			tmpy = tmp1 + tmp2 + CardinalPoint.y;

			NowShape->ChangeBBPoint(i, tmpx, tmpy);
		}

		//図形の回転
		while (v != NULL) {
			ACPOINT move = { v->GetX() - CardinalPoint.x, v->GetY() - CardinalPoint.y };
			float tmp1, tmp2;

			tmp1 = move.x * CosAngle;
			tmp2 = move.y * SinAngle;
			v->SetX(tmp1 - tmp2 + CardinalPoint.x);

			tmp1 = move.x * SinAngle;
			tmp2 = move.y * CosAngle;
			v->SetY(tmp1 + tmp2 + CardinalPoint.y);

			if (v->GetNextVertex() == NULL) {
				SetFirstPoint(v->GetX(), v->GetY());
			}
			v = v->GetNextVertex();
		}
	}
}

//回転
void CAdminControl::TurnShape()
{
	if (NowShape != NULL) {
		CVertex *v = NowShape->GetVertexhead();

		//基点
		ACPOINT CardinalPoint = { NowShape->GetCenterPointX(), NowShape->GetCenterPointY() };
		//角度
		float angle = ACM.Angle(CardinalPoint.x, CardinalPoint.y, NowShape->GetBBPointX(BBPoint), NowShape->GetBBPointY(BBPoint), LastBB.x, LastBB.y);

		float CosAngle = cos(angle);
		float SinAngle = sin(angle);

		//BBの回転
		float tmpx, tmpy;
		for (int i = 1; i <= 4; i++) {
			ACPOINT move = { NowShape->GetBBPointX(i) - CardinalPoint.x, NowShape->GetBBPointY(i) - CardinalPoint.y };
			float tmp1, tmp2;

			tmp1 = move.x * CosAngle;
			tmp2 = move.y * SinAngle;
			tmpx = tmp1 - tmp2 + CardinalPoint.x;

			tmp1 = move.x * SinAngle;
			tmp2 = move.y * CosAngle;
			tmpy = tmp1 + tmp2 + CardinalPoint.y;

			NowShape->ChangeBBPoint(i, tmpx, tmpy);
		}

		//図形の回転
		while (v != NULL) {
			ACPOINT move = { v->GetX() - CardinalPoint.x, v->GetY() - CardinalPoint.y };
			float tmp1, tmp2;

			tmp1 = move.x * CosAngle;
			tmp2 = move.y * SinAngle;
			v->SetX(tmp1 - tmp2 + CardinalPoint.x);

			tmp1 = move.x * SinAngle;
			tmp2 = move.y * CosAngle;
			v->SetY(tmp1 + tmp2 + CardinalPoint.y);

			if (v->GetNextVertex() == NULL) {
				SetFirstPoint(v->GetX(), v->GetY());
			}
			v = v->GetNextVertex();
		}
	}
}

//1点目を格納する
void CAdminControl::SetFirstPoint(float x, float y)
{
	FirstPoint.x = x;
	FirstPoint.y = y;
}

//終点の時の処理
void CAdminControl::EndWorldPoint(void)
{
	shape_head->SetClosedFlag(true);

	if (GetSubButtonMode(0)) {
		shape_head->SetColorFlag(true);
	}
}

//1点目のx座標を返す
float CAdminControl::GetFirstPointX()
{
	return FirstPoint.x;
}

//1点目のy座標を返す
float CAdminControl::GetFirstPointY()
{
	return FirstPoint.y;
}

//描画途中の点のx座標を返す
float CAdminControl::GetNewPointX()
{
	return NewPoint.x;
}

//描画途中の点のy座標を返す
float CAdminControl::GetNewPointY()
{
	return NewPoint.y;
}

//先頭のVertexの個数を返す
int CAdminControl::GetHeadVertexCount(void)
{
	return shape_head->GetVertexCount();
}

//先頭のshapeのClosedFlagを返す
bool CAdminControl::GetHeadClosedFlag(void)
{
	//1つ目の図形の場合
	if (shape_head == NULL) {
		return true;
	}

	//それ以外の場合
	return shape_head->GetClosedFlag();
}

//Shapeを追加する
void CAdminControl::AppendShape()
{
	CShape *S1 = new CShape();
	S1->SetNextShape(shape_head);
	shape_head = S1;
	ShapeCount++;
}

//Shapeのみ開放する
void CAdminControl::FreeShape()
{
	for (CShape *tmp = shape_head; shape_head != NULL;) {
		tmp = tmp->GetNextShape();
		delete shape_head;
		shape_head = tmp;
	}
}

//全部開放する
void CAdminControl::FreeAll(void)
{
	for (CShape *s = shape_head; s != NULL; s = s->GetNextShape()) {
		s->FreeVertex();
		s->FreeTriangle();
	}
	FreeShape();
}

//1点目と点(x, y)の距離を返す
float CAdminControl::FirstPointDistance(float x, float y)
{
	float dis;
	dis = ACM.Point_PointDistance(x, y, GetFirstPointX(), GetFirstPointY());

	return dis;
}

//NowPointと点(x, y)の距離を返す
float CAdminControl::FirstPointDistance(void)
{
	float dis;
	dis = ACM.Point_PointDistance(NewPoint.x, NewPoint.y, GetFirstPointX(), GetFirstPointY());

	return dis;
}

//自己交差判定（交差していなければtrueを返す）
bool CAdminControl::Judge1(float NewX, float NewY)
{
	//1～3点目のとき
	if (shape_head == NULL || GetHeadVertexCount() < 3) {
		return true;
	}

	CShape *s = shape_head;
	CVertex *v = s->GetVertexhead();

	//BsとBeの設定
	ACPOINT Bs;
	v->GetXY(&Bs.x, &Bs.y);
	v = v->GetNextVertex();
	ACPOINT Be = { NewX, NewY };

	//AsとAeの設定
	ACPOINT As, Ae;
	v->GetXY(&Ae.x, &Ae.y);

	v = v->GetNextVertex();
	while (v != NULL) {
		v->GetXY(&As.x, &As.y);
		CVector A(As.x, As.y, Ae.x, Ae.y), a1(As.x, As.y, Bs.x, Bs.y), a2(As.x, As.y, Be.x, Be.y);
		CVector B(Bs.x, Bs.y, Be.x, Be.y), b1(Bs.x, Bs.y, As.x, As.y), b2(Bs.x, Bs.y, Ae.x, Ae.y);

		if (ACM.CrossProduct(A, a1) * ACM.CrossProduct(A, a2) <= 0 && ACM.CrossProduct(B, b1) * ACM.CrossProduct(B, b2) <= 0) {
			return false;
		}

		v->GetXY(&Ae.x, &Ae.y);
		v = v->GetNextVertex();
	}
	return true;
}

//他の形状との交差判定（交差していなければtrueを返す）
bool CAdminControl::Judge2(float NewX, float NewY)
{
	//1つ目の図形のとき
	if (shape_head == NULL || ShapeCount < 2) {
		return true;
	}

	CShape *s = shape_head;
	CVertex *v = s->GetVertexhead();

	//BsとBeの設定
	ACPOINT Bs;
	ACPOINT Be = { NewX, NewY };
	v->GetXY(&Bs.x, &Bs.y);

	//AsとAeの設定
	ACPOINT As, Ae;
	s = s->GetNextShape();

	while (s != NULL) {
		v = s->GetVertexhead();
		v->GetXY(&Ae.x, &Ae.y);
		v = v->GetNextVertex();
		for (int i = 0; i < s->GetVertexCount(); i++) {
			v->GetXY(&As.x, &As.y);

			CVector A(As.x, As.y, Ae.x, Ae.y), a1(As.x, As.y, Bs.x, Bs.y), a2(As.x, As.y, Be.x, Be.y);
			CVector B(Bs.x, Bs.y, Be.x, Be.y), b1(Bs.x, Bs.y, As.x, As.y), b2(Bs.x, Bs.y, Ae.x, Ae.y);

			if (ACM.CrossProduct(A, a1) * ACM.CrossProduct(A, a2) <= 0 && ACM.CrossProduct(B, b1) * ACM.CrossProduct(B, b2) <= 0) {
				return false;
			}
			else {
				v->GetXY(&Ae.x, &Ae.y);
				v = s->GetNextVertexLoop(v);
			}
		}
		s = s->GetNextShape();
	}
	return true;
}

//内包判定：始点（内包されていなければtrueを返す）
bool CAdminControl::Judge3(float NewX, float NewY)
{
	//1つ目の図形のとき
	if (shape_head == NULL || (ShapeCount < 2 && !GetHeadClosedFlag())) {
		return true;
	}

	//点の設定
	ACPOINT P = { NewX, NewY };
	ACPOINT A, B;
	CShape *s = shape_head;

	while (s != NULL) {
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
			return false;
		}
		else {
			s = s->GetNextShape();
		}
	}
	return true;
}

//内包判定：終点（内包されていなければtrueを返す）
//shape_headの図形が閉じた場合、他の図形の1点目が内包されていないかをチェックする
bool CAdminControl::Judge4(void)
{
	//1つ目の図形の場合
	if (ShapeCount < 1) {
		return true;
	}

	//点の設定
	ACPOINT P;
	ACPOINT A, B;

	//点AとB用のsとv（ずっとshape_head）
	CShape *s1 = shape_head;
	CVertex *v1 = s1->GetVertexhead();

	//点P用のsとv（shape_headの次からNULLまで）
	CShape *s2 = shape_head->GetNextShape();
	CVertex *v2;

	while (s2 != NULL) {
		v2 = s2->GetVertexhead();
		v2->GetXY(&P.x, &P.y);

		v1 = s1->GetVertexhead();
		v1->GetXY(&A.x, &A.y);
		v1 = v1->GetNextVertex();

		//角度を格納するための配列の設定
		float *check;
		check = new float[s1->GetVertexCount()];

		for (int i = 0; i < s1->GetVertexCount(); i++) {
			v1->GetXY(&B.x, &B.y);

			check[i] = ACM.Angle(P.x, P.y, A.x, A.y, B.x, B.y);

			v1->GetXY(&A.x, &A.y);
			v1 = s1->GetNextVertexLoop(v1);
		}
		float sum = 0;
		for (int j = 0; j < s1->GetVertexCount(); j++) {
			sum = sum + check[j];
		}
		sum = (int)(fabsf(sum) * 100);

		delete[] check;
		if (sum == 628) {
			return false;
		}
		else {
			s2 = s2->GetNextShape();
		}
	}
	return true;
}

//砂時計対策
bool CAdminControl::Judge5(void)
{
	CShape *s = shape_head;
	CVertex *v = s->GetVertexhead();

	if (s->GetVertexCount() <= 3) {
		return true;
	}

	//BsとBeの設定
	ACPOINT Bs;
	ACPOINT Be = { GetFirstPointX(), GetFirstPointY() };
	v->GetXY(&Bs.x, &Bs.y);

	//AsとAeの設定
	ACPOINT As, Ae;
	v = v->GetNextVertex();
	v->GetXY(&Ae.x, &Ae.y);
	v = v->GetNextVertex();

	while (v != NULL) {
		v->GetXY(&As.x, &As.y);

		CVector A(As.x, As.y, Ae.x, Ae.y), a1(As.x, As.y, Bs.x, Bs.y), a2(As.x, As.y, Be.x, Be.y);
		CVector B(Bs.x, Bs.y, Be.x, Be.y), b1(Bs.x, Bs.y, As.x, As.y), b2(Bs.x, Bs.y, Ae.x, Ae.y);

		if (ACM.CrossProduct(A, a1) * ACM.CrossProduct(A, a2) <= 0 && ACM.CrossProduct(B, b1) * ACM.CrossProduct(B, b2) <= 0) {
			return false;
		}
		else {
			v->GetXY(&Ae.x, &Ae.y);
			v = v->GetNextVertex();
			if (v->GetNextVertex() == NULL) break;
		}
	}
	return true;
}

//全部判定する
bool CAdminControl::JudgeAll()
{
	if (shape_head == NULL) {
		return true;
	}

	CShape *s = shape_head;
	CVertex *v = s->GetVertexhead();

	CShape *NowS = shape_head;
	CVertex *NowV = NowS->GetVertexhead();

	//自己・他己交差判定用
	ACPOINT As, Ae;
	ACPOINT Bs, Be;
	//内包判定用
	ACPOINT P;

	while (NowS != NULL) {
		NowV = NowS->GetVertexhead();
		NowV->GetXY(&Be.x, &Be.y);
		NowV = NowS->GetNextVertexLoop(NowV);

		NowV->GetXY(&P.x, &P.y);

		for (int i = 0; i < NowS->GetVertexCount(); i++) {
			NowV->GetXY(&Bs.x, &Bs.y);

			while (s != NULL) {
				v = s->GetVertexhead();
				v->GetXY(&Ae.x, &Ae.y);
				v = s->GetNextVertexLoop(v);

				//角度を格納するための配列の設定
				float *check;
				check = new float[s->GetVertexCount()];

				for (int j = 0; j < s->GetVertexCount(); j++) {
					v->GetXY(&As.x, &As.y);

					//自己・他己交差判定
					if (!CheckPoint(As, Bs) && !CheckPoint(Ae, Be) && !CheckPoint(As, Be) && !CheckPoint(Ae, Bs)) {
						CVector A(As.x, As.y, Ae.x, Ae.y), a1(As.x, As.y, Bs.x, Bs.y), a2(As.x, As.y, Be.x, Be.y);
						CVector B(Bs.x, Bs.y, Be.x, Be.y), b1(Bs.x, Bs.y, As.x, As.y), b2(Bs.x, Bs.y, Ae.x, Ae.y);

						if (ACM.CrossProduct(A, a1) * ACM.CrossProduct(A, a2) <= 0 && ACM.CrossProduct(B, b1) * ACM.CrossProduct(B, b2) <= 0) {
							delete[] check;
							return false;
						}
					}

					//内包判定準備
					check[j] = ACM.Angle(P.x, P.y, As.x, As.y, Ae.x, Ae.y);

					//更新処理
					v->GetXY(&Ae.x, &Ae.y);
					if (!s->GetClosedFlag() && v->GetNextVertex() == NULL) {
						break;
					}
					v = s->GetNextVertexLoop(v);
				}
				//内包判定
				float sum = 0;
				for (int k = 0; k < s->GetVertexCount(); k++) {
					sum = sum + check[k];
				}
				sum = (int)(fabsf(sum) * 100);

				delete[] check;
				if (sum == 628 && s->GetClosedFlag()) {
					return false;
				}

				//更新処理
				s = s->GetNextShape();
			}

			NowV->GetXY(&Be.x, &Be.y);
			if (!NowS->GetClosedFlag() && NowV->GetNextVertex() == NULL) {
				break;
			}
			NowV = NowS->GetNextVertexLoop(NowV);
			s = shape_head;

		}

		NowS = NowS->GetNextShape();
	}

	return true;
}

//点を選択する（小さめ）
void CAdminControl::ChoicePoint(float NewX, float NewY)
{
	ChoicePoint(NewX, NewY, 0.02, 0);
}

//点を選択する（n == 1の場合vertex_headしか選択しない）
void CAdminControl::ChoicePoint(float NewX, float NewY, float dis, int n)
{
	if (shape_head != NULL) {

		CShape *s = shape_head;
		ACPOINT P;

		while (s != NULL) {
			CVertex *v = s->GetVertexhead();
			while (v != NULL) {
				v->GetXY(&P.x, &P.y);
				if (ACM.Point_PointDistance(P.x, P.y, NewX, NewY) < dis) {
					NowPointS = s;
					NowPointV = v;

					if (n == 1 && NowPointV == NowPointS->GetVertexhead()){
						ClearChoice();
					}
					return;
				}
				v = v->GetNextVertex();
			}
			s = s->GetNextShape();
		}
	}
	NowPointS = NULL;
	NowPointV = NULL;
}

//稜線を選択する
void CAdminControl::ChoiceLine(float NewX, float NewY)
{
	if (shape_head != NULL) {

		//点の設定
		ACPOINT P = { NewX, NewY };
		ACPOINT A, B;
		CShape *s;
		s = shape_head;
		//点が2つ以下の場合検索しない
		if (shape_head->GetVertexCount() < 2) {
			s = s->GetNextShape();
		}

		while (s != NULL) {
			CVertex *v = s->GetVertexhead();
			CVertex *tmp;
			v->GetXY(&A.x, &A.y);
			int LineNum = s->GetVertexCount();
			if (!s->GetClosedFlag()) {
				LineNum--;
			}

			for (int i = 0; i < LineNum; i++) {
				tmp = s->GetNextVertexLoop(v);
				tmp->GetXY(&B.x, &B.y);

				float d = ACM.Point_LineDistance(P.x, P.y, A.x, A.y, B.x, B.y);
				//直線と点が近いかどうか判定
				if (d < 0.01 && NowPointV == NULL) {
					//点が線分の範囲内にあるかどうかの判定
					if (ACM.Check_Point_Line(P.x, P.y, A.x, A.y, B.x, B.y)) {

						NowLineS = s;
						NowLineV = v;
						return;
					}
				}
				tmp->GetXY(&A.x, &A.y);
				v = v->GetNextVertex();
			}
			s = s->GetNextShape();
		}
	}
	NowLineS = NULL;
	NowLineV = NULL;
}

//図形を選択する
void CAdminControl::ChoiceShape(float NewX, float NewY)
{
	if (shape_head != NULL) {

		//点の設定
		ACPOINT P = { NewX, NewY };
		ACPOINT A, B;
		CShape *s;
		s = shape_head;

		if (NowLineV != NULL) {
			return;
		}

		//shape_headの点が1つ以下の場合検索しない
		if (!shape_head->GetClosedFlag() && shape_head->GetVertexCount() < 2) {
			if (ShapeCount == 1) {
				NowShape = NULL;
				return;
			}
			else {
				s = s->GetNextShape();
			}
		}
		//shape_headが開いた図形の場合
		if (s != NULL && !s->GetClosedFlag()) {
			ChoiceLine(NewX, NewY);
			if (NowLineS != NULL) {
				CShape *tmp = NowLineS;
				ClearChoice();
				NowShape = tmp;
				return;
			}

			//shape_headの検索
			float *check;
			check = new float[shape_head->GetVertexCount()];

			CVertex *v = shape_head->GetVertexhead();
			v->GetXY(&A.x, &A.y);
			v = v->GetNextVertex();
			for (int i = 0; i < shape_head->GetVertexCount(); i++) {
				v->GetXY(&B.x, &B.y);

				check[i] = ACM.Angle(P.x, P.y, A.x, A.y, B.x, B.y);

				v->GetXY(&A.x, &A.y);
				v = shape_head->GetNextVertexLoop(v);
			}

			float sum = 0;
			for (int j = 0; j < shape_head->GetVertexCount(); j++) {
				sum = sum + check[j];
			}

			//3桁目までで切り捨てて判定する
			sum = (int)(fabsf(sum) * 100);

			//314 * 2 = 628
			delete[] check;
			if (sum == 628) {

				//shape_headの図形の中に、他の図形が含まれていない場合
				if (Judge4()) {
					NowShape = shape_head;
					return;
				}

				//shape_headの図形の中に、他の図形が含まれている場合
				s = s->GetNextShape();

				while (s != NULL) {
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
						NowShape = s;
						return;
					}
					else {
						s = s->GetNextShape();
					}
				}

				NowShape = shape_head;
				return;
			}
		}

		//shape_headが閉じた図形だった場合
		ChoiceLine(NewX, NewY);
		if (NowLineS != NULL) {
			CShape *tmp = NowLineS;
			ClearChoice();
			NowShape = tmp;
			return;
		}
		while (s != NULL) {
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
				NowShape = s;
				return;
			}
			else {
				s = s->GetNextShape();
			}
		}
	}

	NowShape = NULL;
}

//新しい点を選択する
void CAdminControl::ChoiceNewPoint(float NewX, float NewY)
{
	float New[2];

	ChoiceLine(NewX, NewY);

	if (NowLineV != NULL) {
		if (NowLineV->GetNextVertex() != NULL) {
			ACM.Perpendicular(New, NewX, NewY, NowLineV->GetX(), NowLineV->GetY(), NowLineV->GetNextVertex()->GetX(), NowLineV->GetNextVertex()->GetY());
		}
		else {
			ACM.Perpendicular(New, NewX, NewY, NowLineV->GetX(), NowLineV->GetY(), NowLineS->GetVertexhead()->GetX(), NowLineS->GetVertexhead()->GetY());
		}

		SetNewPoint(New[0], New[1]);
	}
	else {
		ChoiceShape(NewX, NewY);
	}
}

//選択を解除する
void CAdminControl::ClearChoice(void)
{
	NowPointS = NULL;
	NowPointV = NULL;
	NowLineS = NULL;
	NowLineV = NULL;
	NowShape = NULL;
}

//NewPointに格納する
void CAdminControl::SetNewPoint(float NewX, float NewY)
{
	NewPoint.x = NewX;
	NewPoint.y = NewY;
}

//ボタンのフラグ処理の代わり
//0→描画モード、1→移動、2→点の追加、3→点の削除、4→拡大・縮小、5→回転
//11→視点変更（移動）、12→視点変更（回転）
int CAdminControl::GetButtonMode()
{
	return ButtonMode;
}

//ボタンのフラグ処理の代わり
//0→描画モード、1→移動、2→点の追加、3→点の削除、4→拡大・縮小、5→回転
//11→視点変更（移動）、12→視点変更（回転）
void CAdminControl::SetButtonMode(int n)
{
	ButtonMode = n;
}

//ボタンのフラグ処理の代わり（独立してる）
//0→面張り、1→xyz軸
bool CAdminControl::GetSubButtonMode(int n)
{
	return SubButtonMode[n];
}

//ボタンのフラグ処理の代わり（独立してる）
//100で初期設定
//0→面張り、1→xyz軸
void CAdminControl::SetSubButtonMode(int n)
{
	//初期設定
	if (n == 100) {
		for (int i = 0; i < 2; i++) {
			SubButtonMode[i] = false;
		}
	}

	//フラグ処理
	if (0 <= n && n <= 1) {

		if (SubButtonMode[n]) {
			SubButtonMode[n] = false;
		}
		else {
			SubButtonMode[n] = true;
		}
	}

	//強制的に変更する
	if (n == 101) {
		SubButtonMode[0] = true;

		CShape *s = shape_head;
		while (s != NULL) {
			s->SetColorFlag(true);
			s = s->GetNextShape();
		}
	}

	//面張りの処理
	CShape *s = shape_head;
	while (s != NULL) {
		s->SetColorFlag(SubButtonMode[0]);
		s = s->GetNextShape();
	}
}


//LastPointに格納する
void CAdminControl::SetLastPoint()
{
	if (NowPointS != NULL) {
		NowPointV->GetXY(&LastPoint.x, &LastPoint.y);
	}
}

//LastPointに格納する
void CAdminControl::SetLastPoint(float x, float y)
{
	LastPoint.x = x;
	LastPoint.y = y;
}

//MoveBeforPointに格納する
void CAdminControl::SetMoveBeforPoint(float x, float y)
{
	MoveBeforPoint.x = x;
	MoveBeforPoint.y = y;
}

//CVertexとACPOINTを比べる
bool CAdminControl::CheckPoint(CVertex *v, ACPOINT p)
{
	if (v->GetX() == p.x && v->GetY() == p.y) {
		return true;
	}

	return false;
}

//CVertexとACPOINTを比べる
bool CAdminControl::CheckPoint(ACPOINT p, ACPOINT q)
{
	if (p.x == q.x && p.y == p.y) {
		return true;
	}

	return false;
}

//今選択しているものが何か返す
//0→選択してない、1→点、2→稜線、3→図形
int CAdminControl::GetNowChoice()
{
	if (NowPointS != NULL) {
		return 1;
	}
	else if (NowLineS != NULL) {
		return 2;
	}
	else if (NowShape != NULL) {
		return 3;
	}

	return 0;
}

//BBの中のどの点を選んでいるか
void CAdminControl::ChoiceBB(float x, float y)
{
	if (NowShape != NULL) {
		float MinX, MaxX, MinY, MaxY;
		ACPOINT A = { NowShape->GetBBPointX(1), NowShape->GetBBPointY(1) };
		ACPOINT B = { NowShape->GetBBPointX(2), NowShape->GetBBPointY(2) };
		ACPOINT C = { NowShape->GetBBPointX(3), NowShape->GetBBPointY(3) };
		ACPOINT D = { NowShape->GetBBPointX(4), NowShape->GetBBPointY(4) };

		if (ACM.Point_PointDistance(A.x, A.y, x, y) < 0.02) {
			BBPoint = 1;
			BBPointOtherSide = 3;
			return;
		}
		else if (ACM.Point_PointDistance(B.x, B.y, x, y) < 0.02) {
			BBPoint = 2;
			BBPointOtherSide = 4;
			return;
		}
		else if (ACM.Point_PointDistance(C.x, C.y, x, y) < 0.02) {
			BBPoint = 3;
			BBPointOtherSide = 1;
			return;
		}
		else if (ACM.Point_PointDistance(D.x, D.y, x, y) < 0.02) {
			BBPoint = 4;
			BBPointOtherSide = 2;
			return;
		}
		else
		{
			BBPoint = 0;
			BBPointOtherSide = 0;
		}
	}
}

//BBPoinntを返す
int CAdminControl::GetBBPoint()
{
	return BBPoint;
}

//BBPointを初期化格納する
void CAdminControl::ClearBBPoint(int n)
{
	if (NowShape != NULL && n == 1) {
		NowShape->ClearChangeBBFlag();
	}

	BBPoint = 0;
	BBPointOtherSide = 0;
}

//LastBBを格納する
void CAdminControl::SetLastBB()
{
	if (NowShape != NULL && BBPoint != 0) {
		LastBB.x = NowShape->GetBBPointX(BBPoint);
		LastBB.y = NowShape->GetBBPointY(BBPoint);
	}
}

//DrawBBFlagを格納
void CAdminControl::SetDrawBBFlag(bool b)
{
	DrawBBFlag = b;
}

//視点変更（移動）の移動量の設定
void CAdminControl::SetWatchMoveValue(float NowX, float NowY)
{
	CVector move(MoveBeforPoint.x, MoveBeforPoint.y, NowX, NowY);

	WatchValue.x = move.GetX();
	WatchValue.y = move.GetY();
	WatchValue.z = 0;
}

//WatchValueに格納する
void CAdminControl::SetWatchValue(float nx, float ny, float nz)
{
	WatchValue.x = nx;
	WatchValue.y = ny;
	WatchValue.z = nz;
}

//WatchValueに格納する（マウスホイールを利用する場合）
void CAdminControl::SetWatchValue(int del)
{
	//視点変更（移動）の場合
	if (GetButtonMode() == 11) {
		//z軸の場合
		if (GetXYZ() == 3) {
			if (del == 1) {
				WatchValue.z = 1.1;
			}
			else {
				WatchValue.z = 1 / 1.1;
			}
		}
		else {
			//x軸の場合
			if (GetXYZ() == 1) {
				WatchValue.x = del * 0.2;
			}
			//y軸の場合
			else if (GetXYZ() == 2) {
				WatchValue.y = del * 0.2;
			}
		}
	}

	//視点変更（回転）の場合
	else if (GetButtonMode() == 12) {
		WatchValue.z = 10 * del;
	}
}

//キーボード入力の処理（押していない場合0、押している間だけ切り替わる）
void CAdminControl::SetKeyButton(int key)
{
	//17→Ctrl、13→Enter
	KeyButton = key;
}

//xyzのどれかを格納する（x→1、y→2、z→3）
void CAdminControl::SetXYZ(int which)
{
	if (which == 1) {
		ChoiceXYZ = 1;
	}
	else if (which == 2) {
		ChoiceXYZ = 2;
	}
	else {
		ChoiceXYZ = 3;
	}
}

//xyzのどれかを返す（x→1、y→2、z→3）
int CAdminControl::GetXYZ()
{
	return ChoiceXYZ;
}

//色を入力する
void CAdminControl::SetDColor(float R, float G, float B)
{
	if (NowShape != NULL) {
		NowShape->SetColor(R, G, B);
	}
}

//選択されている図形の色を返却する
void CAdminControl::GetNowShapeColor(float *R, float *G, float *B)
{
	NowShape->GetColor(R, G, B);
}

//ドラッグしているか示す
void CAdminControl::SetDragFlag(bool flag)
{
	DragFlag = flag;
}

//shape_headが閉じているかどうか
bool CAdminControl::IsShapeHeadClosed()
{
	if (shape_head != NULL) {
		return shape_head->GetClosedFlag();
	}
}

//NowShapeがshape_headかどうか、また開いているなら選択を解除
void CAdminControl::CheckShapeHead()
{
	if (NowShape == shape_head && !IsShapeHeadClosed()) {
		ClearChoice();
	}
}

//shape_headがNULLならtrue
bool CAdminControl::IsShapeHeadNull()
{
	if (shape_head == NULL) {
		return true;
	}
	else {
		return false;
	}
}

//Shapeの数
int CAdminControl::GetShapeNum()
{
	CShape *s = shape_head;
	int num = 0;

	while (s != NULL) {
		num++;
		s = s->GetNextShape();
	}

	return num;
}

//DeleteErrorを返す
int CAdminControl::GetDeleteError()
{
	return DeleteError;
}


float CAdminControl::GetHighValue()
{
	return high;
}


void CAdminControl::SetHighValue(float h)
{
	high = h;
}
