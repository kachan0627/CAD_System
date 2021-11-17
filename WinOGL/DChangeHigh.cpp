// DChangeHigh.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "WinOGL.h"
#include "DChangeHigh.h"
#include "afxdialogex.h"


// CDChangeHigh �_�C�A���O

IMPLEMENT_DYNAMIC(CDChangeHigh, CDialogEx)

CDChangeHigh::CDChangeHigh(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDChangeHigh::IDD, pParent)
{

}

CDChangeHigh::~CDChangeHigh()
{
}

void CDChangeHigh::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_SIRI);
}


BEGIN_MESSAGE_MAP(CDChangeHigh, CDialogEx)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &CDChangeHigh::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CDChangeHigh::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDChangeHigh ���b�Z�[�W �n���h���[
BOOL CDChangeHigh::OnInitDialog()
{
	CDialog::OnInitDialog();

	CScrollBar *mySIRI = (CScrollBar *)GetDlgItem(IDC_SCROLLBAR1);
	mySIRI->SetScrollRange(0, 300);
	mySIRI->SetScrollPos((int)(Value * 100));
	UpdateData(FALSE);

	return TRUE;
}

void CDChangeHigh::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h���[ �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	int pos = pScrollBar->GetScrollPos();
	switch(nSBCode) {
	case SB_LEFT:
		pos = 0;		break;
	case SB_RIGHT:
		pos = 500;		break;
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
	if (pos > 300) {
		pos = 300;
	}

	pScrollBar->SetScrollPos(pos);
	if (pos == 0) {
		Value = 0.001;
	}
	else {
		Value = (float)pos / 100;
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDChangeHigh::SetHighValue(float high)
{
	Value = high;
}


float CDChangeHigh::GetHighValue()
{
	return Value;
}


void CDChangeHigh::OnBnClickedOk()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	OKFlag = true;
	CDialogEx::OnOK();
}


bool CDChangeHigh::GetOKFlag()
{
	return OKFlag;
}


void CDChangeHigh::OnBnClickedButton1()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	Value = 0.5;
	CScrollBar *mySIRI = (CScrollBar *)GetDlgItem(IDC_SCROLLBAR1);
	mySIRI->SetScrollPos((int)(Value * 100));
}
