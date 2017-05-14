
// producer- consumerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include<list>
using namespace std;


// CproducerconsumerDlg 对话框
class CproducerconsumerDlg : public CDialogEx
{
// 构造
public:
	CproducerconsumerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PRODUCERCONSUMER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
