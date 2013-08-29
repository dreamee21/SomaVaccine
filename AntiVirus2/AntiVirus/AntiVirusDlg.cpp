
// AntiVirusDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "AntiVirus.h"
#include "AntiVirusDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAntiVirusDlg ��ȭ ����



CAntiVirusDlg::CAntiVirusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAntiVirusDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAntiVirusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCAN, m_Scan);
	DDX_Control(pDX, IDC_DRAG, m_Drag);
}

BEGIN_MESSAGE_MAP(CAntiVirusDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_EXIT, &CAntiVirusDlg::OnBnClickedExit)
END_MESSAGE_MAP()


// CAntiVirusDlg �޽��� ó����

BOOL CAntiVirusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CAntiVirusDlg::OnPaint()
{
	CRect rect;
	CPaintDC dc(this);
	CDC MemDC;
	BITMAP bmpinfo, bmpinfo2;
	MemDC.CreateCompatibleDC( &dc );
	CBitmap bmp, bmp2;
	CBitmap *pOldBmp = NULL, *pOldBmp2 = NULL;
	bmp.LoadBitmapW(IDB_SCAN);
	bmp.GetBitmap(&bmpinfo);
	pOldBmp = MemDC.SelectObject(&bmp);
	
	m_Scan.GetWindowRect(&rect);
	ScreenToClient(&rect);
	dc.StretchBlt(rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, &MemDC, 0,0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
	//dc.StretchBlt(1,1,100,100, &MemDC, 0,0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
	bmp2.LoadBitmapW(IDB_DRAG);
	bmp2.GetBitmap(&bmpinfo2);
	pOldBmp2 = MemDC.SelectObject(&bmp2);
	m_Drag.GetWindowRect(&rect);
	ScreenToClient(&rect);
	dc.StretchBlt(rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top, &MemDC, 0,0, bmpinfo2.bmWidth, bmpinfo2.bmHeight, SRCCOPY);
	MemDC.SelectObject(pOldBmp2);


	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CAntiVirusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAntiVirusDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CRect rect;
	CRect moveableRect;
	GetClientRect(&moveableRect);
	moveableRect.bottom  = max(1, moveableRect.top + 40);
	m_ptmouse = point;
	m_Scan.GetWindowRect(&rect);
	ScreenToClient(&rect);
	if(rect.left < m_ptmouse.x && m_ptmouse.x < rect.right && rect.top < m_ptmouse.y && m_ptmouse.y < rect.bottom)
		OnOK();
	m_Drag.GetWindowRect(&rect);
	ScreenToClient(&rect);
	if(rect.left < m_ptmouse.x && m_ptmouse.x < rect.right && rect.top < m_ptmouse.y && m_ptmouse.y < rect.bottom)
		OnOK();
	if( PtInRect(&moveableRect, point))
    {
        PostMessage( WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM( point.x, point.y));
    } 
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CAntiVirusDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect rt;
	AfxGetMainWnd()->GetWindowRect(&rt);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, rt.Width(), rt.Height(), 20, 20);
	AfxGetMainWnd()->SetWindowRgn((HRGN)rgn, TRUE);
}


void CAntiVirusDlg::OnBnClickedExit()
{
	OnOK();
}
