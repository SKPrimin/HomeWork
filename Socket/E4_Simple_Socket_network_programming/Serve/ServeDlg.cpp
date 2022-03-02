
// ServeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Serve.h"
#include "ServeDlg.h"
#include "afxdialogex.h"
// socket库
#include <WinSock2.h>
#include<atlconv.h>
#include<string.h>
#include<iostream>
using namespace std;
#pragma comment(lib,"WS2_32.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BUF_SIZE 64
//变量声明
WSADATA wsd;
SOCKET sServer;//用于监听
SOCKET sClient;//实现与客户端通信
SOCKADDR IN serveAddr;
char buf[BUF_SIZE];  //用于接收数据
CString res[BUF_SIZE];  //用于对收到数据的提取划分
//CDC *//用于得到全局的设备描述表
int retVal;
HANDLE hThread;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
CString s1, s2, s3, s4, s5;

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


// CServeDlg 对话框



CServeDlg::CServeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_info);
}

BEGIN_MESSAGE_MAP(CServeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CServeDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &CServeDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CServeDlg 消息处理程序

BOOL CServeDlg::OnInitDialog()
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
	//SetTimer(0, 1000, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CServeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServeDlg::OnPaint()
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
HCURSOR CServeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


DWORD WINAPI ClientThread(LPVOID lpParameter)
{
	CServeDlg* dlg = (CServeDlg*)lpParameter;
	SOCKADDR_IN addrcClient{};
	int cClientaddlen = sizeof(addrcClient);
	//接收数据
	sClient = accept(sServer, (struct sockaddr*)&addrcClient, &cClientaddlen);
	if (INVALID_SOCKET == sClient)
	{
		AfxMessageBox("accept failed！");
		closesocket(sServer);
		closesocket(sClient);
		WSACleanup();
		return 0;
	}
	s5 = "\r\n客户端请求成功！";
	CString strText = "";
	//获得当前文本
	dlg->m_info.GetWindowText(strText);
	strText += s5;
	//设置追加后的文本
	dlg->m_info.SetWindowText(strText);

	// 阻塞等待
	while (TRUE)
	{
		/*memset(buf, 0x00, 100);
		int bufsize;*/
		ZeroMemory(buf, BUF_SIZE);
		retVal = recv(sClient, buf, 100, 0);
		if (SOCKET_ERROR == retVal)
		{

			AfxMessageBox("recv failed！");
			closesocket(sServer);
			closesocket(sClient);
			WSACleanup();
			return 0;
		}
		//将数据转换为便于处理的 CString 类对象 RcvData
		CString	RcvData = CString(buf);
		SYSTEMTIME tim;
		GetLocalTime(&tim);
		char sDateTime[30];
		sprintf_s(sDateTime, "%4d-%2d-%2d  %2d:%2d:%2d", tim.wYear, tim.wMonth, tim.wDay, tim.wHour, tim.wMinute, tim.wSecond);
		CString year(sDateTime);
		strText = "";
		//获得当前文本
		dlg->m_info.GetWindowText(strText);
		strText += "\r\n\r\n" + year + "\r\n\r\n" + RcvData;
		//设置追加后的文本
		dlg->m_info.SetWindowText(strText);
		int pos;
		CString rest;
		for (int i = 0; i < 11; i++)
		{
			pos = RcvData.Find(';');
			rest = RcvData.Mid(pos + 1, RcvData.GetLength());
			res[i] = RcvData.Left(pos);
			RcvData = rest;
		}

		CWnd* pWnd = dlg->GetDlgItem(IDC_STATIC1);
		CDC* dc = pWnd->GetDC();//注意这里获取了新的 dc
		pWnd->Invalidate();
		pWnd->UpdateWindow();
		CRect rectView;
		CRgn rgn;
		dlg->GetDlgItem(IDC_STATIC1)->GetClientRect(&rectView);
		rgn.CreateRectRgn(rectView.left, rectView.top, rectView.right, rectView.bottom);
		dc->SelectClipRgn(&rgn);
		CPen pNewPen(PS_SOLID, 2, RGB(0, 0, 0));
		CPen* pOldPen;
		pOldPen = dc->SelectObject(&pNewPen);
		CBrush pNewBrush1(RGB(255, 255, 0));
		CBrush* pOldBrush;
		if (res[3] == 'R')
		{
			CRect rect1(_ttoi(res[4]), _ttoi(res[5]), _ttoi(res[6]), _ttoi(res[7]));
			CBrush pNewBrush1(RGB(_ttoi(res[8]), _ttoi(res[9]), _ttoi(res[10])));
			dlg->m_info.GetWindowText(res[4] + res[8]);
			dc->Rectangle(&rect1);
			pOldBrush = dc->SelectObject(&pNewBrush1);
			dc->Rectangle(&rect1);
			dc->SelectObject(pOldPen);//恢复原有的笔
			dc->SelectObject(pOldBrush);
			dc->DeleteDC();
		}
		if (res[3] == 'C')
		{
			CRect rect1(_ttoi(res[4]), _ttoi(res[5]), _ttoi(res[6]), _ttoi(res[7]));
			CBrush pNewBrush1(RGB(_ttoi(res[8]), _ttoi(res[9]), _ttoi(res[10])));
			dc->Ellipse(&rect1);
			pOldBrush = dc->SelectObject(&pNewBrush1);
			dc->Ellipse(&rect1);
			dc->SelectObject(pOldPen);//恢复原有的笔
			dc->SelectObject(pOldBrush);
			dc->DeleteDC();
		}
	}

	return 0;
}


void CServeDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//初始化
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	{
		s1 = "WSAstartup failed!";
		return;
	}
	s1 = "WSAstartup 初始化套接字动态库成功!";
	//m_info.SetWindowText(s1);
	CString strText = "";
	//获得当前文本
	m_info.GetWindowText(strText);
	strText += s1;
	//设置追加后的文本
	m_info.SetWindowText(strText);
	//监听
	sServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == sServer)
	{
		s2 = "socket error!";
		WSACleanup();
		return;
	}
	s2 = "基于TCP的流式socket创建成功!";
	//m_info.SetWindowText(s1 + "\n" + s2);
	strText = "";
	m_info.GetWindowText(strText);
	strText += "\n\r\n" + s2;
	m_info.SetWindowText(strText);
	SOCKADDR_IN addrsServ{};
	int i = 0;
	//设置地址
//	str.Format(_T("%d"), i);
	addrsServ.sin_family = AF_INET;
	addrsServ.sin_port = htons(9990);
	addrsServ.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	int sSreveraddlen = sizeof(addrsServ);
	//绑定地址
	retVal = bind(sServer, (const struct sockaddr*)&addrsServ, sizeof(SOCKADDR_IN));
	if (SOCKET_ERROR == retVal)
	{
		s3 = "bind failed！";
		closesocket(sServer);
		WSACleanup();
		return;
	}
	s3 = "bind成功！";
	//m_info.SetWindowText(s1 + "\n" + s2 + "\n" + s3);
	strText = "";
	m_info.GetWindowText(strText);
	strText += "\n\r\n" + s3;
	m_info.SetWindowText(strText);
	//监听
	retVal = listen(sServer, 1);
	if (SOCKET_ERROR == retVal)
	{
		s4 = "listen failed！";
		closesocket(sServer);
		WSACleanup();
		return;
	}
	s4 = "设置为listen成功！";
	//m_info.SetWindowText(s1 + "\r\n\n" + s2 + "\r\n\n" + s3 + "\r\n\n" + s4);
	strText = "";
	m_info.GetWindowText(strText);
	strText += "\n\r\n" + s4;
	m_info.SetWindowText(strText);
	hThread = CreateThread(NULL, 0, ClientThread, (LPVOID)this, 0, NULL);
	if (hThread == NULL)
	{
		CString ss;
		ss = "Create Thread Failed!! !";
		AfxMessageBox(ss);
		closesocket(sServer);
		WSACleanup();
		return;
	}
	
}


void CServeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nIDEvent != 0)
		return;
	KillTimer(0);

	// 阻塞获得的数据
	char buf2[512];
	memset(buf2, 0, 5128 * sizeof(char));
	// 接收数据
	int retRal = recv(sServer, buf2, 512, 0);
	//if (retRal > 0)
	//{
	//	buf = buf2;
	//}
	SetTimer(0, 1000, NULL);
	CDialogEx::OnTimer(nIDEvent);
}


void CServeDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	hThread = CreateThread(NULL, 0, ClientThread, (LPVOID)this, 0, NULL);
}
