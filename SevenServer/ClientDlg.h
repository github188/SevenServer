#pragma once
#include "IOCPServer.h"

// ClientDlg �Ի���

class ClientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ClientDlg)

public:
	ClientDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ClientDlg();

// �Ի�������
	enum { IDD = IDD_CLIENTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void OnReceiveComplete();
};
