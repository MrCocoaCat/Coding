
// producer- consumerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "producer- consumer.h"
#include "producer- consumerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CproducerconsumerDlg 对话框



CproducerconsumerDlg::CproducerconsumerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CproducerconsumerDlg::IDD, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	count=1;
	Flag=false;
	
}

void CproducerconsumerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, m_lstBox);
	DDX_Control(pDX, IDC_LIST3, m_user);
}

BEGIN_MESSAGE_MAP(CproducerconsumerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CproducerconsumerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CproducerconsumerDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CproducerconsumerDlg 消息处理程序

BOOL CproducerconsumerDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CproducerconsumerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CproducerconsumerDlg::OnPaint()
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
HCURSOR CproducerconsumerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



DWORD WINAPI CproducerconsumerDlg::ThreadProc(  LPVOID lpThreadParameter)
{
	int * p=(int *)lpThreadParameter;
	CproducerconsumerDlg *pthis=(CproducerconsumerDlg*)theApp.m_pMainWnd;
	CString str;
	WaitForSingleObject(pthis->m_semp,INFINITE); 
	while(pthis->count<=100)
	{
		Sleep(200);
		WaitForSingleObject(pthis->m_metx,INFINITE); 
		
		if(pthis->count>100)
		{
			break;
			ReleaseMutex(pthis->m_metx);
		
		}
		str.Format(_T("第%d个生产者正在生产第%d个产品"),p,pthis->count);
		pthis->m_lstBox.AddString(str);


		pthis->m_lst.push_back(pthis->count);
		pthis->count++;
		
		ReleaseMutex(pthis->m_metx);
		
		ReleaseSemaphore(pthis->m_semp2,10,NULL);
	}

	return 0;
}
DWORD WINAPI CproducerconsumerDlg::ThreadProcUser(  LPVOID lpThreadParameter)
{
	int * p=(int *)lpThreadParameter;
	CproducerconsumerDlg *pthis=(CproducerconsumerDlg*)theApp.m_pMainWnd;
	CString str;
	
	while(1)
	{
		
		WaitForSingleObject(pthis->m_semp2,INFINITE); 
		WaitForSingleObject(pthis->m_metx2,INFINITE); 
		if(pthis->m_lst.empty()==false)
		{
			str.Format(_T("第%d个消费者正在消费第%d个产品"),p,pthis->m_lst.front());
			pthis->m_user.AddString(str);
			pthis->m_lst.pop_front();

		ReleaseMutex(pthis->m_metx2);
		}
		
	}
  
  
  return 0;

}

void CproducerconsumerDlg::OnBnClickedButton1()
{
	m_semp=CreateSemaphore(NULL,0,10,NULL);
	m_semp2=CreateSemaphore(NULL,0,10,NULL);

	for(int i=0;i<10;i++)
	{
		HANDLE m_handle=CreateThread(NULL,0,&CproducerconsumerDlg::ThreadProc,(void *)i,0,0);
		if(m_handle)
		{
			CloseHandle(m_handle);
			m_handle=NULL;
		}

	}
	//创建10个消费者线程
	for(int i=0;i<10;i++)
	{
		HANDLE m_user=CreateThread(NULL,0,&CproducerconsumerDlg::ThreadProcUser,(void *)i,0,0);


	}
}


void CproducerconsumerDlg::OnBnClickedButton2()
{
	m_metx=CreateMutex(NULL,FALSE,NULL);
	m_metx2=CreateMutex(NULL,FALSE,NULL);
	ReleaseSemaphore(m_semp,10,NULL);
	
}
