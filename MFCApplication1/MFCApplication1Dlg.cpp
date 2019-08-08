
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	CRect r;
	GetClientRect(r);
	SetScrollRange(SB_VERT, 0, 8*9*24-r.Height(), 0);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{
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
		CString str;
		int count = 0;
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(255, 0, 0));
		int scroll_pos = GetScrollPos(SB_VERT);

		for (int dan = 2; dan <= 9; dan++) {
			for (int i = 1; i < 9; i++) {
				str.Format(L"%d * %d = %d", dan, i, dan * 2);
				dc.TextOut(10, count*24- scroll_pos, str);
				count++;
			}
		}
		// CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar == NULL)	// 컨트롤로 만들어진 스크롤바의 경우 아이디가 있지만, 다이얼로그에 만들어진 스크롤 바는 아이디가 없다
	{
		int scroll_pos = GetScrollPos(SB_VERT), min = 0, max = 0;
		GetScrollRange(SB_VERT, &min, &max);

		switch (nSBCode) {
		// 스크롤바 화살표 클릭
		case SB_LINEDOWN :
			if(scroll_pos < max) SetScrollPos(SB_VERT, ++scroll_pos);
			break;
		case SB_LINEUP :
			if (scroll_pos > min) SetScrollPos(SB_VERT, --scroll_pos);
			break;
		// 스크롤바 자체를 클릭
		case SB_PAGEDOWN:
			if (scroll_pos + 24 < max) SetScrollPos(SB_VERT, scroll_pos + 24);
			break;
		case SB_PAGEUP:
			if (scroll_pos - 24 > min) SetScrollPos(SB_VERT, scroll_pos - 24);
			break;
		// 스크롤바 잡고 드레그
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			SetScrollPos(SB_VERT, nPos);
			break;
		}
	}
	Invalidate();

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CMFCApplication1Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect r;
	GetClientRect(r);
	SetScrollRange(SB_VERT, 0, 8 * 9 * 24 - r.Height(), 0);
}
