
// producer- consumerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include<list>
using namespace std;


// CproducerconsumerDlg �Ի���
class CproducerconsumerDlg : public CDialogEx
{
// ����
public:
	CproducerconsumerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PRODUCERCONSUMER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
public:
	
	static DWORD WINAPI ThreadProc(  LPVOID lpThreadParameter);
	static DWORD WINAPI ThreadProcUser(  LPVOID lpThreadParameter);
	list<int> m_lst;		
	HANDLE m_metx;
	HANDLE m_semp;
	int count;
	BOOL Flag;
	HANDLE m_metx2;
	HANDLE m_semp2 ;
	CListBox m_user;
	CListBox m_lstBox;
};
