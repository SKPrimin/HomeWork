#pragma once


// Cmodel 对话框

class Cmodel : public CDialogEx
{
	DECLARE_DYNAMIC(Cmodel)

public:
	Cmodel(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cmodel();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
