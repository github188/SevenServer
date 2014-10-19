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
	DDX_Control(pDX, IDC_COMBO2, m_diskList);
	//	DDX_Control(pDX, IDC_TREE1, m_dic);
	DDX_Control(pDX, IDC_LIST1, m_fileList);
	DDX_Control(pDX, IDC_BACK, m_backButton);
	DDX_Control(pDX, IDC_FRESH, m_freshButton);
	DDX_Control(pDX, IDC_EDIT1, m_crtDic);
}


BEGIN_MESSAGE_MAP(CFileDlg, CDialogEx)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO2, &CFileDlg::OnCbnSelchangeCombo2)
//	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CFileDlg::OnTvnSelchangedTree1)
	ON_BN_CLICKED(IDC_BACK, &CFileDlg::OnBnClickedBack)
	ON_BN_CLICKED(IDC_FRESH, &CFileDlg::OnBnClickedFresh)
END_MESSAGE_MAP()


// CFileDlg ��Ϣ�������
void CFileDlg::OnReceiveComplete()
{
	switch (m_Context->m_DeCompressionBuffer.GetBuffer(0)[0])
	{
	case FILE_TOKEN_DRIVE_LIST:
		ReceiveRemoteDriveList();
		break;
	case FILE_TOKEN_FILE_LIST:
		ReceiveRemoteFileList();
		break;
	default:
		break;

	}
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

void CFileDlg::OnCbnSelchangeCombo2()
{
	CString str;
	int nSel;   
	  
	nSel = m_diskList.GetCurSel();    
	m_diskList.GetLBText(nSel, str);   
	m_crtDic.Clear();
	m_crtDic.SetWindowText(str);
	m_Remote_Path = str;
	GetRemoteFileList(m_Remote_Path);
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CFileDlg::ReceiveRemoteDriveList()
{
	memset(m_bRemoteDriveList, 0, sizeof(m_bRemoteDriveList));
	memcpy(m_bRemoteDriveList, m_Context->m_DeCompressionBuffer.GetBuffer(), m_Context->m_DeCompressionBuffer.GetBufferLen());
	DRIVE_LIST *pDrivelist;
	pDrivelist = (DRIVE_LIST*)m_bRemoteDriveList;
	wchar_t* szDrive = pDrivelist->DriveString;
	m_diskList.ResetContent();
	do 
	{
		m_diskList.AddString(szDrive);
		szDrive += (lstrlen(szDrive)+1);
	} while (*szDrive !='\x00');


}

void CFileDlg::OnBnClickedBack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFileDlg::OnBnClickedFresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CFileDlg::GetRemoteFileList(CString directory)
{
	// ��������ǰ��ջ�����
	FILE_DATA *pData = new FILE_DATA;
	pData->bToken = FILE_COMMAND_LIST_FILES;
	memcpy((void*)pData->pData,m_Remote_Path.GetBuffer(),m_Remote_Path.GetLength());
	//pData->pData	  = m_Remote_Path.GetBuffer();
	m_iocpServer->Send(m_Context, (LPBYTE)pData, 2*m_Remote_Path.GetLength()+1);
	m_crtDic.SetWindowText(m_Remote_Path);

	// �õ���������ǰ������
	m_fileList.EnableWindow(FALSE);
}

CString CFileDlg::GetParentDirectory(CString strPath)
{
	CString	strCurPath = strPath;
	int Index = strCurPath.ReverseFind('\\');
	if (Index == -1)
	{
		return strCurPath;
	}
	CString str = strCurPath.Left(Index);
	Index = str.ReverseFind('\\');
	if (Index == -1)
	{
		strCurPath = "";
		return strCurPath;
	}
	strCurPath = str.Left(Index);

	if(strCurPath.Right(1) != "\\")
		strCurPath += "\\";
	return strCurPath;
}

void CFileDlg::ReceiveRemoteFileList()
{
	AfxMessageBox(_T("aa"));
}