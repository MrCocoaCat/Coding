
// producer- consumerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "producer- consumer.h"
#include "producer- consumerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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


// CproducerconsumerDlg �Ի���



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


// CproducerconsumerDlg ��Ϣ�������

BOOL CproducerconsumerDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CproducerconsumerDlg::OnPaint()
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
		str.Format(_T("��%d������������������%d����Ʒ"),p,pthis->count);
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
			str.Format(_T("��%d���������������ѵ�%d����Ʒ"),p,pthis->m_lst.front());
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
	//����10���������߳�
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
