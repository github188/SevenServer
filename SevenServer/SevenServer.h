
// SevenServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSevenServerApp:
// �йش����ʵ�֣������ SevenServer.cpp
//

class CSevenServerApp : public CWinApp
{
public:
	CSevenServerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSevenServerApp theApp;