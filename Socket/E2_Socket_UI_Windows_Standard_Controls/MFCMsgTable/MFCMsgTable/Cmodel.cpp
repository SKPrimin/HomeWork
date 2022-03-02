// Cmodel.cpp: 实现文件
//

#include "pch.h"
#include "MFCMsgTable.h"
#include "model.h"
#include "afxdialogex.h"


// Cmodel 对话框

IMPLEMENT_DYNAMIC(Cmodel, CDialogEx)

Cmodel::Cmodel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Cmodel::~Cmodel()
{
}

void Cmodel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Cmodel, CDialogEx)
END_MESSAGE_MAP()


// Cmodel 消息处理程序
