#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CDChangeHigh �_�C�A���O

class CDChangeHigh : public CDialogEx
{
	DECLARE_DYNAMIC(CDChangeHigh)

public:
	CDChangeHigh(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CDChangeHigh();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ChangeHigh };
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

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
