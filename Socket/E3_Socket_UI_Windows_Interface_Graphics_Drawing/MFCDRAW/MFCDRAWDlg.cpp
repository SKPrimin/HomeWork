
// MFCDRAWDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCDRAW.h"
#include "MFCDRAWDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCDRAWDlg 对话框



CMFCDRAWDlg::CMFCDRAWDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCDRAW_DIALOG, pParent)
	, m_radio(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDRAWDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Control(pDX, IDC_SLIDER1, Sliderx);
	DDX_Control(pDX, IDC_SLIDER2, Slidery);
}

BEGIN_MESSAGE_MAP(CMFCDRAWDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RADIO1, &CMFCDRAWDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFCDRAWDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CMFCDRAWDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CMFCDRAWDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CMFCDRAWDlg::OnBnClickedRadio5)
	ON_STN_CLICKED(IDC_STATIC_DRAW, &CMFCDRAWDlg::OnStnClickedStaticDraw)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CMFCDRAWDlg::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CMFCDRAWDlg::OnNMCustomdrawSlider2)
END_MESSAGE_MAP()


// CMFCDRAWDlg 消息处理程序

BOOL CMFCDRAWDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//初始化坐标
	x1 = 50;	x2 = 50;	x3 = 50;	x4 = 50;	x5 = 50;
	y1 = 50;	y2 = 50;	y3 = 50;	y4 = 50;	y5 = 50;
	Sliderx.SetPos(50);
	Slidery.SetPos(50);
	pointx = Sliderx.GetPos();
	pointy = Slidery.GetPos();

	//更新时间
	SetTimer(1, 1000, NULL);

	cfont.CreateFont(20, 0, 10, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("微软雅黑"));
	GetDlgItem(IDC_STATIC_YEAR)->SetFont(&cfont);
	GetDlgItem(IDC_STATIC_MONTH)->SetFont(&cfont);
	GetDlgItem(IDC_STATIC_DAY)->SetFont(&cfont);
	GetDlgItem(IDC_STATIC_TIME)->SetFont(&cfont);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCDRAWDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCDRAWDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//-----布置界面，使用一个静态文本控件，调整其大小后作为你的绘图区域。------
		CWnd* pWnd = GetDlgItem(IDC_STATIC_DRAW);
		CDC* dc = pWnd->GetDC();
		pWnd->Invalidate();
		pWnd->UpdateWindow();

		CRect rectView;
		CRgn rgn;
		GetDlgItem(IDC_STATIC_DRAW)->GetWindowRect(&rectView);
		ScreenToClient(&rectView);
		rgn.CreateRectRgn(rectView.left, rectView.top, rectView.right, rectView.bottom);
		dc->SelectClipRgn(&rgn);

		CPaintDC newdc(this);
		newdc.SelectClipRgn(&rgn);

		CPen pNewPen(PS_SOLID, 3, RGB(0, 0, 0));
		CBrush yellowBrush(RGB(255, 255, 0));//选中新笔
		CPen* pOldPen = newdc.SelectObject(&pNewPen);//选中新画刷

		//画黄色圆形
		CBrush* pOldBrush = newdc.SelectObject(&yellowBrush);
		CRect yellowEclipse(rectView);
		yellowEclipse.left += x1;
		yellowEclipse.top += y1;
		yellowEclipse.right += x1;
		yellowEclipse.bottom += y1;
		newdc.Ellipse(yellowEclipse);
		newdc.SelectObject(pOldPen);
		newdc.SelectObject(pOldBrush);

		//画红色矩形
		CBrush redBrush(RGB(255, 0, 0));
		pOldBrush = newdc.SelectObject(&redBrush);
		CRect redRect(rectView);
		redRect.left += x2 + 100 ;
		redRect.top += y2 + 100;
		redRect.right += x2 - 100;
		redRect.bottom += y2 - 100;
		newdc.Rectangle(redRect);
		newdc.SelectObject(pOldBrush);

		//画绿色矩形
		CBrush greeBrush(RGB(0, 255, 0));
		pOldBrush = newdc.SelectObject(&greeBrush);
		CRect greeRect(rectView);
		greeRect.left += x3 + 170;
		greeRect.top += y3 + 170;
		greeRect.right += x3 - 170;
		greeRect.bottom += y3 - 170;
		newdc.Rectangle(greeRect);
		newdc.SelectObject(pOldBrush);

		//画深蓝色矩形
		CBrush navyblueBrush(RGB(0, 0, 255));
		pOldBrush = newdc.SelectObject(&navyblueBrush);
		CRect navyblueRect(rectView);
		navyblueRect.left += x4 + 240;
		navyblueRect.top += y4 + 240;
		navyblueRect.right += x4 - 240;
		navyblueRect.bottom += y4 - 240;
		newdc.Rectangle(navyblueRect);
		newdc.SelectObject(pOldBrush);

		//画浅蓝色圆形
		CBrush lightbrueBrush(RGB(0, 255, 255));
		pOldBrush = newdc.SelectObject(&lightbrueBrush);
		rectView.left += x5 + 240;
		rectView.top += y5 + 240;
		rectView.right += x5 - 240;
		rectView.bottom += y5 - 240;
		newdc.Ellipse(rectView);
		newdc.SelectObject(pOldBrush);

		//显示学号姓名
		newdc.SelectObject(&cfont);
		newdc.SetBkMode(TRANSPARENT);//设置背景透明
		newdc.TextOut(100, 210, "姓名:张丞");
		newdc.TextOut(100, 230, "学号：E01914168");

		CDialogEx::OnPaint();
	}
}

void CMFCDRAWDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CTime m_GlobalTime;
	m_GlobalTime = CTime::GetCurrentTime(); //使用 CTime 对象得到当前时间
	CString str1, str2, str3, str4;
	str1 = m_GlobalTime.Format("%Y");
	GetDlgItem(IDC_STATIC_YEAR)->SetWindowText(str1);
	str2 = m_GlobalTime.Format("%m");
	GetDlgItem(IDC_STATIC_MONTH)->SetWindowText(str2);
	str3 = m_GlobalTime.Format("%d");
	GetDlgItem(IDC_STATIC_DAY)->SetWindowText(str3);
	str4 = m_GlobalTime.Format("%H:%M:%S");
	GetDlgItem(IDC_STATIC_TIME)->SetWindowText(str4);
	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CMFCDRAWDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_YEAR)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_MONTH)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_DAY)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIME)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCDRAWDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCDRAWDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和或调用默认值
	UpdateData(TRUE);
	pointx = Sliderx.GetPos();
	pointy = Slidery.GetPos();
	switch (m_radio)
	{
	case 0:
		x1 = pointx;
		y1 = pointy;
		break;
	case 1:
		x2 = pointx;
		y2 = pointy;
		break;
	case 2:
		x3 = pointx;
		y3 = pointy;
		break;
	case 3:
		x4 = pointx;
		y5 = pointy;
		break;
	case 4:
		x5 = pointx;
		y5 = pointy;
		break;
	default:
		break;

	}
	Invalidate(TRUE);
	CMFCDRAWDlg::OnPaint();
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}



void CMFCDRAWDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Sliderx.SetPos(x1);
	Slidery.SetPos(y1);

	x1 = Sliderx.GetPos();
	y1 = Slidery.GetPos();
	CMFCDRAWDlg::OnPaint();
}


void CMFCDRAWDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Sliderx.SetPos(x2);
	Slidery.SetPos(y2);

	x2 = Sliderx.GetPos();
	y2 = Slidery.GetPos();
	CMFCDRAWDlg::OnPaint();
}


void CMFCDRAWDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Sliderx.SetPos(x3);
	Slidery.SetPos(y3);

	x3 = Sliderx.GetPos();
	y3 = Slidery.GetPos();
	CMFCDRAWDlg::OnPaint();
}


void CMFCDRAWDlg::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Sliderx.SetPos(x4);
	Slidery.SetPos(y4);

	x4 = Sliderx.GetPos();
	y4 = Slidery.GetPos();
	CMFCDRAWDlg::OnPaint();
}


void CMFCDRAWDlg::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	Sliderx.SetPos(x5);
	Slidery.SetPos(y5);

	x5 = Sliderx.GetPos();
	y5 = Slidery.GetPos();
	CMFCDRAWDlg::OnPaint();
}


//void CMFCDRAWDlg::OnDblclkStaticDraw()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void CMFCDRAWDlg::OnStnClickedStaticDraw()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CMFCDRAWDlg::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CMFCDRAWDlg::OnNMCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
