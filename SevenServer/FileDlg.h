#pragma once

#include "IOCPServer.h"
// CFileDlg 对话框

class CFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFileDlg)

public:
	CFileDlg(CIOCPServer* iocpServer,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileDlg();

// 对话框数据
	enum { IDD = IDD_FLIE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	void Start(CIOCPServer* pServer,void* pClient);
	void OnReceiveComplete();
public:
	CIOCPServer*		m_iocpServer;
	ClientContext*		m_Context;
};
