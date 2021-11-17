#pragma once
#include "afxwin.h"
#include "WinOGL.h"

// CDColor ダイアログ

class CDColor : public CDialogEx
{
	DECLARE_DYNAMIC(CDColor)

public:
	CDColor(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CDColor();

// ダイアログ データ
	enum { IDD = IDD_DColor };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMThemeChangedSred(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void MyPeint();
	CStatic m_pict;
	CScrollBar m_sbar1;
	CScrollBar m_sbar2;
	CScrollBar m_sbar3;

	afx_msg void OnBnClickedOk();
private:
	bool OKflag = false;
	int Ri = 1;
	int Gi = 1;
	int Bi = 1;
public:
	bool GetDColor(float *R, float *G, float *B);
	afx_msg void OnBnClickedCancel();
	void SetDColor(float Rf, float Gf, float Bf);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
