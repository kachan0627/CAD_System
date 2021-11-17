
// WinOGLView.cpp : CWinOGLView �N���X�̎���
//

#include "stdafx.h"
// SHARED_HANDLERS �́A�v���r���[�A�k���ŁA����ь����t�B���^�[ �n���h���[���������Ă��� ATL �v���W�F�N�g�Œ�`�ł��A
// ���̃v���W�F�N�g�Ƃ̃h�L�������g �R�[�h�̋��L���\�ɂ��܂��B
#ifndef SHARED_HANDLERS
#include "WinOGL.h"
#endif

#include "WinOGLDoc.h"
#include "WinOGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool MouseFlag = false;
bool DragFlag = false;
bool ChoiceShapeIs = false;
bool ChoiceVertexIs = false;
bool DFlag = false;

// CWinOGLView

IMPLEMENT_DYNCREATE(CWinOGLView, CView)

BEGIN_MESSAGE_MAP(CWinOGLView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_COMMAND(ID_change, &CWinOGLView::Onchange)
	ON_UPDATE_COMMAND_UI(ID_change, &CWinOGLView::OnUpdatechange)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_StartDraw, &CWinOGLView::OnStartdraw)
	ON_UPDATE_COMMAND_UI(ID_StartDraw, &CWinOGLView::OnUpdateStartdraw)
	ON_COMMAND(ID_AppendPoint, &CWinOGLView::OnAppendpoint)
	ON_UPDATE_COMMAND_UI(ID_AppendPoint, &CWinOGLView::OnUpdateAppendpoint)
	ON_COMMAND(ID_DeletePoint, &CWinOGLView::OnDeletepoint)
	ON_UPDATE_COMMAND_UI(ID_DeletePoint, &CWinOGLView::OnUpdateDeletepoint)
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSELEAVE()
	ON_COMMAND(ID_ShapeChange, &CWinOGLView::OnShapechange)
	ON_UPDATE_COMMAND_UI(ID_ShapeChange, &CWinOGLView::OnUpdateShapechange)
	ON_COMMAND(ID_ShapeTurn, &CWinOGLView::OnShapeturn)
	ON_UPDATE_COMMAND_UI(ID_ShapeTurn, &CWinOGLView::OnUpdateShapeturn)
	ON_COMMAND(ID_MakeSurface, &CWinOGLView::OnMakesurface)
	ON_UPDATE_COMMAND_UI(ID_MakeSurface, &CWinOGLView::OnUpdateMakesurface)
	ON_COMMAND(ID_XYZ, &CWinOGLView::OnXyz)
	ON_UPDATE_COMMAND_UI(ID_XYZ, &CWinOGLView::OnUpdateXyz)
	ON_COMMAND(ID_WatchMove, &CWinOGLView::OnWatchmove)
	ON_UPDATE_COMMAND_UI(ID_WatchMove, &CWinOGLView::OnUpdateWatchmove)
	ON_COMMAND(ID_WatchTurn, &CWinOGLView::OnWatchturn)
	ON_UPDATE_COMMAND_UI(ID_WatchTurn, &CWinOGLView::OnUpdateWatchturn)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID__TurnX, &CWinOGLView::OnMenu1X)
	ON_COMMAND(ID__TurnY, &CWinOGLView::OnMenu1Y)
	ON_COMMAND(ID__TurnZ, &CWinOGLView::OnMenu1Z)
	ON_UPDATE_COMMAND_UI(ID__TurnX, &CWinOGLView::OnUpdateMenu1X)
	ON_UPDATE_COMMAND_UI(ID__TurnY, &CWinOGLView::OnUpdateMenu1Y)
	ON_UPDATE_COMMAND_UI(ID__TurnZ, &CWinOGLView::OnUpdateMenu1Z)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID__ShapeDel, &CWinOGLView::OnShapeDel)
	ON_COMMAND(ID__ALLdel, &CWinOGLView::OnAllDel)
	ON_COMMAND(ID__VertexDel, &CWinOGLView::OnVertexDel)
	ON_COMMAND(ID_Color, &CWinOGLView::OnColor)
	ON_UPDATE_COMMAND_UI(ID_Color, &CWinOGLView::OnUpdateColor)
	ON_COMMAND(ID__BothDel, &CWinOGLView::OnBothDel)
	ON_COMMAND(ID__High, &CWinOGLView::OnHigh)
END_MESSAGE_MAP()


// CWinOGLView �R���X�g���N�V����/�f�X�g���N�V����

CWinOGLView::CWinOGLView()
{
	// TODO: �\�z�R�[�h�������ɒǉ����܂��B

}

CWinOGLView::~CWinOGLView()
{
}

BOOL CWinOGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���̈ʒu�� CREATESTRUCT cs ���C������ Window �N���X�܂��̓X�^�C����
	//  �C�����Ă��������B

	return CView::PreCreateWindow(cs);
}

// CWinOGLView �`��

void CWinOGLView::OnDraw(CDC* pDC)
{
	CWinOGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	wglMakeCurrent(pDC->m_hDC, m_hRC);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	AC.Draw();
	glFlush();
	SwapBuffers(pDC->m_hDC);

	wglMakeCurrent(pDC->m_hDC, NULL);
}


// CWinOGLView �f�f

#ifdef _DEBUG
void CWinOGLView::AssertValid() const
{
	CView::AssertValid();
}

void CWinOGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinOGLDoc* CWinOGLView::GetDocument() const // �f�o�b�O�ȊO�̃o�[�W�����̓C�����C���ł��B
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinOGLDoc)));
	return (CWinOGLDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinOGLView ���b�Z�[�W �n���h���[


void CWinOGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//�E�B���h�E�T�C�Y�ɍ��킹�Đ}�`��`�悷��
	DragFlag = true;
	AC.SetDragFlag(true);

	CRect rect;
	GetClientRect(rect);	//�`��̈�̑傫�����擾
	float viewing;
	float point_world_x;
	float point_world_y;	//���[���h���W�n

	viewing = (float)point.x / rect.Width();
	point_world_x = (2 * viewing) - 1;

	viewing = (float)point.y / rect.Height();
	viewing = 1 - viewing;
	point_world_y = (2 * viewing) - 1;

	float resize;
	if (rect.Height() < rect.Width()) {
		resize = (float)rect.Width() / rect.Height();
		point_world_x = point_world_x * resize;
	}
	else {
		resize = (float)rect.Height() / rect.Width();
		point_world_y = point_world_y * resize;
	}

	//�ҏW���[�h�̏ꍇ
	//�ړ�
	if (AC.GetButtonMode() == 1) {
		if (AC.GetNowChoice() == 1) {
			AC.SetLastPoint();
		}
		else if (AC.GetNowChoice() == 3) {
			AC.SetLastPoint(point_world_x, point_world_y);
			AC.SetMoveBeforPoint(point_world_x, point_world_y);
		}
	}
	//�_�̒ǉ�
	else if (AC.GetButtonMode() == 2) {
		AC.AddWorldPoint();
	}
	//�폜
	else if (AC.GetButtonMode() == 3) {
		if (AC.GetNowChoice() == 1) {
			AC.DeleteWorldPoint();

			//�G���[�\��
			if (AC.GetDeleteError() == 1) {
				CClientDC myDC(this);
				int ret = AfxMessageBox(_T("3�_�ȉ��̌`��ɂȂ邽�߁A���̓_�͍폜�ł��܂���B"), MB_OK | MB_APPLMODAL | MB_ICONSTOP);
			}
			else if (AC.GetDeleteError() == 2) {
				CClientDC myDC(this);
				int ret = AfxMessageBox(_T("�����܂��͓���邽�߁A���̓_�͍폜�ł��܂���B"), MB_OK | MB_APPLMODAL | MB_ICONSTOP);
			}
		}
		else if (AC.GetNowChoice() == 3) {
			AC.DeleteShape();
			if (AC.IsShapeHeadNull()) {
				AC.SetButtonMode(0);
			}
		}
	}
	//�g��E�k��
	else if (AC.GetButtonMode() == 4) {
		AC.SetLastPoint(point_world_x, point_world_y);
		AC.SetMoveBeforPoint(point_world_x, point_world_y);

		//�����I������Ă��Ȃ��ꍇ
		if (MouseFlag == false && AC.GetNowChoice() != 0) {
			MouseFlag = true;
		}
		else {
			//BB���I������Ă��Ȃ��ꍇ�A�}�`���Č���
			if (AC.GetBBPoint() == 0) {
				AC.ClearBBPoint(0);
				AC.ClearChoice();
				AC.ChoiceShape(point_world_x, point_world_y);
				if (AC.GetNowChoice() == 0) {
					MouseFlag = false;

				}
			}
		}
	}
	//��]
	else if (AC.GetButtonMode() == 5) {
		AC.SetLastPoint(point_world_x, point_world_y);
		AC.SetMoveBeforPoint(point_world_x, point_world_y);
		AC.SetLastBB();

		//�����I������Ă��Ȃ��ꍇ
		if (MouseFlag == false && AC.GetNowChoice() != 0) {
			MouseFlag = true;
		}
		else {
			//BB���I������Ă��Ȃ��ꍇ�A�}�`���Č���
			if (AC.GetBBPoint() == 0) {
				AC.ClearBBPoint(0);
				AC.ClearChoice();
				AC.ChoiceShape(point_world_x, point_world_y);
				if (AC.GetNowChoice() == 0) {
					MouseFlag = false;
				}
			}
		}
	}
	//�F�ҏW
	else if (AC.GetButtonMode() == 6) {
		//�����I������Ă��Ȃ��ꍇ
		if (MouseFlag == false && AC.GetNowChoice() == 3) {
			MouseFlag = true;
		}
		else {
			//BB���I������Ă��Ȃ��ꍇ�A�}�`���Č���
			if (AC.GetBBPoint() == 0) {
				AC.ClearBBPoint(0);
				AC.ClearChoice();
				AC.ChoiceShape(point_world_x, point_world_y);
				AC.CheckShapeHead();
				if (AC.GetNowChoice() == 0) {
					MouseFlag = false;
				}
			}
		}

		if (AC.GetNowChoice() == 3 && MouseFlag == true) {
			//�F�I���̃E�B���h�E���J��
			CDColor m_cd;
			float R, G, B;

			AC.GetNowShapeColor(&R, &G, &B);
			m_cd.SetDColor(R, G, B);
			m_cd.DoModal();
			bool DChange = m_cd.GetDColor(&R, &G, &B);
			//�L�����Z�����������ꍇ�A�ύX���Ȃ�
			if (DChange == true) {
				AC.SetDColor(R, G, B);
			}
			RedrawWindow();

			AC.ClearBBPoint(1);
			AC.ClearChoice();
			DragFlag = false;
			MouseFlag = false;
		}

		RedrawWindow();
	}

	//�`�惂�[�h�̏ꍇ
	else if (AC.GetButtonMode() == 0){
		//�n�_�̏ꍇ
		if (AC.GetHeadClosedFlag()) {
			if (AC.Judge3(point_world_x, point_world_y)) {
				AC.SetWorldPoint(point_world_x, point_world_y);
				AC.SetNewPoint(point_world_x, point_world_y);
			}
		}

		//�I�_�̏ꍇ
		else if (AC.FirstPointDistance(point_world_x, point_world_y) < 0.05) {
			if (AC.GetHeadVertexCount() > 2 && AC.Judge1(point_world_x, point_world_y) && AC.Judge2(point_world_x, point_world_y) && AC.Judge4() && AC.Judge5()) {
				AC.EndWorldPoint();
			}
		}
		//����ȊO�̏ꍇ
		else {
			AC.SetWorldPoint();
		}
	}

	//���_�ύX���[�h�̏ꍇ
	//�ړ�
	else if (AC.GetButtonMode() == 11) {
		AC.SetMoveBeforPoint(point_world_x, point_world_y);
	}



	//�`�悷��
	RedrawWindow();

	CView::OnLButtonDown(nFlags, point);
}


int CWinOGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		24,
		0, 0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0,
	};

	CClientDC clientDC(this);
	int pixelFormat = ChoosePixelFormat(clientDC.m_hDC, &pfd);
	SetPixelFormat(clientDC.m_hDC, pixelFormat, &pfd);
	m_hRC = wglCreateContext(clientDC.m_hDC);

	//�{�^���̏�����
	AC.SetSubButtonMode(100);

	return 0;
}


void CWinOGLView::OnDestroy()
{
	CView::OnDestroy();
	wglDeleteContext(m_hRC);
	AC.FreeAll();
}


BOOL CWinOGLView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}


void CWinOGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CClientDC clientDC(this);
	wglMakeCurrent(clientDC.m_hDC, m_hRC);

	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float resize;
	if (cy < cx) {
		resize = (float)cx / cy;
		glOrtho(-1 * resize, 1 * resize, -1, 1, -100, 100);
	}
	else {
		resize = (float)cy / cx;
		glOrtho(-1, 1, -1 * resize, 1 * resize, -100, 100);
	}

	glMatrixMode(GL_MODELVIEW);

	RedrawWindow();
	wglMakeCurrent(clientDC.m_hDC, NULL);
}

void CWinOGLView::OnMouseMove(UINT nFlags, CPoint point)
{

	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	//�E�B���h�E�T�C�Y�ɍ��킹�Đ}�`��`�悷��

	//���[���h���W�ɕϊ�����
	CRect rect;
	GetClientRect(rect);	//�`��̈�̑傫�����擾
	float viewing;
	float point_world_x;
	float point_world_y;	//���[���h���W�n

	viewing = (float)point.x / rect.Width();
	point_world_x = (2 * viewing) - 1;

	viewing = (float)point.y / rect.Height();
	viewing = 1 - viewing;
	point_world_y = (2 * viewing) - 1;

	float resize;
	if (rect.Height() < rect.Width()) {
		resize = (float)rect.Width() / rect.Height();
		point_world_x = point_world_x * resize;
	}
	else {
		resize = (float)rect.Height() / rect.Width();
		point_world_y = point_world_y * resize;
	}

	//���ꂼ��̏���
	//�ړ�
	if (AC.GetButtonMode() == 1) {
		if (DragFlag == true) {
			if (AC.GetNowChoice() == 1) {
				AC.MovePoint(point_world_x, point_world_y);
			}
			else if (AC.GetNowChoice() == 3) {
				AC.MoveShape(point_world_x, point_world_y);
				AC.SetMoveBeforPoint(point_world_x, point_world_y);
			}
		}
		else {
			AC.ClearChoice();
			if (ChoiceVertexIs == true) {
				AC.ChoicePoint(point_world_x, point_world_y);
			}
			if(ChoiceShapeIs == true) {
				AC.ChoiceShape(point_world_x, point_world_y);
			}
		}

		RedrawWindow();
	}
	//�_�̒ǉ�
	else if (AC.GetButtonMode() == 2) {
		AC.ClearChoice();
		AC.ChoiceNewPoint(point_world_x, point_world_y);

		RedrawWindow();
	}
	//�_�̍폜
	else if (AC.GetButtonMode() == 3) {
		AC.ClearChoice();
		if (ChoiceVertexIs == true) {
			AC.ChoicePoint(point_world_x, point_world_y);
		}
		if(ChoiceShapeIs == true) {
			AC.ChoiceShape(point_world_x, point_world_y);
		}

		RedrawWindow();
	}
	//�g��E�k��
	else if (AC.GetButtonMode() == 4) {
		if (MouseFlag == false) {
			AC.ClearChoice();
			AC.ChoiceShape(point_world_x, point_world_y);
		}
		else {
			if (DragFlag == false) {
				AC.ChoiceBB(point_world_x, point_world_y);
			}
			else {
				if (AC.GetBBPoint() != 0) {
					AC.ScalingShape(point_world_x, point_world_y);
				}
				else if (AC.GetNowChoice() == 3) {
					AC.MoveShape(point_world_x, point_world_y);
					AC.SetMoveBeforPoint(point_world_x, point_world_y);
				}
			}
		}

		RedrawWindow();
	}
	//��]
	else if (AC.GetButtonMode() == 5) {
		if (MouseFlag == false) {
			AC.ClearChoice();
			AC.ChoiceShape(point_world_x, point_world_y);
		}
		else {
			if (DragFlag == false) {
				AC.ChoiceBB(point_world_x, point_world_y);
			}
			else {
				if (AC.GetBBPoint() != 0) {
					AC.TurnShape(point_world_x, point_world_y);
					AC.SetMoveBeforPoint(point_world_x, point_world_y);
				}
				else if (AC.GetNowChoice() == 3) {
					AC.MoveShape(point_world_x, point_world_y);
					AC.SetMoveBeforPoint(point_world_x, point_world_y);
				}
			}
		}

		RedrawWindow();
	}
	//�F�ҏW
	else if (AC.GetButtonMode() == 6) {
		if (MouseFlag == false) {
			AC.ClearChoice();
			AC.ChoiceShape(point_world_x, point_world_y);
			AC.CheckShapeHead();
		}

		RedrawWindow();
	}
	//�`�惂�[�h
	else if (AC.GetButtonMode() == 0) {
		if (!AC.GetHeadClosedFlag()) {
			if (AC.FirstPointDistance(point_world_x, point_world_y) < 0.05) {
				if (AC.GetHeadVertexCount() > 2 && AC.Judge1(point_world_x, point_world_y) && AC.Judge2(point_world_x, point_world_y) && AC.Judge4() && AC.Judge5()) {
					AC.SetNewPoint(point_world_x, point_world_y); 
					AC.ChoicePoint(point_world_x, point_world_y, 0.05, 1);
					RedrawWindow();
				}
			}
			else if (AC.Judge1(point_world_x, point_world_y) && AC.Judge2(point_world_x, point_world_y)){
				AC.SetNewPoint(point_world_x, point_world_y);
				RedrawWindow();
			}
		}
	}
	//���_�ύX���[�h
	else if (AC.GetButtonMode() == 11) {
		if (DragFlag == true) {
			AC.SetWatchMoveValue(point_world_x, point_world_y);
			AC.SetMoveBeforPoint(point_world_x, point_world_y);
			RedrawWindow();
		}
	}

	CView::OnMouseMove(nFlags, point);
}

void CWinOGLView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	DragFlag = false;
	AC.SetDragFlag(false);
	AC.SetDrawBBFlag(true);

	//���[���h���W�ɕϊ�����
	CRect rect;
	GetClientRect(rect);	//�`��̈�̑傫�����擾
	float viewing;
	float point_world_x;
	float point_world_y;	//���[���h���W�n

	viewing = (float)point.x / rect.Width();
	point_world_x = (2 * viewing) - 1;

	viewing = (float)point.y / rect.Height();
	viewing = 1 - viewing;
	point_world_y = (2 * viewing) - 1;

	float resize;
	if (rect.Height() < rect.Width()) {
		resize = (float)rect.Width() / rect.Height();
		point_world_x = point_world_x * resize;
	}
	else {
		resize = (float)rect.Height() / rect.Width();
		point_world_y = point_world_y * resize;
	}

	//�ړ�
	if (AC.GetButtonMode() == 1) {
		if (!AC.JudgeAll()) {
			if (AC.GetNowChoice() == 1) {
				AC.MovePoint();
			}
			else if (AC.GetNowChoice() == 3) {
				AC.MoveShape();
			}
			RedrawWindow();
		}

		AC.ClearChoice();
	}
	//�g��E�k��
	else if (AC.GetButtonMode() == 4) {
		if (AC.GetBBPoint() != 0) {
			if (!AC.JudgeAll()) {
				AC.ScalingShape();
			}
			AC.ClearBBPoint(0);
		}
		else if (!AC.JudgeAll() && AC.GetNowChoice() == 3) {
			AC.MoveShape();
		}
		RedrawWindow();
	}
	//��]
	else if (AC.GetButtonMode() == 5) {
		if (AC.GetBBPoint() != 0) {
			if (!AC.JudgeAll()) {
				AC.TurnShape();
			}
			AC.ClearBBPoint(0);
		}
		else if (!AC.JudgeAll() && AC.GetNowChoice() == 3) {
			AC.MoveShape();
		}
		RedrawWindow();
	}
	//���_�ύX���[�h
	else if (AC.GetButtonMode() == 11) {
		RedrawWindow();
		AC.SetWatchValue(0, 0, 0);
	}

	CView::OnLButtonUp(nFlags, point);
}


void CWinOGLView::OnStartdraw()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetButtonMode() != 0) {
		AC.SetButtonMode(0);
		ClearWatch();
	}

	AC.ClearChoice();
	DragFlag = false;
	MouseFlag = false;
	RedrawWindow();
}


void CWinOGLView::OnUpdateStartdraw(CCmdUI *pCmdUI)
{
	// TODO:�����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetButtonMode() == 0) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}

void CWinOGLView::Onchange()
{
	if (AC.GetButtonMode() != 1) {
		AC.SetButtonMode(1);
		ClearWatch();
		ChoiceVertexIs = true;
		ChoiceShapeIs = true;
	}

	AC.ClearChoice();
	DragFlag = false;
	MouseFlag = false;
	RedrawWindow();
}

void CWinOGLView::OnUpdatechange(CCmdUI *pCmdUI)
{
	if (AC.GetButtonMode() == 1) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}

	if (AC.IsShapeHeadNull()) {
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
	}
}

void CWinOGLView::OnAppendpoint()
{
	if (AC.GetButtonMode() != 2) {
		AC.SetButtonMode(2);
		ClearWatch();
	}

	AC.ClearChoice();
	DragFlag = false;
	MouseFlag = false;
	RedrawWindow();
}

void CWinOGLView::OnUpdateAppendpoint(CCmdUI *pCmdUI)
{
	// TODO:�����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetButtonMode() == 2) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}

	if (AC.IsShapeHeadNull() || (AC.GetShapeNum() == 1 && AC.GetHeadVertexCount() < 2)) {
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
	}
}

void CWinOGLView::OnDeletepoint()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetButtonMode() != 3) {
		AC.SetButtonMode(3);
		ClearWatch();
		ChoiceVertexIs = true;
		ChoiceShapeIs = true;
	}

	AC.ClearChoice();
	DragFlag = false;
	MouseFlag = false;
	RedrawWindow();
}

void CWinOGLView::OnUpdateDeletepoint(CCmdUI *pCmdUI)
{
	// TODO:�����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetButtonMode() == 3) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}

	if (AC.IsShapeHeadNull() || (AC.GetShapeNum() == 1 && AC.GetHeadVertexCount() < 2)) {
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
	}
}

void CWinOGLView::OnMouseLeave()
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	AC.MovePoint();
	DragFlag = false;
	MouseFlag = false;
	AC.ClearChoice();
	RedrawWindow();

	CView::OnMouseLeave();
}


void CWinOGLView::OnShapechange()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetButtonMode() != 4) {
		AC.SetButtonMode(4);
		ClearWatch();
	}

	AC.ClearBBPoint(1);
	AC.ClearChoice();
	DragFlag = false;
	MouseFlag = false;
	RedrawWindow();
}


void CWinOGLView::OnUpdateShapechange(CCmdUI *pCmdUI)
{
	// TODO:�����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetButtonMode() == 4) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}

	if (AC.IsShapeHeadNull() || (AC.GetShapeNum() == 1 && AC.GetHeadVertexCount() < 2)) {
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
	}
}


void CWinOGLView::OnShapeturn()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetButtonMode() != 5) {
		AC.SetButtonMode(5);
		ClearWatch();
	}

	AC.ClearBBPoint(1);
	AC.ClearChoice();
	DragFlag = false;
	MouseFlag = false;
	RedrawWindow();
}


void CWinOGLView::OnUpdateShapeturn(CCmdUI *pCmdUI)
{
	// TODO:�����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetButtonMode() == 5) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}

	if (AC.IsShapeHeadNull() || (AC.GetShapeNum() == 1 && AC.GetHeadVertexCount() < 2)) {
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
	}
}


void CWinOGLView::OnMakesurface()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	AC.SetSubButtonMode(0);

	if (AC.GetButtonMode() == 6 || AC.GetButtonMode() == 11 || AC.GetButtonMode() == 12) {
		AC.SetSubButtonMode(101);
	}
	RedrawWindow();
}


void CWinOGLView::OnUpdateMakesurface(CCmdUI *pCmdUI)
{
	// TODO:�����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetSubButtonMode(0)) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void CWinOGLView::OnXyz()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	AC.SetSubButtonMode(1);
	RedrawWindow();
}


void CWinOGLView::OnUpdateXyz(CCmdUI *pCmdUI)
{
	// TODO:�����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetSubButtonMode(1)) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void CWinOGLView::OnWatchmove()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.IsShapeHeadClosed()) {
		if (AC.GetButtonMode() != 11) {
			AC.SetButtonMode(11);
			AC.SetXYZ(3);
		}

		AC.ClearBBPoint(1);
		AC.ClearChoice();
		DragFlag = false;
		MouseFlag = false;
		AC.SetWatchValue(0, 0, 0);
		RedrawWindow();
	}
	else {
		CClientDC myDC(this);
		int ret = AfxMessageBox(_T("���Ă��Ȃ��`�󂪂��邽�߁A���̉��ł��܂���B"), MB_OK | MB_APPLMODAL | MB_ICONSTOP);
		AC.SetButtonMode(0);
	}
}


void CWinOGLView::OnUpdateWatchmove(CCmdUI *pCmdUI)
{
	// TODO:�����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetButtonMode() == 11) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}

	if (AC.IsShapeHeadNull() || !AC.IsShapeHeadClosed()) {
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
	}
}


void CWinOGLView::OnWatchturn()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.IsShapeHeadClosed()) {
		if (AC.GetButtonMode() != 12) {
			AC.SetButtonMode(12);
			AC.SetXYZ(3);
		}

		AC.ClearBBPoint(1);
		AC.ClearChoice();
		DragFlag = false;
		MouseFlag = false;
		AC.SetWatchValue(0, 0, 0);
		RedrawWindow();
	}
	else {
		CClientDC myDC(this);
		int ret = AfxMessageBox(_T("���Ă��Ȃ��`�󂪂��邽�߁A���̉��ł��܂���B"), MB_OK | MB_APPLMODAL | MB_ICONSTOP);
		AC.SetButtonMode(0);
	}
}


void CWinOGLView::OnUpdateWatchturn(CCmdUI *pCmdUI)
{
	// TODO:�����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetButtonMode() == 12) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}

	if (AC.IsShapeHeadNull() || !AC.IsShapeHeadClosed()) {
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
	}
}

void CWinOGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	AC.SetKeyButton(nChar);

	//�`��쐬���[�h�̏ꍇ
	if (AC.GetButtonMode() == 0 && nChar == 13) {
		if (AC.GetHeadVertexCount() > 2 && AC.Judge4() && AC.Judge5()) {
			//Enter���������Ƃ��A������Ȃ����
			AC.EndWorldPoint();
			RedrawWindow();
		}
	}
	//���_�ύX���[�h�̏ꍇ
	else if ((AC.GetButtonMode() == 11 || AC.GetButtonMode() == 12) && nChar == 13) {
		//Enter�������ꂽ�ꍇ�ŏ��̎��_�ɖ߂�
		ClearWatch();
		AC.SetXYZ(3);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CWinOGLView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	AC.SetKeyButton(0);
	DragFlag = false;

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CWinOGLView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

	//�|�b�v�A�b�v��\�����邩���肷��
	#define PNum 9
	int PopPupNum[PNum] = { 0, 1, 2, 3, 4, 5, 6, 11, 12 };
	bool PFlag = false;

	for (int i = 0; i < PNum; i++) {
		if (AC.GetButtonMode() == PopPupNum[i]) {
			PFlag = true;
			break;
		}
	}

	if (PFlag == true) {
		CMenu *popupMenuP = NULL;
		CMenu cMenu;
		int err = 0;

		//****************�|�b�v�A�b�v�̑I��******************
		//xyz���̃|�b�v�A�b�v
		if (AC.GetButtonMode() == 11 || AC.GetButtonMode() == 12) {
			if (!err) if (!cMenu.LoadMenu(IDR_MENU1)) err = 1;
		}
		//�I���A�S�폜�̃|�b�v�A�b�v
		else if (AC.GetButtonMode() == 1 || AC.GetButtonMode() == 3) {
			if (!err) if (!cMenu.LoadMenu(IDR_MENU2)) err = 1;
		}
		//�S�폜�̃|�b�v�A�b�v
		else if (AC.GetButtonMode() == 0 || AC.GetButtonMode() == 2 || AC.GetButtonMode() == 4 || AC.GetButtonMode() == 5 || AC.GetButtonMode() == 6) {
			if (!err) if (!cMenu.LoadMenu(IDR_MENU3)) err = 1;
		}
		//*****************�����܂�***************************

		if (!err) if ((popupMenuP = cMenu.GetSubMenu(0)) == NULL) err = 1;
		if (!err)
		{
			ClientToScreen(&point);
			if (!popupMenuP->TrackPopupMenu(TPM_LEFTBUTTON, point.x, point.y, this)) err = 1;
		}

		cMenu.DestroyMenu();
	}

	CView::OnRButtonUp(nFlags, point);
}


void CWinOGLView::OnMenu1X()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	AC.SetXYZ(1);
	RedrawWindow();
}


void CWinOGLView::OnMenu1Y()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	AC.SetXYZ(2);
	RedrawWindow();
}


void CWinOGLView::OnMenu1Z()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	AC.SetXYZ(3);
	RedrawWindow();
}


void CWinOGLView::OnUpdateMenu1X(CCmdUI *pCmdUI)
{
	// TODO:�����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetXYZ() == 1) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void CWinOGLView::OnUpdateMenu1Y(CCmdUI *pCmdUI)
{
	// TODO:�����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetXYZ() == 2) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void CWinOGLView::OnUpdateMenu1Z(CCmdUI *pCmdUI)
{
	// TODO:�����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetXYZ() == 3) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


BOOL CWinOGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	if (AC.GetButtonMode() == 11 && DragFlag == false) {
		if (zDelta > 0) {
			AC.SetWatchValue(1);
		}
		else {
			AC.SetWatchValue(-1);
		}
	}
	else if (AC.GetButtonMode() == 12) {
		if (zDelta > 0) {
			AC.SetWatchValue(1);
		}
		else {
			AC.SetWatchValue(-1);
		}
	}

	RedrawWindow();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CWinOGLView::ClearWatch()
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		24,
		0, 0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0,
	};

	CClientDC clientDC(this);
	int pixelFormat = ChoosePixelFormat(clientDC.m_hDC, &pfd);
	SetPixelFormat(clientDC.m_hDC, pixelFormat, &pfd);
	m_hRC = wglCreateContext(clientDC.m_hDC);

	//��ʃT�C�Y�ɍ��킹�ĕϊ�
	CRect rect;
	GetClientRect(&rect);

	int cx = rect.right;
	int cy = rect.bottom;

	wglMakeCurrent(clientDC.m_hDC, m_hRC);

	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float resize;
	if (cy < cx) {
		resize = (float)cx / cy;
		glOrtho(-1 * resize, 1 * resize, -1, 1, -100, 100);
	}
	else {
		resize = (float)cy / cx;
		glOrtho(-1, 1, -1 * resize, 1 * resize, -100, 100);
	}

	glMatrixMode(GL_MODELVIEW);


	RedrawWindow();
	wglMakeCurrent(clientDC.m_hDC, NULL);
}

void CWinOGLView::OnVertexDel()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	ChoiceVertexIs = true;
	ChoiceShapeIs = false;
	RedrawWindow();
}

void CWinOGLView::OnShapeDel()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	ChoiceVertexIs = false;
	ChoiceShapeIs = true;
	RedrawWindow();
}


void CWinOGLView::OnAllDel()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	CClientDC myDC(this);
	int ret = AfxMessageBox(_T("�{���ɍ폜���܂����H\n�i�폜����ƌ��ɂ͖߂�܂���j"), MB_OKCANCEL | MB_APPLMODAL | MB_ICONQUESTION);

	if (ret == 1) {
		AC.FreeAll();
		AC.SetButtonMode(0);
	}
	RedrawWindow();
}

void CWinOGLView::OnColor()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetButtonMode() != 6) {
		AC.SetButtonMode(6);
		ClearWatch();
	}

	AC.ClearBBPoint(1);
	AC.ClearChoice();
	DragFlag = false;
	MouseFlag = false;
	RedrawWindow();
}


void CWinOGLView::OnUpdateColor(CCmdUI *pCmdUI)
{
	// TODO:�����ɃR�}���h�X�V UI �n���h���[ �R�[�h��ǉ����܂��B
	if (AC.GetButtonMode() == 6) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}

	if (AC.IsShapeHeadNull() || (AC.GetShapeNum() == 1 && !AC.IsShapeHeadClosed())) {
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
	}
}

void CWinOGLView::OnBothDel()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B
	ChoiceVertexIs = true;
	ChoiceShapeIs = true;
	RedrawWindow();
}


void CWinOGLView::OnHigh()
{
	// TODO: �����ɃR�}���h �n���h���[ �R�[�h��ǉ����܂��B

	float high = AC.GetHighValue();
	CDChangeHigh m_cd;
	m_cd.SetHighValue(high);
	m_cd.DoModal();
	if (m_cd.GetOKFlag()) {
		high = m_cd.GetHighValue();
		AC.SetHighValue(high);
	}

	RedrawWindow();
}
