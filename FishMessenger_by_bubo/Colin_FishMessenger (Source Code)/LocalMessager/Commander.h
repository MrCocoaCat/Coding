//--------------------------------------------------------------
//	Commander.h.
//	6/8/2013.		by bubo.
//	Modified		6/16/2013.
//--------------------------------------------------------------
#pragma once

#ifndef _COMMANDER_H
#define _COMMANDER_H 

//--------------------------------------------------------------
//	Headers.
//--------------------------------------------------------------
#include "UIManager.h"
#include "ProgressDialog.h"
#include "UserDialog.h"
#include "TransferIndicator.h"
#include "SettingsDialog.h"

//--------------------------------------------------------------
namespace cinderella
{
	class Communicator;
	//--------------------------------------------------------------
	class Commander
	{
	public:
		static Commander* GetSingleton ();
		static void  DestroySingleton ();
		bool Initialize (HINSTANCE, HWND, int);

		void RefreshData ();
		void SetCommunicator (Communicator*);
		void SetUIManager (UIManager*);
		Communicator* GetCommunicator () const;
		UIManager* GetUIManager () const;
		bool GetSavePath (wchar_t*);
		void BroadcastInfo (bool bRegister = true);
		void BroadcastQueryInfo ();
		void SetLocalNameW (wchar_t*);
		void SetIPMask(wchar_t* szIPMask);
		void SendFile(wstring&, wchar_t*, bool);
		void SendDir(wstring&, wchar_t*);
		void Shutdown();

	private:
		Commander ();
		Commander (Commander&){}
		~Commander (){}

	private:
		static Commander* ms_pCommander;
		Communicator* m_pCommunicator;
		UIManager* m_pUIManager;
	};

	//--------------------------------------------------------------
	//	Global testing event.
	//--------------------------------------------------------------
	extern HANDLE g_hNamedMutex;
	bool TestSingleton();

	//--------------------------------------------------------------
}

//--------------------------------------------------------------
#endif //!_COMMANDER_H

