#include "stdafx.h"
#include "ACDraw.h"

CACDraw::CACDraw()
{
}


CACDraw::~CACDraw()
{
}

//�}�`��`�悷��i��{�`�j
void CACDraw::Draw(CShape *s)
{
	DrawShape(s, 5, 1.0, 0.7, 0.7, 0.7);
}

//�}�`��`�悷��
void CACDraw::DrawShape(CShape *s, GLfloat size, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
	//�����}�`�̏ꍇ
	if (s->GetClosedFlag()) {
		//�_�̕`��
		glColor3f(R, G, B);
		glPointSize(size);
		glBegin(GL_POINTS);
		for (CVertex *v = s->GetVertexhead(); v != NULL; v = v->GetNextVertex()) {
			glVertex2f(v->GetX(), v->GetY());
		}
		glEnd();

		//�Ő��̕`��
		glColor3f(R, G, B);
		glLineWidth(width);
		glBegin(GL_LINE_LOOP);
		for (CVertex *v = s->GetVertexhead(); v != NULL; v = v->GetNextVertex()) {
			glVertex2f(v->GetX(), v->GetY());
		}
		glEnd();
	}
	//�J�����}�`�̏ꍇ
	else {
		//�_�̕`��
		glColor3f(R, G, B);
		glPointSize(size);
		glBegin(GL_POINTS);
		for (CVertex *v = s->GetVertexhead(); v != NULL; v = v->GetNextVertex()) {
			glVertex2f(v->GetX(), v->GetY());
		}
		glEnd();

		//�Ő��̕`��
		glColor3f(R, G, B);
		glLineWidth(width);
		glBegin(GL_LINE_STRIP);
		for (CVertex *v = s->GetVertexhead(); v != NULL; v = v->GetNextVertex()) {
			glVertex2f(v->GetX(), v->GetY());
		}
		glEnd();
	}
}

//�Ő��i�Ɠ_�j��`�悷��
void CACDraw::DrawLine(CShape *s, CVertex *v, GLfloat size, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
	//�_�̕`��
	CVertex *tmp = v;
	glColor3f(R, G, B);
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(tmp->GetX(), tmp->GetY());
	tmp = s->GetNextVertexLoop(tmp);
	glVertex2f(tmp->GetX(), tmp->GetY());
	glEnd();

	//�Ő��̕`��
	tmp = v;
	glColor3f(R, G, B);
	glLineWidth(width);
	glBegin(GL_LINES);
	glVertex2f(tmp->GetX(), tmp->GetY());
	tmp = s->GetNextVertexLoop(tmp);
	glVertex2f(tmp->GetX(), tmp->GetY());
	glEnd();
}

//�_���ŗŐ��i�Ɠ_�j��`�悷��
void CACDraw::DrawDotLine(CVertex *v, float x, float y, GLfloat size, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
	//�_�̕`��
	glColor3f(R, G, B);
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(v->GetX(), v->GetY());
	glVertex2f(x, y);
	glEnd();

	//�Ő��̕`��
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

//�_��`�悷��
void CACDraw::DrawPoint(CVertex *v, GLfloat size, GLfloat R, GLfloat G, GLfloat B)
{
	glColor3f(R, G, B);
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(v->GetX(), v->GetY());
	glEnd();
}

//�_��`�悷��
void CACDraw::DrawPoint(float x, float y, GLfloat size, GLfloat R, GLfloat G, GLfloat B)
{
	glColor3f(R, G, B);
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

//�_����BB��`�悷��
void CACDraw::DrawBB(CShape *s, GLfloat size, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
	//�_�̕`��
	glColor3f(R, G, B);
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex2f(s->GetBBPointX(1), s->GetBBPointY(1));
	glVertex2f(s->GetBBPointX(2), s->GetBBPointY(2));
	glVertex2f(s->GetBBPointX(3), s->GetBBPointY(3));
	glVertex2f(s->GetBBPointX(4), s->GetBBPointY(4));
	glEnd();

	//�Ő��̕`��
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

//�ʒ���i�ʏ�j
void CACDraw::DrawColor(CShape *s)
{
	float R, G, B;
	s->GetColor(&R, &G, &B);
	DrawColor(s, R, G, B);
}

//�ʒ���i�F�w��j
void CACDraw::DrawColor(CShape *s, float R, float G, float B)
{
	//ClosedShapeFlag��ColorFlag��false�������牽�����Ȃ�
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


	//***************��������e�X�g�p�⏕��***************
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
	//*******************�����܂�*************************
}

//XYZ���̕`��
void CACDraw::DrawXYZ()
{
	glEnable(GL_DEPTH_TEST);
	glLineWidth(1.0);
	glBegin(GL_LINES);

	//X��
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);

	//Y��
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, -1.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);

	//Z��
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
		//X��
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-1.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
	}
	else if (n == 2) {
		//Y��
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, -1.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
	}
	else if (n == 3) {
		//Z��
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, -1.0);
		glVertex3f(0.0, 0.0, 1.0);
	}

	glEnd();
	glDisable(GL_DEPTH_TEST);
}





//�������牺�͌v�Z�Ƃ�����Ƃ��Ƃ�
//�ʌ`��Ȃ�true�A���`��Ȃ�false��Ԃ�
bool CACDraw::WhichShape(CShape *s)
{
	//�ʌ`�󉻂ǂ�������
	float *check;
	check = new float[s->GetVertexCount()];
	DPOINT A, B, C;
	CVertex *v = s->GetVertexhead();

	//B���擪����NULL�܂œ����AA�͂���1�O�AC�͂���1��
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
	//�����_�ȉ���؂�̂�
	sum = (int)sum;
	delete[] check;

	int tmp = s->GetVertexCount() - 2;
	if (tmp * 180 == sum) {
		return true;
	}

	return false;
}

//��������
bool CACDraw::Judge1(CShape *s, CVertex *StartV, CVertex *EndV)
{
	//Bs��Be�̐ݒ�
	DPOINT Bs, Be;
	StartV->GetXY(&Bs.x, &Bs.y);
	EndV->GetXY(&Be.x, &Be.y);

	CVertex *v = s->GetVertexhead();

	//As��Ae�̐ݒ�
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

//���_�̓����i�ʏ�̓�����true��false���t�Ȃ̂Œ��Ӂj
bool CACDraw::Judge2(CShape *s, CVertex *StartV, CVertex *EndV)
{
	//���_�̍��W
	DPOINT P = { (StartV->GetX() + EndV->GetX()) / 2, (StartV->GetY() + EndV->GetY()) / 2 };
	DPOINT A, B;

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
		return true;
	}

	return false;
}

//�_�̔�r
bool CACDraw::CheckPoint(DPOINT p, DPOINT q)
{
	if (p.x == q.x && p.y == p.y) {
		return true;
	}

	return false;
}




void CACDraw::GetTrianglePoint(CShape *s)
{
	//ClosedShapeFlag��ColorFlag��false�������牽�����Ȃ�
	if (s->GetClosedFlag() == false || s->GetColorFlag() == false) {
		return;
	}

	//Triangle�̏���
	s->FreeTriangle();

	while (s->GetVertexCountT() != 3) {
		//v�͒����̓_���w��
		CVertex *v = s->GetVertexhead()->GetNextVertex();
		if (v->GetThroughFlag()) {
			v = s->GetNextVertexLoopT(v);
		}

		for (int i = 0; i < s->GetVertexCountT(); i++) {
			//LastV��NextV�̍X�V����
			CVertex *LastV = s->GetLastVertexLoopT(v);
			CVertex *NextV = s->GetNextVertexLoopT(v);

			//����
			if (Judge1(s, LastV, NextV) && Judge2(s, LastV, NextV)) {
				s->AppendTriangle(LastV->GetX(), LastV->GetY(), v->GetX(), v->GetY(), NextV->GetX(), NextV->GetY());
				v->SetThroughFlag(true);
				break;
			}

			//v�̍X�V����
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

	//����Ƃ��̏���
	s->ClearThroughFlag();
}
