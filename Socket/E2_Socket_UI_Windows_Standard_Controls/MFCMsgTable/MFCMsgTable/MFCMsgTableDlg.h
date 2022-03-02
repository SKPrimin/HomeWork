
// MFCMsgTableDlg.h: 头文件
//

#pragma once


// CMFCMsgTableDlg 对话框
class CMFCMsgTableDlg : public CDialogEx
{
// 构造
public:
	CMFCMsgTableDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCMSGTABLE_DIALOG };
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
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
	CComboBox m_CboxGrade;
	CComboBox m_CboxProce;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CString m_name;
	CString m_stuid;
	CString m_ip;
	CString m_mac;
	CString m_subnetmask;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit5();
	CString m_nativeplace;
	CString m_politicallandscape;
	CString m_contact;
	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl m_AgeSlider;
	afx_msg void OnEnChangeEdit9();
	CString m_age;

	afx_msg void OnNMCustomdrawProgress1(NMHDR* pNMHDR, LRESULT* pResult);
	void OnTimer(UINT_PTR nIDEvent);
	CProgressCtrl m_progress;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit8();
	CButton radio_man;
	CButton radio_woman;
};
