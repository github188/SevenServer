// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SevenServer.h"
#include "ClientDlg.h"
#include "afxdialogex.h"


// ClientDlg 对话框

IMPLEMENT_DYNAMIC(ClientDlg, CDialogEx)

ClientDlg::ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ClientDlg::IDD, pParent)
{

}

ClientDlg::~ClientDlg()
{
}

void ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ClientDlg, CDialogEx)
END_MESSAGE_MAP()


// ClientDlg 消息处理程序
void ClientDlg::OnReceiveComplete()
{
	return;
}