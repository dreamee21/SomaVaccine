
// AntiVirusDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CAntiVirusDlg ��ȭ ����
class CAntiVirusDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CAntiVirusDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ANTIVIRUS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CPoint m_ptmouse;
	CStatic m_Scan;
	CStatic m_Drag;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedExit();
};
