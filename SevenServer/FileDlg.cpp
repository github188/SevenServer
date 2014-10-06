// FileDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SevenServer.h"
#include "FileDlg.h"
#include "afxdialogex.h"


// CFileDlg 对话框

IMPLEMENT_DYNAMIC(CFileDlg, CDialogEx)

CFileDlg::CFileDlg(CIOCPServer* iocpServer,CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileDlg::IDD, pParent)
{
	m_iocpServer = iocpServer;

}

CFileDlg::~CFileDlg()
{
}

void CFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFileDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CFileDlg 消息处理程序
void CFileDlg::OnReceiveComplete()
{
	AfxMessageBox(_T("file recv"));
	return;
}

void CFileDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
}


BOOL CFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CFileDlg::Start(CIOCPServer* dwServer,void* pClient)
{
	m_iocpServer    = dwServer;
	m_Context		= (ClientContext*)pClient;
	// 通知远程控制端对话框已经打开
	BYTE bToken = BASE_TOKEN_NEXT;
	m_iocpServer->Send(m_Context, &bToken, 1);
}
