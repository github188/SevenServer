// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SevenServer.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
CCmdDialog* ClientDlg::m_cmdDlg		= NULL;
CFileDlg*	ClientDlg::m_fileDlg	= NULL;
// ClientDlg 对话框


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
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
}


BEGIN_MESSAGE_MAP(ClientDlg, CDialogEx)
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &ClientDlg::OnTcnSelchangeTab1)

END_MESSAGE_MAP()


// ClientDlg 消息处理程序

BOOL ClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect tabRect;
	m_tabCtrl.InsertItem(0,_T("Command"));
	m_tabCtrl.InsertItem(1,_T("File"));
	m_tabCtrl.InsertItem(2,_T("Process"));
	m_tabCtrl.InsertItem(3,_T("Service"));
	m_cmdDlg = new CCmdDialog(m_piocpServer);
	m_fileDlg = new CFileDlg(m_piocpServer);
	m_cmdDlg->Create(IDD_CMD,&m_tabCtrl);
	m_fileDlg->Create(IDD_FLIE,&m_tabCtrl);

	m_tabCtrl.GetClientRect(&tabRect);
	tabRect.left += 2;                  
	tabRect.right -= 2;   
	tabRect.top += 22;   
	tabRect.bottom -= 2; 
	m_cmdDlg->SetWindowPos(NULL,tabRect.left, tabRect.top,
		tabRect.Width(), tabRect.Height(),SWP_SHOWWINDOW);
	m_fileDlg->SetWindowPos(NULL,tabRect.left, tabRect.top,
		tabRect.Width(), tabRect.Height(),SWP_HIDEWINDOW);

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ClientDlg::SetIOCPServerAndContext(CIOCPServer* dwServer,DWORD dwMainClientContxt)
{
	m_piocpServer = dwServer;
	m_mainClientContext = (ClientContext*) dwMainClientContxt;
}
void ClientDlg::OnReceiveComplete(ClientContext* pContext)
{
	switch (pContext->m_DeCompressionBuffer.GetBuffer(0)[0])
	{
		case SHELL_TOKEN_START:
			m_cmdDlg->Start(m_piocpServer,pContext);
			pContext->m_Dialog[0] = SHELL_DLG;
			pContext->m_Dialog[1] = (int)m_cmdDlg;
			
			break;
		case FILE_TOKEN_START:
			m_fileDlg->Start(m_piocpServer,pContext);
			pContext->m_Dialog[0] = FILE_DLG;
			pContext->m_Dialog[1] = (int)m_fileDlg;
			break;
		default:
			break;

	}

	return;
}

void ClientDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	if(m_tabCtrl.m_hWnd == NULL)
		return;      // Return if window is not created yet.
	CRect mainDlgRect;
	GetClientRect(&mainDlgRect);
	m_tabCtrl.MoveWindow(&mainDlgRect);   
	CRect tabRect;
	m_tabCtrl.GetClientRect(&tabRect);
	tabRect.left += 2;                  
	tabRect.right -= 2;   
	tabRect.top += 22;   
	tabRect.bottom -= 2; 
	
	m_cmdDlg->MoveWindow(tabRect);
	m_fileDlg->MoveWindow(tabRect);
}



void ClientDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	switch(m_tabCtrl.GetCurSel())
	{
	case 0:
		m_cmdDlg->ShowWindow(TRUE);
		m_fileDlg->ShowWindow(FALSE);
		break;
	case 1:
		m_cmdDlg->ShowWindow(FALSE);
		m_fileDlg->ShowWindow(TRUE);
		break;
	default:
		break;
	}
	*pResult = 0;
}

void ClientDlg::SendCmdCommand(int pClientdlg)
{
	Cmd *cmd = new Cmd;
	cmd->command = COMMAND_SHELLMANAGER;
	cmd->DialogPointer = pClientdlg;
	m_piocpServer->Send(m_mainClientContext, (PBYTE)cmd, sizeof(Cmd));
}

void ClientDlg::SendFileCommand(int pClientdlg)
{
	Cmd *cmd = new Cmd;
	cmd->command = COMMAND_FILEMANAGER;
	cmd->DialogPointer = pClientdlg;
	m_piocpServer->Send(m_mainClientContext, (PBYTE)cmd, sizeof(Cmd));
}