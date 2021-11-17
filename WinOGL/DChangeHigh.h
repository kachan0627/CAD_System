#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDChangeHigh ダイアログ

class CDChangeHigh : public CDialogEx
{
	DECLARE_DYNAMIC(CDChangeHigh)

public:
	CDChangeHigh(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CDChangeHigh();

// ダイアログ データ
	enum { IDD = IDD_ChangeHigh };
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_SIRI;
	CStatic m_TEXT;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	float Value;
	void SetHighValue(float high);
	float GetHighValue();
	afx_msg void OnBnClickedOk();
	bool OKFlag = false;
	bool GetOKFlag();
	afx_msg void OnBnClickedButton1();
};
