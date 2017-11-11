//--------------------------------------------------------------
//	UserDialog.h.
//	6/9/2013.		by bubo.
//	Modified		6/16/2013.
//--------------------------------------------------------------
#pragma once

#ifndef _USERDIALOG_H
#define _USERDIALOG_H

//--------------------------------------------------------------
//	Headers.
//--------------------------------------------------------------
#include "Communicator.h"
#include <windows.h>
#include <map>

using namespace std;

//--------------------------------------------------------------
namespace cinderella
{
	class UIManager;

	//--------------------------------------------------------------
	//	The static class UserDialog for processing Dialog loop...
	//--------------------------------------------------------------
	class UserDialog
	{
	public:
		UserDialog (HINSTANCE, HWND, Communicator::UserData* = nullptr, bool bGboal = false);
		~UserDialog ();
		static void Initialize (HWND);
		static INT_PTR CALLBACK fnUserDialog (HWND, UINT, WPARAM, LPARAM);
		static bool IsDialogMsg (LPMSG);
		static void Shutdown();
		
		static LRESULT CALLBACK fnGetMsgProc(int iCode, WPARAM wParam, LPARAM lParam);
		HWND GetWindow () const;
		static UserDialog* GetDlgPtrFromWindow (HWND);
		static in6_addr UserDialog::GetInfo(wchar_t*);
		static in6_addr UserDialog::GetInfo(wchar_t*,
			Communicator::UserData*);
		static void SetUIManager (UIManager*);
		static UIManager* GetUIManager ();
		void AddString (const wchar_t* );
		void AddStringMyself(const wchar_t* );
		Communicator::UserData* GetCurrentUserData ();
		void SetCurrentUserData (Communicator::UserData*);
		wstring GetIPString ();
		void SetIPString(wstring&);

	private:
		static void OnInitDialog (HWND);
		inline void OnTransmit ();
		void OnExit ();
		void OnSendFile(TCHAR* pFileName = nullptr);
		void OnSendDir(TCHAR* pDirName = nullptr);

	private:
		static map<HWND, cinderella::UserDialog*> ms_pUserDialogContainer;
		//static UserDialog* ms_pUserDialog;
		static HWND ms_hViewList;
		HWND m_hDlg;
		static Communicator::UserData* ms_pUserData;
		static UIManager* ms_pUiManager;
		wstring m_szIP;
		bool m_bGlobal;
		static int ms_iDlgPosX, ms_iDlgPosY;
		static bool ms_bDlgPos;
		static bool ms_bLButtonDown;
		static HHOOK ms_hHook;

	};

	//--------------------------------------------------------------

}

//---------------------------------------------------------------------
//		including inline files...
//---------------------------------------------------------------------
#include "UserDialog.inl"

//--------------------------------------------------------------
#endif // !_USERDIALOG_H


