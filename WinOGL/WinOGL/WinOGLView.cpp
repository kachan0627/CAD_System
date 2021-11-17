
// WinOGLView.cpp : CWinOGLView クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
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


// CWinOGLView コンストラクション/デストラクション

CWinOGLView::CWinOGLView()
{
	// TODO: 構築コードをここに追加します。

}

CWinOGLView::~CWinOGLView()
{
}

BOOL CWinOGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CWinOGLView 描画

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


// CWinOGLView 診断

#ifdef _DEBUG
void CWinOGLView::AssertValid() const
{
	CView::AssertValid();
}

void CWinOGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinOGLDoc* CWinOGLView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinOGLDoc)));
	return (CWinOGLDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinOGLView メッセージ ハンドラー


void CWinOGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//ウィンドウサイズに合わせて図形を描画する
	DragFlag = true;
	AC.SetDragFlag(true);

	CRect rect;
	GetClientRect(rect);	//描画領域の大きさを取得
	float viewing;
	float point_world_x;
	float point_world_y;	//ワールド座標系

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

	//編集モードの場合
	//移動
	if (AC.GetButtonMode() == 1) {
		if (AC.GetNowChoice() == 1) {
			AC.SetLastPoint();
		}
		else if (AC.GetNowChoice() == 3) {
			AC.SetLastPoint(point_world_x, point_world_y);
			AC.SetMoveBeforPoint(point_world_x, point_world_y);
		}
	}
	//点の追加
	else if (AC.GetButtonMode() == 2) {
		AC.AddWorldPoint();
	}
	//削除
	else if (AC.GetButtonMode() == 3) {
		if (AC.GetNowChoice() == 1) {
			AC.DeleteWorldPoint();

			//エラー表示
			if (AC.GetDeleteError() == 1) {
				CClientDC myDC(this);
				int ret = AfxMessageBox(_T("3点以下の形状になるため、この点は削除できません。"), MB_OK | MB_APPLMODAL | MB_ICONSTOP);
			}
			else if (AC.GetDeleteError() == 2) {
				CClientDC myDC(this);
				int ret = AfxMessageBox(_T("交差または内包するため、この点は削除できません。"), MB_OK | MB_APPLMODAL | MB_ICONSTOP);
			}
		}
		else if (AC.GetNowChoice() == 3) {
			AC.DeleteShape();
			if (AC.IsShapeHeadNull()) {
				AC.SetButtonMode(0);
			}
		}
	}
	//拡大・縮小
	else if (AC.GetButtonMode() == 4) {
		AC.SetLastPoint(point_world_x, point_world_y);
		AC.SetMoveBeforPoint(point_world_x, point_world_y);

		//何も選択されていない場合
		if (MouseFlag == false && AC.GetNowChoice() != 0) {
			MouseFlag = true;
		}
		else {
			//BBが選択されていない場合、図形を再検索
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
	//回転
	else if (AC.GetButtonMode() == 5) {
		AC.SetLastPoint(point_world_x, point_world_y);
		AC.SetMoveBeforPoint(point_world_x, point_world_y);
		AC.SetLastBB();

		//何も選択されていない場合
		if (MouseFlag == false && AC.GetNowChoice() != 0) {
			MouseFlag = true;
		}
		else {
			//BBが選択されていない場合、図形を再検索
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
	//色編集
	else if (AC.GetButtonMode() == 6) {
		//何も選択されていない場合
		if (MouseFlag == false && AC.GetNowChoice() == 3) {
			MouseFlag = true;
		}
		else {
			//BBが選択されていない場合、図形を再検索
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
			//色選択のウィンドウを開く
			CDColor m_cd;
			float R, G, B;

			AC.GetNowShapeColor(&R, &G, &B);
			m_cd.SetDColor(R, G, B);
			m_cd.DoModal();
			bool DChange = m_cd.GetDColor(&R, &G, &B);
			//キャンセルを押した場合、変更しない
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

	//描画モードの場合
	else if (AC.GetButtonMode() == 0){
		//始点の場合
		if (AC.GetHeadClosedFlag()) {
			if (AC.Judge3(point_world_x, point_world_y)) {
				AC.SetWorldPoint(point_world_x, point_world_y);
				AC.SetNewPoint(point_world_x, point_world_y);
			}
		}

		//終点の場合
		else if (AC.FirstPointDistance(point_world_x, point_world_y) < 0.05) {
			if (AC.GetHeadVertexCount() > 2 && AC.Judge1(point_world_x, point_world_y) && AC.Judge2(point_world_x, point_world_y) && AC.Judge4() && AC.Judge5()) {
				AC.EndWorldPoint();
			}
		}
		//それ以外の場合
		else {
			AC.SetWorldPoint();
		}
	}

	//視点変更モードの場合
	//移動
	else if (AC.GetButtonMode() == 11) {
		AC.SetMoveBeforPoint(point_world_x, point_world_y);
	}



	//描画する
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

	//ボタンの初期化
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

	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	//ウィンドウサイズに合わせて図形を描画する

	//ワールド座標に変換する
	CRect rect;
	GetClientRect(rect);	//描画領域の大きさを取得
	float viewing;
	float point_world_x;
	float point_world_y;	//ワールド座標系

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

	//それぞれの処理
	//移動
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
	//点の追加
	else if (AC.GetButtonMode() == 2) {
		AC.ClearChoice();
		AC.ChoiceNewPoint(point_world_x, point_world_y);

		RedrawWindow();
	}
	//点の削除
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
	//拡大・縮小
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
	//回転
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
	//色編集
	else if (AC.GetButtonMode() == 6) {
		if (MouseFlag == false) {
			AC.ClearChoice();
			AC.ChoiceShape(point_world_x, point_world_y);
			AC.CheckShapeHead();
		}

		RedrawWindow();
	}
	//描画モード
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
	//視点変更モード
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
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	DragFlag = false;
	AC.SetDragFlag(false);
	AC.SetDrawBBFlag(true);

	//ワールド座標に変換する
	CRect rect;
	GetClientRect(rect);	//描画領域の大きさを取得
	float viewing;
	float point_world_x;
	float point_world_y;	//ワールド座標系

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

	//移動
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
	//拡大・縮小
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
	//回転
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
	//視点変更モード
	else if (AC.GetButtonMode() == 11) {
		RedrawWindow();
		AC.SetWatchValue(0, 0, 0);
	}

	CView::OnLButtonUp(nFlags, point);
}


void CWinOGLView::OnStartdraw()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
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
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
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
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
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
	// TODO: ここにコマンド ハンドラー コードを追加します。
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
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
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
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	AC.MovePoint();
	DragFlag = false;
	MouseFlag = false;
	AC.ClearChoice();
	RedrawWindow();

	CView::OnMouseLeave();
}


void CWinOGLView::OnShapechange()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
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
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
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
	// TODO: ここにコマンド ハンドラー コードを追加します。
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
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
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
	// TODO: ここにコマンド ハンドラー コードを追加します。
	AC.SetSubButtonMode(0);

	if (AC.GetButtonMode() == 6 || AC.GetButtonMode() == 11 || AC.GetButtonMode() == 12) {
		AC.SetSubButtonMode(101);
	}
	RedrawWindow();
}


void CWinOGLView::OnUpdateMakesurface(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	if (AC.GetSubButtonMode(0)) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void CWinOGLView::OnXyz()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	AC.SetSubButtonMode(1);
	RedrawWindow();
}


void CWinOGLView::OnUpdateXyz(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	if (AC.GetSubButtonMode(1)) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void CWinOGLView::OnWatchmove()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
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
		int ret = AfxMessageBox(_T("閉じていない形状があるため、立体化できません。"), MB_OK | MB_APPLMODAL | MB_ICONSTOP);
		AC.SetButtonMode(0);
	}
}


void CWinOGLView::OnUpdateWatchmove(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
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
	// TODO: ここにコマンド ハンドラー コードを追加します。
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
		int ret = AfxMessageBox(_T("閉じていない形状があるため、立体化できません。"), MB_OK | MB_APPLMODAL | MB_ICONSTOP);
		AC.SetButtonMode(0);
	}
}


void CWinOGLView::OnUpdateWatchturn(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
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
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	AC.SetKeyButton(nChar);

	//形状作成モードの場合
	if (AC.GetButtonMode() == 0 && nChar == 13) {
		if (AC.GetHeadVertexCount() > 2 && AC.Judge4() && AC.Judge5()) {
			//Enterを押したとき、閉じられるなら閉じる
			AC.EndWorldPoint();
			RedrawWindow();
		}
	}
	//視点変更モードの場合
	else if ((AC.GetButtonMode() == 11 || AC.GetButtonMode() == 12) && nChar == 13) {
		//Enterが押された場合最初の視点に戻る
		ClearWatch();
		AC.SetXYZ(3);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CWinOGLView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	AC.SetKeyButton(0);
	DragFlag = false;

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CWinOGLView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	//ポップアップを表示するか判定する
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

		//****************ポップアップの選択******************
		//xyz軸のポップアップ
		if (AC.GetButtonMode() == 11 || AC.GetButtonMode() == 12) {
			if (!err) if (!cMenu.LoadMenu(IDR_MENU1)) err = 1;
		}
		//選択、全削除のポップアップ
		else if (AC.GetButtonMode() == 1 || AC.GetButtonMode() == 3) {
			if (!err) if (!cMenu.LoadMenu(IDR_MENU2)) err = 1;
		}
		//全削除のポップアップ
		else if (AC.GetButtonMode() == 0 || AC.GetButtonMode() == 2 || AC.GetButtonMode() == 4 || AC.GetButtonMode() == 5 || AC.GetButtonMode() == 6) {
			if (!err) if (!cMenu.LoadMenu(IDR_MENU3)) err = 1;
		}
		//*****************ここまで***************************

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
	// TODO: ここにコマンド ハンドラー コードを追加します。
	AC.SetXYZ(1);
	RedrawWindow();
}


void CWinOGLView::OnMenu1Y()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	AC.SetXYZ(2);
	RedrawWindow();
}


void CWinOGLView::OnMenu1Z()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	AC.SetXYZ(3);
	RedrawWindow();
}


void CWinOGLView::OnUpdateMenu1X(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	if (AC.GetXYZ() == 1) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void CWinOGLView::OnUpdateMenu1Y(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	if (AC.GetXYZ() == 2) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void CWinOGLView::OnUpdateMenu1Z(CCmdUI *pCmdUI)
{
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
	if (AC.GetXYZ() == 3) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


BOOL CWinOGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
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

	//画面サイズに合わせて変換
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
	// TODO: ここにコマンド ハンドラー コードを追加します。
	ChoiceVertexIs = true;
	ChoiceShapeIs = false;
	RedrawWindow();
}

void CWinOGLView::OnShapeDel()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	ChoiceVertexIs = false;
	ChoiceShapeIs = true;
	RedrawWindow();
}


void CWinOGLView::OnAllDel()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
	CClientDC myDC(this);
	int ret = AfxMessageBox(_T("本当に削除しますか？\n（削除すると元には戻りません）"), MB_OKCANCEL | MB_APPLMODAL | MB_ICONQUESTION);

	if (ret == 1) {
		AC.FreeAll();
		AC.SetButtonMode(0);
	}
	RedrawWindow();
}

void CWinOGLView::OnColor()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。
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
	// TODO:ここにコマンド更新 UI ハンドラー コードを追加します。
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
	// TODO: ここにコマンド ハンドラー コードを追加します。
	ChoiceVertexIs = true;
	ChoiceShapeIs = true;
	RedrawWindow();
}


void CWinOGLView::OnHigh()
{
	// TODO: ここにコマンド ハンドラー コードを追加します。

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
