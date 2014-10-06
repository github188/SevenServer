#pragma once
#include "IOCPServer.h"
#include "afxcmn.h"
#include "CmdDialog.h"
#include "FileDlg.h"
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
	CTabCtrl m_tabCtrl;
	ClientContext*			m_mainClientContext;
	CIOCPServer*			m_piocpServer;
	static CCmdDialog*			m_cmdDlg;
	static CFileDlg*			m_fileDlg;
public:
	void SetIOCPServerAndContext(CIOCPServer* dwServer,DWORD dwMainClientContxt);
	void OnReceiveComplete(ClientContext* pContext);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	void	SendCmdCommand(int pClientdlg);
	void	SendFileCommand(int pClientdlg);
};
