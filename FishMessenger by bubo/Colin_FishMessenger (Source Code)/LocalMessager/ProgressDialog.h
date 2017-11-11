//--------------------------------------------------------------
//	ProgressDialog.h.
//	6/21/2013.		by bubo.
//	Modified		6/21/2013.
//--------------------------------------------------------------
#pragma once

#ifndef _PROGRESSDIALOG_H
#define _PROGRESSDIALOG_H

//--------------------------------------------------------------
//	Headers.
//--------------------------------------------------------------
#include <windows.h>
#include <map>

using namespace std;

//--------------------------------------------------------------
namespace cinderella
{	
	//--------------------------------------------------------------
	class ProgressDialog
	{
	public:
		ProgressDialog();
		~ProgressDialog();

		static bool IsDialogMsg(LPMSG pMsg);
		static void Initialize(HWND hWndParent, HINSTANCE);
		static void Shutdown();
		static void ShowAllProgresses();
		static void HideAllProgresses();

		void SetText(wchar_t*);
		void SetRange(long long llStart, long long llEnd);
		void SetCurrentValue(long long llValue);
		void Update();
		void SetFinish(bool bFinish = true);
		bool IsCanceled() const;
		void Exit();
		HWND GetHWND();

	private:
		static void OnInitDialog (HWND hDlg);
		static INT_PTR CALLBACK fnProgressDialog(HWND hDlg, UINT message, 
			WPARAM wParam, 
			LPARAM lParam);

	private:
		wchar_t m_szText[MAX_PATH];
		long long m_llStart, m_llEnd, m_llCurrentValue;
		static HWND ms_hWndParent;
		HWND m_hDlg;
		static HINSTANCE ms_hInstance;		
		static ULONG_PTR ms_gdiplusToken;
		bool m_bFinish;
		bool m_bCanceled;
		bool m_bFirst;

	private:
		static map<HWND, ProgressDialog*> ms_pkDialogContainer;

	};

	//--------------------------------------------------------------
}

//--------------------------------------------------------------
#endif // !_PROGRESSDIALOG_H


