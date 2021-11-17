
// WinOGLView.h : CWinOGLView クラスのインターフェイス
//

#pragma once
#include <gl/GL.h>
#include "AdminControl.h"
#include "afxwin.h"
#include "DColor.h"
#include "DChangeHigh.h"

class CWinOGLView : public CView
{
protected: // シリアル化からのみ作成します。
	CWinOGLView();
	DECLARE_DYNCREATE(CWinOGLView)

	// 属性
public:
	CWinOGLDoc* GetDocument() const;

	// 操作
public:

	// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

	// 実装
public:
	virtual ~CWinOGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 生成された、メッセージ割り当て関数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
private:
	// OpenGLを利用するために使用する変数
	HGLRC m_hRC;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	CAdminControl AC;
public:
	afx_msg void Onchange();
	afx_msg void OnUpdatechange(CCmdUI *pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnStartdraw();
	afx_msg void OnUpdateStartdraw(CCmdUI *pCmdUI);
	afx_msg void OnAppendpoint();
	afx_msg void OnUpdateAppendpoint(CCmdUI *pCmdUI);
	afx_msg void OnDeletepoint();
	afx_msg void OnUpdateDeletepoint(CCmdUI *pCmdUI);
	afx_msg void OnMouseLeave();
	afx_msg void OnShapechange();
	afx_msg void OnUpdateShapechange(CCmdUI *pCmdUI);
	afx_msg void OnShapeturn();
	afx_msg void OnUpdateShapeturn(CCmdUI *pCmdUI);
	afx_msg void OnMakesurface();
	afx_msg void OnUpdateMakesurface(CCmdUI *pCmdUI);
	afx_msg void OnXyz();
	afx_msg void OnUpdateXyz(CCmdUI *pCmdUI);
	afx_msg void OnWatchmove();
	afx_msg void OnUpdateWatchmove(CCmdUI *pCmdUI);
	afx_msg void OnWatchturn();
	afx_msg void OnUpdateWatchturn(CCmdUI *pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMenu1X();
	afx_msg void OnMenu1Y();
	afx_msg void OnMenu1Z();
	afx_msg void OnUpdateMenu1X(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenu1Y(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenu1Z(CCmdUI *pCmdUI);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void ClearWatch();
	afx_msg void OnShapeDel();
	afx_msg void OnAllDel();
	afx_msg void OnVertexDel();
	afx_msg void OnColor();
	afx_msg void OnUpdateColor(CCmdUI *pCmdUI);
	afx_msg void OnBothDel();
	afx_msg void OnHigh();
};

#ifndef _DEBUG  // WinOGLView.cpp のデバッグ バージョン
inline CWinOGLDoc* CWinOGLView::GetDocument() const
{
	return reinterpret_cast<CWinOGLDoc*>(m_pDocument);
}
#endif

