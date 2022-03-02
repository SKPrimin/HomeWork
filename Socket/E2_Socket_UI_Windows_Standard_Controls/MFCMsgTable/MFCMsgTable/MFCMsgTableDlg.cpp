
// MFCMsgTableDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCMsgTable.h"
#include "MFCMsgTableDlg.h"
#include "afxdialogex.h"
#include<locale>
#include<fstream>

#include "model.h"
#include "nomodel.h"
#include <io.h> 
using namespace std;
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


// CMFCMsgTableDlg 对话框



CMFCMsgTableDlg::CMFCMsgTableDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCMSGTABLE_DIALOG, pParent)
	, m_name(_T(""))
	, m_stuid(_T(""))
	, m_ip(_T(""))
	, m_mac(_T(""))
	, m_subnetmask(_T(""))
	, m_nativeplace(_T(""))
	, m_politicallandscape(_T(""))
	, m_contact(_T(""))

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCMsgTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_CboxGrade);
	DDX_Control(pDX, IDC_COMBO2, m_CboxProce);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_stuid);
	DDX_Text(pDX, IDC_EDIT3, m_ip);
	DDX_Text(pDX, IDC_EDIT4, m_mac);
	DDX_Text(pDX, IDC_EDIT5, m_subnetmask);
	DDX_Text(pDX, IDC_EDIT6, m_nativeplace);
	DDX_Text(pDX, IDC_EDIT7, m_politicallandscape);
	DDX_Text(pDX, IDC_EDIT8, m_contact);
	DDX_Control(pDX, IDC_SLIDER1, m_AgeSlider);
	DDX_Text(pDX, IDC_EDIT9, m_age);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);

	DDX_Control(pDX, IDC_RADIO1, radio_man);
	DDX_Control(pDX, IDC_RADIO2, radio_woman);
}

BEGIN_MESSAGE_MAP(CMFCMsgTableDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCMsgTableDlg::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMFCMsgTableDlg::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCMsgTableDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCMsgTableDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCMsgTableDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCMsgTableDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCMsgTableDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT5, &CMFCMsgTableDlg::OnEnChangeEdit5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CMFCMsgTableDlg::OnNMCustomdrawSlider1)
	ON_EN_CHANGE(IDC_EDIT9, &CMFCMsgTableDlg::OnEnChangeEdit9)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CMFCMsgTableDlg::OnNMCustomdrawProgress1)
	ON_BN_CLICKED(IDC_RADIO1, &CMFCMsgTableDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFCMsgTableDlg::OnBnClickedRadio2)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCMsgTableDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCMsgTableDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT4, &CMFCMsgTableDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT6, &CMFCMsgTableDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CMFCMsgTableDlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &CMFCMsgTableDlg::OnEnChangeEdit8)
END_MESSAGE_MAP()


// CMFCMsgTableDlg 消息处理程序

BOOL CMFCMsgTableDlg::OnInitDialog()
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
	m_CboxGrade.AddString(_T("大三")); //默认值
	m_CboxGrade.AddString(_T("大一"));
	m_CboxGrade.AddString(_T("大二"));
	m_CboxGrade.AddString(_T("大四"));

	m_CboxProce.AddString(_T("信息安全"));//默认值
	m_CboxProce.AddString(_T("软件工程"));
	m_CboxProce.AddString(_T("数字媒体"));
	m_CboxProce.AddString(_T("计算机科学与技术"));
	// 年龄滑块的初始值设置
	m_AgeSlider.SetRange(0, 100); //设置滑动范围
	m_AgeSlider.SetLineSize(10); 
	m_AgeSlider.SetTicFreq(1);//每1个单位画一刻度
	m_AgeSlider.SetPos(20);//设置滑块初始位置为20

	//初始化进度条
	m_progress.SetRange(0, 1600);
	m_progress.SetPos(10);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCMsgTableDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCMsgTableDlg::OnPaint()
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
HCURSOR CMFCMsgTableDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCMsgTableDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	int i;
	i = m_CboxGrade.GetCurSel();   //取得当前的位置
	//str.Format("%d",i);
	m_CboxGrade.GetLBText(i, str);//取得当前的字符串
	AfxMessageBox(str);

	m_progress.SetStep(100);
	m_progress.StepIt();
}


void CMFCMsgTableDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strgrade;
	int i;
	i = m_CboxProce.GetCurSel();   //取得当前的位置
	//str.Format("%d",i);
	m_CboxProce.GetLBText(i, strgrade);//取得当前的字符串
	AfxMessageBox(strgrade);

	m_progress.SetStep(100);
	m_progress.StepIt();
}


void CMFCMsgTableDlg::OnBnClickedButton3()
{

	m_progress.SetStep(100);
	m_progress.StepIt();
	// TODO: 在此添加控件通知处理程序代码
	char* location = _strdup(setlocale(LC_CTYPE, NULL));
	setlocale(LC_CTYPE, "chs");
	BOOL isOpen = TRUE;		//是否打开(FALSE则为保存)
	CString defaultDir = "E:";	//默认打开的文件路径
	CString filter = ".txt";	//文件过虑的类型
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");

	CFileDialog openFileDlg(TRUE, "txt", NULL, 0, szFilter, this);

	CString m_path;
	if (openFileDlg.DoModal() == IDOK)
	{
		CString m_path = openFileDlg.GetPathName();//取出文件路径    
		CStdioFile file;
		CString str;
		if (file.Open(m_path, CFile::modeRead))
		{
			while (file.ReadString(str))
			{
				int len = str.GetLength();
				int index = str.Find(_T(":"), 0);
				CString strL = str.Left(index);
				strL.TrimRight();
				CString strR = str.Mid(index + 1, len);
				strR.TrimLeft();
				if (strL == "姓名")
				{
					m_name = strR;
					UpdateData(FALSE);
				}
				if (strL == "学号")
				{
					m_stuid = strR;
					UpdateData(FALSE);
				}
				if (strL == "IP地址")
				{
					m_ip = strR;
					UpdateData(FALSE);
				}
				if (strL == "MAC地址")
				{
					m_mac = strR;
					UpdateData(FALSE);
				}
				if (strL == "子网掩码")
				{
					m_subnetmask = strR;
					UpdateData(FALSE);
				}
				if (strL == "籍贯")
				{
					m_ip = strR;
					UpdateData(FALSE);
				}
				if (strL == "政治面貌")
				{
					m_mac = strR;
					UpdateData(FALSE);
				}
				if (strL == "联系方式")
				{
					m_subnetmask = strR;
					UpdateData(FALSE);
				}

			}
			file.Close();
		}
		UpdateData(FALSE);
	}
	setlocale(LC_CTYPE, location);
	free(location);
}


void CMFCMsgTableDlg::OnBnClickedButton4()
{
	m_progress.SetStep(100);
	m_progress.StepIt();

	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);


	TCHAR szFilter[] = "文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||";
	CFileDialog saveFileDlg(FALSE, "txt", NULL, 0, szFilter, this);
	if (saveFileDlg.DoModal() == IDOK)
	{

		CString strFilePath = saveFileDlg.GetFileName();//取出文件路径    
		// 判断是否已经存在
		if (_access(strFilePath, 0) == 0)
		{
			CString strQuery; 
			CString prompt = ".txt";
			strQuery.Format("%s 已经存在，要替换它吗？", strFilePath);
			if (IDNO == ::MessageBox(m_hWnd, strQuery, prompt, MB_ICONQUESTION | MB_YESNO))
			{
				return;
			}
		}
		CString grade, proce, age, sex; //用来存放选择内容年级、专业、年龄、性别信息

		m_CboxGrade.GetLBText(m_CboxGrade.GetCurSel(), grade);
		m_CboxProce.GetLBText(m_CboxProce.GetCurSel(), proce);
		age.Format("%d", m_AgeSlider.GetPos());  //将整型变量i转化为字符串型

		sex = "男"; //默认为男，如果未选中第一个则为女
		int state_man = ((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck();
		if (state_man == 0) sex = "女";
		
		
		CFile file;  //创建一个文件
		file.Open(strFilePath, CFile::modeCreate | CFile::modeReadWrite);  //打开该文件
		UpdateData(TRUE); //各编辑框的变量获取输入值
		CString strlist; //定义一个输入
		strlist = "姓名:" + m_name + "\n学号:" + m_stuid + "\nIP地址:" + m_ip + "\n物理地址:" + m_mac + "\n子网掩码:" + m_subnetmask;
		file.Write(strlist, strlist.GetLength());
		strlist = "\n籍贯:" + m_nativeplace + "\n政治面貌:" + m_politicallandscape + "\n联系方式:" + m_contact;
		file.Write(strlist, strlist.GetLength());
		strlist = "\n年级:" + grade + "\n专业:" +  proce + "\n年龄:" + age + "\n性别:" + sex;
		file.Write(strlist, strlist.GetLength());//将该列表写入创建的文件
		file.Close(); //关闭文件
	}
}


void CMFCMsgTableDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	Cmodel cm;
	cm.DoModal();

	m_progress.SetStep(100);
	m_progress.StepIt();
}


void CMFCMsgTableDlg::OnBnClickedButton2()
{

	// TODO: 在此添加控件通知处理程序代码
	Cnomodel* pDlg = new Cnomodel;
	pDlg->Create(IDD_DIALOG2, this);
	pDlg->ShowWindow(SW_SHOW);

	m_progress.SetStep(100);
	m_progress.StepIt();

}





void CMFCMsgTableDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	m_progress.SetStep(100);
	m_progress.StepIt();
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCMsgTableDlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	m_progress.SetStep(100);
	m_progress.StepIt();
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCMsgTableDlg::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int nPos = m_AgeSlider.GetPos(); //获得滑块当前位置

	CString str  = _T("");
	str.Format(_T("%d"), nPos);

	SetDlgItemText(IDC_EDIT9, str);
	*pResult = 0;
}




void CMFCMsgTableDlg::OnEnChangeEdit9()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码




}


void CMFCMsgTableDlg::OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//指定进度条控件的步进增量 
	*pResult = 0;
}



void CMFCMsgTableDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_progress.SetStep(50);
	m_progress.StepIt();
}


void CMFCMsgTableDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_progress.SetStep(50);
	m_progress.StepIt();
}


void CMFCMsgTableDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	m_progress.SetStep(100);
	m_progress.StepIt();
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCMsgTableDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	m_progress.SetStep(100);
	m_progress.StepIt();
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCMsgTableDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	m_progress.SetStep(100);
	m_progress.StepIt();
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCMsgTableDlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	m_progress.SetStep(100);
	m_progress.StepIt();
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCMsgTableDlg::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	m_progress.SetStep(100);
	m_progress.StepIt();
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCMsgTableDlg::OnEnChangeEdit8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	m_progress.SetStep(100);
	m_progress.StepIt();
	// TODO:  在此添加控件通知处理程序代码
}
