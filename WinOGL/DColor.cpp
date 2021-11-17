// DColor.cpp : 実装ファイル
//

#include "stdafx.h"
#include "DColor.h"
#include "afxdialogex.h"


// CDColor ダイアログ

IMPLEMENT_DYNAMIC(CDColor, CDialogEx)

CDColor::CDColor(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDColor::IDD, pParent)
{

}

CDColor::~CDColor()
{
}

void CDColor::DoDataExchange(CDataExchange* pDX)
{
	CScrollBar *mySBAR1 = (CScrollBar *)GetDlgItem(IDC_SRed);
	mySBAR1->SetScrollRange(0, 255);
	mySBAR1->SetScrollPos(Ri);

	CScrollBar *mySBAR2 = (CScrollBar *)GetDlgItem(IDC_SGreen);
	mySBAR2->SetScrollRange(0, 255);
	mySBAR2->SetScrollPos(Gi);

	CScrollBar *mySBAR3 = (CScrollBar *)GetDlgItem(IDC_SBlue);
	mySBAR3->SetScrollRange(0, 255);
	mySBAR3->SetScrollPos(Bi);

	DDX_Control(pDX, IDC_PICT, m_pict);
	DDX_Control(pDX, IDC_SRed, m_sbar1);
	DDX_Control(pDX, IDC_SGreen, m_sbar2);
	DDX_Control(pDX, IDC_SBlue, m_sbar3);

	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDColor, CDialogEx)
	ON_NOTIFY(NM_THEMECHANGED, IDC_SRed, &CDColor::OnNMThemeChangedSred)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &CDColor::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDColor::OnBnClickedCancel)
	ON_WM_CREATE()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CDColor メッセージ ハンドラー


void CDColor::OnNMThemeChangedSred(NMHDR *pNMHDR, LRESULT *pResult)
{
	// この機能は Windows XP それ以降のバージョンを必要とします。
	// シンボル _WIN32_WINNT は >= 0x0501にならなければなりません。
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	*pResult = 0;
}


void CDColor::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	int pos = pScrollBar->GetScrollPos();
	switch(nSBCode) {
	case SB_LEFT:
		pos = 0;		break;
	case SB_RIGHT:
		pos = 255;		break;
	case SB_LINELEFT:
		pos = pos - 1;	break;
	case SB_LINERIGHT:
		pos = pos + 1;	break;
	case SB_PAGELEFT:
		pos = pos - 10;	break;
	case SB_PAGERIGHT:
		pos = pos + 10;	break;
	case SB_THUMBPOSITION:
		pos = nPos;		break;
	case SB_THUMBTRACK:
		pos = nPos;		break;
	case SB_ENDSCROLL:
		break;
	}

	if (pos < 0) {
		pos = 0;
	}
	if (pos > 255) {
		pos = 255;
	}

	pScrollBar->SetScrollPos(pos);
	MyPeint();

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDColor::MyPeint()
{
	CClientDC myDC(&m_pict);

	CRect mySize;
	m_pict.GetClientRect(mySize);

	Ri = m_sbar1.GetScrollPos();
	Gi = m_sbar2.GetScrollPos();
	Bi = m_sbar3.GetScrollPos();

	myDC.FillSolidRect(mySize, RGB(Ri, Gi, Bi));
}


void CDColor::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	OKflag = true;

	CDialogEx::OnOK();
}

bool CDColor::GetDColor(float *R, float *G, float *B)
{
	*R = (float)Ri / 255;
	*G = (float)Gi / 255;
	*B = (float)Bi / 255;

	return OKflag;
}


void CDColor::OnBnClickedCancel()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	OKflag = false;

	CDialogEx::OnCancel();
}


void CDColor::SetDColor(float Rf, float Gf, float Bf)
{
	Ri = (int)(Rf * 255);
	Gi = (int)(Gf * 255);
	Bi = (int)(Bf * 255);
}

void CDColor::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	MyPeint();

	CDialogEx::OnMouseMove(nFlags, point);
}
