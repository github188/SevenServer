#pragma once
#include "IOCPServer.h"

// ClientDlg 对话框

class ClientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ClientDlg)

public:
	ClientDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ClientDlg();

// 对话框数据
	enum { IDD = IDD_CLIENTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void OnReceiveComplete();
};
