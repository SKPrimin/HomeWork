
// RSocketDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "RSocket.h"
#include "RSocketDlg.h"
#include "afxdialogex.h"
// 导入库
#include <WinSock2.h>
#include<atlconv.h>
#pragma comment(lib,"WS2_32.lib")
#include <string> 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//变量声明
#define BUF_SIZE 64
WSADATA wsd;
SOCKET sHost;
SOCKADDR IN serveAddr;
char buf[BUF_SIZE];
int retVal;

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


// CRSocketDlg 对话框



CRSocketDlg::CRSocketDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RSOCKET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRSocketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRSocketDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CRSocketDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CRSocketDlg::OnBnClickedButton1)
//	ON_WM_TIMER()
END_MESSAGE_MAP()


// CRSocketDlg 消息处理程序

BOOL CRSocketDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CRSocketDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRSocketDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRSocketDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRSocketDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码 连接程序
	UpdateData(TRUE);
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		AfxMessageBox("WSAstartup failed!");
		return;
	}

	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sHost)
	{
		AfxMessageBox("socket error!");
		WSACleanup();
		return;
	}
	SOCKADDR_IN addrsServ{};
	int i = 0;
	//str.Format(_T("%d"), i);
	addrsServ.sin_family = AF_INET;

//	addrsServ.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrsServ.sin_addr.s_addr = htonl(2130706433);
	addrsServ.sin_port = htons(9990);
	int sSreveraddlen = sizeof(addrsServ);
	m_ipa.LockBuffer();
	UpdateData(false);
	retVal = connect(sHost, (LPSOCKADDR)&addrsServ, sizeof(addrsServ));
	if (SOCKET_ERROR == retVal)
	{
		AfxMessageBox("connect failed!");
		closesocket(sHost);
		WSACleanup();
		return;
	}
}


void CRSocketDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int bufsize;
	CString str;
	CString str1;
	CString str2;
	CString str3;
	CString str4;
	CString str5;
	CString str6;
	CString str7;
	CString str8;
	CString str9;
	CString str10;
	CString str11;
	CString str12;
	if (((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck() == 1)
	{
		str11 = "R";
	}
	if (((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck() == 1)
	{
		str11 = "C";
	}
	str12 = ";";
	GetDlgItemText(IDC_EDIT3, str1);
	GetDlgItemText(IDC_EDIT4, str2);
	GetDlgItemText(IDC_EDIT5, str3);
	GetDlgItemText(IDC_EDIT6, str4);
	GetDlgItemText(IDC_EDIT7, str5);
	GetDlgItemText(IDC_EDIT8, str6);
	GetDlgItemText(IDC_EDIT9, str7);
	GetDlgItemText(IDC_EDIT10, str8);
	GetDlgItemText(IDC_EDIT11, str9);
	GetDlgItemText(IDC_EDIT12, str10);
	str = str1 + str12 + str2 + str12 + str3 + str12 + str11 + str12 + str4 + str12 + str5 + str12 + str6 + str12 + str7 + str12 + str8 + str12 + str9 + str12 + str10 + str12;
	USES_CONVERSION;
	char* a = T2A(str.GetBuffer(0));
	str.ReleaseBuffer();
	sprintf_s(buf, "%s", a);
	bufsize = send(sHost, buf, strlen(buf), 0);
	if (SOCKET_ERROR == bufsize)
	{
		AfxMessageBox("send failed!");
		closesocket(sHost);
		WSACleanup();
		return;
	}
}