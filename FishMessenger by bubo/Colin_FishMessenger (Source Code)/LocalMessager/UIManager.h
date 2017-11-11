//--------------------------------------------------------------
//	UIManager.h.
//	6/9/2013.		by bubo.
//--------------------------------------------------------------
#pragma once

#ifndef _UIMANAGER_H
#define _UIMANAGER_H

//--------------------------------------------------------------
//	Headers.
//--------------------------------------------------------------
#include "Communicator.h"
#include <windows.h>
#include <set>
#include "Messages.h"


//--------------------------------------------------------------
namespace cinderella
{
	//--------------------------------------------------------------
	class Commander;

	//--------------------------------------------------------------
	class UIManager
	{
	public:
		UIManager ();
		void SetMainWindow (HINSTANCE, HWND);
		HWND GetMainWindow ();
		void Initialize ();
		INT_PTR ProcessEvent (int iEvent, LONG_PTR ulParameter);
		void SetCommander (Commander*);
		void UpdateContent ();
		void ShowUserDialog (Communicator::UserDataText*);
		void SendMessage(wstring&, wchar_t*);
		bool OnFileArrived(wchar_t*, wstring& szIP, HANDLE* hEvent = nullptr);
		bool OnDirArrived (wchar_t*, wstring& szIP, HANDLE* hEvent = nullptr);

	private:
		void CreateListView ();
		bool InitListViewImageLists ();
		bool InitlistViewColumns ();
		bool AddListViewItems (const wchar_t* tempChar[2]);
		void CreateMainButton();
		void OnSelectAll ();
		void CreateInputDialog(wstring&, Communicator::UserData*
			pUserData = nullptr);

		friend class UserDialog;

	private:
		HWND m_hMainWindow;
		Commander* m_pCommander;
		HWND m_hWndListView;
		HINSTANCE m_hInstance;
		int m_iCurrentValidIntex;

		//--------------------------------------------------------------
		//Holding User's IP and corresponding Window's handle.
		//--------------------------------------------------------------
		map<wstring, HWND> m_DialogsContainer;

		//--------------------------------------------------------------
		//	Used for Multi-User Dialog box, holding the every unique IP.
		//--------------------------------------------------------------
		std::set<wstring> m_ulIPContainer;

		//--------------------------------------------------------------
		bool m_bAcceptFile;
		UserDialog* m_pGolbalUserDlg;

		//--------------------------------------------------------------
		//	Determine whether this is a Multi-User dialog.
		//--------------------------------------------------------------
		bool m_bGlobalDlg;

		//--------------------------------------------------------------

	};

	//--------------------------------------------------------------
}

//--------------------------------------------------------------
#endif //!_UIMANAGER_H


