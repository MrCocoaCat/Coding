//--------------------------------------------------------------
//	TransferIndicator.h.
//	05/28/2014.		by bubo.
//	Modified		05/28/2014.
//--------------------------------------------------------------
#pragma once

#ifndef _TRANSFERINDICATOR_H
#define _TRANSFERINDICATOR_H

//--------------------------------------------------------------
//	Headers.
//--------------------------------------------------------------
#include <windows.h>
#include <map>
#include <set>
#include <list>
#include <mutex>

using namespace std;

//--------------------------------------------------------------
namespace cinderella
{
	//--------------------------------------------------------------
	class TransferIndicator
	{
	public:
		//--------------------------------------------------------------
		friend class MultiFileCoordinator;

		//--------------------------------------------------------------
		//	Inner class: ItemInfo.
		//--------------------------------------------------------------
		class ItemInfo
		{
		public:
			enum TransferType
			{
				TT_PENDING = 0,
				TT_TRANSFERING,
				TT_FINISH,
				TT_FAILED
			};

			enum ItemFileType
			{
				IFT_REGULARFILE = 0,
				IFT_DIRECTORY
			};

		public:
			ItemInfo();

			wstring GetFileName();
			void SetFileName(wstring&);

			wstring GetUserName();
			void SetUserName(wstring&);

			wstring GetUserIP();
			void SetUserIP(wstring&);

			void SetUserEvent();
			void ResetUserEvent();

			HANDLE GetUserEvent();
			void SetupUserEvent(HANDLE);

			void SetTransferType(TransferType);
			TransferType GetTransferType();

			void SetItemFileType(ItemFileType);
			ItemFileType GetItemFileType();

		private:
			wstring m_szFileName;
			wstring m_szUserName;
			wstring m_szUserIP;
			HANDLE m_hUserEvent;
			TransferType m_eTransferType;
			ItemFileType m_eItemFileType;
		};

		//--------------------------------------------------------------
		//	End of inner Class: ItemInfo.
		//--------------------------------------------------------------
		//	Inner class: MultiFileCoordinator.
		//--------------------------------------------------------------
		class MultiFileCoordinator
		{
		public:
			MultiFileCoordinator();
			void AddSingleFile(HANDLE hEvent);
			void BeginToProcess();
			void StopAndClearPipeline();
			bool HasFile(HANDLE hEvent);
			void RemoveFile(HANDLE hEvent);
			bool HasNext();
			void* GetProgressDlgPtr();
			void SetProgressDlgPtr(void* pProgressPtr);
			void WaitForEvent();
			void SetWaitEvent();
			bool TestCurWorkingEvent(HANDLE);

		private:
			list<HANDLE> m_kEventQueue;
			bool m_bWorking;
			mutex m_mutex;
			void* m_pProgressPtr;
			HANDLE m_hWaitEvent;
			// Used to indicate which is the current file task. 
			HANDLE m_hCurrentWorkingEvent;
			mutex m_CurrentWorkingMutex;
		};

		//--------------------------------------------------------------
		//	End of inner Class: MultiFileCoordinator.
		//--------------------------------------------------------------
	private:
		TransferIndicator();
		~TransferIndicator();

	public:
		static TransferIndicator* GetSingleton();
		static void DestroySingleton();
		static bool IsDialogMsg(LPMSG pMsg);
		static void Initialize(HWND hWndParent, HINSTANCE);

		HANDLE AddTask(ItemInfo* pItemInfo);

		bool CreateUI();
		void Shutdown();
		void ShowTransferIndicator();
		void HideTransferIndicator();
		HWND GetHWND();

		void Update();
		wstring GetFileName(HANDLE);

		// bNormal: true -> finished. false -> cancled.
		void SetFinish(HANDLE, bool bNormal = true);
		void SetFailed(HANDLE);

		MultiFileCoordinator* GetMultiFileCoordinator();

	private:
		void OnInitDialog(HWND hDlg);
		bool OnTransferALL();
		bool OnTransferSelected();
		bool OnCancelSelected();
		bool OnCancelALL();
		static INT_PTR CALLBACK fnTransferIndicator(HWND hDlg, UINT message,
			WPARAM wParam,
			LPARAM lParam);
		void CreateListView();
		void CreateControlButton();
		bool InitlistViewColumns();
		bool AddListViewItems(ItemInfo* pItemInfo);

		void SetFileName(HANDLE hEvent, wstring& szFileName);
		void DrawCircleNumber();


	private:
		static HWND ms_hWndParent;
		static HWND ms_hDlg;
		static HINSTANCE ms_hInstance;
		HWND m_hWndListView;
		/*static ULONG_PTR ms_gdiplusToken;*/

	private:
		map<HANDLE, ItemInfo*> ms_kItemContainer;
		map<HANDLE, wstring> ms_kFileNameContainer;
		static TransferIndicator* ms_pTransferIndicator;
		set<HANDLE> m_ulIPContainer;
		int m_iCurrentValidIntex;
		HANDLE m_hMutex;
		MultiFileCoordinator* m_pMultiFileCoordinator;

	};

	//--------------------------------------------------------------
}

//--------------------------------------------------------------
#endif // !_TRANSFERINDICATOR_H


