
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

//�S���`�悷��
void CAdminControl::Draw()
{
	//���_�ύX���[�h
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
		//x�����S�̏ꍇ
		if (GetXYZ() == 1) {
			glRotatef(WatchValue.z, 1, 0, 0);
		}
		//y�����S�̏ꍇ
		else if (GetXYZ() == 2) {
			glRotatef(WatchValue.z, 0, 1, 0);
		}
		//z�����S�̏ꍇ
		else {
			glRotatef(WatchValue.z, 0, 0, 1);
		}
		SetWatchValue(0, 0, 0);
	}

	//XYZ��
	if (GetSubButtonMode(1)) {
		ACD.DrawXYZ();
		if (GetButtonMode() == 11 || GetButtonMode() == 12) {
			ACD.DrawXYZ(GetXYZ());
		}
	}

	if (GetButtonMode() != 11 && GetButtonMode() != 12) {
		//2�����̕`��
		Draw2();
	}
	else {
		//3�����̕`��
		Draw3();
	}
}

//�S���`�悷��i2�����j
void CAdminControl::Draw2()
{
	if (shape_head != NULL) {
		//�S��
		//�ʒ���
		CShape *s = shape_head;
		if (GetSubButtonMode(0)) {
			while (s != NULL) {
				//�ʒ���̗�O�������낢��
				if (s == NowPointS || s == NowLineS || s == NowShape) {
					s = s->GetNextShape();
				}
				else {
					ACD.DrawColor(s);
					s = s->GetNextShape();
				}
			}
		}
		//�g�Ɠ_
		for (CShape *s = shape_head; s != NULL; s = s->GetNextShape()) {
			ACD.Draw(s);
		}

		//�e���[�h���Ƃ̏���
		//�`�惂�[�h
		if (GetButtonMode() == 0 && !shape_head->GetClosedFlag())
		{
			ACD.DrawDotLine(shape_head->GetVertexhead(), NewPoint.x, NewPoint.y, 5, 1, 1, 1, 1);

			if (NowPointV != NULL) {
				ACD.DrawPoint(NowPointV, 8, 1, 1, 1);
				ClearChoice();
			}
		}
		//�ҏW���[�h�i�ړ��j
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
		//�ҏW���[�h�i�ǉ��j
		else if (GetButtonMode() == 2) {
			if (NowLineV != NULL) {
				ACD.DrawPoint(NewPoint.x, NewPoint.y, 10, 0, 1.0, 0);
			}
		}
		//�ҏW���[�h�i�폜�j
		else if (GetButtonMode() == 3) {
			if (NowPointV != NULL) {
				ACD.DrawPoint(NowPointV, 10, 0, 1.0, 0);
			}
			else if (NowShape != NULL) {
				ACD.DrawShape(NowShape, 5, 1.0, 0, 1, 0);
			}
		}
		//�ҏW���[�h�i�g��E�k���j
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
		//�ҏW���[�h�i��]�j
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
		//�F�ҏW
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

//�S���`�悷��i3�����j
void CAdminControl::Draw3()
{
	CShape *s = shape_head;

	//�����I�ɖʒ���
	SetSubButtonMode(101);
	while (s != NULL) {
		ACD.GetTrianglePoint(s);
		s = s->GetNextShape();
	}

	//�@���x�N�g��
	float Ni, Nj, Nk;

	//�}�e���A���̐ݒ�
	//����
	float dif[4] = { 1.0, 1.0, 1.0, 1.0 };
	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	//******************��������`�揈��*********************
	s = shape_head;
	CTriangle *t;

	while (s != NULL) {
		//�F
		float R, G, B;
		s->GetColor(&R, &G, &B);
		float C[4] = { R, G, B, 10 };

		//�^�����͌����Ȃ��̂ő΍�
		if (R == 0 && G == 0 && B == 0) {
			C[0] = 0.025;
			C[1] = 0.025;
			C[2] = 0.025;
		}

		glMaterialfv(GL_FRONT, GL_DIFFUSE, C);
		glMaterialfv(GL_FRONT, GL_AMBIENT, C);

		//�E���̎�true
		bool RightFlag = true;

		//�\��
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

		//����
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

		//����
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

	//**********************�����܂�*************************
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);
}

//���[���h���W���i�[����
void CAdminControl::SetWorldPoint(float wx, float wy)
{
	//1�_�ڂ̏���
	if (shape_head == NULL || shape_head->GetClosedFlag()) {
		AppendShape();
		shape_head->AppendVertex(wx, wy);
		SetFirstPoint(wx, wy);
	}
	//2�_�ڈȍ~�̏���
	else {
		shape_head->AppendVertex(wx, wy);
	}
}

//���[���h���W���i�[����
void CAdminControl::SetWorldPoint()
{
	
	SetWorldPoint(NewPoint.x, NewPoint.y);
}

//�_���ړ�������
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

//LastPoint�Ɉړ�������
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

//�}�`�̈ړ�
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

//���̏ꏊ�Ɉړ�
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

//�_��ǉ�����
void CAdminControl::AddWorldPoint(void)
{
	if (NowLineV != NULL) {
		NowLineS->AddVertex(NewPoint.x, NewPoint.y, NowLineV);
	}
}

//�_���폜����
void CAdminControl::DeleteWorldPoint(void)
{
	//0���G���[�����A1��3�_�ȉ��ɂȂ�A2�������܂��͓����
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

//�}�`���폜����
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

		//�����}�`��1�Ԗڂ̏ꍇ
		if (LastS == NULL) {
			shape_head = NowShape->GetNextShape();
		}
		//�����}�`���Ō�̏ꍇ
		else if (NowShape->GetNextShape() == NULL) {
			LastS->SetNextShape(NULL);
		}
		//����ȊO�̏ꍇ
		else {
			LastS->SetNextShape(NowShape->GetNextShape());
		}

		delete NowShape;
	}

	ClearChoice();
}

//�g��E�k��
void CAdminControl::ScalingShape(float NowX, float NowY)
{
	if (NowShape != NULL) {
		CVertex *v = NowShape->GetVertexhead();
		//�{��
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

//�g��E�k��
void CAdminControl::ScalingShape()
{
	if (NowShape != NULL) {
		CVertex *v = NowShape->GetVertexhead();
		//�{��
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

//��]
void CAdminControl::TurnShape(float NowX, float NowY)
{
	if (NowShape != NULL) {
		CVertex *v = NowShape->GetVertexhead();

		//��_
		ACPOINT CardinalPoint = { NowShape->GetCenterPointX(), NowShape->GetCenterPointY() };

		//�p�x
		float angle = ACM.Angle(CardinalPoint.x, CardinalPoint.y, MoveBeforPoint.x, MoveBeforPoint.y, NowX, NowY);

		float CosAngle = cos(angle);
		float SinAngle = sin(angle);

		//BB�̉�]
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

		//�}�`�̉�]
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

//��]
void CAdminControl::TurnShape()
{
	if (NowShape != NULL) {
		CVertex *v = NowShape->GetVertexhead();

		//��_
		ACPOINT CardinalPoint = { NowShape->GetCenterPointX(), NowShape->GetCenterPointY() };
		//�p�x
		float angle = ACM.Angle(CardinalPoint.x, CardinalPoint.y, NowShape->GetBBPointX(BBPoint), NowShape->GetBBPointY(BBPoint), LastBB.x, LastBB.y);

		float CosAngle = cos(angle);
		float SinAngle = sin(angle);

		//BB�̉�]
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

		//�}�`�̉�]
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

//1�_�ڂ��i�[����
void CAdminControl::SetFirstPoint(float x, float y)
{
	FirstPoint.x = x;
	FirstPoint.y = y;
}

//�I�_�̎��̏���
void CAdminControl::EndWorldPoint(void)
{
	shape_head->SetClosedFlag(true);

	if (GetSubButtonMode(0)) {
		shape_head->SetColorFlag(true);
	}
}

//1�_�ڂ�x���W��Ԃ�
float CAdminControl::GetFirstPointX()
{
	return FirstPoint.x;
}

//1�_�ڂ�y���W��Ԃ�
float CAdminControl::GetFirstPointY()
{
	return FirstPoint.y;
}

//�`��r���̓_��x���W��Ԃ�
float CAdminControl::GetNewPointX()
{
	return NewPoint.x;
}

//�`��r���̓_��y���W��Ԃ�
float CAdminControl::GetNewPointY()
{
	return NewPoint.y;
}

//�擪��Vertex�̌���Ԃ�
int CAdminControl::GetHeadVertexCount(void)
{
	return shape_head->GetVertexCount();
}

//�擪��shape��ClosedFlag��Ԃ�
bool CAdminControl::GetHeadClosedFlag(void)
{
	//1�ڂ̐}�`�̏ꍇ
	if (shape_head == NULL) {
		return true;
	}

	//����ȊO�̏ꍇ
	return shape_head->GetClosedFlag();
}

//Shape��ǉ�����
void CAdminControl::AppendShape()
{
	CShape *S1 = new CShape();
	S1->SetNextShape(shape_head);
	shape_head = S1;
	ShapeCount++;
}

//Shape�̂݊J������
void CAdminControl::FreeShape()
{
	for (CShape *tmp = shape_head; shape_head != NULL;) {
		tmp = tmp->GetNextShape();
		delete shape_head;
		shape_head = tmp;
	}
}

//�S���J������
void CAdminControl::FreeAll(void)
{
	for (CShape *s = shape_head; s != NULL; s = s->GetNextShape()) {
		s->FreeVertex();
		s->FreeTriangle();
	}
	FreeShape();
}

//1�_�ڂƓ_(x, y)�̋�����Ԃ�
float CAdminControl::FirstPointDistance(float x, float y)
{
	float dis;
	dis = ACM.Point_PointDistance(x, y, GetFirstPointX(), GetFirstPointY());

	return dis;
}

//NowPoint�Ɠ_(x, y)�̋�����Ԃ�
float CAdminControl::FirstPointDistance(void)
{
	float dis;
	dis = ACM.Point_PointDistance(NewPoint.x, NewPoint.y, GetFirstPointX(), GetFirstPointY());

	return dis;
}

//���Ȍ�������i�������Ă��Ȃ����true��Ԃ��j
bool CAdminControl::Judge1(float NewX, float NewY)
{
	//1�`3�_�ڂ̂Ƃ�
	if (shape_head == NULL || GetHeadVertexCount() < 3) {
		return true;
	}

	CShape *s = shape_head;
	CVertex *v = s->GetVertexhead();

	//Bs��Be�̐ݒ�
	ACPOINT Bs;
	v->GetXY(&Bs.x, &Bs.y);
	v = v->GetNextVertex();
	ACPOINT Be = { NewX, NewY };

	//As��Ae�̐ݒ�
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

//���̌`��Ƃ̌�������i�������Ă��Ȃ����true��Ԃ��j
bool CAdminControl::Judge2(float NewX, float NewY)
{
	//1�ڂ̐}�`�̂Ƃ�
	if (shape_head == NULL || ShapeCount < 2) {
		return true;
	}

	CShape *s = shape_head;
	CVertex *v = s->GetVertexhead();

	//Bs��Be�̐ݒ�
	ACPOINT Bs;
	ACPOINT Be = { NewX, NewY };
	v->GetXY(&Bs.x, &Bs.y);

	//As��Ae�̐ݒ�
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

//�����F�n�_�i�����Ă��Ȃ����true��Ԃ��j
bool CAdminControl::Judge3(float NewX, float NewY)
{
	//1�ڂ̐}�`�̂Ƃ�
	if (shape_head == NULL || (ShapeCount < 2 && !GetHeadClosedFlag())) {
		return true;
	}

	//�_�̐ݒ�
	ACPOINT P = { NewX, NewY };
	ACPOINT A, B;
	CShape *s = shape_head;

	while (s != NULL) {
		//�p�x���i�[���邽�߂̔z��̐ݒ�
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
		//3���ڂ܂łŐ؂�̂ĂĔ��肷��
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

//�����F�I�_�i�����Ă��Ȃ����true��Ԃ��j
//shape_head�̐}�`�������ꍇ�A���̐}�`��1�_�ڂ������Ă��Ȃ������`�F�b�N����
bool CAdminControl::Judge4(void)
{
	//1�ڂ̐}�`�̏ꍇ
	if (ShapeCount < 1) {
		return true;
	}

	//�_�̐ݒ�
	ACPOINT P;
	ACPOINT A, B;

	//�_A��B�p��s��v�i������shape_head�j
	CShape *s1 = shape_head;
	CVertex *v1 = s1->GetVertexhead();

	//�_P�p��s��v�ishape_head�̎�����NULL�܂Łj
	CShape *s2 = shape_head->GetNextShape();
	CVertex *v2;

	while (s2 != NULL) {
		v2 = s2->GetVertexhead();
		v2->GetXY(&P.x, &P.y);

		v1 = s1->GetVertexhead();
		v1->GetXY(&A.x, &A.y);
		v1 = v1->GetNextVertex();

		//�p�x���i�[���邽�߂̔z��̐ݒ�
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

//�����v�΍�
bool CAdminControl::Judge5(void)
{
	CShape *s = shape_head;
	CVertex *v = s->GetVertexhead();

	if (s->GetVertexCount() <= 3) {
		return true;
	}

	//Bs��Be�̐ݒ�
	ACPOINT Bs;
	ACPOINT Be = { GetFirstPointX(), GetFirstPointY() };
	v->GetXY(&Bs.x, &Bs.y);

	//As��Ae�̐ݒ�
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

//�S�����肷��
bool CAdminControl::JudgeAll()
{
	if (shape_head == NULL) {
		return true;
	}

	CShape *s = shape_head;
	CVertex *v = s->GetVertexhead();

	CShape *NowS = shape_head;
	CVertex *NowV = NowS->GetVertexhead();

	//���ȁE���Ȍ�������p
	ACPOINT As, Ae;
	ACPOINT Bs, Be;
	//�����p
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

				//�p�x���i�[���邽�߂̔z��̐ݒ�
				float *check;
				check = new float[s->GetVertexCount()];

				for (int j = 0; j < s->GetVertexCount(); j++) {
					v->GetXY(&As.x, &As.y);

					//���ȁE���Ȍ�������
					if (!CheckPoint(As, Bs) && !CheckPoint(Ae, Be) && !CheckPoint(As, Be) && !CheckPoint(Ae, Bs)) {
						CVector A(As.x, As.y, Ae.x, Ae.y), a1(As.x, As.y, Bs.x, Bs.y), a2(As.x, As.y, Be.x, Be.y);
						CVector B(Bs.x, Bs.y, Be.x, Be.y), b1(Bs.x, Bs.y, As.x, As.y), b2(Bs.x, Bs.y, Ae.x, Ae.y);

						if (ACM.CrossProduct(A, a1) * ACM.CrossProduct(A, a2) <= 0 && ACM.CrossProduct(B, b1) * ACM.CrossProduct(B, b2) <= 0) {
							delete[] check;
							return false;
						}
					}

					//����菀��
					check[j] = ACM.Angle(P.x, P.y, As.x, As.y, Ae.x, Ae.y);

					//�X�V����
					v->GetXY(&Ae.x, &Ae.y);
					if (!s->GetClosedFlag() && v->GetNextVertex() == NULL) {
						break;
					}
					v = s->GetNextVertexLoop(v);
				}
				//�����
				float sum = 0;
				for (int k = 0; k < s->GetVertexCount(); k++) {
					sum = sum + check[k];
				}
				sum = (int)(fabsf(sum) * 100);

				delete[] check;
				if (sum == 628 && s->GetClosedFlag()) {
					return false;
				}

				//�X�V����
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

//�_��I������i�����߁j
void CAdminControl::ChoicePoint(float NewX, float NewY)
{
	ChoicePoint(NewX, NewY, 0.02, 0);
}

//�_��I������in == 1�̏ꍇvertex_head�����I�����Ȃ��j
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

//�Ő���I������
void CAdminControl::ChoiceLine(float NewX, float NewY)
{
	if (shape_head != NULL) {

		//�_�̐ݒ�
		ACPOINT P = { NewX, NewY };
		ACPOINT A, B;
		CShape *s;
		s = shape_head;
		//�_��2�ȉ��̏ꍇ�������Ȃ�
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
				//�����Ɠ_���߂����ǂ�������
				if (d < 0.01 && NowPointV == NULL) {
					//�_�������͈͓̔��ɂ��邩�ǂ����̔���
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

//�}�`��I������
void CAdminControl::ChoiceShape(float NewX, float NewY)
{
	if (shape_head != NULL) {

		//�_�̐ݒ�
		ACPOINT P = { NewX, NewY };
		ACPOINT A, B;
		CShape *s;
		s = shape_head;

		if (NowLineV != NULL) {
			return;
		}

		//shape_head�̓_��1�ȉ��̏ꍇ�������Ȃ�
		if (!shape_head->GetClosedFlag() && shape_head->GetVertexCount() < 2) {
			if (ShapeCount == 1) {
				NowShape = NULL;
				return;
			}
			else {
				s = s->GetNextShape();
			}
		}
		//shape_head���J�����}�`�̏ꍇ
		if (s != NULL && !s->GetClosedFlag()) {
			ChoiceLine(NewX, NewY);
			if (NowLineS != NULL) {
				CShape *tmp = NowLineS;
				ClearChoice();
				NowShape = tmp;
				return;
			}

			//shape_head�̌���
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

			//3���ڂ܂łŐ؂�̂ĂĔ��肷��
			sum = (int)(fabsf(sum) * 100);

			//314 * 2 = 628
			delete[] check;
			if (sum == 628) {

				//shape_head�̐}�`�̒��ɁA���̐}�`���܂܂�Ă��Ȃ��ꍇ
				if (Judge4()) {
					NowShape = shape_head;
					return;
				}

				//shape_head�̐}�`�̒��ɁA���̐}�`���܂܂�Ă���ꍇ
				s = s->GetNextShape();

				while (s != NULL) {
					//�p�x���i�[���邽�߂̔z��̐ݒ�
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

					//3���ڂ܂łŐ؂�̂ĂĔ��肷��
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

		//shape_head�������}�`�������ꍇ
		ChoiceLine(NewX, NewY);
		if (NowLineS != NULL) {
			CShape *tmp = NowLineS;
			ClearChoice();
			NowShape = tmp;
			return;
		}
		while (s != NULL) {
			//�p�x���i�[���邽�߂̔z��̐ݒ�
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

			//3���ڂ܂łŐ؂�̂ĂĔ��肷��
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

//�V�����_��I������
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

//�I������������
void CAdminControl::ClearChoice(void)
{
	NowPointS = NULL;
	NowPointV = NULL;
	NowLineS = NULL;
	NowLineV = NULL;
	NowShape = NULL;
}

//NewPoint�Ɋi�[����
void CAdminControl::SetNewPoint(float NewX, float NewY)
{
	NewPoint.x = NewX;
	NewPoint.y = NewY;
}

//�{�^���̃t���O�����̑���
//0���`�惂�[�h�A1���ړ��A2���_�̒ǉ��A3���_�̍폜�A4���g��E�k���A5����]
//11�����_�ύX�i�ړ��j�A12�����_�ύX�i��]�j
int CAdminControl::GetButtonMode()
{
	return ButtonMode;
}

//�{�^���̃t���O�����̑���
//0���`�惂�[�h�A1���ړ��A2���_�̒ǉ��A3���_�̍폜�A4���g��E�k���A5����]
//11�����_�ύX�i�ړ��j�A12�����_�ύX�i��]�j
void CAdminControl::SetButtonMode(int n)
{
	ButtonMode = n;
}

//�{�^���̃t���O�����̑���i�Ɨ����Ă�j
//0���ʒ���A1��xyz��
bool CAdminControl::GetSubButtonMode(int n)
{
	return SubButtonMode[n];
}

//�{�^���̃t���O�����̑���i�Ɨ����Ă�j
//100�ŏ����ݒ�
//0���ʒ���A1��xyz��
void CAdminControl::SetSubButtonMode(int n)
{
	//�����ݒ�
	if (n == 100) {
		for (int i = 0; i < 2; i++) {
			SubButtonMode[i] = false;
		}
	}

	//�t���O����
	if (0 <= n && n <= 1) {

		if (SubButtonMode[n]) {
			SubButtonMode[n] = false;
		}
		else {
			SubButtonMode[n] = true;
		}
	}

	//�����I�ɕύX����
	if (n == 101) {
		SubButtonMode[0] = true;

		CShape *s = shape_head;
		while (s != NULL) {
			s->SetColorFlag(true);
			s = s->GetNextShape();
		}
	}

	//�ʒ���̏���
	CShape *s = shape_head;
	while (s != NULL) {
		s->SetColorFlag(SubButtonMode[0]);
		s = s->GetNextShape();
	}
}


//LastPoint�Ɋi�[����
void CAdminControl::SetLastPoint()
{
	if (NowPointS != NULL) {
		NowPointV->GetXY(&LastPoint.x, &LastPoint.y);
	}
}

//LastPoint�Ɋi�[����
void CAdminControl::SetLastPoint(float x, float y)
{
	LastPoint.x = x;
	LastPoint.y = y;
}

//MoveBeforPoint�Ɋi�[����
void CAdminControl::SetMoveBeforPoint(float x, float y)
{
	MoveBeforPoint.x = x;
	MoveBeforPoint.y = y;
}

//CVertex��ACPOINT���ׂ�
bool CAdminControl::CheckPoint(CVertex *v, ACPOINT p)
{
	if (v->GetX() == p.x && v->GetY() == p.y) {
		return true;
	}

	return false;
}

//CVertex��ACPOINT���ׂ�
bool CAdminControl::CheckPoint(ACPOINT p, ACPOINT q)
{
	if (p.x == q.x && p.y == p.y) {
		return true;
	}

	return false;
}

//���I�����Ă�����̂������Ԃ�
//0���I�����ĂȂ��A1���_�A2���Ő��A3���}�`
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

//BB�̒��̂ǂ̓_��I��ł��邩
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

//BBPoinnt��Ԃ�
int CAdminControl::GetBBPoint()
{
	return BBPoint;
}

//BBPoint���������i�[����
void CAdminControl::ClearBBPoint(int n)
{
	if (NowShape != NULL && n == 1) {
		NowShape->ClearChangeBBFlag();
	}

	BBPoint = 0;
	BBPointOtherSide = 0;
}

//LastBB���i�[����
void CAdminControl::SetLastBB()
{
	if (NowShape != NULL && BBPoint != 0) {
		LastBB.x = NowShape->GetBBPointX(BBPoint);
		LastBB.y = NowShape->GetBBPointY(BBPoint);
	}
}

//DrawBBFlag���i�[
void CAdminControl::SetDrawBBFlag(bool b)
{
	DrawBBFlag = b;
}

//���_�ύX�i�ړ��j�̈ړ��ʂ̐ݒ�
void CAdminControl::SetWatchMoveValue(float NowX, float NowY)
{
	CVector move(MoveBeforPoint.x, MoveBeforPoint.y, NowX, NowY);

	WatchValue.x = move.GetX();
	WatchValue.y = move.GetY();
	WatchValue.z = 0;
}

//WatchValue�Ɋi�[����
void CAdminControl::SetWatchValue(float nx, float ny, float nz)
{
	WatchValue.x = nx;
	WatchValue.y = ny;
	WatchValue.z = nz;
}

//WatchValue�Ɋi�[����i�}�E�X�z�C�[���𗘗p����ꍇ�j
void CAdminControl::SetWatchValue(int del)
{
	//���_�ύX�i�ړ��j�̏ꍇ
	if (GetButtonMode() == 11) {
		//z���̏ꍇ
		if (GetXYZ() == 3) {
			if (del == 1) {
				WatchValue.z = 1.1;
			}
			else {
				WatchValue.z = 1 / 1.1;
			}
		}
		else {
			//x���̏ꍇ
			if (GetXYZ() == 1) {
				WatchValue.x = del * 0.2;
			}
			//y���̏ꍇ
			else if (GetXYZ() == 2) {
				WatchValue.y = del * 0.2;
			}
		}
	}

	//���_�ύX�i��]�j�̏ꍇ
	else if (GetButtonMode() == 12) {
		WatchValue.z = 10 * del;
	}
}

//�L�[�{�[�h���͂̏����i�����Ă��Ȃ��ꍇ0�A�����Ă���Ԃ����؂�ւ��j
void CAdminControl::SetKeyButton(int key)
{
	//17��Ctrl�A13��Enter
	KeyButton = key;
}

//xyz�̂ǂꂩ���i�[����ix��1�Ay��2�Az��3�j
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

//xyz�̂ǂꂩ��Ԃ��ix��1�Ay��2�Az��3�j
int CAdminControl::GetXYZ()
{
	return ChoiceXYZ;
}

//�F����͂���
void CAdminControl::SetDColor(float R, float G, float B)
{
	if (NowShape != NULL) {
		NowShape->SetColor(R, G, B);
	}
}

//�I������Ă���}�`�̐F��ԋp����
void CAdminControl::GetNowShapeColor(float *R, float *G, float *B)
{
	NowShape->GetColor(R, G, B);
}

//�h���b�O���Ă��邩����
void CAdminControl::SetDragFlag(bool flag)
{
	DragFlag = flag;
}

//shape_head�����Ă��邩�ǂ���
bool CAdminControl::IsShapeHeadClosed()
{
	if (shape_head != NULL) {
		return shape_head->GetClosedFlag();
	}
}

//NowShape��shape_head���ǂ����A�܂��J���Ă���Ȃ�I��������
void CAdminControl::CheckShapeHead()
{
	if (NowShape == shape_head && !IsShapeHeadClosed()) {
		ClearChoice();
	}
}

//shape_head��NULL�Ȃ�true
bool CAdminControl::IsShapeHeadNull()
{
	if (shape_head == NULL) {
		return true;
	}
	else {
		return false;
	}
}

//Shape�̐�
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

//DeleteError��Ԃ�
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
