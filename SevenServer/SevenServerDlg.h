
// SevenServerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "IOCPServer.h"
#include "ClientDlg.h"
#include "macros.h"


typedef struct
{	
	BYTE			bToken;			// = 1
	OSVERSIONINFOEX	OsVerInfoEx;	// version
	IN_ADDR			IPAddress;		// 存储32位的IPv4的地址数据结构
	wchar_t			HostName[50];	// HostName
	wchar_t	        UserName[50];	// UserName
}LOGININFO;


// CSevenServerDlg 对话框
class CSevenServerDlg : public CDialogEx
{
// 构造
public:
	CSevenServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SEVENSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl		m_listCtrl;
	int				m_Column_Count;
	static CIOCPServer*	m_iocpServer;
	int				m_nComputerNum;
public:
	void InitListCtrl();
	void StartIOCPServer();
	static  void CALLBACK NotifyProc(LPVOID lpParam, ClientContext* pContext, UINT nCode);
	void ProcessReceiveComplete(ClientContext *pContext);
	void ProcessReceive(ClientContext *pContext);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	void OnDisconnect(ClientContext* pContext);
	int AddToList(ClientContext* pContext);
	afx_msg void OnListManager();
	afx_msg void OnListDisconnect();
	
};
