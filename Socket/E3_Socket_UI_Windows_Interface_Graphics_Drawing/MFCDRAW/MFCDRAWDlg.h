
// MFCDRAWDlg.h: 头文件
//

#pragma once


// CMFCDRAWDlg 对话框
class CMFCDRAWDlg : public CDialogEx
{
// 构造
public:
	CMFCDRAWDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCDRAW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	//自定义全局变量，用来控制图形移动
	int x1, x2, x3, x4, x5;
	int y1, y2, y3, y4, y5;
	// 自定义滑块移动距离
	int pointx, pointy;
	//增加 CFont 类成员变量
	CFont cfont;
public:
	int m_radio;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	CSliderCtrl Sliderx;
	CSliderCtrl Slidery;
	//afx_msg void OnDblclkStaticDraw();
	afx_msg void OnStnClickedStaticDraw();
	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
};
