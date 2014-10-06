// FileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SevenServer.h"
#include "FileDlg.h"
#include "afxdialogex.h"


// CFileDlg �Ի���

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


// CFileDlg ��Ϣ�������
void CFileDlg::OnReceiveComplete()
{
	AfxMessageBox(_T("file recv"));
	return;
}

void CFileDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}


BOOL CFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CFileDlg::Start(CIOCPServer* dwServer,void* pClient)
{
	m_iocpServer    = dwServer;
	m_Context		= (ClientContext*)pClient;
	// ֪ͨԶ�̿��ƶ˶Ի����Ѿ���
	BYTE bToken = BASE_TOKEN_NEXT;
	m_iocpServer->Send(m_Context, &bToken, 1);
}
