
// AntiVirusDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "AntiVirus.h"
#include "AntiVirusDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAntiVirusDlg 대화 상자



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


// CAntiVirusDlg 메시지 처리기

BOOL CAntiVirusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

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
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAntiVirusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAntiVirusDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
