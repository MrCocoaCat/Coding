
// producer- consumer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CproducerconsumerApp:
// �йش����ʵ�֣������ producer- consumer.cpp
//

class CproducerconsumerApp : public CWinApp
{
public:
	CproducerconsumerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CproducerconsumerApp theApp;