// Cnomodel.cpp: 实现文件
//

#include "pch.h"
#include "MFCMsgTable.h"
#include "nomodel.h"
#include "afxdialogex.h"


// Cnomodel 对话框

IMPLEMENT_DYNAMIC(Cnomodel, CDialogEx)

Cnomodel::Cnomodel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

Cnomodel::~Cnomodel()
{
}

void Cnomodel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}




BEGIN_MESSAGE_MAP(Cnomodel, CDialogEx)
END_MESSAGE_MAP()


// Cnomodel 消息处理程序
