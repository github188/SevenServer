// ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SevenServer.h"
#include "ClientDlg.h"
#include "afxdialogex.h"


// ClientDlg �Ի���

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


// ClientDlg ��Ϣ�������
void ClientDlg::OnReceiveComplete()
{
	return;
}