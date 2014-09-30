
// SevenServerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "IOCPServer.h"
#include "ClientDlg.h"
#include "macros.h"
// CSevenServerDlg �Ի���
class CSevenServerDlg : public CDialogEx
{
// ����
public:
	CSevenServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SEVENSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl		m_listCtrl;
	int				m_Column_Count;
	CIOCPServer*	m_iocpServer;
public:
	void InitListCtrl();
	void StartIOCPServer();
	static  void CALLBACK NotifyProc(LPVOID lpParam, ClientContext* pContext, UINT nCode);
	void ProcessReceiveComplete(ClientContext *pContext);
	void ProcessReceive(ClientContext *pContext);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	void OnDisconnect(ClientContext* pContext);
	void AddToList(ClientContext* pContext);
};
